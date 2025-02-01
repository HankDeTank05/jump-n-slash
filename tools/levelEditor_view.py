# language imports
import tkinter as tk

# game imports
from levelEditor_view_tilePalette import TilePaletteView
from levelEditor_view_tileDetails import TileDetailsView
from levelEditor_view_editorOptions import EditorOptionsView
from levelEditor_view_gridView import GridView
from levelEditor_view_layerSelector import LayerSelectorView

class View:

	def __init__(self, parent: tk.Tk) -> None:
		# create the menu bar
		# TODO: (henry) carry over menu bar gui code

		# create the other gui elements
		self.tilePalette: TilePaletteView = TilePaletteView(parent,
													  column=0, row=2,
													  columnspan=3)
		self.tileDetails: TileDetailsView = TileDetailsView(parent,
													  column=2, row=0,
													  rowspan=2)
		self.editorOptions: EditorOptionsView = EditorOptionsView(parent,
															column=1, row=1)
		self.gridView: GridView = GridView(parent,
									 column=1, row=1)
		self.layerSelector: LayerSelectorView = LayerSelectorView(parent,
															column=0, row=0,
															rowspan=2)