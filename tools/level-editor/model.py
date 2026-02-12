# language imports
import tkinter as tk
import os.path
import json

# game imports
import jnscommon as jns


class Model:
	
	# General Model for the Level Editor.

	def __init__(self) -> None:
		#############
		# constants #
		#############

		self.TILE_SIZE: int = 32
		
		self.BRUSH_MODE_NORMAL: str = "normal"
		self.BRUSH_MODE_LINE: str = "line"

		#################
		# non-constants #
		#################
		
		# Stores tile images with filename as keys
		self._tileImgs: dict[str, tk.PhotoImage] = {}  # TODO: Consider switching to PIL images
		self._LoadAllImages()

		# The filename of the currently selected tile to be used for editing
		self._brushTileName: str = list(self._tileImgs.keys())[0] if self._tileImgs else ""

		# Stores loaded tile data (JSON)
		self._tileData: dict = {}

		# Map data instance
		# stuff for gridview
		self._mapData: MapData = MapData()
		self._brushMode: str = self.BRUSH_MODE_NORMAL
		self._lastClickedGridX: int = -1
		self._lastClickedGridY: int = -1
		self._lastHoveredGridX: int = -1
		self._lastHoveredGridY: int = -1

	######################
	# Internal Functions #
	######################

	def _LoadAllImages(self) -> None:
		
		# Loads all tile images from the asset directory and stores them in a dictionary.
		
		fileList: list[str] = jns.GetFilesWithConvention(jns.PATH_ASSETS_TEXTURES_LEVELTILES, jns.CONVENTION_SPR_LEVELTILE)
		for filename in fileList:
			filePath: str = os.path.join(jns.PATH_ASSETS_TEXTURES_LEVELTILES, filename)
			self._tileImgs[filename] = tk.PhotoImage(file=filePath, name=filename)

	#############
	# Accessors #
	#############
	
	def GetAllTileFilenames(self) -> list[str]:
		return list(self._tileImgs.keys())
	
	def GetTileImg(self, filename: str) -> tk.PhotoImage:
		assert filename in self._tileImgs.keys()
		return self._tileImgs[filename]

	def GetBrushTileName(self) -> str:
		return self._brushTileName

	def GetBrushTileImg(self) -> tk.PhotoImage:
		return self._tileImgs[self._brushTileName]

	def GetMapGrid(self) -> list[list[str | None]]:
		return self._mapData.GetGrid()
	
	def GetMapWidth(self) -> int:
		return self._mapData.GetWidth()
	
	def GetMapHeight(self) -> int:
		return self._mapData.GetHeight()

	############
	# Mutators #
	############

	def SelectBrushTile(self, filename: str) -> None:
		
		# Selects a tile to be used as the brush for map editing.
		
		assert filename in self._tileImgs, f"Invalid tile filename: \"{filename}\""
		self._brushTileName = filename

	def ResizeMap(self, newTileWidth: int, newTileHeight: int) -> None:
		self._mapData.Resize(newTileWidth, newTileHeight)

	"""
	Loads tile properties from a JSON file.
	tile_name: The name of the tile without prefix or file extension.
	returns: A dictionary with tile properties.
	"""
	def LoadTileData(self, tileFilename: str) -> dict:
		print(f"loading data for the following tile: \"{tileFilename}\"")
		tileBaseName: str = tileFilename
		tileBaseName = tileBaseName.split("_")[1] # remove the palette prefix from the filename
		tileBaseName = tileBaseName[:-4] # remove the file extension from the filename
		print(f"tile base name: \"{tileBaseName}\"")
		tileDataFilename: str = tileBaseName + ".json"
		tileJsonPath: str = os.path.join(jns.PATH_ASSETS_TEXTURES_LEVELTILES, tileDataFilename)

		if os.path.exists(tileJsonPath):
			with open(tileJsonPath, "r") as jsonFile:
				self.tileData = json.load(jsonFile)
		else:
			print(f"Warning: No JSON data found for tile \"{tileBaseName}\" (filename: \"{tileDataFilename}\")")
			self.tileData = {}  # Reset data

		return self.tileData

	def WriteToMap(self, gridX: int, gridY: int) -> None:
		print(f"write to map at grid pos ({gridX}, {gridY})")
		self._mapData.WriteTile(self._brushTileName, gridX, gridY)

	def EraseFromMap(self, gridX: int, gridY: int) -> None:
		print(f"erase from map at grid pos ({gridX}, {gridY})")
		self._mapData.EraseTile(gridX, gridY)
  
	def LoadMapData(self, data: dict) -> None:
		#Replaces the current map data with new data from a file.
		self._mapData = MapData(data)

