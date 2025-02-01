# language imports
import tkinter as tk
import tkinter.ttk as ttk
from functools import partial

# app imports
from spriteConnectorEditor_model import Point

class View:

	def __init__(self, parent: tk.Tk) -> None:
		self.entitySelector: EntitySelectorView = EntitySelectorView(parent)
		self.animSelector: AnimationSelectorView = AnimationSelectorView(parent)	
		self.sprSelector: SpriteSelectorView = SpriteSelectorView(parent)
		self.ptSelector: PointSelectorView = PointSelectorView(parent)

class EntitySelectorView:

	def __init__(self, parent: tk.Tk) -> None:
		self._w_containerFrame: ttk.Labelframe = ttk.Labelframe(parent, text="Entity Selector")
		self._w_containerFrame.grid(column=0, row=0, rowspan=2, sticky="NSEW")

		self._w_buttonContainer: tk.Canvas = tk.Canvas(self._w_containerFrame)
		self._w_buttonContainer.grid(column=0, row=0)

		self._w_scrollbar: ttk.Scrollbar = ttk.Scrollbar(self._w_containerFrame, orient=tk.VERTICAL)
		# TODO: make this scrollbar actually do something
		self._w_scrollbar.grid(column=1, row=0, sticky="NS")

		self._wc_buttonList: list[ttk.Button] = []

	def PopulateButtonList(self, buttonText: list[str], cmd) -> None:
		for i in range(len(buttonText)):
			currText: str = buttonText[i]
			button: ttk.Button = ttk.Button(self._w_buttonContainer, text=currText, command=partial(cmd, currText)) # TODO: set command for entity selector buttons
			button.grid(column=0, row=i)
			self._wc_buttonList.append(button)

class AnimationSelectorView:

	def __init__(self, parent: tk.Tk) -> None:
		self._w_containerFrame: ttk.Labelframe = ttk.Labelframe(parent, text="Animation Selector")
		self._w_containerFrame.grid(column=1, row=0, rowspan=2, sticky="NSEW")

		self._w_buttonContainer: tk.Canvas = tk.Canvas(self._w_containerFrame)
		self._w_buttonContainer.grid(column=0, row=0)

		self._w_scrollbar: ttk.Scrollbar = ttk.Scrollbar(self._w_containerFrame, orient=tk.VERTICAL)
		# TODO: make this scrollbar actually do something
		self._w_scrollbar.grid(column=1, row=0, sticky="NS")

		self._wc_buttonList: list[ttk.Button] = []

	def PopulateButtonList(self, buttonText: list[str], cmd) -> None:
		# delete any buttons that are currently in the list before populating with new buttons
		self.DepopulateButtonList()
		
		# populate the button list
		for i in range(len(buttonText)):
			currText: str = buttonText[i]
			button: ttk.Button = ttk.Button(self._w_buttonContainer, text=currText, command=partial(cmd, currText))
			button.grid(column=0, row=i)
			self._wc_buttonList.append(button)

	def DepopulateButtonList(self) -> None:
		while len(self._wc_buttonList) > 0:
			self._wc_buttonList[-1].destroy()
			self._wc_buttonList.pop()

class SpriteSelectorView: 

	def __init__(self, parent: tk.Tk) -> None:
		self._w_containerFrame: ttk.Labelframe = ttk.Labelframe(parent, text="Sprite Selector")
		self._w_containerFrame.grid(column=2, row=1, columnspan=2, sticky="NSEW")

		self._w_buttonContainer: tk.Canvas = tk.Canvas(self._w_containerFrame)
		self._w_buttonContainer.grid(column=0, row=0)

		self._w_scrollbar: ttk.Scrollbar = ttk.Scrollbar(self._w_containerFrame, orient=tk.HORIZONTAL)
		# TODO: make this scrollbar actually do something
		self._w_scrollbar.grid(column=0, row=1, sticky="EW")

		self._wc_buttonList: list[ttk.Button] = []

	def PopulateButtonList(self, buttonText: list[str], buttonImg: list[tk.PhotoImage], cmd) -> None:
		# delete any buttons that are currently in the list before populating with new buttons
		self.DepopulateButtonList()

		# populate the button list
		assert len(buttonText) == len(buttonImg)
		for i in range(len(buttonText)):
			currText: str = buttonText[i]
			currImg: tk.PhotoImage = buttonImg[i]
			button: ttk.Button = ttk.Button(self._w_buttonContainer, text=currText, image=currImg, compound=tk.BOTTOM, command=partial(cmd, currText)) # TODO: set command for sprite selector buttons
			button.grid(column=i, row=0)
			self._wc_buttonList.append(button)

	def DepopulateButtonList(self) -> None:
		while len(self._wc_buttonList) > 0:
			self._wc_buttonList[-1].destroy()
			self._wc_buttonList.pop()

