# language imports
import tkinter as tk
import json
import os.path

# game imports
import jnscommon as jns

# level editor imports
from levelEditor_layerSelector import GuiLayerSelector
from levelEditor_gridView import GuiGridView
from levelEditor_editorOptions import GuiEditorOptions
from levelEditor_tilePalette import GuiTilePalette
from levelEditor_tileDetails import GuiTileDetailsPanel

class GuiLevelEditorApp:

	def __init__(self) -> None:
		self.root: tk.Tk = tk.Tk()
		self.root.title("Level Editor")
		# self.root.geometry("1920x1080") # TODO: come back to this later once the editor is mostly finished
		self.root.state("normal") # "normal" will be windowed, "zoomed" will be maximized

		############################
		# create the non-gui stuff #
		############################

		# constants
		self._PADX: int = 0
		self._PADY: int = 0

		# non-constants
		
		fileList: list[str] = jns.GetFilesWithConvention(jns.READ_LOCATION_TEXTURES_LEVELTILES, jns.CONVENTION_SPR_LEVELTILE)

		# a dict where the key is the filename, and the value is the corresponding tk.PhotoImage
		self.tileImgs: dict[str, tk.PhotoImage] = {}
		self._LoadAllImages(fileList)
		# jns.PrintDict(self.tileImgs)

		self.brushTileName: str
		
		########################
		# create the gui stuff #
		########################

		# create the menu bar
		self.root.option_add("*tearOff", tk.FALSE)
		self.menuBar: tk.Menu = tk.Menu(self.root)
		self.root.config(menu=self.menuBar)

		# File menu
		self.fileMenu = tk.Menu(self.menuBar)
		self.fileMenu.add_command(label="New") # TODO: add a command to make this do something
		self.fileMenu.add_command(label="Save (ctrl + s)", command=self.Save)
		self.fileMenu.add_command(label="Open (ctrl + o)", command=self.Load)
		self.fileMenu.add_separator()
		self.fileMenu.add_command(label="Exit") # TODO: add a command to make this do something
		self.menuBar.add_cascade(label="File", menu=self.fileMenu)
	
        # Edit menu
		self.editMenu = tk.Menu(self.menuBar)
		self.editMenu.add_command(label="Undo") # TODO: add a command to make this do something
		self.editMenu.add_command(label="Redo") # TODO: add a command to make this do something
		self.editMenu.add_separator()
		self.editMenu.add_command(label="Clear") # TODO: add a command to make this do something
		self.menuBar.add_cascade(label="Edit", menu=self.editMenu)

 		# View menu
		self.viewMenu = tk.Menu(self.menuBar)
		self.viewMenu.add_command(label="Zoom In") # TODO: add a command to make this do something
		self.viewMenu.add_command(label="Zoom Out") # TODO: add a command to make this do something
		self.viewMenu.add_command(label="Reset Zoom") # TODO: add a command to make this do something
		self.menuBar.add_cascade(label="View", menu=self.viewMenu)

		self.BindKeyboardShortcuts()
		
		# create the layer selector
		self.wc_layerSelector: GuiLayerSelector = GuiLayerSelector(parent=self.root, # the parent widget
															 column=0, row=0, # column/row position in the parent
															 columnspan=1, rowspan=2, # column/row span
															 padx=self._PADX, pady=self._PADY, # padding around the outside of this object's parent frame
															 sticky="NSEW") # which sides should this object's parent frame stick to
		
		# create the grid view
		self.wc_gridView: GuiGridView = GuiGridView(parent=self.root,
											  column=1, row=0,
											  columnspan=1, rowspan=1,
											  padx=self._PADX, pady=self._PADY,
											  sticky="NSEW",
											  fGetTileByNameCallback=self.GetTileByName)

		# create the editor options
		self.wc_editorOptions: GuiEditorOptions = GuiEditorOptions(parent=self.root,
															 column=1, row=1,
															 columnspan=1, rowspan=1,
															 padx=self._PADX, pady=self._PADY,
															 sticky="NSEW")

		# create the tile details panel
		self.wc_tileDetails: GuiTileDetailsPanel = GuiTileDetailsPanel(parent=self.root,
																 column=2, row=0,
																 columnspan=1, rowspan=2,
																 padx=self._PADX, pady=self._PADY,
																 sticky="NSEW")

		# create the tile palette
		self.wc_tilePalette: GuiTilePalette = GuiTilePalette(parent=self.root,
													   column=0, row=2,
													   columnspan=3, rowspan=1,
													   padx=self._PADX, pady=self._PADY,
													   sticky="NSEW",
													   imgs=self.tileImgs,
													   fSelectBrushTileCallback=self.SelectBrushTile)
		
	###################
	# setup functions #
	###################

	def _LoadAllImages(self, fileList: list[str]) -> None:
		for filename in fileList:
			filePath: str = os.path.join(jns.READ_LOCATION_TEXTURES_LEVELTILES, filename)
			self.tileImgs[filename] = tk.PhotoImage(file=filePath, name=filename)

	###############################
	# keyboard shortcut functions #
	###############################

	def BindKeyboardShortcuts(self) -> None:
		print("binding keyboard shortcuts")
		# file menu
		# TODO: bind ctrl+n to the "New" command
		self.root.bind("<Control-s>", self.KeyboardShortcutSave)
		self.root.bind("<Control-o>", self.KeyboardShortcutLoad)
		# TODO: bind ctrl+x to the "Exit" command

		# edit menu
		# TODO: bind ctrl+z to the "Undo" command
		# TODO: bind ctrl+y to the "Redo" command
		# TODO: figure out a binding for the "Clear" command

		# view menu
		# TODO: bind ctrl+= to the "Zoom In" command
		# TODO: bind ctrl+- to the "Zoom Out" command
		# TODO: bind ctrl+r to the "Reset Zoom" command

		# other commands
		# TODO: bind ctrl+up to the "Move to Layer Above" command
		# TODO: bind ctrl+down to the "Move to Layer Below" command
		# TODO: bind ctrl+, to the "Switch to Palette Left" command
		# TODO: bind ctrl+. to the "Switch to Palette Right" command
		# TODO: bind ctrl+1 to the "Cursor Mode: Normal" command
		# TODO: bind ctrl+2 to the "Cursor Mode: Line" command
		# TODO: bind ctrl+3 to the "Cursor Mode: Fill" command
		# TODO: bind ctrl+4 to the "Cursor Mode: Rectangle" command
		# TODO: bind ctrl+5 to the "Cursor Mode: Circle" command

	def KeyboardShortcutSave(self, event: tk.Event) -> None:
		self.Save()

	def KeyboardShortcutLoad(self, event: tk.Event) -> None:
		self.Load()

	#################################
	# gui interoperability funcions #
	#################################

	'''
	called by the tile palette in order to select the brush tile
	'''
	def SelectBrushTile(self, tileFilename: str) -> None:
		self.brushTileName = tileFilename
		print(f"Selected brush tile : \"{self.brushTileName}\"")

		# call a GuiGridView function to update the brush tile image
		self.wc_gridView.SetCurrentBrushTile(self.GetBrushTileImg())
		# TODO: call a GuiTileDetailsPanel function to update the tile details
		self.wc_tileDetails.UpdateTileDetails(self.GetBrushTileImg())

	'''
	called by anyone who needs the image for the current brush tile
	'''
	def GetBrushTileImg(self) -> tk.PhotoImage:
		return self.tileImgs[self.brushTileName]

	'''
	called by anyone who needs to retrieve an image by its filename
	'''
	def GetTileByName(self, filename: str) -> tk.PhotoImage:
		assert filename in self.tileImgs.keys()
		return self.tileImgs[filename]
	
	########################
	# filesystem functions #
	########################

	def Save(self) -> None:
		# NOTE: DO NOT MODIFY THE LOADED DATA IN ANY WAY, SAVE IT TO FILE AS IT WAS RECEIVED FROM GRIDVIEW
		data: dict = self.wc_gridView.GetDataForSaving()
		filename: str = "test.json" # TODO: allow the user to pick the file name
		filePath: str = os.path.join(jns.READ_LOCATION_LEVELDATA, filename)
		with open(file=filePath, mode='w') as jsonFile:
			json.dump(data, jsonFile, indent=4)
		print(f"Saved file: \"{filePath}\"")

	def Load(self) -> None:
		# NOTE: DO NOT MODIFY THE LOADED DATA IN ANY WAY, PASS IT ALONG TO GRIDVIEW AS-IS
		# load data from file
		data: dict[str, any]
		filename: str = "test.json"
		filePath: str = os.path.join(jns.READ_LOCATION_LEVELDATA, filename)
		with open(file=filePath, mode='r') as jsonFile:
			data = json.load(jsonFile)
		print(f"Opened file: \"{filePath}\"")

		# print(f"Loaded the following data from {filePath}")
		# jns.PrintDict(data)

		# pass data along to the GuiGridView
		self.wc_gridView.ReadLoadedData(data)

	##################
	# misc functions #
	##################

	def Run(self) -> None:
		self.root.mainloop()

if __name__ == "__main__":
	# app = Editor()
	# app.mainloop()
	app: GuiLevelEditorApp = GuiLevelEditorApp()
	app.Run()