class MapData:
	
	# Handles the map layout, grid, and resizing.
	
	VERSION_KEY: str = "Version"
	PROPS_KEY: str = "Properties"
	PROPS_SIZE_KEY: str = "Size"
	LAYOUT_KEY: str = "Layout"

	def __init__(self, data: dict | None = None) -> None:
		"""
		Initializes the map grid.
		If no data is provided, creates a default blank map.
		"""
		self.grid: list[list[str | None]] = []
		self.width: int = 0
		self.height: int = 0

		if data is None:
			print("Constructing blank MapData object")
			self.width = 40
			self.height = 20
			self._InitializeEmptyGrid()
		else:
			print("Constructing MapData object from provided data")
			self._LoadMapData(data)

	##################
	# Internal Setup #
	##################

	def _InitializeEmptyGrid(self) -> None:
		
		# Creates an empty map grid with the current width and height.
		
		for _ in range(self.height):
			self.grid.append([None] * self.width)

	def _LoadMapData(self, data: dict) -> None:
		
		# Loads map data from a JSON object.
		
		self.width, self.height = data[MapData.PROPS_KEY][MapData.PROPS_SIZE_KEY]
		self.Resize(self.width, self.height)

		layout: dict[str, list[tuple[int, int]]] = data[MapData.LAYOUT_KEY]
		self.PopulateGridWithData(layout)

	############
	# Mutators #
	############

	def PopulateGridWithData(self, layoutData: dict[str, list[tuple[int, int]]]) -> None:
		
		# Populates the grid with tile data based on the given layout dictionary.
		
		for y in range(self.height):
			for x in range(self.width):
				self.grid[y][x] = None

		for tileFilename, positions in layoutData.items():
			for x, y in positions:
				if 0 <= x < self.width and 0 <= y < self.height:
					self.grid[y][x] = tileFilename

	def Resize(self, newTileWidth: int, newTileHeight: int) -> None:
		# print("MapData.Resize()")
		assert newTileWidth > 0
		assert newTileHeight > 0

		# Handle width changes
		
		if newTileWidth > self.width:
			print(f"Expanding map width: {self.width} -> {newTileWidth}")
			for row in self.grid:
				row.extend([None] * (newTileWidth - self.width))

		elif newTileWidth < self.width:
			print(f"Reducing map width: {self.width} -> {newTileWidth}")
			for row in self.grid:
				del row[newTileWidth:]

		# Handle height changes
		
		if newTileHeight > self.height:
			print(f"Expanding map height: {self.height} -> {newTileHeight}")
			for _ in range(newTileHeight - self.height):
				self.grid.append([None] * newTileWidth)

		elif newTileHeight < self.height:
			print(f"Reducing map height: {self.height} -> {newTileHeight}")
			del self.grid[newTileHeight:]

		self.width = newTileWidth
		self.height = newTileHeight

	#############
	# Accessors #
	#############

	def GetGrid(self) -> list[list[str | None]]:
		return [row[:] for row in self.grid]  # Deep copy

	def GetWidth(self) -> int:
		return self.width

	def GetHeight(self) -> int:
		return self.height

	def GetLayoutAsDict(self) -> dict[str, list[tuple[int, int]]]:
	
		# Returns the map layout as a dictionary where keys are tile filenames, and values are lists of (x, y) positions.
		
		layout: dict[str, list[tuple[int, int]]] = {}
		for y, row in enumerate(self.grid):
			for x, tile in enumerate(row):
				if tile:
					layout.setdefault(tile, []).append((x, y))
		return layout

	'''
	Places a tile on the grid at the given position.
	'''
	def WriteTile(self, filename: str, gridX: int, gridY: int) -> None:
		assert filename is not None
		if 0 <= gridX < self.width and 0 <= gridY < self.height:
			self.grid[gridY][gridX] = filename

	'''
	Erases a tile from the grid at the given position.
	'''
	def EraseTile(self, gridX: int, gridY: int) -> None:
		if 0 <= gridX < self.width and 0 <= gridY < self.height:
			self.grid[gridY][gridX] = None