class PointSelectorView:
	
	def __init__(self, parent: tk.Tk) -> None:
		self._w_containerFrame: ttk.Labelframe = ttk.Labelframe(parent, text="Point Selector")
		self._w_containerFrame.grid(column=3, row=0, sticky="NSEW")

		self._w_itemContainer: tk.Canvas = tk.Canvas(self._w_containerFrame)
		self._w_itemContainer.grid(column=0, row=0)

		self._w_scrollbar: ttk.Scrollbar = ttk.Scrollbar(self._w_containerFrame, orient=tk.VERTICAL)
		# TODO: make this scrollbar actually do something
		self._w_scrollbar.grid(column=1, row=0)

		self._wc_itemList: list[PointItem] = []

		self._w_addPtBtn: ttk.Button = ttk.Button(self._w_containerFrame, text="Add Point", state='disabled', command=None) # NOTE: command is set by self.SetAddPointCommand() function
		self._w_addPtBtn.grid(column=0, row=1, sticky="NSEW")

	def PopulateItemList(self, ptList: list[Point]) -> None:
		# delete any items that are currently in the list before populating it with new items
		self.DepopulateItemList()

		# populate the item list
		for i in range(len(ptList)):
			currPt: Point = ptList[i]
			item: PointItem = PointItem(self._w_itemContainer, i, currPt)
			self._wc_itemList.append(item)

	def DepopulateItemList(self) -> None:
		while len(self._wc_itemList) > 0:
			self._wc_itemList[-1].Destroy()
			self._wc_itemList.pop()

	def SetAddPointCommand(self, addPtCmd) -> None:
		ptName: str = "test point"
		self._w_addPtBtn.config(command=partial(addPtCmd, ptName))

	def EnableAddPointButton(self) -> None:
		self._w_addPtBtn.config(state='normal')

	def DisableAddPointButton(self) -> None:
		self._w_addPtBtn.config(state='disabled')

class PointItem:

	SPRITE_SIZE: float = 32.0

	def __init__(self, parent: tk.Canvas, rowNum: int, point: Point) -> None:
		self._w_containerFrame: ttk.Frame = ttk.Frame(parent)
		self._w_containerFrame.grid(column=0, row=rowNum, sticky="NSEW")

		self._w_nameLabel: ttk.Label = ttk.Label(self._w_containerFrame, text=point.name)
		self._w_nameLabel.grid(column=0, row=0, columnspan=2, sticky="NSEW")

		self._w_xLabel: ttk.Label = ttk.Label(self._w_containerFrame, text="X")
		self._w_xLabel.grid(column=0, row=1, sticky="NSEW")
		self._xVar: tk.DoubleVar = tk.DoubleVar(value=point.x, name=f"{point.name} x")
		self._w_xBox: ttk.Spinbox = ttk.Spinbox(self._w_containerFrame,
										  from_=0.0, to=PointItem.SPRITE_SIZE, increment=0.1,
										  textvariable=self._xVar) # TODO: configure the spinbox for the point x-pos
		self._w_xBox.grid(column=1, row=1, sticky="NSEW")

		self._w_yLabel: ttk.Label = ttk.Label(self._w_containerFrame, text="Y")
		self._w_yLabel.grid(column=0, row=2, sticky="NSEW")
		self._yVar: tk.DoubleVar = tk.DoubleVar(value=point.y, name=f"{point.name} y")
		self._w_yBox: ttk.Spinbox = ttk.Spinbox(self._w_containerFrame,
										  from_=0.0, to=PointItem.SPRITE_SIZE, increment=0.1,
										  textvariable=self._yVar) # TODO: configure the spinbox for the point y-pos
		self._w_yBox.grid(column=1, row=2, sticky="NSEW")

		self._w_setButton: ttk.Button = ttk.Button(self._w_containerFrame, text="Set") # TODO: set a command for this button
		self._w_setButton.grid(column=0, row=3, columnspan=2, sticky="NSEW")

	def Destroy(self) -> None:
		self._w_containerFrame.destroy()