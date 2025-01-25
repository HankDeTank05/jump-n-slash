# language imports
import json
import os.path
import tkinter as tk
from tkinter import messagebox
from tkinter import filedialog
import tkinter.ttk as ttk
from functools import partial

# module imports
from PIL import Image, ImageTk

# game imports
import jnscommon as jns

"""
NOTE: IF RUNNING FROM VSCODE, "cd" TO THE FOLDER CONTAINING THIS FILE BEFORE RUNNING TO AVOID PATHING ISSUES

- any class that is a GUI element, prepend "Gui" to the name of the class
	- any class that is a GUI element(s) should take a parent widget in their constructor
	- any class that is a GUI element(s) should take a column, row, columnspan, and rowspan as four ints in their constructor
	- member variables of a class that are a widget should follow this convention: "self.w_<variableName>"
	- member variables of a class that are a collection of widgets should follow this convention "self.wc_<variableName>"
- variable names should always be in camelCase
- always do type hints when declaring variables
- use assert statements LIBERALLY
- use TODO (and regular) comments liberally
	- remember: use comments to describe the meaning of the code, not a restated version of the logic
"""

class Map:
	def __init__(self):
		self.tiles: dict[tuple[int, int], int] = {}  # Store tile data: dict[tuple(int, int), int]
		self.is_saved: bool = True  # Track if the map has been saved

		# Map dimensions
		self.x_min = 0
		self.x_max = 0
		self.y_min = 0
		self.y_max = 0
		self.rows = 1
		self.cols = 1

	def remember_position(self, position):
		x, y = position
		self.x_min = min(x, self.x_min)
		self.x_max = max(x, self.x_max)
		self.y_min = min(y, self.y_min)
		self.y_max = max(y, self.y_max)
		self.rows = self.y_max - self.y_min + 1
		self.cols = self.x_max - self.x_min + 1

	def add_tile(self, position, tile_index):
		self.remember_position(position)
		self.tiles[position] = tile_index
		self.is_saved = False

	def remove_tile(self, position):
		if position in self.tiles:
			self.tiles.pop(position)
			self.is_saved = False

	def save(self, filename):
		data = {
			"size": {
				"rows": self.rows,
				"cols": self.cols
			},
			"tiles": [
				{"position": position, "tile_index": tile_index}
				for position, tile_index in self.tiles.items()
			]
		}
		with open(filename, "w") as file:
			json.dump(data, file, indent=4)
		self.is_saved = True

	def load(self, filename):
		with open(filename, "r") as file:
			data = json.load(file)
		self.tiles = {}
		self.rows = data["size"]["rows"]
		self.cols = data["size"]["cols"]
		for tile in data["tiles"]:
			position = tuple(tile["position"])
			tile_index = tile["tile_index"]
			self.tiles[position] = tile_index
		self.is_saved = True

