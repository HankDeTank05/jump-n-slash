# language imports
import tkinter as tk

# game imports
from view_menuBarAndShortcuts import MenuBar
from view_tilePalette import TilePaletteView
from view_tileDetails import TileDetailsView
from view_editorOptions import EditorOptionsView
from view_gridView import GridView
from view_layerSelector import LayerSelectorView

class View:

	def __init__(self, parent: tk.Tk) -> None:
		# create the menu bar
		self.menuBar: MenuBar = MenuBar(parent)

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
