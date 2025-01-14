# language imports
import tkinter as tk
import tkinter.ttk as ttk
from functools import partial

# game imports
import jnscommon as jns

"""
NOTE: IF RUNNING FROM VSCODE, "cd" TO THE FOLDER CONTAINING THIS FILE BEFORE RUNNING TO AVOID PATHING ISSUES
- any class that is a GUI element, prepend "Gui" to the name of the class
    - any class that is a GUI element(s) should take a parent widget in their constructor
    - any class that is a GUI element(s) should take a column, row, columnspan, and rowspan as four ints in their constructor
    - member variables of a class that are a widget should follow this convention: "self.w_<variableName>"
    - member variables of a class that are a collection of widgets should follow this convention "self.wc_<variableName>"
- variable names should always be in camelCase
- always do type hints when declaring variables
- use assert statements LIBERALLY
- use TODO (and regular) comments liberally
    - remember: use comments to describe the meaning of the code, not a restated version of the logic
"""

class GuiTileInfo:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int) -> None:
		############################
		# create the non-gui stuff #
		############################

		# code goes here

		########################
		# create the gui stuff #
		########################

		# tile name (label)
		self.w_name_label: ttk.Label = ttk.Label(parent, text="Name")
		self.w_name_label.grid(column=0, row=0, sticky="W")
		# tile name (entry)
		self.nameVar: tk.StringVar = tk.StringVar(name="nameVar", value="")
		self.w_name_entry: ttk.Entry = ttk.Entry(parent,
										   textvariable=self.nameVar)
		self.w_name_entry.grid(column=1, row=0, sticky="E")
		self.nameVar.trace_add("write", partial(self._DebugEntryValue, "name entry contents", self.w_name_entry))

	def _DebugEntryValue(self, name: str, entryVar: ttk.Entry, *args) -> None:
		print(f"{name} : {entryVar.get()}")

	def GetTileName(self) -> str:
		return self.w_name_entry.get()

