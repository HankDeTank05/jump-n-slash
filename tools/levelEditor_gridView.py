# language imports
import tkinter as tk
import tkinter.ttk as ttk

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
