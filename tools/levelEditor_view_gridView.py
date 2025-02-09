# language imports
import tkinter as tk
import tkinter.ttk as ttk

# game imports
import jnscommon as jns

class GridView:

	def __init__(self, parent: tk.Tk, column: int, row: int, columnspan: int = 1, rowspan: int = 1, sticky: str = "NSEW") -> None:
		
		# create the parent frame and place it in the gui
		self._w_parentFrame: ttk.Labelframe = ttk.Labelframe(parent, text="Grid View")
		self._w_parentFrame.grid(column=column, row=row,
						   columnspan=columnspan, rowspan=rowspan,
						   sticky=sticky)
		
		# create the canvas and place it in the gui
		self._w_canvas: tk.Canvas = tk.Canvas(self._w_parentFrame)
		self._w_canvas.grid(column=0, row=0, sticky="NSEW")

		# create the scrollbars
		self._w_scrollH: ttk.Scrollbar = ttk.Scrollbar(self._w_parentFrame, orient=tk.HORIZONTAL)
		self._w_scrollV: ttk.Scrollbar = ttk.Scrollbar(self._w_parentFrame, orient=tk.VERTICAL)

		# make the scrollbars work
		self._w_canvas.config(xscrollcommand=self._w_scrollH.set, yscrollcommand=self._w_scrollV.set)
		self._w_scrollH.config(command=self._w_canvas.xview)
		self._w_scrollV.config(command=self._w_canvas.yview)

		# place the scrollbars in the gui
		self._w_scrollH.grid(column=0, row=1, sticky="NSEW")
		self._w_scrollV.grid(column=1, row=0, sticky="NSEW")

	def ResizeCanvas(self, newTileWidth: int, newTileHeight: int) -> None:
		pass