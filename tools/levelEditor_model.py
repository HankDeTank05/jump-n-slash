# language imports
import tkinter as tk
import os.path
import json

# game imports
import jnscommon as jns


class Model:
    
    # General Model for the Level Editor.

    def __init__(self) -> None:
        # Stores tile images with filename as keys
        self._tileImgs: dict[str, tk.PhotoImage] = {}  # TODO: Consider switching to PIL images
        self._LoadAllImages()

        # The filename of the currently selected tile to be used for editing
        self._brushTileName: str = list(self._tileImgs.keys())[0] if self._tileImgs else ""

        # Stores loaded tile data (JSON)
        self._tileData: dict = {}

        # Map data instance
        self._mapData: MapData = MapData()

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

    def GetTileImages(self) -> dict[str, tk.PhotoImage]:
        return self._tileImgs

    def GetBrushTileName(self) -> str:
        return self._brushTileName

    ############
    # Mutators #
    ############

    def SelectBrushTile(self, filename: str) -> None:
        
        # Selects a tile to be used as the brush for map editing.
        
        assert filename in self._tileImgs, f"Invalid tile filename: \"{filename}\""
        self._brushTileName = filename


class TileDetailsModel:
    
    # Model responsible for handling tile data from JSON files.
    
    def __init__(self):
        self.tile_data = {}

    def load_tile_data(self, tile_name: str) -> dict:
        """
        Loads tile properties from a JSON file.
		tile_name: The name of the tile without prefix or file extension.
        returns: A dictionary with tile properties.
        """
        tile_base_name = jns.ConvertToCamelCase(tile_name.replace(".png", ""))
        tile_json_path = os.path.join(jns.PATH_ASSETS_TEXTURES_LEVELTILES, tile_base_name + "_data.json")

        if os.path.exists(tile_json_path):
            with open(tile_json_path, "r") as json_file:
                self.tile_data = json.load(json_file)
        else:
            print(f"Warning: No JSON data found for tile: {tile_base_name}")
            self.tile_data = {}  # Reset data

        return self.tile_data


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
    
        # Resizes the map while preserving existing tiles where possible.
        
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

    def WriteTile(self, filename: str, gridX: int, gridY: int) -> None:

        # Places a tile on the grid at the given position.
        
        if 0 <= gridX < self.width and 0 <= gridY < self.height:
            self.grid[gridY][gridX] = filename