class GuiTileProperties:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int) -> None:
		############################
		# create the non-gui stuff #
		############################

		# code goes here
		
		########################
		# create the gui stuff #
		########################

		# damage stuff #
		# vvvvvvvvvvvv #
		
		# create the damage labelframe
		self.w_dmgLFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Damage")
		self.w_dmgLFrame.grid(column=0, row=0, sticky="NSEW")

		# create the stuff inside the damage labelframe

		# to player (label)
		self.w_dmg_label_toPlayer: ttk.Label = ttk.Label(self.w_dmgLFrame, text="To Player")
		self.w_dmg_label_toPlayer.grid(column=0, row=0, sticky="W")
		# to player (spinbox)
		self.dmgToPlayerVar: tk.DoubleVar = tk.DoubleVar(name="dmgToPlayerVar", value=0) # TODO: init this value based on data read from json
		self.w_dmg_counter_toPlayer: ttk.Spinbox = ttk.Spinbox(self.w_dmgLFrame,
														 textvariable=self.dmgToPlayerVar,
														 from_=0.0, to=9999.0,
														 command=partial(self._DebugSpinboxValue, self.dmgToPlayerVar)) # TODO: make this do something
		self.w_dmg_counter_toPlayer.grid(column=1, row=0, sticky="E")

		# to enemies (label)
		self.w_dmg_label_toEnemies: ttk.Label = ttk.Label(self.w_dmgLFrame, text="To Enemies")
		self.w_dmg_label_toEnemies.grid(column=0, row=1, sticky="W")
		# to enemies (spinbox)
		self.dmgToEnemiesVar: tk.DoubleVar = tk.DoubleVar(name="dmgToEnemiesVar", value=0) # TODO: init this value based on data read from json
		self.w_dmg_counter_toEnemies: ttk.Spinbox = ttk.Spinbox(self.w_dmgLFrame,
														  textvariable=self.dmgToEnemiesVar,
														  from_=0.0, to=9999.0,
														  command=partial(self._DebugSpinboxValue, self.dmgToEnemiesVar))
		self.w_dmg_counter_toEnemies.grid(column=1, row=1, sticky="E")
		
		# to npcs (label)
		self.w_dmg_label_toNPCs: ttk.Label = ttk.Label(self.w_dmgLFrame, text="To NPCs")
		self.w_dmg_label_toNPCs.grid(column=0, row=2, sticky="W")
		# to npcs (spinbox)
		self.dmgToNpcsVar: tk.DoubleVar = tk.DoubleVar(name="dmgToNpcsVar", value=0) # TODO: init this value based on data read from json
		self.w_dmg_counter_toNPCs: ttk.Spinbox = ttk.Spinbox(self.w_dmgLFrame,
													   textvariable=self.dmgToNpcsVar,
													   from_=0.0, to=9999.0,
													   command=partial(self._DebugSpinboxValue, self.dmgToNpcsVar))
		self.w_dmg_counter_toNPCs.grid(column=1, row=2, sticky="E")

		# ^^^^^^^^^^^^ #
		# damage stuff #

		# ============================================================================== #
		
		# collision stuff #
		# vvvvvvvvvvvvvvv #
		
		# create the collision labelframe
		self.w_colLFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Collision")
		self.w_colLFrame.grid(column=0, row=1, sticky="NSEW")

		# breakable (label)
		self.w_col_label_breakable: ttk.Label = ttk.Label(self.w_colLFrame, text="Breakable")
		self.w_col_label_breakable.grid(column=0, row=0, sticky="W")
		# breakable (checkbox)
		self.breakableVar: tk.BooleanVar = tk.BooleanVar(name="breakableVar", value=False) # TODO: init this value based on data read from json
		self.w_col_check_breakable: ttk.Checkbutton = ttk.Checkbutton(self.w_colLFrame,
																variable=self.breakableVar,
																onvalue=True, offvalue=False,
																command=partial(self._DebugCheckValue, self.breakableVar))
		self.w_col_check_breakable.grid(column=1, row=0, sticky="E")

		# solid top (label)
		self.w_col_label_solidTop: ttk.Label = ttk.Label(self.w_colLFrame, text="Solid on top")
		self.w_col_label_solidTop.grid(column=0, row=1, sticky="W")
		# solid top (checkbox)
		self.solidTopVar: tk.BooleanVar = tk.BooleanVar(name="solidTopVar", value=False) # TODO: init this value based on data read from json
		self.w_col_check_solidTop: ttk.Checkbutton = ttk.Checkbutton(self.w_colLFrame,
															   variable=self.solidTopVar,
															   onvalue=True, offvalue=False,
															   command=partial(self._DebugCheckValue, self.solidTopVar))
		self.w_col_check_solidTop.grid(column=1, row=1, sticky="E")

		# solid sides (label)
		self.w_col_label_solidSides: ttk.Label = ttk.Label(self.w_colLFrame, text="Solid on sides")
		self.w_col_label_solidSides.grid(column=0, row=2, sticky="W")
		# solid sides (checkbox)
		self.solidSidesVar: tk.BooleanVar = tk.BooleanVar(name="solidSidesVar", value=False) # TODO: init this value based on data read from json
		self.w_col_check_solidSides: ttk.Checkbutton = ttk.Checkbutton(self.w_colLFrame,
																 variable=self.solidSidesVar,
																 onvalue=True, offvalue=False,
																 command=partial(self._DebugCheckValue, self.solidSidesVar))
		self.w_col_check_solidSides.grid(column=1, row=2, sticky="E")
		
		# solid bottom (label)
		self.w_col_label_solidBottom: ttk.Label = ttk.Label(self.w_colLFrame, text="Solid on bottom")
		self.w_col_label_solidBottom.grid(column=0, row=3, sticky="W")
		# solid bottom (checkbox)
		self.solidBottomVar: tk.BooleanVar = tk.BooleanVar(name="solidBottomVar", value=False) # TODO: init this value based on data read from json
		self.w_col_check_solidBottom: ttk.Checkbutton = ttk.Checkbutton(self.w_colLFrame,
																  variable=self.solidBottomVar,
																  onvalue=True, offvalue=False,
																  command=partial(self._DebugCheckValue, self.solidBottomVar))
		self.w_col_check_solidBottom.grid(column=1, row=3, sticky="E")

		# ^^^^^^^^^^^^^^^ #
		# collision stuff #

	def _DebugSpinboxValue(self, spinVar: tk.DoubleVar) -> None:
		print(f"{spinVar} : {spinVar.get()}")

	def _DebugCheckValue(self, checkVar: tk.BooleanVar) -> None:
		print(f"{checkVar} : {checkVar.get()}")

	def GetDamageToPlayer(self) -> float:
		return self.dmgToPlayerVar.get()
	
	def GetDamageToEnemies(self) -> float:
		return self.dmgToEnemiesVar.get()
	
	def GetDamageToNPCs(self) -> float:
		return self.dmgToNpcsVar.get()
	
	def IsBreakable(self) -> bool:
		return self.breakableVar.get()
	
	def IsSolidTop(self) -> bool:
		return self.solidTopVar.get()
	
	def IsSolidSides(self) -> bool:
		return self.solidSidesVar.get()
	
	def IsSolidBottom(self) -> bool:
		return self.solidBottomVar.get()

