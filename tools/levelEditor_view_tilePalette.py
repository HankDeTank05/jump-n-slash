# imports go here# language imports
import tkinter as tk
import tkinter.ttk as ttk

# game imports
import jnscommon as jns

class TilePaletteView:

	def __init__(self, parent: tk.Tk, column: int, row: int, columnspan: int = 1, rowspan: int = 1, sticky: str = "NSEW") -> None:
		
		# create the parent frame
		self._w_parentFrame: ttk.Labelframe = ttk.Labelframe(parent, text="Tile Palette")
		self._w_parentFrame.grid(column=column, row=row,
						   columnspan=columnspan, rowspan=rowspan,
						   sticky=sticky)

		# create the notebook
		self._w_notebook: ttk.Notebook = ttk.Notebook(self._w_parentFrame)
		self._w_notebook.grid(column=0, row=0)

		# create notebook page frame collection
		#						  page name		corresponding frame
		#								  vvv  vvvvvvvvv
		self._wc_notebookPageFrames: dict[str, ttk.Frame] = {}

		# create the notebook button collection
		#					page name    list of buttons on that page
		#						   vvv  vvvvvvvvvvvvvvvv
		self._wc_tileButtons: dict[str, list[ttk.Button]] = {}

	def AddNotebookPages(self, pageNames: list[str]) -> None:
		for name in pageNames:
			self._AddNotebookPage(name)

	def _AddNotebookPage(self, pageName: str) -> None:
		frame: ttk.Frame = ttk.Frame(self._w_notebook)
		frame.grid(column=0, row=0)
		self._w_notebook.add(frame, text=pageName)
		self._wc_notebookPageFrames[pageName] = frame

	def AddTileToNotebookPage(self, pageName: str, img: tk.PhotoImage, callback) -> None:
		assert pageName in self._wc_notebookPageFrames.keys()
		parentFrame: ttk.Frame = self._wc_notebookPageFrames[pageName]

		# if the given page name has no entry in the dict, create it
		if pageName not in self._wc_tileButtons.keys():
			self._wc_tileButtons[pageName] = []

		# create the button and place it in its parent frame
		button: ttk.Button = ttk.Button(parentFrame, image=img, command=callback)
		MAX_COLUMNS: int = 25 # TODO: come back and make this a dynamically generated number based on screen size
		listLen: int = len(self._wc_tileButtons[pageName])
		columnNum: int = listLen % MAX_COLUMNS
		rowNum: int = listLen // MAX_COLUMNS
		button.grid(column=columnNum, row=rowNum)

		# add the button to the dict
		self._wc_tileButtons[pageName].append(button)



	# TODO: (henry) tile palette gui code