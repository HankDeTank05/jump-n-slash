import tkinter as tk

# Game imports
from levelEditor_model import Model, TileDetailsModel
from levelEditor_view import View, GuiTileDetailsPanel

class Controller:

    def __init__(self, model: Model, view: View) -> None:
        self.model: Model = model
        self.view: View = view
        self.tile_details_model = TileDetailsModel()  # Tile details model
        self.tile_details_panel = GuiTileDetailsPanel(self.view.root, column=1, row=0, columnspan=1, rowspan=1, padx=10, pady=10, sticky="NSEW")  # Tile Details GUI
        self._InitTilePalette()
		self._InitGridView()

	##########################
	# tile palette functions #
	##########################

    def _InitTilePalette(self) -> None:
        #Initialize the tile palette by fetching tile images from the model and setting up the view accordingly.
        
        # Get a list of tile filenames and their corresponding images
        files: dict[str, tk.PhotoImage] = self.model.GetTileImages()

        pageNames: list[str] = list(set([filename.split("_")[0] for filename in files.keys()]))
        pageNames.sort()
        print(f"Palette tab names: {pageNames}")

        # Create the notebook pages for tile palettes
        self.view.tilePalette.AddNotebookPages(pageNames)

        # Add buttons for each tile
        for pageName in pageNames:
            for filename in files.keys():
                if pageName in filename:
                    img: tk.PhotoImage = files[filename]
                    self.view.tilePalette.AddTileToNotebookPage(pageName, img, callback=self.SelectTile)

    def SelectTile(self, img: tk.PhotoImage) -> None:
        
        # Called when a tile is selected. Loads tile data and updates the details panel.
    
        tile_name = img.name
        tile_data = self.tile_details_model.load_tile_data(tile_name)
        self.tile_details_panel.update_tile_details(tile_data, img)

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