class Editor(tk.Tk):
	def __init__(self):
		super().__init__()
		self.title("2D Platformer Level Editor")
		self.geometry("1920x1080")

		self.map = Map()
		self.camera_pos = (0, 0)
		self.brush_index = 0
		filenames = jns.GetFilesWithConvention(jns.READ_LOCATION_TEXTURES_LEVELTILES,jns.CONVENTION_SPR_LEVELTILE)
		print (filenames)

		self.tile_images = [
			ImageTk.PhotoImage(Image.open(os.path.join(jns.READ_LOCATION_TEXTURES_LEVELTILES, "placeholder_solidBlock.png"))),
			ImageTk.PhotoImage(Image.open(os.path.join(jns.READ_LOCATION_TEXTURES_LEVELTILES, "placeholder_breakableBlock.png"))),
			ImageTk.PhotoImage(Image.open(os.path.join(jns.READ_LOCATION_TEXTURES_LEVELTILES, "placeholder_hazardBlock.png"))),
			ImageTk.PhotoImage(Image.open(os.path.join(jns.READ_LOCATION_TEXTURES_LEVELTILES, "placeholder_semisolidPlatform.png"))),
		]

		self.brush_labels = [
			"Solid Block",
			"Breakable Block",
			"Hazard Block",
			"Semisolid Platform",
		]

		self.protocol("WM_DELETE_WINDOW", self.on_exit)

		self.main_frame = ttk.Frame(self)
		self.main_frame.pack(fill=tk.BOTH, expand=True)

		self.canvas = tk.Canvas(self.main_frame, bg="white", width=1000, height=1000)
		self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

		self.side_frame = ttk.Frame(self.main_frame)
		self.side_frame.pack(side=tk.RIGHT, fill=tk.Y)

		self.save_button = ttk.Button(self.side_frame, text="Save", command=self.save_map)
		self.save_button.pack(pady=10)

		self.load_button = ttk.Button(self.side_frame, text="Load", command=self.load_map)
		self.load_button.pack(pady=10)

		self.new_button = ttk.Button(self.side_frame, text="New", command=self.new_map)
		self.new_button.pack(pady=10)

		self.left_brush_button = ttk.Button(self.side_frame, text="<", command=self.select_left_brush)
		self.left_brush_button.pack(pady=5)

		self.tile_label = tk.Label(self.side_frame)
		self.tile_label.pack(pady=5)

		self.tile_preview = tk.Label(self.side_frame)
		self.tile_preview.pack(pady=10)

		self.right_brush_button = ttk.Button(self.side_frame, text=">", command=self.select_right_brush)
		self.right_brush_button.pack(pady=5)

		self.clear_button = ttk.Button(self.side_frame, text="Clear", command=self.clear_map)
		self.clear_button.pack(pady=10)

		self.update_tile_image()
		self.canvas.bind("<Button-1>", self.on_canvas_click)
		self.draw_grid()

	def draw_grid(self):
		self.canvas.delete("grid_line")
		for x in range(0, 1000, 32):
			self.canvas.create_line(x, 0, x, 1000, fill="black", tags="grid_line")
		for y in range(0, 1000, 32):
			self.canvas.create_line(0, y, 1000, y, fill="black", tags="grid_line")

	def on_canvas_click(self, event):
		x = (event.x // 32)
		y = (event.y // 32)
		position = (self.camera_pos[0] + x, self.camera_pos[1] + y)
		self.map.add_tile(position, self.brush_index)
		self.draw_tiles()

	def draw_tiles(self):
		self.canvas.delete("tile")
		for (position, tile_index) in self.map.tiles.items():
			x, y = position
			x = (x - self.camera_pos[0]) * 32
			y = (y - self.camera_pos[1]) * 32
			self.canvas.create_image(x, y, anchor=tk.NW, image=self.tile_images[tile_index], tags="tile")

	def save_map(self):
		filename = filedialog.asksaveasfilename(defaultextension=".json", filetypes=[("JSON Files", "*.json")])
		if filename:
			self.map.save(filename)

	def load_map(self):
		filename = filedialog.askopenfilename(filetypes=[("JSON Files", "*.json")])
		if filename:
			self.map.load(filename)
			self.draw_tiles()

	def new_map(self):
		self.map = Map()
		self.draw_tiles()

	def clear_map(self):
		if messagebox.askyesno("Clear Map", "Are you sure you want to clear the map? This action cannot be undone."):
			self.map = Map()
			self.draw_tiles()

	def select_left_brush(self):
		self.brush_index = (self.brush_index - 1) % len(self.tile_images)
		self.update_tile_image()

	def select_right_brush(self):
		self.brush_index = (self.brush_index + 1) % len(self.tile_images)
		self.update_tile_image()

	def update_tile_image(self):
		self.tile_label.config(text=self.brush_labels[self.brush_index])
		self.tile_preview.config(image=self.tile_images[self.brush_index])

	def on_exit(self):
		if not self.map.is_saved:
			if messagebox.askyesno("Exit", "You have unsaved changes. Do you want to exit without saving?"):
				self.destroy()
		else:
			self.destroy()

# above are the original classes used in the MVP prototype. they may be used in the final editor, or they may be removed

# below are the classes that will be used for the editor

# TODO: unfinished todos in this class
class MapData:

	def __init__(self) -> None:
		self.width = 10
		self.height = 10
		self.grid: list[list[str | None]] = []

		for y in range(self.height):
			self.grid.append([])
			for x in range(self.width):
				self.grid[y].append(None)

	############
	# mutators #
	############

	def PopulateGridWithData(self, data: dict[str, list[tuple[int, int]]]) -> None:
		# keep track of grid positions that have been written to
		writtenPositions: list[tuple[int, int]] = []

		# write to the grid positions listed in the dict
		for key in data.keys():
			for pos in data[key]:
				xPos: int = pos[0]
				yPos: int = pos[1]
				self.grid[yPos][xPos] = key
				writtenPositions.append(pos)
		
		# clear any spaces which were not written to
		for y in range(len(self.grid)):
			for x in range(len(self.grid[y])):
				if (x, y) not in writtenPositions:
					self.grid[y][x] = None

	# TODO: unfinished todos in this function
	def Resize(self, newTileWidth: int, newTileHeight: int) -> None:
		assert newTileWidth > 0
		assert newTileHeight > 0

		# TODO: when the width gets larger...
		if newTileWidth > self.width:
			assert False

		# TODO: when the width gets smaller...
		elif newTileWidth < self.width:
			assert False

		# TODO: when the height gets larger...
		if newTileHeight > self.height:
			assert False

		# TODO: when the height gets smaller...
		elif newTileHeight < self.height:
			assert False

	#############
	# accessors #
	#############

	def GetLayoutAsDict(self) -> dict[str, list[tuple[int, int]]]:
		layout: dict[str, list[tuple[int, int]]] = {}
		for y in range(len(self.grid)):
			for x in range(len(self.grid[y])):
				# only write data if there is a tile at the current x/y pos
				if self.grid[y][x] is not None:
					tileFilename: str = self.grid[y][x]
					if tileFilename not in layout.keys():
						# if there is no key for this tile, create a list with one x/y tuple
						layout[tileFilename] = [(x, y)]
					else:
						# if the tile already exists as a key, add the x/y tuple to the list
						layout[tileFilename].append((x, y))
		return layout

	def GetPropertiesAsDict(self) -> dict:
		props: dict = {
			"Size": (self.width, self.height)
		}
		return props

	############
	# mutators #
	############

	def WriteTile(self, filename: str, gridX: int, gridY: int) -> None:
		assert 0 <= gridX
		assert gridX < len(self.grid[0])
		assert 0 <= gridY
		assert gridY < len(self.grid)

		self.grid[gridY][gridX] = filename

class GuiLayerSelector:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, padx: int, pady: int, sticky: str) -> None:
		############################
		# create the non-gui stuff #
		############################

		# code goes here

		########################
		# create the gui stuff #
		########################
		
		# create the parent frame
		self.w_parentFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Layer Selector")
		self.w_parentFrame.grid(column=column, row=row,
						  columnspan=columnspan, rowspan=rowspan,
						  padx=padx, pady=pady,
						  sticky=sticky)


		self.w_placeholderLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="coming soon")
		self.w_placeholderLabel.grid(column=0, row=0)

