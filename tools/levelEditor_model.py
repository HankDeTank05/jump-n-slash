# language imports
import tkinter as tk
import os.path
import json

# game imports
import jnscommon as jns

class Model:

	def __init__(self) -> None:
		#               filename    corresponding image to be used
		#                    vvv  vvvvvvvvvvvvv
		self._tileImgs: dict[str, tk.PhotoImage] = {} # TODO: at some point we need to switch from tk.PhotoImage over to PIL images
		self._LoadAllImages()

		# the filename of the currently selected tile to be used to edit the map
		self._brushTileName: str = list(self._tileImgs.keys())[0]

		self._tileData: dict # TODO: (len) specify type hint more in detail

		self._mapData: MapData = MapData()

	######################
	# internal functions #
	######################

	def _LoadAllImages(self) -> None:
		fileList: list[str] = jns.GetFilesWithConvention(jns.PATH_ASSETS_TEXTURES_LEVELTILES, jns.CONVENTION_SPR_LEVELTILE)
		for filename in fileList:
			filePath: str = os.path.join(jns.PATH_ASSETS_TEXTURES_LEVELTILES, filename)
			self._tileImgs[filename] = tk.PhotoImage(file=filePath, name=filename)

	#############
	# accessors #
	#############

	def GetTileImages(self) -> dict[str, tk.PhotoImage]:
		return self._tileImgs

	############
	# mutators #
	############

	def SelectBrushTile(self, filename: str) -> None:
		assert filename in list(self._tileImgs.keys()), f"Trying to set invalid tile filename as the brush tile: \"{filename}\""
		self._brushTileName = filename

	

class TileDetailsModel:
    
    # Manages tile data, loads from JSON, and provides structured data for the VIEW.
    # Model responsible for handling tile data from JSON files.

	def __init__(self):
		self.tile_data = {}
   
	def load_tile_data(self, tile_name: str) -> dict:

		tile_base_name = jns.ConvertToCamelCase(tile_name.replace(".png", ""))
		tile_json_path = os.path.join(jns.READ_LOCATION_TEXTURES_LEVELTILES, tile_base_name + "_data.json")

		if os.path.exists(tile_json_path):
			with open(tile_json_path, "r") as json_file:
				self.tile_data = json.load(json_file)
		else:
			print(f"Warning: No JSON data found for tile: {tile_base_name}")
			self.tile_data = {}  # Reset data

		return self.tile_data
class MapData:

	VERSION_KEY: str = "Version"
	PROPS_KEY: str = "Properties"
	PROPS_SIZE_KEY: str = "Size"
	LAYOUT_KEY: str = "Layout"

	def __init__(self, data: dict | None = None) -> None:
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
		assert False
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
				pass

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
		return self.grid # TODO: return a deep copy
	
	def GetWidth(self) -> int:
		return self.width # TODO: return a deep copy
	
	def GetHeight(self) -> int:
		return self.height # TODO: return a deep copy

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
