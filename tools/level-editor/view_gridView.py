# language imports
import tkinter as tk
import tkinter.ttk as ttk

# game imports
import jnscommon as jns

class GridView:

	def __init__(self, parent: tk.Tk, column: int, row: int, columnspan: int = 1, rowspan: int = 1, sticky: str = "NSEW") -> None:

		#############
		# constants #
		#############

		self._EMPTY_TAG: str = "empty"
		self._GRIDLINE_TAG: str = "gridline"
		self._COORDS_TAG: str = "coords"

		###################
		# everything else #
		###################
		
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

	#####################
	# private functions #
	#####################

	def _GetPosTag(self, gridX: int, gridY: int) -> str:
		return f"{gridX},{gridY}"
	
	def _SetCanvasObjectBindings(self, canvasObject, drawBinding, eraseBinding) -> None:
		self._w_canvas.tag_bind(canvasObject, "<Button-1>", drawBinding)
		self._w_canvas.tag_bind(canvasObject, "<Button-3>", eraseBinding)

	def CanvasDraw(self, image: tk.PhotoImage, gridX: int, gridY: int, tileSize: int, drawBinding, eraseBinding) -> None:
		print(f"canvas draw at pixel ({gridX * tileSize}, {gridY * tileSize})")
		self._DrawImageAtGridPos(image, gridX, gridY, tileSize, drawBinding, eraseBinding)
		# TODO: finish this function

	def CanvasErase(self, gridX: int, gridY: int, tileSize: int, drawBinding, eraseBinding) -> None:
		print(f"canvas erase at pixel ({gridX * tileSize}, {gridY * tileSize})")
		self._DrawSquareAtGridPos(gridX, gridY, tileSize, drawBinding, eraseBinding)
		# TODO: finish this function

	####################
	# public functions #
	####################

	def ResizeCanvas(self, newPixelWidth: int, newPixelHeight: int) -> None:
		canvasLeftX: int = 0
		canvasTopY: int = 0
		canvasRightX: int = newPixelWidth
		canvasBottomY: int = newPixelHeight
		self._w_canvas.config(scrollregion=(canvasLeftX, canvasTopY, canvasRightX, canvasBottomY),
						width=min(newPixelWidth, 1280), height=min(newPixelHeight, 720))
		# TODO: replace the 1280 and 720 with numbers calculated based on the user's screen size
		
	def _DrawImageAtGridPos(self, image: tk.PhotoImage, gridX: int, gridY: int, tileSize: int, drawBinding, eraseBinding) -> None:
		# delete what was there before
		objectTag: str = self._GetPosTag(gridX, gridY)
		itemsWithTag: list = self._w_canvas.find_withtag(objectTag)
		print(itemsWithTag)
		assert len(itemsWithTag) == 0 or len(itemsWithTag) == 1
		self._w_canvas.delete(objectTag)
		print(f"deleted {len(itemsWithTag)} items with tag \"{objectTag}\"")

		# draw the image on the grid and set its input bindings
		canvasObject = self._w_canvas.create_image(gridX * tileSize, gridY * tileSize,
											 image=image,
											 anchor='nw',
											 tags=(image.name, objectTag))
		self._SetCanvasObjectBindings(canvasObject, drawBinding, eraseBinding)
		
	def _DrawSquareAtGridPos(self, gridX: int, gridY: int, tileSize: int, drawBinding, eraseBinding) -> None:
		# delete what was there before
		objectTag: str = self._GetPosTag(gridX, gridY)
		itemsWithTag: list = self._w_canvas.find_withtag(objectTag)
		# print(itemsWithTag)
		assert len(itemsWithTag) == 0 or len(itemsWithTag) == 1
		self._w_canvas.delete(objectTag)
		# print(f"deleted {len(itemsWithTag)} items with tag \"{objectTag}\"")

		# replace erased item with an empty square and set its input bindings
		x0: int = gridX * tileSize
		y0: int = gridY * tileSize
		x1: int = x0 + tileSize - 1
		y1: int = y0 + tileSize - 1
		canvasObject = self._w_canvas.create_rectangle(x0, y0, x1, y1,
												 fill="white", # fill the square with white
												 width=0, # TODO: should squares have no outline?
												 tags=(self._EMPTY_TAG, objectTag))
		self._SetCanvasObjectBindings(canvasObject, drawBinding, eraseBinding)