# TODO: unfinished TODOs in this class
class GuiGridView:

	BRUSH_MODE_NORMAL: str = "normal"
	BRUSH_MODE_LINE: str = "line"

	# TODO: unfinished TODOs in this function
	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, padx: int, pady: int, sticky: str, fGetBrushTileCallback: any, fGetTileByNameCallback: any) -> None:
		############################
		# create the non-gui stuff #
		############################
		
		# constants
		self.TILE_SIZE: int = 32
		self.EMPTY_TAG: str = "empty"

		# non-constants
		self.brushMode: str = GuiGridView.BRUSH_MODE_NORMAL
		self.mapData: MapData = MapData()
		self.fGetBrushTile = fGetBrushTileCallback
		self.fGetTileByName = fGetTileByNameCallback

		########################
		# create the gui stuff #
		########################
		
		# create the parent frame
		self.w_parentFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Grid View")
		self.w_parentFrame.grid(column=column, row=row,
						  columnspan=columnspan, rowspan=rowspan,
						  padx=padx, pady=pady,
						  sticky=sticky)

		# create the canvas
		self.w_canvas: tk.Canvas = tk.Canvas(self.w_parentFrame)
		self._ResizeCanvas(10, 10)
		self.w_canvas.grid(column=0, row=0, sticky="NSEW")
		self._InitCanvas()

		# call a function when the left mouse button is clicked on the canvas
		self.w_canvas.bind("<Button-1>", self._CanvasClicked)
		# TODO: bind the right-click mouse button to the erase function. right-clicking to erase will erase according to the current brush mode!

		# create the canvas scrollbars
		self.w_scrollH: ttk.Scrollbar = ttk.Scrollbar(self.w_parentFrame, orient=tk.HORIZONTAL)
		self.w_scrollV: ttk.Scrollbar = ttk.Scrollbar(self.w_parentFrame, orient=tk.VERTICAL)
		self.w_canvas.config(xscrollcommand=self.w_scrollH.set, yscrollcommand=self.w_scrollV.set)
		self.w_scrollH.config(command=self.w_canvas.xview)
		self.w_scrollV.config(command=self.w_canvas.yview)
		self.w_scrollH.grid(column=0, row=1, stick="EW")
		self.w_scrollV.grid(column=1, row=0, sticky="NS")

	####################
	# canvas functions #
	####################

	def _InitCanvas(self) -> None:
		for y in range(self.mapData.height):
			for x in range(self.mapData.width):
				x0: int = x * self.TILE_SIZE
				y0: int = y * self.TILE_SIZE
				x1: int = x0 + self.TILE_SIZE - 1
				y1: int = y0 + self.TILE_SIZE - 1
				self.w_canvas.create_rectangle(x0, y0, x1, y1, tags=(self.EMPTY_TAG))

	def _CanvasClicked(self, event) -> None:
		if self.brushMode == GuiGridView.BRUSH_MODE_NORMAL:
			self.WriteTile(event.x, event.y)
		elif self.brushMode == GuiGridView.BRUSH_MODE_LINE:
			assert False
		else:
			assert False

	'''
	write a single tile to the map data and draw it on the canvas
	'''
	def WriteTile(self, pixelX: int, pixelY: int) -> None:
		# get the grid coordinates
		tileX: int = pixelX // self.TILE_SIZE
		tileY: int = pixelY // self.TILE_SIZE

		# get the image to place on the grid
		currentImg: tk.PhotoImage = self.fGetBrushTile()

		# place the image in the map data
		self.mapData.WriteTile(currentImg.name, tileX, tileY)

		# draw the image on the grid
		self.w_canvas.create_image(tileX * self.TILE_SIZE, tileY * self.TILE_SIZE, image=currentImg, anchor='nw', tags=(currentImg.name))

	'''
	write a line of tiles to the map data, and draw it on the canvas
	'''
	def WriteTileLine(self, pixelX0: int, pixelY0: int, pixelX1: int, pixelY1: int) -> None:
		lineCoords: list[tuple[int, int]] = [] # a list of tuples (x,y) for each tile in the line to be drawn
		# TODO: line algo to determine x/y's goes here
		for pos in lineCoords:
			x: int = pos[0]
			y: int = pos[1]
			self.WriteTile(x, y)

	def _DrawCanvasFromLayoutData(self) -> None:
		grid: list[list[str | None]] = self.mapData.GetGrid()
		for y in range(len(grid)):
			for x in range(len(grid[y])):
				if grid[y][x] is not None:
					img: tk.PhotoImage = self.fGetTileByName(grid[y][x])
					self.w_canvas.create_image(x * self.TILE_SIZE, y * self.TILE_SIZE, image=img, anchor='nw')

	def _ResizeCanvas(self, newTileWidth: int, newTileHeight: int) -> None:
		self.mapData.Resize(newTileWidth, newTileHeight)
		canvasLeftX: int = 0
		canvasTopY: int = 0
		canvasRightX: int = self.mapData.width * self.TILE_SIZE
		canvasBottomY: int = self.mapData.height * self.TILE_SIZE
		canvasPixWidth: int = canvasRightX - canvasLeftX
		canvasPixHeight: int = canvasBottomY - canvasTopY
		self.w_canvas.config(scrollregion=(canvasLeftX, canvasTopY, canvasRightX, canvasBottomY),
					   width=min(canvasPixWidth, 1280), height=min(canvasPixHeight, 720))


	########################
	# whole-grid functions #
	########################
 
  # Type hints added. Kind of meh on it, but it's fine.
	def GetDataForSaving(self) -> dict[str,any]:
		data: dict = {
			"Version": 1,
			"Properties": self.mapData.GetPropertiesAsDict(),
			"Layout": self.mapData.GetLayoutAsDict()
		}
		return data

	# TODO: define this type hint more specifically
	def ReadLoadedData(self, data: dict) -> None:
		self.mapData = MapData(data)
		self._DrawCanvasFromLayoutData()


