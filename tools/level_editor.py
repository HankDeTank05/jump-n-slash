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
			# TODO: check the columns between the old width and the new width
			# TODO: if there are any tiles (not None) in any of those columns...
			# 			warn the user that tiles in those columns will be deleted (with a popup window)
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

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, padx: int, pady: int, sticky: str, fGetTileByNameCallback: any) -> None:
		############################
		# create the non-gui stuff #
		############################
		
		# constants
		self.TILE_SIZE: int = 32
		self.EMPTY_TAG: str = "empty"

		# non-constants
		self.brushMode: str = GuiGridView.BRUSH_MODE_NORMAL
		self.mapData: MapData = MapData()
		self.brushTileImg: tk.PhotoImage # declare, don't define (will be defined externally)
		self.fGetTileByName = fGetTileByNameCallback
		self.lastMouseGridX: int = -1
		self.lastMouseGridY: int = -1
		self.mouseButtonReleased: bool = True

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
		self._InitCanvas()

		# call a function when the left mouse button is clicked-and-dragged
		self.w_canvas.bind("<B1-Motion>", self._CanvasClicked) # do stuff when click-and-dragging mouse1
		self.w_canvas.bind("<B3-Motion>", self._CanvasErase) # do stuff when click-and-dragging mouse2
		self.w_canvas.bind("<B1-ButtonRelease>", self._MouseButtonReleased)
		self.w_canvas.bind("<B3-ButtonRelease>", self._MouseButtonReleased)

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
		# print("GuiGridView._InitCanvas()")
		grid: list[list[str | None]] = self.mapData.GetGrid()
		gridHeight: int = self.mapData.GetHeight()
		gridWidth: int = self.mapData.GetWidth()
		self._ResizeCanvas(gridWidth, gridHeight)
		for y in range(gridHeight):
			for x in range(gridWidth):
				x0: int = x * self.TILE_SIZE
				y0: int = y * self.TILE_SIZE
				if grid[y][x] is None:
					x1: int = x0 + self.TILE_SIZE - 1
					y1: int = y0 + self.TILE_SIZE - 1
					self.DrawSqaureAtGridPos(x, y)
				else:
					tileFilename: str = grid[y][x]
					imageToDraw: tk.PhotoImage = self.fGetTileByName(tileFilename)
					self.DrawImageAtGridPos(imageToDraw, x, y)

	def _CanvasClicked(self, event: tk.Event) -> None:
		# print("GuiGridView._CanvasClicked()")

		# only do stuff if the mouse button is released or the cursor is in a new grid square
		mouseGridPos: tuple[int, int] = self.PixelToGridPos(event.x, event.y)
		if self.mouseButtonReleased == True or mouseGridPos[0] != self.lastMouseGridX or mouseGridPos[1] != self.lastMouseGridY:
			self.mouseButtonReleased = False
			print(event)
			if self.brushMode == GuiGridView.BRUSH_MODE_NORMAL:
				self.WriteTile(event.x, event.y)
			elif self.brushMode == GuiGridView.BRUSH_MODE_LINE:
				assert False
			else:
				assert False
			self.UpdateLastMouseGridPos(event.x, event.y)

	def _CanvasErase(self, event: tk.Event) -> None:
		# print("GuiGridView._CanvasErase")

		# only do stuff if the mouse button is released or the cursor is in a new grid square
		mouseGridPos: tuple[int, int] = self.PixelToGridPos(event.x, event.y)
		if self.mouseButtonReleased == True or mouseGridPos[0] != self.lastMouseGridX or mouseGridPos[1] != self.lastMouseGridY:
			self.mouseButtonReleased = False
			print(event)
			# right-clicking to erase will erase according to the current brush mode!
			if self.brushMode == GuiGridView.BRUSH_MODE_NORMAL:
				self.EraseTile(event.x, event.y)
			elif self.brushMode == GuiGridView.BRUSH_MODE_LINE:
				assert False
			else:
				assert False
			self.UpdateLastMouseGridPos(event.x, event.y)

	'''
	write a single tile to the map data, and draw it on the canvas
	'''
	def WriteTile(self, pixelX: int, pixelY: int) -> None:
		# get the grid coordinates
		gridPos: tuple[int, int] = self.PixelToGridPos(pixelX, pixelY)
		gridX: int = gridPos[0]
		gridY: int = gridPos[1]

		# place the image in the map data
		self.mapData.WriteTile(self.brushTileImg.name, gridX, gridY)

		# draw the image
		self.DrawImageAtGridPos(self.brushTileImg, gridX, gridY)

	'''
	erase a single tile from the map data, and erase it from the canvas as well
	'''
	def EraseTile(self, pixelX: int, pixelY: int) -> None:
		# get the grid coordinates
		gridPos: tuple[int, int] = self.PixelToGridPos(pixelX, pixelY)
		gridX = gridPos[0]
		gridY = gridPos[1]

		# erase the image from map data
		self.mapData.WriteTile(None, gridX, gridY)

		# draw an empty square
		self.DrawSqaureAtGridPos(gridX, gridY)

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
					self.DrawImageAtGridPos(img, x, y)
				else:
					self.DrawSqaureAtGridPos(x, y)

	def _ResizeCanvas(self, newTileWidth: int, newTileHeight: int) -> None:
		# print("GuiGridView._ResizeCanvas()")
		self.mapData.Resize(newTileWidth, newTileHeight)
		canvasLeftX: int = 0
		canvasTopY: int = 0
		canvasRightX: int = self.mapData.width * self.TILE_SIZE
		canvasBottomY: int = self.mapData.height * self.TILE_SIZE
		canvasPixWidth: int = canvasRightX - canvasLeftX
		canvasPixHeight: int = canvasBottomY - canvasTopY
		self.w_canvas.config(scrollregion=(canvasLeftX, canvasTopY, canvasRightX, canvasBottomY),
					   width=min(canvasPixWidth, 1280), height=min(canvasPixHeight, 720)) # TODO: replace the 1280 and 720 with numbers calculated based on the user's screen size

	############################
	# utility/helper functions #
	############################

	def PixelToGridPos(self, pixelX: int, pixelY: int) -> tuple[int, int]:
		# TODO: come back and adjust this logic when zoom functionality is added
		return (pixelX // self.TILE_SIZE, pixelY // self.TILE_SIZE)

	def SetCanvasObjectBindings(self, canvasObject) -> None:
		print(canvasObject)
		self.w_canvas.tag_bind(canvasObject, "<Button-1>", self._CanvasClicked)
		self.w_canvas.tag_bind(canvasObject, "<Button-3>", self._CanvasErase)
		# NOTE: click-and-drag functionality is bound to the canvas itself, not the objects on it

	def DrawImageAtGridPos(self, image: tk.PhotoImage, gridX: int, gridY: int) -> None:
		# delete what was there before
		objectTag: str = f"{gridX},{gridY}"
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
		self.SetCanvasObjectBindings(canvasObject)

	def DrawSqaureAtGridPos(self, gridX, gridY) -> None:
		# delete what was there before
		objectTag: str = f"{gridX},{gridY}"
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
												fill="white",
												tags=(self.EMPTY_TAG, objectTag))
		self.SetCanvasObjectBindings(canvasObject)

	def UpdateLastMouseGridPos(self, pixelX: int, pixelY: int) -> None:
		gridPos: tuple[int, int] = self.PixelToGridPos(pixelX, pixelY)
		self.lastMouseGridX = gridPos[0]
		self.lastMouseGridY = gridPos[1]
		print(f"last mouse grid pos : ({self.lastMouseGridX}, {self.lastMouseGridY})")

	def _MouseButtonReleased(self, event: tk.Event) -> None:
		print(event)
		self.mouseButtonReleased = True

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

	def UpdateTileDetails(self, img: tk.PhotoImage) -> None:
		# TODO: finish this function
		# NOTE: currently, this is displaying the filename for the brush tile
		# TODO: we want just the tile name (no "<paletteName>_" prefix, no ".png" suffix) so that we can look for "<tileName>.json" and read the tile's data from there
		# TODO: we also want a second version of the <tileName> that's not in camel case so that the displayed name looks nice in the GUI
		self.w_nameValue.config(text=img.name)
		# self.w_damagePlayerValue.config(text="UPDATED DAMAGE TO PLAYER")
		# self.w_damageEnemiesValue.config(text="UPDATED DAMAGE TO ENEMIES")
		# self.w_breakableValue.config(text="UPDATED BREAKABILITY")
		# self.w_solidValue.config(text="UPDATED SOLIDITY")

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

		# non-constants
		
		fileList: list[str] = jns.GetFilesWithConvention(jns.READ_LOCATION_TEXTURES_LEVELTILES, jns.CONVENTION_SPR_LEVELTILE)

		# a dict where the key is the filename, and the value is the corresponding tk.PhotoImage
		self.tileImgs: dict[str, tk.PhotoImage] = {}
		self._LoadAllImages(fileList)
		# jns.PrintDict(self.tileImgs)

		self.brushTileName: str
		
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
		self.fileMenu.add_command(label="Save (ctrl + s)", command=self.Save)
		self.fileMenu.add_command(label="Open (ctrl + o)", command=self.Load)
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

		self.BindKeyboardShortcuts()
		
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

	###############################
	# keyboard shortcut functions #
	###############################

	def BindKeyboardShortcuts(self) -> None:
		print("binding keyboard shortcuts")
		# file menu
		# TODO: bind ctrl+n to the "New" command
		self.root.bind("<Control-s>", self.KeyboardShortcutSave)
		self.root.bind("<Control-o>", self.KeyboardShortcutLoad)
		# TODO: bind ctrl+x to the "Exit" command

		# edit menu
		# TODO: bind ctrl+z to the "Undo" command
		# TODO: bind ctrl+y to the "Redo" command
		# TODO: figure out a binding for the "Clear" command

		# view menu
		# TODO: bind ctrl+= to the "Zoom In" command
		# TODO: bind ctrl+- to the "Zoom Out" command
		# TODO: bind ctrl+r to the "Reset Zoom" command

		# other commands
		# TODO: bind ctrl+up to the "Move to Layer Above" command
		# TODO: bind ctrl+down to the "Move to Layer Below" command
		# TODO: bind ctrl+, to the "Switch to Palette Left" command
		# TODO: bind ctrl+. to the "Switch to Palette Right" command
		# TODO: bind ctrl+1 to the "Cursor Mode: Normal" command
		# TODO: bind ctrl+2 to the "Cursor Mode: Line" command
		# TODO: bind ctrl+3 to the "Cursor Mode: Fill" command
		# TODO: bind ctrl+4 to the "Cursor Mode: Rectangle" command
		# TODO: bind ctrl+5 to the "Cursor Mode: Circle" command

	def KeyboardShortcutSave(self, event: tk.Event) -> None:
		self.Save()

	def KeyboardShortcutLoad(self, event: tk.Event) -> None:
		self.Load()

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
