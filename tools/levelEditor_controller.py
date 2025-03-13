# language imports
import tkinter as tk
from functools import partial

# Game imports
from levelEditor_model import Model
from levelEditor_view import View

class Controller:

	def __init__(self, model: Model, view: View) -> None:
		self.model: Model = model
		self.view: View = view
		self._InitTilePalette()
		self._InitGridView()

	##########################
	# tile palette functions #
	##########################

	def _InitTilePalette(self) -> None:
		#Initialize the tile palette by fetching tile images from the model and setting up the view accordingly.
		
		# Get a list of tile filenames and their corresponding images
		# files: dict[str, tk.PhotoImage] = self.model.GetTileImages()
		filenames: list[str] = self.model.GetAllTileFilenames()

		pageNames: list[str] = list(set([filename.split("_")[0] for filename in filenames]))
		pageNames.sort()
		print(f"Palette tab names: {pageNames}")

		# Create the notebook pages for tile palettes
		self.view.tilePalette.AddNotebookPages(pageNames)

		# Add buttons for each tile
		for pageName in pageNames:
			for filename in filenames:
				if pageName in filename:
					print(filename)
					img: tk.PhotoImage = self.model.GetTileImg(filename)
					self.view.tilePalette.AddTileToNotebookPage(pageName, img, callback=partial(self.SelectTile, img))

	def SelectTile(self, img: tk.PhotoImage) -> None:
		
		# Called when a tile is selected. Loads tile data and updates the details panel.
	
		tileFilename = img.name
		self.model.SelectBrushTile(tileFilename)
		tileData = self.model.LoadTileData(tileFilename)
		self.view.tileDetails.UpdateTileDetails(tileData, img)

	#######################
	# grid view functions #
	#######################

	def _InitGridView(self) -> None:
		grid: list[list[str | None]] = self.model.GetMapGrid()
		width: int = self.model.GetMapWidth()
		height: int = self.model.GetMapHeight()

		self.model.ResizeMap(width, height)
		self.view.gridView.ResizeCanvas(width * self.model.TILE_SIZE, height * self.model.TILE_SIZE)

		for y in range(height):
			for x in range(width):
				assert grid[y][x] is None
				self.view.gridView.CanvasErase(x, y, self.model.TILE_SIZE,
										   partial(self.GridWrite, x, y),
										   partial(self.GridErase, x, y))

	def GridWrite(self, gridX: int, gridY: int, event: tk.Event) -> None:
		print(f"GridWrite at {gridX},{gridY}")
		self.view.gridView.CanvasDraw(self.model.GetBrushTileImg(),
								gridX, gridY, self.model.TILE_SIZE,
								partial(self.GridWrite, gridX, gridY),
								partial(self.GridErase, gridX, gridY))
		self.model.WriteToMap(gridX, gridY)

	def GridErase(self, gridX: int, gridY: int, event: tk.Event) -> None:
		print(f"GridErase at {gridX},{gridY}")
		self.view.gridView.CanvasErase(gridX, gridY, self.model.TILE_SIZE,
								 partial(self.GridWrite, gridX, gridY),
								 partial(self.GridErase, gridX, gridY))
		self.model.EraseFromMap(gridX, gridY)
