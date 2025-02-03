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

	# TODO: (henry) tile palette controller code
	# TODO: (len) tile details controller code
