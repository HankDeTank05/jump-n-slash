# language imports
import tkinter as tk
import tkinter.ttk as ttk
from functools import partial

class GuiTilePalette:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, padx: int, pady: int, sticky: str, imgs: dict[str, tk.PhotoImage], fSelectBrushTileCallback: any) -> None:
		############################
		# create the non-gui stuff #
		############################
		
		# constants
		self._NOTEBOOK_PAGE_FRAME_PADX: int = 10
		self._NOTEBOOK_PAGE_FRAME_PADY: int = 10
		
		self._TILE_PADX: int = 5
		self._TILE_PADY: int = 5

		# get a list of files that fit the naming convention
		fileList: list[str] = list(imgs.keys())
		self.tileImgs: dict[str, list[tk.PhotoImage]] = {}

		# get a list of unique palette names from the files
		paletteSet: set[str] = set([filename.split("_")[0] for filename in fileList])
		self.notebookPageNames: list[str] = list(paletteSet)
		self.notebookPageNames.sort()

		# determine the currently selected tile
		fSelectBrushTileCallback(fileList[0])

		########################
		# create the gui stuff #
		########################
		
		# create the parent frame
		self.w_parentFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Tile Palette")
		self.w_parentFrame.grid(column=column, row=row,
						  columnspan=columnspan, rowspan=rowspan,
						  padx=padx, pady=pady,
						  sticky=sticky)

		# create the notebook widget
		self.w_notebook: ttk.Notebook = ttk.Notebook(self.w_parentFrame)
		self.w_notebook.grid(column=0, row=0,
					   sticky="NSEW")

		# create one frame for each of the notebook page names
		self.wc_notebookPageFrames: list[ttk.Frame] = []
		for name in self.notebookPageNames:
			self._AddNotebookPage(name)

		# create the tile images inside of each notebook page
		self.wc_tileButtons: dict[str, list[ttk.Button]] = {}
		for i in range(len(fileList)):
			filename: str = fileList[i]
			pageName: str = filename.split("_")[0] # TODO: there has to be a better way to do this than just duplicating the split code from above
			self._AddTileToNotebookPage(pageName, filename, imgs[filename], i, fSelectBrushTileCallback=fSelectBrushTileCallback)

	def _AddNotebookPage(self, pageName: str) -> None:
		frame: ttk.Frame = ttk.Frame(self.w_notebook)
		frame.grid(column=0, row=0,
			 padx=self._NOTEBOOK_PAGE_FRAME_PADX, pady=self._NOTEBOOK_PAGE_FRAME_PADY)
		self.w_notebook.add(frame, text=pageName)
		self.wc_notebookPageFrames.append(frame)

	def _AddTileToNotebookPage(self, pageName: str, filename: str, img: tk.PhotoImage, columnNum: int, fSelectBrushTileCallback: any) -> None:
		assert pageName in self.notebookPageNames, f"Page name \"{pageName}\" not found!"
		pageIndex: int = self.notebookPageNames.index(pageName)
		parentFrame: ttk.Frame = self.wc_notebookPageFrames[pageIndex]
		
		# add the image to the dict
		if pageName not in self.tileImgs.keys():
			self.tileImgs[pageName] = []
		self.tileImgs[pageName].append(img)
		
		# create the button using the image that was just created
		button: ttk.Button = ttk.Button(parentFrame, image=img, command=partial(fSelectBrushTileCallback, filename)) 
		button.grid(column=columnNum, row=0,
			  padx=self._TILE_PADX, pady=self._TILE_PADY)

		# add the button to the dict
		if pageName not in self.wc_tileButtons.keys():
			self.wc_tileButtons[pageName] = []
		self.wc_tileButtons[pageName].append(button)

	def GetSelectedTile(self) -> str:
		return self.currTile