class GuiSkinEditor:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int) -> None:
		############################
		# create the non-gui stuff #
		############################

		# code goes here
		
		########################
		# create the gui stuff #
		########################

		# create the container frame
		self.w_frame: ttk.Frame = ttk.Frame(parent, relief="groove")
		self.w_frame.grid(column=column, row=row, columnspan=columnspan, rowspan=rowspan)

		# palette name (label)
		self.w_paletteName_label: ttk.Label = ttk.Label(self.w_frame, text="Palette Name")
		self.w_paletteName_label.grid(column=0, row=0)

		# palette name (entry)
		self.w_paletteName_entry: ttk.Entry = ttk.Entry(self.w_frame) # TODO: add text variable
		self.w_paletteName_entry.grid(column=1, row=0, columnspan=2)

		# create separator #1
		self.w_sep1: ttk.Separator = ttk.Separator(self.w_frame, orient="horizontal")
		self.w_sep1.grid(column=0, row=1, columnspan=3)

		# selected file (label)
		self.w_selectedFile_label: ttk.Label = ttk.Label(self.w_frame, text="Selected File")
		self.w_selectedFile_label.grid(column=0, row=2, rowspan=2)

		# selected file name (label)
		self.w_selectedFile_name_label: ttk.Label = ttk.Label(self.w_frame, text="<filename.png>") # TODO: make the text in this label change based on name of selected file
		self.w_selectedFile_name_label.grid(column=1, row=2, columnspan=2)

		# selected file icon (label)
		self.w_selectedFile_icon_label: ttk.Label = ttk.Label(self.w_frame, text="<image icon>") # TODO: make this label display the selected file
		self.w_selectedFile_icon_label.grid(column=1, row=3)

		# selected file replace (button)
		self.w_selectedFile_replace_button: ttk.Button = ttk.Button(self.w_frame, text="Replace...") # TODO: add a command to make this button open the file select dialog
		self.w_selectedFile_replace_button.grid(column=2, row=3)

		# create separator #2
		self.w_sep2: ttk.Separator = ttk.Separator(self.w_frame, orient="horizontal")
		self.w_sep2.grid(column=0, row=4, columnspan=3)

		# delete skin (button)
		self.w_deleteSkin_button: ttk.Button = ttk.Button(self.w_frame, text="Delete Skin") # TODO: add a command to make this button delete the skin
		self.w_deleteSkin_button.grid(column=0, row=5, columnspan=3, sticky="NSEW")