class GuiEditorOptions:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, padx: int, pady: int, sticky: str) -> None:
		############################
		# create the non-gui stuff #
		############################

		# code goes here

		########################
		# create the gui stuff #
		########################
		
		# create the parent frame
		self.w_parentFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Editor Options")
		self.w_parentFrame.grid(column=column, row=row,
						  columnspan=columnspan, rowspan=rowspan,
						  padx=padx, pady=pady,
						  sticky=sticky)


		self.w_placeholderLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="coming soon")
		self.w_placeholderLabel.grid(column=0, row=0)

class GuiTileDetailsPanel:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, padx: int, pady: int, sticky: str) -> None:
		############################
		# create the non-gui stuff #
		############################

		# hardcoded test. Do not touch.
		self.tile_data = {
            "name": "Breakable Block",
            "damage_to_player": 0,
            "damage_to_enemies": 0,
            "is_breakable": True,
            "is_solid": True
        }

		########################
		# create the gui stuff #
		########################
		
		# create the parent frame
		self.w_parentFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Tile Details Panel")
		self.w_parentFrame.grid(column=column, row=row,
						  columnspan=columnspan, rowspan=rowspan,
						  padx=padx, pady=pady,
						  sticky=sticky)

		#self.w_placeholderLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="coming soon")
		#self.w_placeholderLabel.grid(column=0, row=0)
  
		# Tile Name
		self.w_nameLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Name:")
		self.w_nameLabel.grid(column=0, row=0, sticky="W", padx=10, pady=5)
		self.w_nameValue: ttk.Label = ttk.Label(self.w_parentFrame, text=self.tile_data["name"])
		self.w_nameValue.grid(column=1, row=0, sticky="W", padx=10, pady=5)

        # Damage to Player
		self.w_damagePlayerLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Damage to Player:")
		self.w_damagePlayerLabel.grid(column=0, row=1, sticky="W", padx=10, pady=5)
		self.w_damagePlayerValue: ttk.Label = ttk.Label(self.w_parentFrame, text=self.tile_data["damage_to_player"])
		self.w_damagePlayerValue.grid(column=1, row=1, sticky="W", padx=10, pady=5)

        # Damage to Enemies
		self.w_damageEnemiesLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Damage to Enemies:")
		self.w_damageEnemiesLabel.grid(column=0, row=2, sticky="W", padx=10, pady=5)
		self.w_damageEnemiesValue: ttk.Label = ttk.Label(self.w_parentFrame, text=self.tile_data["damage_to_enemies"])
		self.w_damageEnemiesValue.grid(column=1, row=2, sticky="W", padx=10, pady=5)

        # Breakable Status
		self.w_breakableLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Breakable:")
		self.w_breakableLabel.grid(column=0, row=3, sticky="W", padx=10, pady=5)
		self.w_breakableValue: ttk.Label = ttk.Label(self.w_parentFrame, text="Yes" if self.tile_data["is_breakable"] else "No")
		self.w_breakableValue.grid(column=1, row=3, sticky="W", padx=10, pady=5)

        # Solid Status
		self.w_solidLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Solid:")
		self.w_solidLabel.grid(column=0, row=4, sticky="W", padx=10, pady=5)
		self.w_solidValue: ttk.Label = ttk.Label(self.w_parentFrame, text="Yes" if self.tile_data["is_solid"] else "No")
		self.w_solidValue.grid(column=1, row=4, sticky="W", padx=10, pady=5)

		# TODO: Hard-coded the tile info. Still need to integrate into GUITilePalette.

