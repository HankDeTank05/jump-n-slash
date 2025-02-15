# language imports
import tkinter as tk

# game imports
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
		# get a list of tile filenames
		files: dict[str, tk.PhotoImage] = self.model.GetTileImages()
		
		# get a list of unique palette names from the files
		# TODO: this is bad form. make this a function in jnscommon.py
		#                                vvvvvvvvvvvvvvvvvvvvvv
		pageNames: list[str] = list(set([filename.split("_")[0] for filename in list(files.keys())]))
		pageNames.sort() # NOTE: we sort this so the palette names appear in alphabetical order
		print(f"palette tab names: {pageNames}")

		# create the notebook pages
		self.view.tilePalette.AddNotebookPages(pageNames)

		# add buttons for tiles
		for pageName in pageNames:
			for filename in list(files.keys()):
				if pageName in filename:
					img: tk.PhotoImage = files[filename]
					self.view.tilePalette.AddTileToNotebookPage(pageName, img, callback=None)

	# TODO: (len) tile details controller code

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
				self.view.gridView.DrawSquareAtGridPos(x, y, self.model.TILE_SIZE)