class GuiTileSkins:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int) -> None:
		############################
		# create the non-gui stuff #
		############################

		# code goes here
		
		########################
		# create the gui stuff #
		########################
		
		# create the container canvas
		self.w_canvas: tk.Canvas = tk.Canvas(parent)
		self.w_canvas.grid(column=0, row=0)

		# create skin editor boxes
		self.wc_skinEditors: list[GuiSkinEditor] = []
		self._PopulateSkinEditorList()

		# TODO: create scrollbar for canvas

		# create "add skin" button
		self.w_addSkinBtn: ttk.Button = ttk.Button(parent, text="Add Skin...") # TODO: add a command to make this button open the file select dialog
		self.w_addSkinBtn.grid(column=0, row=1, sticky="NSEW")

	def _PopulateSkinEditorList(self) -> None:
		# TODO: make this list populate based on data read from json
		for i in range(3):
			self.wc_skinEditors.append(GuiSkinEditor(self.w_canvas, column=0, row=i, columnspan=1, rowspan=1))

class GuiTileDataEditor:

	def __init__(self) -> None:
		############################
		# create the non-gui stuff #
		############################

		# code goes here

		########################
		# create the gui stuff #
		########################

		self.root: tk.Tk = tk.Tk()
		self.root.title("Tile Data Editor")

		# create the notebook widget
		self.w_notebook: ttk.Notebook = ttk.Notebook(self.root)
		self.w_notebook.grid(column=0, row=0)

		# create one frame for each of the notebook page names
		self.notebookPageNames: list[str] = ["Info", "Properties", "Skins"]
		self.wc_notebookPageFrames: list[ttk.Frame] = []
		for name in self.notebookPageNames:
			self._AddNotebookPage(name)

		# create the basic info page
		self.wc_tileInfo: GuiTileInfo = GuiTileInfo(self.wc_notebookPageFrames[0], column=0, row=0, columnspan=1, rowspan=1)

		# create the properties page
		self.wc_tileProps: GuiTileProperties = GuiTileProperties(self.wc_notebookPageFrames[1], column=0, row=0, columnspan=1, rowspan=1)

		# create the skins page
		self.wc_tileSkins: GuiTileSkins = GuiTileSkins(self.wc_notebookPageFrames[2], column=0, row=0, columnspan=1, rowspan=1)

	def _AddNotebookPage(self, pageName: str) -> None:
		frame: ttk.Frame = ttk.Frame(self.w_notebook)
		frame.grid(column=0, row=0)
		self.w_notebook.add(frame, text=pageName)
		self.wc_notebookPageFrames.append(frame)

	def _Read(self) -> None:
		# TODO: read a selected json file
		# TODO: assign values based on data read from the json
		assert False

	def _Write(self) -> None:
		#         tile name          properties             skins
		#               vvv   vvvvvvvvvvvvvvvvvvvvvvv   vvvvvvvvvvvvvv
		data: dict[str, str | dict[str, bool | float] | dict[str, str]] = {
			"name": self.wc_tileInfo.GetTileName(),
			"properties": {
				"damage to player": self.wc_tileProps.GetDamageToPlayer(),
				"damage to enemies": self.wc_tileProps.GetDamageToEnemies(),
				"damage to npcs": self.wc_tileProps.GetDamageToNPCs(),
				"breakable": self.wc_tileProps.IsBreakable,
				"solid on top": self.wc_tileProps.IsSolidTop(),
				"solid on sides": self.wc_tileProps.IsSolidSides(),
				"solid on bottom": self.wc_tileProps.IsSolidBottom()
			},
			"skins": {
				"placeholder": "filename.png" # TODO: come back and link this to a variable or function call
			}
		}
		# TODO: write the above dict to a json file
		assert False

	def Run(self) -> None:
		self.root.mainloop()


if __name__ == "__main__":
	app: GuiTileDataEditor = GuiTileDataEditor()
	app.Run()