# TODO: there are unfinished todos in here
class GuiTilePalette:

	# TODO: there are unfinished todos in here
	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, padx: int, pady: int, sticky: str, imgs: dict[str, tk.PhotoImage], fSelectBrushTileCallback: any) -> None:
		############################
		# create the non-gui stuff #
		############################
		
		# constants
		self._NOTEBOOK_PAGE_FRAME_PADX: int = 10
		self._NOTEBOOK_PAGE_FRAME_PADY: int = 10
		
		self._TILE_PADX: int = 5
		self._TILE_PADY: int = 5

		# get a list of files that fit the naming convention
		fileList: list[str] = list(imgs.keys())
		self.tileImgs: dict[str, list[tk.PhotoImage]] = {}

		# get a list of unique palette names from the files
		paletteSet: set[str] = set([filename.split("_")[0] for filename in fileList])
		self.notebookPageNames: list[str] = list(paletteSet)
		self.notebookPageNames.sort()

		# determine the currently selected tile
		fSelectBrushTileCallback(fileList[0])

		########################
		# create the gui stuff #
		########################
		
		# create the parent frame
		self.w_parentFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Tile Palette")
		self.w_parentFrame.grid(column=column, row=row,
						  columnspan=columnspan, rowspan=rowspan,
						  padx=padx, pady=pady,
						  sticky=sticky)

		# create the notebook widget
		self.w_notebook: ttk.Notebook = ttk.Notebook(self.w_parentFrame)
		self.w_notebook.grid(column=0, row=0,
					   sticky="NSEW")

		# create one frame for each of the notebook page names
		self.wc_notebookPageFrames: list[ttk.Frame] = []
		for name in self.notebookPageNames:
			self._AddNotebookPage(name)

		# create the tile images inside of each notebook page
		self.wc_tileButtons: dict[str, list[ttk.Button]] = {}
		for i in range(len(fileList)):
			filename: str = fileList[i]
			pageName: str = filename.split("_")[0] # TODO: there has to be a better way to do this than just duplicating the split code from above
			self._AddTileToNotebookPage(pageName, filename, imgs[filename], i, fSelectBrushTileCallback=fSelectBrushTileCallback)

	def _AddNotebookPage(self, pageName: str) -> None:
		frame: ttk.Frame = ttk.Frame(self.w_notebook)
		frame.grid(column=0, row=0,
			 padx=self._NOTEBOOK_PAGE_FRAME_PADX, pady=self._NOTEBOOK_PAGE_FRAME_PADY)
		self.w_notebook.add(frame, text=pageName)
		self.wc_notebookPageFrames.append(frame)

	def _AddTileToNotebookPage(self, pageName: str, filename: str, img: tk.PhotoImage, columnNum: int, fSelectBrushTileCallback: any) -> None:
		assert pageName in self.notebookPageNames, f"Page name \"{pageName}\" not found!"
		pageIndex: int = self.notebookPageNames.index(pageName)
		parentFrame: ttk.Frame = self.wc_notebookPageFrames[pageIndex]
		
		# add the image to the dict
		if pageName not in self.tileImgs.keys():
			self.tileImgs[pageName] = []
		self.tileImgs[pageName].append(img)
		
		# create the button using the image that was just created
		button: ttk.Button = ttk.Button(parentFrame, image=img, command=partial(fSelectBrushTileCallback, filename)) 
		button.grid(column=columnNum, row=0,
			  padx=self._TILE_PADX, pady=self._TILE_PADY)

		# add the button to the dict
		if pageName not in self.wc_tileButtons.keys():
			self.wc_tileButtons[pageName] = []
		self.wc_tileButtons[pageName].append(button)

	def GetSelectedTile(self) -> str:
		return self.currTile

