# language imports
import json
import os.path
import tkinter as tk
from tkinter import messagebox
from tkinter import filedialog
import tkinter.ttk as ttk
from functools import partial

# game imports
import jnscommon as jns

# module imports
try:
	from PIL import Image, ImageTk
except ModuleNotFoundError:
	jns.PipInstall("PIL")
	from PIL import Image, ImageTk

"""
NOTE: IF RUNNING FROM VSCODE, "cd" TO THE FOLDER CONTAINING THIS FILE BEFORE RUNNING TO AVOID PATHING ISSUES

- any class that is a GUI element, append the word "View" to the name of the class
	- any class that is a GUI element(s) should take a parent widget in their constructor
	- any class that is a GUI element(s) should take a column, row, columnspan, and rowspan as four ints in their constructor
	- member variables of a class that are a widget should follow this convention: "self.w_<variableName>"
	- member variables of a class that are a collection of widgets should follow this convention "self.wc_<variableName>"
- variable naming conventions
	- variable names should always be in camelCase
	- always do type hints when declaring variables
- ALL MEMBER VARIABLES ARE PRIVATE
	- private member variables should begin with a leading underscore, as is convention in Python (ex: self._privateMemberVar, self.publicMemberVar)
	- UNLESS you find yourself writing both an accessor fucntion and a mutator function that are simply assigning and returning
		- then AND ONLY THEN should a member variable be public
	- NOTE: if your accessors are more complicated than a single-line return, AND your mutators are more complicated than a single-line variable assignment...
		- KEEP THE MEMBER VARIABLE THAT IT'S AFFECTING PRIVATE. complicated accessors and mutators have a purpose because they simplify complex operations down to a single function call
- use assert statements LIBERALLY
- use TODO (and regular) comments liberally
	- remember: use comments to describe the meaning of the code, not a restated version of the logic
	- FOR TODO COMMENTS: after the "TODO:", put the person's name in parentheses if this todo is meant to be completed by someone specific. (ex: "TODO: (henry) add a command to this button")
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

class MapData:

	VERSION_KEY: str = "Version"
	PROPS_KEY: str = "Properties"
	PROPS_SIZE_KEY: str = "Size"
	LAYOUT_KEY: str = "Layout"

	def __init__(self, data: None | dict = None) -> None:
		# this 2d list contains the filename of the tile or "None" if there is no tile there
		# it should be indexed as self.grid[y][x]
		self.grid: list[list[str | None]] = []

		self.width: int = 0
		self.height: int = 0

		# if we're creating a blank map
		if data is None:
			print("Constructing blank MapData object")
			self.width = 40
			self.height = 20

			for y in range(self.height):
				self.grid.append([])
				for x in range(self.width):
					self.grid[y].append(None)

		# if we're creating a map from json data
		else:
			print("Constructing MapData object from data")
			fileFormatVer: int = dict[MapData.VERSION_KEY]

			properties: dict[str, any] = data[MapData.PROPS_KEY]
			incomingWidth: int = properties[MapData.PROPS_SIZE_KEY][0]
			incomingHeight: int = properties[MapData.PROPS_SIZE_KEY][1]
			self.Resize(incomingWidth, incomingHeight)

			layout: dict[str, list[tuple[int, int]]] = data[MapData.LAYOUT_KEY]
			self.PopulateGridWithData(layout)

	############
	# mutators #
	############

	def PopulateGridWithData(self, layoutData: dict[str, list[tuple[int, int]]]) -> None:
		# print("MapData.PopulateGridWithData()")

		# first, empty out the grid
		for y in range(len(self.grid)):
			for x in range(len(self.grid[y])):
				self.grid[y][x] = None

		# write to the grid positions listed in the dict
		for tileFilename in layoutData.keys():
			for pos in layoutData[tileFilename]:
				xPos: int = pos[0]
				yPos: int = pos[1]
				# print(f"\"{tileFilename}\" at ({xPos}, {yPos})")
				self.grid[yPos][xPos] = tileFilename

	def Resize(self, newTileWidth: int, newTileHeight: int) -> None:
		# print("MapData.Resize()")
		assert newTileWidth > 0
		assert newTileHeight > 0

		# when the width gets larger...
		if newTileWidth > self.width:
			print(f"map width will increase : {self.width} -> {newTileWidth}")
			# set self.width to the new width
			self.width = newTileWidth
			
			# add columns until the width of the grid is equal to self.width
			for y in range(len(self.grid)):
				while len(self.grid[y]) < self.width:
					self.grid[y].append(None)
				assert len(self.grid[y]) == self.width

		# TODO: when the width gets smaller...
		elif newTileWidth < self.width:
			print(f"map width will decrease : {self.width} -> {newTileWidth}")
			
			# check the columns between the old width and the new width for any tiles that might be deleted
			tilesWillDeleteOnResize: bool = False
			currentColumn: int = newTileWidth
			while currentColumn < self.width and tilesWillDeleteOnResize == False:
				# check each space in the current column for a tile
				for x in range(len(self.grid[currentColumn])):
					if self.grid[currentColumn][x] is not None:
						tilesWillDeleteOnResize = True

				# prepare to check next column
				currentColumn += 1 

			# if there are any tiles (not None) in any of those columns...
			if tilesWillDeleteOnResize == True:
				# warn the user that tiles in those columns will be deleted (with a popup window)
				allowResize: bool = messagebox.askyesno(title="Map Resize Warning",
						message="Some tiles will be deleted if you resize the map. Are you sure you want to resize the map?",
						icon="warning")
			# TODO: if they choose to continue with resizing...
			#			set self.width to the new width
			#			delete columns until the width of the grid is equal to self.width

		# when the height gets larger...
		if newTileHeight > self.height:
			print(f"map height will increase : {self.height} -> {newTileHeight}")
			# set self.height to the new height
			self.height = newTileHeight

			# add rows until the height of the grid is equal to self.height
			while len(self.grid) < self.height:
				self.grid.append([])
				for x in range(self.width):
					self.grid[-1].append(None)
				assert len(self.grid[-1]) == self.width
			assert len(self.grid) == self.height

		# TODO: when the height gets smaller...
		elif newTileHeight < self.height:
			print(f"map height will decrease : {self.height} -> {newTileHeight}")
			# TODO: check the rows between the old height and the new height
			# TODO: if there are any tiles (not None) in any of those rows...
			#			warn the user that tiles in those rows will be deleted (with a popup window)
			# TODO: if they choose to continue with resizing...
			#			set self.height to the new height
			#			delete rows until the height of the grid is equal to self.height

	#############
	# accessors #
	#############

	def GetGrid(self) -> list[list[str | None]]:
		return self.grid
	
	def GetWidth(self) -> int:
		return self.width
	
	def GetHeight(self) -> int:
		return self.height

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

	def GetPropertiesAsDict(self) -> dict[str, tuple[int, int]]:
		props: dict = {
			MapData.PROPS_SIZE_KEY: (self.width, self.height)
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

class GuiGridView:

	BRUSH_MODE_NORMAL: str = "normal"
	BRUSH_MODE_LINE: str = "line"

	EMPTY_TAG: str = "empty"
	GRIDLINE_TAG: str = "gridline"
	COORDS_TAG: str = "coords"

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, padx: int, pady: int, sticky: str,
			  fGetTileByNameCallback: any, viewOptShowGridlines: int, viewOptShowCoords: int) -> None:
		############################
		# create the non-gui stuff #
		############################
		
		# constants
		self.TILE_SIZE: int = 32

		# non-constants
		self.brushMode: str = GuiGridView.BRUSH_MODE_NORMAL
		self.mapData: MapData = MapData()
		self.brushTileImg: tk.PhotoImage # declare, don't define (will be defined externally)
		self.fGetTileByName = fGetTileByNameCallback

		self.lastClickedGridX: int = -1
		self.lastClickedGridY: int = -1
		self.lastHoveredGridX: int = -1
		self.lastHoveredGridY: int = -1

		self.mouseButtonReleased: bool = True
		self.cavnasWidth: int = 0
		self.canvasheight: int = 0

		# view options
		self.showGridlines: bool = viewOptShowGridlines
		self.showCoords: int = viewOptShowCoords

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
		self.w_canvas.grid(column=0, row=0, sticky="NSEW")
		self.InitCanvas()

		# call a function when the left mouse button is clicked-and-dragged
		self.w_canvas.bind("<B1-Motion>", self._CanvasClicked) # do stuff when click-and-dragging mouse1
		self.w_canvas.bind("<B3-Motion>", self._CanvasErase) # do stuff when click-and-dragging mouse2
		self.w_canvas.bind("<B1-ButtonRelease>", self._MouseButtonReleased) # do stuff when left mouse button is released
		self.w_canvas.bind("<B3-ButtonRelease>", self._MouseButtonReleased) # do stuff when right mouse button is released
		self.w_canvas.bind("<Motion>", self._MouseMoved) # do stuff when the mouse cursor moves

		# create the canvas scrollbars
		self.w_scrollH: ttk.Scrollbar = ttk.Scrollbar(self.w_parentFrame, orient=tk.HORIZONTAL)
		self.w_scrollV: ttk.Scrollbar = ttk.Scrollbar(self.w_parentFrame, orient=tk.VERTICAL)
		self.w_canvas.config(xscrollcommand=self.w_scrollH.set, yscrollcommand=self.w_scrollV.set)
		self.w_scrollH.config(command=self.w_canvas.xview)
		self.w_scrollV.config(command=self.w_canvas.yview)
		self.w_scrollH.grid(column=0, row=1, stick="EW")
		self.w_scrollV.grid(column=1, row=0, sticky="NS")

	###############################
	# canvas management functions #
	###############################

	def InitCanvas(self) -> None:
		# print("GuiGridView._InitCanvas()")
		self.mapData = MapData()
		grid: list[list[str | None]] = self.mapData.GetGrid()
		gridHeight: int = self.mapData.GetHeight()
		gridWidth: int = self.mapData.GetWidth()
		self._ResizeCanvas(gridWidth, gridHeight)
		for y in range(gridHeight):
			for x in range(gridWidth):
				assert grid[y][x] is None
				self._DrawSqaureAtGridPos(x, y)
		self._DrawViewOptions()

	def _CanvasClicked(self, event: tk.Event) -> None:
		# print("GuiGridView._CanvasClicked()")

		# only do stuff if the mouse button is released or the cursor is in a new grid square
		mouseGridPos: tuple[int, int] = self._ScreenPixelToGridPos(event.x, event.y)
		if self.mouseButtonReleased == True or mouseGridPos[0] != self.lastClickedGridX or mouseGridPos[1] != self.lastClickedGridY:
			self.mouseButtonReleased = False
			# print(event)
			if self.brushMode == GuiGridView.BRUSH_MODE_NORMAL:
				self._WriteTile(event.x, event.y)
			elif self.brushMode == GuiGridView.BRUSH_MODE_LINE:
				assert False
			else:
				assert False
			self._UpdateLastClickedGridPos(event.x, event.y)

	def _CanvasErase(self, event: tk.Event) -> None:
		# print("GuiGridView._CanvasErase")

		# only do stuff if the mouse button is released or the cursor is in a new grid square
		mouseGridPos: tuple[int, int] = self._ScreenPixelToGridPos(event.x, event.y)
		if self.mouseButtonReleased == True or mouseGridPos[0] != self.lastClickedGridX or mouseGridPos[1] != self.lastClickedGridY:
			self.mouseButtonReleased = False
			# print(event)
			# right-clicking to erase will erase according to the current brush mode!
			if self.brushMode == GuiGridView.BRUSH_MODE_NORMAL:
				self._EraseTile(event.x, event.y)
			elif self.brushMode == GuiGridView.BRUSH_MODE_LINE:
				assert False
			else:
				assert False
			self._UpdateLastClickedGridPos(event.x, event.y)

	'''
	write a single tile to the map data, and draw it on the canvas
	'''
	def _WriteTile(self, pixelX: int, pixelY: int) -> None:
		# get the grid coordinates
		gridPos: tuple[int, int] = self._ScreenPixelToGridPos(pixelX, pixelY)
		gridX: int = gridPos[0]
		gridY: int = gridPos[1]

		# place the image in the map data
		self.mapData.WriteTile(self.brushTileImg.name, gridX, gridY)

		# draw the image
		self._DrawImageAtGridPos(self.brushTileImg, gridX, gridY)

	'''
	erase a single tile from the map data, and erase it from the canvas as well
	'''
	def _EraseTile(self, pixelX: int, pixelY: int) -> None:
		# get the grid coordinates
		gridPos: tuple[int, int] = self._ScreenPixelToGridPos(pixelX, pixelY)
		gridX = gridPos[0]
		gridY = gridPos[1]

		# erase the image from map data
		self.mapData.WriteTile(None, gridX, gridY)

		# draw an empty square
		self._DrawSqaureAtGridPos(gridX, gridY)

		if self.showGridlines == True:
			# redraw the gridlines above and to the left
			self._DrawVerticalGridlineAtGridX(gridX)
			self._DrawHorizontalGridlineAtGridY(gridY)

	'''
	write a line of tiles to the map data, and draw it on the canvas
	'''
	def _WriteTileLine(self, pixelX0: int, pixelY0: int, pixelX1: int, pixelY1: int) -> None:
		lineCoords: list[tuple[int, int]] = [] # a list of tuples (x,y) for each tile in the line to be drawn
		# TODO: line algo to determine x/y's goes here
		for pos in lineCoords:
			x: int = pos[0]
			y: int = pos[1]
			self._WriteTile(x, y)

	def _DrawCanvasFromLayoutData(self) -> None:
		# print("GuiGridView._DrawCanvasFromLayoutData()")
		grid: list[list[str | None]] = self.mapData.GetGrid()
		width: int = self.mapData.GetWidth()
		height: int = self.mapData.GetHeight()
		self._ResizeCanvas(width, height)
		self.w_canvas.delete('all')
		for y in range(len(grid)):
			for x in range(len(grid[y])):
				if grid[y][x] is not None:
					# tileFilename: str = grid[y][x]
					# print(f"drawing \"{tileFilename}\" at grid pos ({x}, {y}) on the canvas")
					img: tk.PhotoImage = self.fGetTileByName(grid[y][x])
					self._DrawImageAtGridPos(img, x, y)
				else:
					self._DrawSqaureAtGridPos(x, y)
		self._DrawViewOptions()

	def _ResizeCanvas(self, newTileWidth: int, newTileHeight: int) -> None:
		# print("GuiGridView._ResizeCanvas()")
		self.mapData.Resize(newTileWidth, newTileHeight)
		canvasLeftX: int = 0
		canvasTopY: int = 0
		canvasRightX: int = self.mapData.GetWidth() * self.TILE_SIZE
		canvasBottomY: int = self.mapData.GetHeight() * self.TILE_SIZE
		self.canvasWidth = canvasRightX - canvasLeftX
		self.canvasHeight = canvasBottomY - canvasTopY
		self.w_canvas.config(scrollregion=(canvasLeftX, canvasTopY, canvasRightX, canvasBottomY),
					   width=min(self.canvasWidth, 1280), height=min(self.canvasHeight, 720)) # TODO: replace the 1280 and 720 with numbers calculated based on the user's screen size

	############################
	# canvas drawing functions #
	############################

	def _DrawViewOptions(self) -> None:
		if self.showGridlines == True:
			self._DrawGridlines()
		if self.showCoords == 2:
			self._DrawAllCoords()

	def _DrawImageAtGridPos(self, image: tk.PhotoImage, gridX: int, gridY: int) -> None:
		# delete what was there before
		objectTag: str = self._GetPositionTag(gridX, gridY)
		itemsWithTag: list = self.w_canvas.find_withtag(objectTag)
		# print(itemsWithTag)
		assert len(itemsWithTag) == 0 or len(itemsWithTag) == 1
		self.w_canvas.delete(objectTag)
		# print(f"deleted {len(itemsWithTag)} items with tag \"{objectTag}\"")

		# draw the image on the grid and set its input bindings
		canvasObject = self.w_canvas.create_image(gridX * self.TILE_SIZE, gridY * self.TILE_SIZE,
											image=image,
											anchor='nw',
											tags=(image.name, objectTag))
		self._SetCanvasObjectBindings(canvasObject)

	def _DrawSqaureAtGridPos(self, gridX, gridY) -> None:
		# delete what was there before
		objectTag: str = self._GetPositionTag(gridX, gridY)
		itemsWithTag: list = self.w_canvas.find_withtag(objectTag)
		# print(itemsWithTag)
		assert len(itemsWithTag) == 0 or len(itemsWithTag) == 1
		self.w_canvas.delete(objectTag)
		# print(f"deleted {len(itemsWithTag)} items with tag \"{objectTag}\"")

		# replace the erased item with an empty square and set its input bindings
		x0: int = gridX * self.TILE_SIZE
		y0: int = gridY * self.TILE_SIZE
		x1: int = x0 + self.TILE_SIZE - 1
		y1: int = y0 + self.TILE_SIZE - 1
		canvasObject = self.w_canvas.create_rectangle(x0, y0, x1, y1,
												fill="white", # fill the squares with white
												width=0, # squares should have no outline
												tags=(GuiGridView.EMPTY_TAG, objectTag))
		self._SetCanvasObjectBindings(canvasObject)
		
	def _DrawGridlines(self) -> None:
		self.w_canvas.delete(GuiGridView.GRIDLINE_TAG) # erase all gridlines before re/drawing them
		for x in range(0, self.canvasWidth + 1, self.TILE_SIZE):
			self._DrawVerticalGridlineAtPixelX(x)
		for y in range(0, self.canvasHeight + 1, self.TILE_SIZE):
			self._DrawHorizontalGridlineAtPixelY(y)

	'''
	draws a vertical gridline given a canvasPixelX (a pixel column number)
	NOTE: canvasPixelX must be evenly divisible by self.TILE_SIZE!
	'''
	def _DrawVerticalGridlineAtPixelX(self, canvasPixelX: int) -> None:
		assert canvasPixelX % self.TILE_SIZE == 0, f"Cannot draw vertical gridline at x={canvasPixelX}"
		gridX: int = canvasPixelX // self.TILE_SIZE
		self._CreateVerticalGridlineWithTags(canvasPixelX, gridX)

	'''
	draws a horizontal gridline given a canvasPixelY (a pixel row number)
	NOTE: canvasPixelY must be evenly divisible by self.TILE_SIZE!
	'''
	def _DrawHorizontalGridlineAtPixelY(self, canvasPixelY: int) -> None:
		assert canvasPixelY % self.TILE_SIZE == 0, f"Cannot draw horizontal gridline at y={canvasPixelY}"
		gridY: int = canvasPixelY // self.TILE_SIZE
		self._CreateHorizontalGridlineWithTags(canvasPixelY, gridY)
		
	'''
	draws a vertical gridline given a gridX (a tile column number)
	'''
	def _DrawVerticalGridlineAtGridX(self, gridX: int) -> None:
		assert 0 <= gridX
		assert gridX < self.mapData.GetWidth()
		canvasPixelX: int = gridX * self.TILE_SIZE
		self._CreateVerticalGridlineWithTags(canvasPixelX, gridX)

	'''
	draws a horizontal gridline given a gridY (a tile row number)
	'''
	def _DrawHorizontalGridlineAtGridY(self, gridY: int) -> None:
		assert 0 <= gridY
		assert gridY < self.mapData.GetHeight()
		canvasPixelY: int = gridY * self.TILE_SIZE
		self._CreateHorizontalGridlineWithTags(canvasPixelY, gridY)

	'''
	DO NOT CALL DIRECTLY - THIS IS A HELPER FUNCTION
	creates a vertical gridline with the proper tags
	'''
	def _CreateVerticalGridlineWithTags(self, canvasPixelX: int, gridX: int) -> None:
		uniqueTag: str = self._GetUniqueColumnTag(gridX)
		self.w_canvas.delete(uniqueTag) # delete any canvas object where we want to draw this gridline, before re/drawing it
		self.w_canvas.create_line(canvasPixelX, 0, canvasPixelX, self.canvasHeight,
							tags=(GuiGridView.GRIDLINE_TAG, uniqueTag))

	'''
	DO NOT CALL DIRECTLY - THIS IS A HELPER FUNCTION
	creates a horizontal gridline with the proper tags
	'''
	def _CreateHorizontalGridlineWithTags(self, canvasPixelY: int, gridY: int) -> None:
		uniqueTag: str = self._GetUniqueRowTag(gridY)
		self.w_canvas.delete(uniqueTag) # delete any canvas object where we want to draw this gridline, before re/drawing it
		self.w_canvas.create_line(0, canvasPixelY, self.canvasWidth, canvasPixelY,
							tags=(GuiGridView.GRIDLINE_TAG, uniqueTag))
		
	def _DrawAllCoords(self) -> None:
		self.w_canvas.delete(GuiGridView.COORDS_TAG) # erase all coordinate text before re/drawing them
		for y in range(self.mapData.GetHeight()):
			for x in range(self.mapData.GetWidth()):
				self._DrawCoordsAtGridPos(x, y)

	def _DrawCoordsAtGridPos(self, gridX: int, gridY: int) -> None:
		uniqueTag: str = self._GetUniqueCoordsTag(gridX, gridY)
		# print(f"drawing coords with the following tag: \"{uniqueTag}\"")
		# draw the text in the center of the grid square
		drawX: int = gridX * self.TILE_SIZE + (self.TILE_SIZE / 2)
		drawY: int = gridY * self.TILE_SIZE + (self.TILE_SIZE / 2)
		coordsText: str = f"{gridX},{gridY}"
		canvasObject = self.w_canvas.create_text(drawX, drawY, text=coordsText, font='TkMenuFont', fill="black", width=self.TILE_SIZE,
										   tags=(GuiGridView.COORDS_TAG, self._GetUniqueCoordsTag(gridX, gridY)))
		# NOTE: no anchor specified because we want default anchoring (in the center of the text)
		# every coordinate text has two tags. one generic coordinate tag, and one that's specific to that text's position on the grid
		# the generic coordinate tag is for accessing all coordinate text
		# the position-specific tag is distinct from the tile's position-specific tag so that they can be separately accessed
		self._SetCanvasObjectBindings(canvasObject)

	############################
	# utility/helper functions #
	############################

	def _ScreenPixelToGridPos(self, screenPixelX: int, screenPixelY: int) -> tuple[int, int]:
		# TODO: come back and adjust this logic when zoom functionality is added
		canvasPixelX: int = int(self.w_canvas.canvasx(screenPixelX))
		canvasPixelY: int = int(self.w_canvas.canvasy(screenPixelY))
		return (canvasPixelX // self.TILE_SIZE, canvasPixelY // self.TILE_SIZE)

	def _SetCanvasObjectBindings(self, canvasObject) -> None:
		# print(canvasObject)
		self.w_canvas.tag_bind(canvasObject, "<Button-1>", self._CanvasClicked)
		self.w_canvas.tag_bind(canvasObject, "<Button-3>", self._CanvasErase)
		# NOTE: click-and-drag functionality is bound to the canvas itself, not the drawn canvas objects

	def _UpdateLastClickedGridPos(self, pixelX: int, pixelY: int) -> None:
		gridPos: tuple[int, int] = self._ScreenPixelToGridPos(pixelX, pixelY)
		self.lastClickedGridX = gridPos[0]
		self.lastClickedGridY = gridPos[1]
		# print(f"last clicked grid pos : ({self.lastClickedGridX}, {self.lastClickedGridY})")
		self._UpdateLastHoveredGridPos(pixelX, pixelY)

	def _UpdateLastHoveredGridPos(self, pixelX: int, pixelY: int) -> None:
		gridPos: tuple[int, int] = self._ScreenPixelToGridPos(pixelX, pixelY)
		self.lastHoveredGridX = gridPos[0]
		self.lastHoveredGridY = gridPos[1]
		# print(f"last hovered grid pos : ({self.lastHoveredGridX}, {self.lastHoveredGridY})")

	def _MouseButtonReleased(self, event: tk.Event) -> None:
		# print(event)
		self.mouseButtonReleased = True

		# redraw gridlines after releasing the mouse button
		if self.showGridlines == True:
			self._DrawGridlines()

	def _MouseMoved(self, event: tk.Event) -> None:
		gridPos: tuple[int, int] = self._ScreenPixelToGridPos(event.x, event.y)
		gridX: int = gridPos[0]
		gridY: int = gridPos[1]
		if gridX != self.lastHoveredGridX or gridY != self.lastHoveredGridY:
			self._UpdateLastHoveredGridPos(event.x, event.y)
			if self.showCoords == 1:
				self.w_canvas.delete(GuiGridView.COORDS_TAG) # delete any other coordinate-tagged objects
				self._DrawCoordsAtGridPos(gridX, gridY) # draw the coords at the new gridspot

	############################
	# tag generation functions #
	############################

	def _GetPositionTag(self, gridX: int, gridY: int) -> str:
		return f"{gridX},{gridY}"

	def _GetUniqueCoordsTag(self, gridX: int, gridY: int) -> str:
		return f"{GuiGridView.COORDS_TAG} : {self._GetPositionTag(gridX, gridY)}"

	def _GetUniqueColumnTag(self, gridX) -> str:
		pass

	def _GetUniqueRowTag(self, gridY) -> str:
		pass

	################
	# view options #
	################
	
	def ToggleGridlines(self) -> None:
		print("toggling gridlines")
		if self.showGridlines == True:
			self.DisableGridlines()
		else:
			self.EnableGridlines()
		
	def EnableGridlines(self) -> None:
		self.showGridlines = True
		self._DrawGridlines()

	def DisableGridlines(self) -> None:
		self.showGridlines = False
		self.w_canvas.delete(GuiGridView.GRIDLINE_TAG)

	def SetCoords(self, viewLevel: int) -> None:
		if viewLevel == 0:
			self.SetCoordsLevel0()
		elif viewLevel == 1:
			self.SetCoordsLevel1()
		elif viewLevel == 2:
			self.SetCoordsLevel2()
		else:
			assert False

	def SetCoordsLevel0(self) -> None:
		self.showCoords = 0
		self.w_canvas.delete(GuiGridView.COORDS_TAG)

	def SetCoordsLevel1(self) -> None:
		self.showCoords = 1
		self.w_canvas.delete(GuiGridView.COORDS_TAG)

	def SetCoordsLevel2(self) -> None:
		self.showCoords = 2
		self._DrawAllCoords()

	###############################
	# functions called by the app #
	###############################

	def SetCurrentBrushTile(self, img: tk.PhotoImage) -> None:
		self.brushTileImg = img

	########################
	# whole-grid functions #
	########################

	# Type hints added. Kind of meh on it, but it's fine.
	def GetDataForSaving(self) -> dict[str, any]:
		data: dict = {
			MapData.VERSION_KEY: 1,
			MapData.PROPS_KEY: self.mapData.GetPropertiesAsDict(),
			MapData.LAYOUT_KEY: self.mapData.GetLayoutAsDict()
		}
		return data

	def ReadLoadedData(self, data: dict[str, any]) -> None:
		print("GuiGridView.ReadLoadedData()")
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
    """
    GUI panel for displaying details about the selected tile.
    Reads JSON tile data and displays relevant properties.
    """

    def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, padx: int, pady: int, sticky: str) -> None:
        
        ############################
        # Create the non-GUI stuff #
        ############################
        self.tile_data = {}
        self.tile_image = None

        ########################
        # Create the GUI stuff #
        ########################
        
        # Create the parent frame
        self.w_parentFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Tile Details Panel")
        self.w_parentFrame.grid(column=column, row=row,
                                columnspan=columnspan, rowspan=rowspan,
                                padx=padx, pady=pady, sticky=sticky)

        # Tile Icon
        self.w_tileIcon = tk.Label(self.w_parentFrame, text="No Image", width=10, height=5, relief="solid")
        self.w_tileIcon.grid(column=0, row=0, columnspan=2, pady=10)

        # Tile Name
        self.w_nameLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Name:")
        self.w_nameLabel.grid(column=0, row=1, sticky="W", padx=10, pady=5)
        self.w_nameValue: ttk.Label = ttk.Label(self.w_parentFrame, text="N/A")
        self.w_nameValue.grid(column=1, row=1, sticky="W", padx=10, pady=5)

        # Damage to Player
        self.w_damagePlayerLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Damage to Player:")
        self.w_damagePlayerLabel.grid(column=0, row=2, sticky="W", padx=10, pady=5)
        self.w_damagePlayerValue: ttk.Label = ttk.Label(self.w_parentFrame, text="0")
        self.w_damagePlayerValue.grid(column=1, row=2, sticky="W", padx=10, pady=5)

        # Damage to Enemies
        self.w_damageEnemiesLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Damage to Enemies:")
        self.w_damageEnemiesLabel.grid(column=0, row=3, sticky="W", padx=10, pady=5)
        self.w_damageEnemiesValue: ttk.Label = ttk.Label(self.w_parentFrame, text="0")
        self.w_damageEnemiesValue.grid(column=1, row=3, sticky="W", padx=10, pady=5)

        # Breakable Status
        self.w_breakableLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Breakable:")
        self.w_breakableLabel.grid(column=0, row=4, sticky="W", padx=10, pady=5)
        self.w_breakableValue: ttk.Label = ttk.Label(self.w_parentFrame, text="No")
        self.w_breakableValue.grid(column=1, row=4, sticky="W", padx=10, pady=5)

        # Solid Status
        self.w_solidLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Solid:")
        self.w_solidLabel.grid(column=0, row=5, sticky="W", padx=10, pady=5)
        self.w_solidValue: ttk.Label = ttk.Label(self.w_parentFrame, text="No")
        self.w_solidValue.grid(column=1, row=5, sticky="W", padx=10, pady=5)

    #############################
    # Update Tile Details Panel #
    #############################

    def UpdateTileDetails(self, img: tk.PhotoImage) -> None:
        
        #Reads the JSON file for the selected tile and updates the GUI.
        tileName = img.name 
        tileBaseName = jns.ConvertToCamelCase(tileName.split("_")[-1].replace(".png", ""))
        tileJsonPath = os.path.join(jns.READ_LOCATION_TEXTURES_LEVELTILES, tileBaseName + "_data.json")

        # if JSON exists...
        if os.path.exists(tileJsonPath):
            with open(tileJsonPath, "r") as jsonFile:
                self.tile_data = json.load(jsonFile)

                # Update fields
                self.w_nameValue.config(text=self.tile_data.get("name", "Unknown"))
                self.w_damagePlayerValue.config(text=str(self.tile_data.get("damage to player", 0)))
                self.w_damageEnemiesValue.config(text=str(self.tile_data.get("damage to enemies", 0)))
                self.w_breakableValue.config(text="Yes" if self.tile_data.get("breakable", False) else "No")
                self.w_solidValue.config(text="Yes" if self.tile_data.get("solid on sides", False) else "No")

                # Load and display tile icon
                self.tile_image = img
                self.w_tileIcon.config(image=self.tile_image)
                self.w_tileIcon.image = self.tile_image  # Keep reference
        else:
            print(f"Warning: No JSON data found for tile: {tileBaseName}")
            #self.ResetDetails()
			# Hope to work on a reset function tommorow. I think that might be ideal, but could be in the Tile data editor too.

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
		self.DEFAULT_SHOW_GRIDLINES: bool = True
		self.DEFAULT_SHOW_COORDS: int = 1 # 0=never, 1=on mouse-over, 2=always

		# non-constants
		fileList: list[str] = jns.GetFilesWithConvention(jns.READ_LOCATION_TEXTURES_LEVELTILES, jns.CONVENTION_SPR_LEVELTILE)
		self.tileImgs: dict[str, tk.PhotoImage] = {} # a dict where the key is the filename, and the value is the corresponding tk.PhotoImage
		self._LoadAllImages(fileList)
		# jns.PrintDict(self.tileImgs)

		self.brushTileName: str
		
		########################
		# create the gui stuff #
		########################
		
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
											  fGetTileByNameCallback=self.GetTileByName,
											  viewOptShowGridlines=self.DEFAULT_SHOW_GRIDLINES, # NOTE: this parameter only sets the initial value
											  viewOptShowCoords=self.DEFAULT_SHOW_COORDS) # NOTE: this parameter only sets the initial value

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

		# create the menu bar
		self._SetupMenuBar()
		
	###################
	# setup functions #
	###################

	def _LoadAllImages(self, fileList: list[str]) -> None:
		for filename in fileList:
			filePath: str = os.path.join(jns.READ_LOCATION_TEXTURES_LEVELTILES, filename)
			self.tileImgs[filename] = tk.PhotoImage(file=filePath, name=filename)

	def _SetupMenuBar(self) -> None:
		# create the menu bar
		self.root.option_add("*tearOff", tk.FALSE)
		self.menuBar: tk.Menu = tk.Menu(self.root)
		self.root.config(menu=self.menuBar)
		
		# set up the submenus
		self._SetupFileMenu()
		self._SetupEditMenu()
		self._SetupViewMenu()

	def _SetupFileMenu(self) -> None:
		self.fileMenu: tk.Menu = tk.Menu(self.menuBar)

		self.fileMenu.add_command(label="New", state='disabled', accelerator="Ctrl N") # TODO: add a command to make this do something
		self.root.bind("<Control-n>", self.KbShortNew)

		self.fileMenu.add_separator()

		self.fileMenu.add_command(label="Save", command=self.Save, accelerator="Ctrl S")
		self.root.bind("<Control-s>", self.KbShortSave)
		self.fileMenu.add_command(label="Save As...", state='disabled', accelerator="Ctrl Shift S") # TODO: add a command to make this do something
		self.root.bind("<Control-Shift-s>", self.KbShortSaveAs) # TODO: figure out why this keyboard shortcut isn't working (it probably has something to do with the "Shift" part)

		self.fileMenu.add_separator()

		self.fileMenu.add_command(label="Open", command=self.Load, accelerator="Ctrl O")
		self.root.bind("<Control-o>", self.KbShortOpen)
		self.openRecentMenu: tk.Menu = tk.Menu(self.fileMenu) # create the recent files submenu
		self.fileMenu.add_cascade(label="Open Recent", menu=self.openRecentMenu)
		self.openRecentMenu.add_command(label="1st most recent file goes here", state="disabled", accelerator="Ctrl Alt 1") # TODO: add a command to make this do something
		self.root.bind("<Control-Alt-1>", self.KbShortOpenRecent1)
		self.openRecentMenu.add_command(label="2nd most recent file goes here", state="disabled", accelerator="Ctrl Alt 2") # TODO: add a command to make this do something
		self.root.bind("<Control-Alt-2>", self.KbShortOpenRecent2)
		self.openRecentMenu.add_command(label="3rd most recent file goes here", state="disabled", accelerator="Ctrl Alt 3") # TODO: add a command to make this do something
		self.root.bind("<Control-Alt-3>", self.KbShortOpenRecent3)

		self.fileMenu.add_separator()

		self.fileMenu.add_command(label="Quit", state='disabled', accelerator="Ctrl Q") # TODO: add a command to make this do something
		self.root.bind("<Control-q>", self.KbShortQuit)

		# add the above options to the file menu
		self.menuBar.add_cascade(label="File", menu=self.fileMenu)

	def _SetupEditMenu(self) -> None:
		self.editMenu: tk.Menu = tk.Menu(self.menuBar)

		self.editMenu.add_command(label="Copy", state='disabled', accelerator="Ctrl C") # TODO: add a command to make this do something
		# TODO: bind ctrl+c to the "Copy" command
		self.editMenu.add_command(label="Cut", state='disabled', accelerator="Ctrl X") # TODO: add a command to make this do something
		# TODO: bind ctrl+x to the "Cut" command
		self.editMenu.add_command(label="Paste", state='disabled', accelerator="Ctrl V") # TODO: add a command to make this do something
		# TODO: bind ctrl+v to the "Paste" command
		self.editMenu.add_separator()

		self.editMenu.add_command(label="Undo", state='disabled', accelerator="Ctrl Z") # TODO: add a command to make this do something
		# TODO: bind ctrl+z to the "Undo" command
		self.editMenu.add_command(label="Redo", state='disabled', accelerator="Ctrl Y") # TODO: add a command to make this do something
		# TODO: bind ctrl+y to the "Redo" command
		self.editMenu.add_separator()

		self.editMenu.add_command(label="Clear", command=self.wc_gridView.InitCanvas, accelerator="Ctrl E") # TODO: add a popup warning if changes are unsaved
		self.root.bind("<Control-e>", self.KbShortClear)
		self.editMenu.add_separator()

		self.brushModeMenu: tk.Menu = tk.Menu(self.editMenu) # create the cursor mode menu
		self.editMenu.add_cascade(label="Brush Mode", menu=self.brushModeMenu)
		self.brushModeMenu_selection: tk.IntVar = tk.IntVar(value=1)
		self.brushModeMenu.add_radiobutton(label="Normal", variable=self.brushModeMenu_selection, value=1, accelerator="Ctrl 1") # TODO: add a command to make this do something
		# TODO: bind ctrl+1 to the "Cursor Mode: Normal" command
		self.brushModeMenu.add_radiobutton(label="Fill", variable=self.brushModeMenu_selection, value=2, state='disabled', accelerator="Ctrl 2") # TODO: add a command to make this do something
		# TODO: bind ctrl+2 to the "Cursor Mode: Fill" command
		self.brushModeMenu.add_radiobutton(label="Line", variable=self.brushModeMenu_selection, value=3, state='disabled', accelerator="Ctrl 3") # TODO: add a command to make this do something
		# TODO: bind ctrl+3 to the "Cursor Mode: Line" command
		self.brushModeMenu.add_radiobutton(label="Rectangle", variable=self.brushModeMenu_selection, value=4, state='disabled', accelerator="Ctrl 4") # TODO: add a command to make this do something
		# TODO: bind ctrl+4 to the "Cursor Mode: Rectangle" command
		self.brushModeMenu.add_radiobutton(label="Circle", variable=self.brushModeMenu_selection, value=5, state='disabled', accelerator="Ctrl 5") # TODO: add a command to make this do something
		# TODO: bind ctrl+5 to the "Cursor Mode: Circle" command
		self.editMenu.add_separator()

		self.editMenu.add_command(label="Resize Map...", state='disabled') # TODO: add a command to make this do something
		self.editMenu.add_separator()

		self.editMenu.add_command(label="Switch to layer above", state='disabled', accelerator="Ctrl Up") # TODO: add a command to make this do something
		# TODO: bind ctrl+up to the "Switch to Layer Above" command
		self.editMenu.add_command(label="Switch to layer below", state='disabled', accelerator="Ctrl Down") # TODO: add a command to make this do something
		# TODO: bind ctrl+down to the "Switch to Layer Below" command
		self.editMenu.add_command(label="Switch to palette left", state='disabled', accelerator="Ctrl Left") # TODO: add a command to make this do something
		# TODO: bind ctrl+left to the "Switch to Palette Left" command
		self.editMenu.add_command(label="Switch to palette right", state='disabled', accelerator="Ctrl Right") # TODO: add a command to make this do something
		# TODO: bind ctrl+right to the "Switch to Palette Right" command

		# add the above options to the edit menu
		self.menuBar.add_cascade(label="Edit", menu=self.editMenu)

	def _SetupViewMenu(self) -> None:
		self.viewMenu: tk.Menu = tk.Menu(self.menuBar)

		self.viewMenu.add_command(label="Zoom In", state='disabled', accelerator="Ctrl =") # TODO: add a command to make this do something
		# TODO: bind ctrl+= to the "Zoom In" command
		self.viewMenu.add_command(label="Zoom Out", state='disabled', accelerator="Ctrl -") # TODO: add a command to make this do something
		# TODO: bind ctrl+- to the "Zoom Out" command
		self.viewMenu.add_command(label="Reset Zoom", state='disabled', accelerator="Ctrl R") # TODO: add a command to make this do something
		# TODO: bind ctrl+r to the "Reset Zoom" command
		self.viewMenu.add_separator()

		self.viewMenu_showGridlinesVar: tk.BooleanVar = tk.BooleanVar(value=self.DEFAULT_SHOW_GRIDLINES)
		self.viewMenu.add_checkbutton(label="Show Gridlines", variable=self.viewMenu_showGridlinesVar, onvalue=tk.TRUE, offvalue=tk.FALSE, command=self.wc_gridView.ToggleGridlines)

		self.showCoordsMenu: tk.Menu = tk.Menu(self.viewMenu)
		self.viewMenu.add_cascade(label="Show Coordinates", menu=self.showCoordsMenu)
		self.showCoordsMenu_showTileCoordsVar: tk.IntVar = tk.IntVar(value=self.DEFAULT_SHOW_COORDS)
		self.showCoordsMenu.add_radiobutton(label="Never", variable=self.showCoordsMenu_showTileCoordsVar,			value=0, command=self.wc_gridView.SetCoordsLevel0)
		self.showCoordsMenu.add_radiobutton(label="On Mouse-Over", variable=self.showCoordsMenu_showTileCoordsVar,	value=1, command=self.wc_gridView.SetCoordsLevel1)
		self.showCoordsMenu.add_radiobutton(label="Always", variable=self.showCoordsMenu_showTileCoordsVar,			value=2, command=self.wc_gridView.SetCoordsLevel2)

		# add the above options to the view menu
		self.menuBar.add_cascade(label="View", menu=self.viewMenu)

	###############################
	# keyboard shortcut functions #
	###############################

	def KbShortNew(self, event: tk.Event) -> None:
		print("The command for NEW has not yet been bound")

	def KbShortSave(self, event: tk.Event) -> None:
		self.Save()

	def KbShortSaveAs(self, event: tk.Event) -> None:
		print("The command for SAVE AS has not yet been bound")

	def KbShortOpen(self, event: tk.Event) -> None:
		self.Load() # TODO: change this to a function call that opens a popup listing all files in the jns.READ_LOCATION_LEVELDATA folder

	def KbShortOpenRecent1(self, event: tk.Event) -> None:
		print("The command for OPEN RECENT 1 has not yet been bound")

	def KbShortOpenRecent2(self, event: tk.Event) -> None:
		print("The command for OPEN RECENT 2 has not yet been bound")

	def KbShortOpenRecent3(self, event: tk.Event) -> None:
		print("The command for OPEN RECENT 3 has not yet been bound")

	def KbShortQuit(self, event: tk.Event) -> None:
		print("The command for QUIT has not yet been bound")

	def KbShortClear(self, event: tk.Event) -> None:
		self.wc_gridView.InitCanvas()

	#################################
	# gui interoperability funcions #
	#################################

	'''
	called by the tile palette in order to select the brush tile
	'''
	def SelectBrushTile(self, tileFilename: str) -> None:
		self.brushTileName = tileFilename
		print(f"Selected brush tile : \"{self.brushTileName}\"")

		# call a GuiGridView function to update the brush tile image
		self.wc_gridView.SetCurrentBrushTile(self.GetBrushTileImg())
		# TODO: call a GuiTileDetailsPanel function to update the tile details
		self.wc_tileDetails.UpdateTileDetails(self.GetBrushTileImg())

	'''
	called by anyone who needs the image for the current brush tile
	'''
	def GetBrushTileImg(self) -> tk.PhotoImage:
		return self.tileImgs[self.brushTileName]

	'''
	called by anyone who needs to retrieve an image by its filename
	'''
	def GetTileByName(self, filename: str) -> tk.PhotoImage:
		assert filename in self.tileImgs.keys()
		return self.tileImgs[filename]
	
	########################
	# filesystem functions #
	########################

	def Save(self) -> None:
		# NOTE: DO NOT MODIFY THE LOADED DATA IN ANY WAY, SAVE IT TO FILE AS IT WAS RECEIVED FROM GRIDVIEW
		data: dict = self.wc_gridView.GetDataForSaving()
		filename: str = "test.json" # TODO: allow the user to pick the file name
		filePath: str = os.path.join(jns.READ_LOCATION_LEVELDATA, filename)
		with open(file=filePath, mode='w') as jsonFile:
			json.dump(data, jsonFile, indent=4)
		print(f"Saved file: \"{filePath}\"")

	def Load(self) -> None:
		# NOTE: DO NOT MODIFY THE LOADED DATA IN ANY WAY, PASS IT ALONG TO GRIDVIEW AS-IS
		# load data from file
		data: dict[str, any]
		filename: str = "test.json"
		filePath: str = os.path.join(jns.READ_LOCATION_LEVELDATA, filename)
		with open(file=filePath, mode='r') as jsonFile:
			data = json.load(jsonFile)
		print(f"Opened file: \"{filePath}\"")

		# print(f"Loaded the following data from {filePath}")
		# jns.PrintDict(data)

		# pass data along to the GuiGridView
		self.wc_gridView.ReadLoadedData(data)

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
