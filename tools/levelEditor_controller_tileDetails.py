import tkinter as tk
from levelEditor_model_tileDetails import TileDetailsModel
from levelEditor_view_tileDetails import GuiTileDetailsPanel

class TileDetailsController:
    #Controls interactions between the TileDetailsModel and GuiTileDetailsPanel.

    def __init__(self, parent: any):
        self.model = TileDetailsModel()
        self.view = GuiTileDetailsPanel(parent, column=0, row=0, columnspan=1, rowspan=1, padx=10, pady=10, sticky="NSEW")

    def select_tile(self, img: tk.PhotoImage):
        #Loads tile data and updates the GUI when a tile is selected.
       
        tile_name = img.name
        tile_data = self.model.load_tile_data(tile_name)
        self.view.update_tile_details(tile_data, img)