# TODO: unfinished todos in this class
class GuiLevelEditorApp:

	def __init__(self) -> None:
		self.root: tk.Tk = tk.Tk()
		self.root.title("Level Editor")
		# self.root.geometry("1920x1080") # TODO: come back to this later once the editor is mostly finished
		self.root.state("normal") # "normal" will be windowed, "zoomed" will be maximized

		############################
		# create the non-gui stuff #
		############################

		# constants
		self._PADX: int = 0
		self._PADY: int = 0

		# non-constants
		
		fileList: list[str] = jns.GetFilesWithConvention(jns.READ_LOCATION_TEXTURES_LEVELTILES, jns.CONVENTION_SPR_LEVELTILE)

		# a dict where the key is the filename, and the value is the corresponding tk.PhotoImage
		self.tileImgs: dict[str, tk.PhotoImage] = {}
		self._LoadAllImages(fileList)
		# jns.PrintDict(self.tileImgs)

		self.brushTile: str
		
		########################
		# create the gui stuff #
		########################

		# create the menu bar
		self.root.option_add("*tearOff", tk.FALSE)
		self.menuBar: tk.Menu = tk.Menu(self.root)
		self.root.config(menu=self.menuBar)

		# File menu
		self.fileMenu = tk.Menu(self.menuBar)
		self.fileMenu.add_command(label="New") # TODO: add a command to make this do something
		self.fileMenu.add_command(label="Save", command=self.Save)
		self.fileMenu.add_command(label="Load", command=self.Load)
		self.fileMenu.add_separator()
		self.fileMenu.add_command(label="Exit") # TODO: add a command to make this do something
		self.menuBar.add_cascade(label="File", menu=self.fileMenu)
	
        # Edit menu
		self.editMenu = tk.Menu(self.menuBar)
		self.editMenu.add_command(label="Undo") # TODO: add a command to make this do something
		self.editMenu.add_command(label="Redo") # TODO: add a command to make this do something
		self.editMenu.add_separator()
		self.editMenu.add_command(label="Clear") # TODO: add a command to make this do something
		self.menuBar.add_cascade(label="Edit", menu=self.editMenu)

 		# View menu
		self.viewMenu = tk.Menu(self.menuBar)
		self.viewMenu.add_command(label="Zoom In") # TODO: add a command to make this do something
		self.viewMenu.add_command(label="Zoom Out") # TODO: add a command to make this do something
		self.viewMenu.add_command(label="Reset Zoom") # TODO: add a command to make this do something
		self.menuBar.add_cascade(label="View", menu=self.viewMenu)
		
		# create the layer selector
		self.wc_layerSelector: GuiLayerSelector = GuiLayerSelector(parent=self.root, # the parent widget
															 column=0, row=0, # column/row position in the parent
															 columnspan=1, rowspan=2, # column/row span
															 padx=self._PADX, pady=self._PADY, # padding around the outside of this object's parent frame
															 sticky="NSEW") # which sides should this object's parent frame stick to
		
		# create the grid view
		self.wc_gridView: GuiGridView = GuiGridView(parent=self.root,
											  column=1, row=0,
											  columnspan=1, rowspan=1,
											  padx=self._PADX, pady=self._PADY,
											  sticky="NSEW",
											  fGetBrushTileCallback=self.GetBrushTileImg,
											  fGetTileByNameCallback=self.GetTileByName)

		# create the editor options
		self.wc_editorOptions: GuiEditorOptions = GuiEditorOptions(parent=self.root,
															 column=1, row=1,
															 columnspan=1, rowspan=1,
															 padx=self._PADX, pady=self._PADY,
															 sticky="NSEW")

		# create the tile details panel
		self.wc_tileDetails: GuiTileDetailsPanel = GuiTileDetailsPanel(parent=self.root,
																 column=2, row=0,
																 columnspan=1, rowspan=2,
																 padx=self._PADX, pady=self._PADY,
																 sticky="NSEW")
		
		# create the tile palette
		self.wc_tilePalette: GuiTilePalette = GuiTilePalette(parent=self.root,
													   column=0, row=2,
													   columnspan=3, rowspan=1,
													   padx=self._PADX, pady=self._PADY,
													   sticky="NSEW",
													   imgs=self.tileImgs,
													   fSelectBrushTileCallback=self.SelectBrushTile)
		
	###################
	# setup functions #
	###################

	def _LoadAllImages(self, fileList: list[str]) -> None:
		for filename in fileList:
			filePath: str = os.path.join(jns.READ_LOCATION_TEXTURES_LEVELTILES, filename)
			self.tileImgs[filename] = tk.PhotoImage(file=filePath, name=filename)
	
	#################################
	# gui interoperability funcions #
	#################################

	'''
	called by the tile palette in order to select the brush tile
	'''
	def SelectBrushTile(self, tileFilename: str) -> None:
		self.brushTile = tileFilename
		print(f"Selected brush tile : \"{self.brushTile}\"")

	'''
	called by the grid view in order to paint the canvas with the brush tile
	'''
	def GetBrushTileImg(self) -> tk.PhotoImage:
		return self.tileImgs[self.brushTile]

	'''
	called by various parts of the gui to retrieve an image by its filename
	'''
	def GetTileByName(self, filename: str) -> tk.PhotoImage:
		assert filename in self.tileImgs.keys()
		return self.tileImgs[filename]
	
	########################
	# filesystem functions #
	########################

	# TODO: unfinished TODOs in this function
	def Save(self) -> None:
		# NOTE: DO NOT MODIFY THE LOADED DATA IN ANY WAY, SAVE IT TO FILE AS IT WAS RECEIVED FROM GRIDVIEW
		data: dict = self.wc_gridView.GetDataForSaving()
		filename: str = "test.json" # TODO: allow the user to pick the file name
		filePath: str = os.path.join(jns.READ_LOCATION_LEVELDATA, filename)
		with open(file=filePath, mode='w') as jsonFile:
			json.dump(data, jsonFile, indent=4)
		print(f"Saved file: \"{os.path.join(jns.READ_LOCATION_LEVELDATA, filename)}\"")

	# TODO: unfinished TODOs in this function
	def Load(self) -> None:
		# NOTE: DO NOT MODIFY THE LOADED DATA IN ANY WAY, PASS IT ALONG TO GRIDVIEW AS-IS
		# load data from file
		data: dict
		filename: str = "test.json"
		filePath: str = os.path.join(jns.READ_LOCATION_LEVELDATA, filename)
		with open(file=filePath, mode='r') as jsonFile:
			data = json.load(jsonFile)
		# TODO: pass data along to the GuiGridView
		assert False

	##################
	# misc functions #
	##################

	def Run(self) -> None:
		self.root.mainloop()

if __name__ == "__main__":
	# app = Editor()
	# app.mainloop()
	app: GuiLevelEditorApp = GuiLevelEditorApp()
	app.Run()
