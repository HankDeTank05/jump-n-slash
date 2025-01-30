# language imports
import tkinter as tk
import tkinter.ttk as ttk
from functools import partial

class View:

	def __init__(self, parent) -> None:
		self.entitySelector: EntitySelectorView = EntitySelectorView(parent)
		self.animationSelector: AnimationSelectorView = AnimationSelectorView(parent)	

class EntitySelectorView:

	def __init__(self, parent) -> None:
		self._w_containerFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Entity Selector")
		self._w_containerFrame.grid(column=0, row=0, rowspan=2, sticky="NSEW")

		self._w_buttonContainer: tk.Canvas = tk.Canvas(self._w_containerFrame)
		self._w_buttonContainer.grid(column=0, row=0)

		self._w_scrollbar: ttk.Scrollbar = ttk.Scrollbar(self._w_containerFrame, orient=tk.VERTICAL)
		# TODO: make this scrollbar actually do something
		self._w_scrollbar.grid(column=1, row=0)

		self._wc_buttonList: list[ttk.Button] = []

	def PopulateButtonList(self, buttonText: list[str], command) -> None:
		for i in range(len(buttonText)):
			currText: str = buttonText[i]
			button: ttk.Button = ttk.Button(self._w_buttonContainer, text=currText, command=partial(command, currText)) # TODO: set command for entity selector buttons
			button.grid(column=0, row=i)
			self._wc_buttonList.append(button)

class AnimationSelectorView:

	def __init__(self, parent) -> None:
		self._w_containerFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Animation Selector")
		self._w_containerFrame.grid(column=1, row=0, rowspan=2, sticky="NSEW")

		self._w_buttonContainer: tk.Canvas = tk.Canvas(self._w_containerFrame)
		self._w_buttonContainer.grid(column=0, row=0)

		self._w_scrollbar: ttk.Scrollbar = ttk.Scrollbar(self._w_containerFrame, orient=tk.VERTICAL)
		# TODO: make this scrollbar actually do something
		self._w_scrollbar.grid(column=1, row=0)

		self._wc_buttonList: list[ttk.Button] = []

	def PopulateButtonList(self, buttonText: list[str]) -> None:
		# delete any buttons that are currently in the list before populating with new buttons
		while len(self._wc_buttonList) > 0:
			self._wc_buttonList[-1].destroy()
			self._wc_buttonList.pop()
		
		# populate the button list
		for i in range(len(buttonText)):
			currText: str = buttonText[i]
			button: ttk.Button = ttk.Button(self._w_buttonContainer, text=currText, command=None) # TODO: set command for animation selector buttons
			button.grid(column=0, row=i)
			self._wc_buttonList.append(button)