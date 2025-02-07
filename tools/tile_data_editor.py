# language imports
import os.path
import json
import tkinter as tk
import tkinter.ttk as ttk
from tkinter import filedialog
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

# keys for tile info
KEY_INFO: str = "info"
KEY_INFO_NAME: str = "name"

# keys for tile properties
KEY_PROPS: str = "properties"
KEY_PROPS_DMG_TO_PLAYER: str = "damage to player"
KEY_PROPS_DMG_TO_ENEMIES: str = "damage to enemies"
KEY_PROPS_DMG_TO_NPCS: str = "damage to npcs"
KEY_PROPS_BREAKABLE: str = "breakable"
KEY_PROPS_SOLID_TOP: str = "solid on top"
KEY_PROPS_SOLID_SIDES: str = "solid on sides"
KEY_PROPS_SOLID_BOTTOM: str = "solid on bottom"

# keys for tile skins
KEY_SKINS: str = "skins"

# padding settings
UNIVERSAL_PADX: int = 10
UNIVERSAL_PADY: int = 10

class GuiTileInfo:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int) -> None:
		############################
		# create the non-gui stuff #
		############################

		self.Reset() # this does all of the non-gui variable initialization, so even though the name of the function doesn't fit it's usage here, it's ok to use

		########################
		# create the gui stuff #
		########################

		# tile name (label)
		self.w_name_label: ttk.Label = ttk.Label(parent, text="Name")
		self.w_name_label.grid(column=0, row=0, sticky="W")

		# tile name (entry)
		self.w_name_entry: ttk.Entry = ttk.Entry(parent,
										   textvariable=self.nameVar)
		self.w_name_entry.grid(column=1, row=0, sticky="E")
		
		# make it print every time the entry text is changed
		self.nameVar.trace_add("write", partial(self._DebugEntryValue, "name entry contents", self.w_name_entry))

	#########
	# debug #
	#########

	def _DebugEntryValue(self, name: str, entry: ttk.Entry, *args) -> None:
		print(f"{name} : {entry.get()}")

	#############
	# accessors #
	#############
	
	def GetTileName(self) -> str:
		return self.w_name_entry.get()

	def GetData(self) -> dict[str, str]:
		data: dict[str, str] = {
			KEY_INFO_NAME: self.GetTileName()
		}
		return data

	############
	# mutators #
	############

	def SetTileInfo(self, data: dict[str, str]) -> None:
		print("tile info received")
		self.nameVar.set(data[KEY_INFO_NAME])

	def Reset(self) -> None:
		self.nameVar: tk.StringVar = tk.StringVar(name="nameVar", value="")

class GuiTileProperties:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int) -> None:
		############################
		# create the non-gui stuff #
		############################
		
		self.Reset() # this does all of the non-gui variable initialization, so even though the name of the function doesn't fit it's usage here, it's ok to use
		
		########################
		# create the gui stuff #
		########################

		# damage stuff #
		# vvvvvvvvvvvv #
		
		# create the damage labelframe
		self.w_dmgLFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Damage")
		self.w_dmgLFrame.grid(column=0, row=0,
						sticky="NSEW",
						padx=UNIVERSAL_PADX, pady=UNIVERSAL_PADY, ipadx=UNIVERSAL_PADX, ipady=UNIVERSAL_PADY)

		# create the stuff inside the damage labelframe

		# to player (label)
		self.w_dmg_label_toPlayer: ttk.Label = ttk.Label(self.w_dmgLFrame, text="To Player")
		self.w_dmg_label_toPlayer.grid(column=0, row=0,
								 sticky="W",
								 padx=UNIVERSAL_PADX)
		# to player (spinbox)
		self.w_dmg_counter_toPlayer: ttk.Spinbox = ttk.Spinbox(self.w_dmgLFrame,
														 textvariable=self.dmgToPlayerVar,
														 from_=0.0, to=9999.0,
														 command=partial(self._DebugSpinboxValue, self.dmgToPlayerVar)) # TODO: make this do something
		self.w_dmg_counter_toPlayer.grid(column=1, row=0,
								   sticky="E")

		# to enemies (label)
		self.w_dmg_label_toEnemies: ttk.Label = ttk.Label(self.w_dmgLFrame, text="To Enemies")
		self.w_dmg_label_toEnemies.grid(column=0, row=1,
								  sticky="W",
								  padx=UNIVERSAL_PADX)
		# to enemies (spinbox)
		self.w_dmg_counter_toEnemies: ttk.Spinbox = ttk.Spinbox(self.w_dmgLFrame,
														  textvariable=self.dmgToEnemiesVar,
														  from_=0.0, to=9999.0,
														  command=partial(self._DebugSpinboxValue, self.dmgToEnemiesVar))
		self.w_dmg_counter_toEnemies.grid(column=1, row=1,
									sticky="E")
		
		# to npcs (label)
		self.w_dmg_label_toNPCs: ttk.Label = ttk.Label(self.w_dmgLFrame, text="To NPCs")
		self.w_dmg_label_toNPCs.grid(column=0, row=2,
							   sticky="W",
							   padx=UNIVERSAL_PADX)
		# to npcs (spinbox)
		self.w_dmg_counter_toNPCs: ttk.Spinbox = ttk.Spinbox(self.w_dmgLFrame,
													   textvariable=self.dmgToNpcsVar,
													   from_=0.0, to=9999.0,
													   command=partial(self._DebugSpinboxValue, self.dmgToNpcsVar))
		self.w_dmg_counter_toNPCs.grid(column=1, row=2,
								 sticky="E")

		# ^^^^^^^^^^^^ #
		# damage stuff #

		# ============================================================================== #
		
		# collision stuff #
		# vvvvvvvvvvvvvvv #
		
		# create the collision labelframe
		self.w_colLFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Collision")
		self.w_colLFrame.grid(column=0, row=1,
						sticky="NSEW",
						padx=UNIVERSAL_PADX, pady=UNIVERSAL_PADY, ipadx=UNIVERSAL_PADX, ipady=UNIVERSAL_PADY)

		# breakable (label)
		self.w_col_label_breakable: ttk.Label = ttk.Label(self.w_colLFrame, text="Breakable")
		self.w_col_label_breakable.grid(column=0, row=0,
								  sticky="W",
								  padx=UNIVERSAL_PADX)
		# breakable (checkbox)
		self.w_col_check_breakable: ttk.Checkbutton = ttk.Checkbutton(self.w_colLFrame,
																variable=self.breakableVar,
																onvalue=True, offvalue=False,
																command=partial(self._DebugCheckValue, self.breakableVar))
		self.w_col_check_breakable.grid(column=1, row=0,
								  sticky="E")

		# solid top (label)
		self.w_col_label_solidTop: ttk.Label = ttk.Label(self.w_colLFrame, text="Solid on top")
		self.w_col_label_solidTop.grid(column=0, row=1,
								 sticky="W",
								 padx=UNIVERSAL_PADX)
		# solid top (checkbox)
		self.w_col_check_solidTop: ttk.Checkbutton = ttk.Checkbutton(self.w_colLFrame,
															   variable=self.solidTopVar,
															   onvalue=True, offvalue=False,
															   command=partial(self._DebugCheckValue, self.solidTopVar))
		self.w_col_check_solidTop.grid(column=1, row=1,
								 sticky="E")

		# solid sides (label)
		self.w_col_label_solidSides: ttk.Label = ttk.Label(self.w_colLFrame, text="Solid on sides")
		self.w_col_label_solidSides.grid(column=0, row=2,
								   sticky="W",
								   padx=UNIVERSAL_PADX)
		# solid sides (checkbox)
		self.w_col_check_solidSides: ttk.Checkbutton = ttk.Checkbutton(self.w_colLFrame,
																 variable=self.solidSidesVar,
																 onvalue=True, offvalue=False,
																 command=partial(self._DebugCheckValue, self.solidSidesVar))
		self.w_col_check_solidSides.grid(column=1, row=2,
								   sticky="E")
		
		# solid bottom (label)
		self.w_col_label_solidBottom: ttk.Label = ttk.Label(self.w_colLFrame, text="Solid on bottom")
		self.w_col_label_solidBottom.grid(column=0, row=3,
									sticky="W",
									padx=UNIVERSAL_PADX)
		# solid bottom (checkbox)
		self.w_col_check_solidBottom: ttk.Checkbutton = ttk.Checkbutton(self.w_colLFrame,
																  variable=self.solidBottomVar,
																  onvalue=True, offvalue=False,
																  command=partial(self._DebugCheckValue, self.solidBottomVar))
		self.w_col_check_solidBottom.grid(column=1, row=3,
									sticky="E")

		# ^^^^^^^^^^^^^^^ #
		# collision stuff #

	#########
	# debug #
	#########

	def _DebugSpinboxValue(self, spinVar: tk.DoubleVar) -> None:
		print(f"{spinVar} : {spinVar.get()}")

	def _DebugCheckValue(self, checkVar: tk.BooleanVar) -> None:
		print(f"{checkVar} : {checkVar.get()}")

	#############
	# accessors #
	#############

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

	def GetData(self) -> dict[str, float | bool]:
		data: dict[str, float | bool] = {
			KEY_PROPS_DMG_TO_PLAYER: self.GetDamageToPlayer(),
			KEY_PROPS_DMG_TO_ENEMIES: self.GetDamageToEnemies(),
			KEY_PROPS_DMG_TO_NPCS: self.GetDamageToNPCs(),
			KEY_PROPS_BREAKABLE: self.IsBreakable(),
			KEY_PROPS_SOLID_TOP: self.IsSolidTop(),
			KEY_PROPS_SOLID_SIDES: self.IsSolidSides(),
			KEY_PROPS_SOLID_BOTTOM: self.IsSolidBottom()
		}
		return data

	############
	# mutators #
	############

	def SetPropData(self, propData: dict[str, bool | float]) -> None:
		self.propData = propData
		print("property data received")
		self._SetWidgetsWithData()

	def Reset(self) -> None:
		# reset all non-gui variables

		self.propData: dict[str, bool | float]

		self.dmgToPlayerVar: tk.DoubleVar = tk.DoubleVar(name="dmgToPlayerVar", value=0)
		self.dmgToEnemiesVar: tk.DoubleVar = tk.DoubleVar(name="dmgToEnemiesVar", value=0)
		self.dmgToNpcsVar: tk.DoubleVar = tk.DoubleVar(name="dmgToNpcsVar", value=0)

		self.breakableVar: tk.BooleanVar = tk.BooleanVar(name="breakableVar", value=False)
		self.solidTopVar: tk.BooleanVar = tk.BooleanVar(name="solidTopVar", value=False)
		self.solidSidesVar: tk.BooleanVar = tk.BooleanVar(name="solidSidesVar", value=False)
		self.solidBottomVar: tk.BooleanVar = tk.BooleanVar(name="solidBottomVar", value=False)

	def _SetWidgetsWithData(self) -> None:
		# change widget states based on data
		self.dmgToPlayerVar.set(self.propData[KEY_PROPS_DMG_TO_PLAYER])
		self.dmgToEnemiesVar.set(self.propData[KEY_PROPS_DMG_TO_ENEMIES])
		self.dmgToNpcsVar.set(self.propData[KEY_PROPS_DMG_TO_NPCS])
		self.breakableVar.set(self.propData[KEY_PROPS_BREAKABLE])
		self.solidTopVar.set(self.propData[KEY_PROPS_SOLID_TOP])
		self.solidSidesVar.set(self.propData[KEY_PROPS_SOLID_SIDES])
		self.solidBottomVar.set(self.propData[KEY_PROPS_SOLID_BOTTOM])

class GuiSkinEditor:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, skinName: str | None, skinFilename: str | None) -> None:
		############################
		# create the non-gui stuff #
		############################

		self.skinName: str
		if skinName is not None:
			self.skinName = skinName
		else:
			self.skinName = ""
		self.skinNameVar: tk.StringVar = tk.StringVar(value=self.skinName)

		self.skinFilename: str
		if skinFilename is not None:
			self.skinFilename = skinFilename
			self.skinFilePath: str = os.path.join(jns.PATH_ASSETS_TEXTURES_LEVELTILES, self.skinFilename)
		else:
			self.skinFilePath = self._InitSelectFile()
			self.skinFilename = self.skinFilePath.split("/")[-1]
		self.skinFilenameVar: tk.StringVar = tk.StringVar(value=self.skinFilename)

		self.icon: tk.PhotoImage = tk.PhotoImage(file=self.skinFilePath)
		
		########################
		# create the gui stuff #
		########################

		# create the container frame
		self.w_frame: ttk.Frame = ttk.Frame(parent, relief="groove")
		self.w_frame.grid(column=column, row=row, columnspan=columnspan, rowspan=rowspan,
					sticky="NSEW",
					padx=UNIVERSAL_PADX, pady=UNIVERSAL_PADY, ipadx=UNIVERSAL_PADX, ipady=UNIVERSAL_PADY)

		# palette name (label)
		self.w_paletteName_label: ttk.Label = ttk.Label(self.w_frame, text="Palette Name")
		self.w_paletteName_label.grid(column=0, row=0,
								padx=UNIVERSAL_PADX, pady=UNIVERSAL_PADY)

		# palette name (entry)
		self.w_paletteName_entry: ttk.Entry = ttk.Entry(self.w_frame, textvariable=self.skinNameVar)
		self.w_paletteName_entry.grid(column=1, row=0, columnspan=2)

		# create separator
		self.w_sep1: ttk.Separator = ttk.Separator(self.w_frame, orient="horizontal")
		self.w_sep1.grid(column=0, row=1, columnspan=3,
				   padx=UNIVERSAL_PADX, pady=UNIVERSAL_PADY, ipadx=30)

		# selected file (label)
		self.w_selectedFile_label: ttk.Label = ttk.Label(self.w_frame, text="Selected File")
		self.w_selectedFile_label.grid(column=0, row=2, rowspan=2)

		# selected file name (label)
		self.w_selectedFile_name_label: ttk.Label = ttk.Label(self.w_frame, textvariable=self.skinFilenameVar)
		self.w_selectedFile_name_label.grid(column=1, row=2, columnspan=2)

		# selected file icon (label)
		self.w_selectedFile_icon_label: ttk.Label = ttk.Label(self.w_frame, image=self.icon)
		self.w_selectedFile_icon_label.grid(column=1, row=3)

		# selected file select (button)
		self.w_selectedFile_replace_button: ttk.Button = ttk.Button(self.w_frame, text="Select...", command=self._SelectFile)
		self.w_selectedFile_replace_button.grid(column=2, row=3)

		# make it print every time any text entry is changed
		self.skinNameVar.trace_add("write", partial(self._DebugEntryValue, "skin name entry", self.w_paletteName_entry))

	#########
	# debug #
	#########

	def _DebugEntryValue(self, name: str, entry: ttk.Entry, *args) -> None:
		print(f"{name} : {entry.get()}")

	#############
	# accessors #
	#############

	def GetSkinName(self) -> str:
		return self.skinNameVar.get()
	
	def GetSkinFilename(self) -> str:
		return self.skinFilenameVar.get()

	############
	# mutators #
	############

	def RemoveAndDestroy(self) -> None:
		self.w_frame.grid_remove()
		self.w_frame.destroy()

	def ChangeGridPos(self, column: int, row: int) -> None:
		self.w_frame.grid(column=column, row=row)

	def _InitSelectFile(self) -> str:
		return filedialog.askopenfilename(initialdir=jns.PATH_ASSETS_TEXTURES_LEVELTILES, filetypes=[("PNG images", "*.png")])

	def _SelectFile(self) -> None:
		# load the image
		self.skinFilePath: str = filedialog.askopenfilename(initialdir=jns.PATH_ASSETS_TEXTURES_LEVELTILES, filetypes=[("PNG images", "*.png")])
		self.icon = tk.PhotoImage(file=self.skinFilePath)
		
		# update the file name in the gui
		self.skinFilenameVar.set(self.skinFilePath.split("/")[-1])
		#self.w_selectedFile_name_label.config(textvariable=self.skinFilenameVar)

		# update the icon in the gui
		self.w_selectedFile_icon_label.config(image=self.icon)

class GuiTileSkins:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int) -> None:
		############################
		# create the non-gui stuff #
		############################

		self.skinData: dict[str, str] = {}
		
		########################
		# create the gui stuff #
		########################
		
		# create the container canvas
		self.w_canvas: tk.Canvas = tk.Canvas(parent)
		self.w_canvas.grid(column=0, row=0,
					 padx=UNIVERSAL_PADX, pady=UNIVERSAL_PADY, ipadx=UNIVERSAL_PADX, ipady=UNIVERSAL_PADY)

		# create skin editor boxes
		self.wc_skinEditors: list[GuiSkinEditor] = []

		# create "delete skin" buttons
		self.wc_deleteSkinBtns: list[ttk.Button] = []

		# TODO: create scrollbar for canvas

		# create "add skin" button
		self.w_addSkinBtn: ttk.Button = ttk.Button(parent, text="Add Skin...", command=partial(self._AddSkinEditor, None, None))
		self.w_addSkinBtn.grid(column=0, row=1,
						 sticky="NSEW",
						 padx=UNIVERSAL_PADX, pady=UNIVERSAL_PADY)

	#############
	# accessors #
	#############

	def GetData(self) -> dict[str, str]:
		data: dict[str, str] = {}
		for editor in self.wc_skinEditors:
			skinName: str = editor.GetSkinName()
			skinFilename: str = editor.GetSkinFilename()
			data[skinName] = skinFilename
		return data

	############
	# mutators #
	############

	def _AddSkinEditor(self, skinName: str | None = None, skinFilename: str | None = None) -> None:
		# determine which row the editor and it's delete button should go in
		row: int = len(self.wc_skinEditors)
		print(f"adding editor for \"{skinName}\" skin to row {row}")

		# create a skin editor
		self.wc_skinEditors.append(GuiSkinEditor(self.w_canvas,
										   column=0, row=row,
										   columnspan=1, rowspan=1,
										   skinName=skinName, skinFilename=skinFilename))
		
		# create a corresponding "delete skin" button
		deleteSkinBtn: ttk.Button = ttk.Button(self.w_canvas, text="Delete Skin", command=partial(self._DeleteSkinEditor, row))
		deleteSkinBtn.grid(column=1, row=row)
		self.wc_deleteSkinBtns.append(deleteSkinBtn)

	def _DeleteSkinEditor(self, i: int) -> None:
		assert len(self.wc_skinEditors) == len(self.wc_deleteSkinBtns)
		assert 0 <= i
		assert i < len(self.wc_skinEditors)

		# remove the skin editor from the list AND the GUI
		notRemovedFromEnd: bool = i < len(self.wc_skinEditors) - 1
		removedSkinEditor: GuiSkinEditor = self.wc_skinEditors.pop(i)
		removedSkinEditor.RemoveAndDestroy()

		# remove the delete button from the list AND the GUI
		removedButton: ttk.Button = self.wc_deleteSkinBtns.pop(i)
		removedButton.grid_remove()

		# sanity check
		assert len(self.wc_skinEditors) == len(self.wc_deleteSkinBtns)

		# if the removed skin editor/button were not the last one in the list, then everything below it should be moved up one row
		if notRemovedFromEnd == True:
			for iEdit in range(i, len(self.wc_skinEditors)):
				# move the skin editor up one row
				skinEditor: GuiSkinEditor = self.wc_skinEditors[iEdit]
				skinEditor.ChangeGridPos(column=0, row=iEdit)

				# move the delete button up one row
				deleteBtn: ttk.Button = self.wc_deleteSkinBtns[iEdit]
				deleteBtn.grid(column=1, row=iEdit)
				# the delete button now has a new index in the list, so it's command needs to be updated to reflect this
				deleteBtn.config(command=partial(self._DeleteSkinEditor, iEdit))

	def _PopulateSkinEditorList(self) -> None:
		# TODO: make this list populate based on data read from json
		keyList: list[str] = list(self.skinData.keys())
		for i in range(len(keyList)):
			key: str = keyList[i]
			val: str = self.skinData[key]
			self._AddSkinEditor(skinName=key, skinFilename=val)

	def SetSkinData(self, skinData: dict[str, str]) -> None:
		self.skinData = skinData
		print("skin data received")
		self._PopulateSkinEditorList()

	def Reset(self) -> None:
		# remove and destroy all existing skin editors, and empty the list
		for skinEditor in self.wc_skinEditors:
			skinEditor.RemoveAndDestroy()
		self.wc_skinEditors = []

		# remove and destroy all existing delete buttons, and empty the list
		for deleteBtn in self.wc_deleteSkinBtns:
			deleteBtn.grid_remove()
			deleteBtn.destroy()
		self.wc_deleteSkinBtns = []

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

		# create the menubar
		self.root.option_add("*tearOff", tk.FALSE)
		self.menubar: tk.Menu = tk.Menu(self.root)
		self.root["menu"] = self.menubar

		# create the file menu
		self.menu_file: tk.Menu = tk.Menu(self.menubar)
		self.menubar.add_cascade(menu=self.menu_file, label="File")
		self.menu_file.add_command(label="Save", command=self._Write)
		self.menu_file.add_command(label="Open...", command=self._Read)
		self.menu_file.add_command(label="New", command=self._New)

		# create the notebook widget
		self.w_notebook: ttk.Notebook = ttk.Notebook(self.root)
		self.w_notebook.grid(column=0, row=0)

		# create one frame for each of the notebook page names
		self.notebookPageNames: list[str] = ["Info", "Properties", "Skins"]
		self.wc_notebookPageFrames: list[ttk.Frame] = []
		for name in self.notebookPageNames:
			self._AddNotebookPage(name)  
  
		self.wc_tileInfo: GuiTileInfo = None
		self.wc_tileProps: GuiTileProperties = None
		self.wc_tileSkins: GuiTileSkins = None
		self._New()

	def _AddNotebookPage(self, pageName: str) -> None:
		frame: ttk.Frame = ttk.Frame(self.w_notebook)
		frame.grid(column=0, row=0,
			 sticky="NSEW")
		self.w_notebook.add(frame, text=pageName)
		self.wc_notebookPageFrames.append(frame)

	def _New(self) -> None:
		# basic info page
		if self.wc_tileInfo is None:
			# create the basic info page
			self.wc_tileInfo = GuiTileInfo(self.wc_notebookPageFrames[0], column=0, row=0, columnspan=1, rowspan=1)
		else:
			# if this is not the first time setup, then reset the existing object
			self.wc_tileInfo.Reset()

		# tile properties page
		if self.wc_tileProps is None:
			# create the properties page
			self.wc_tileProps = GuiTileProperties(self.wc_notebookPageFrames[1], column=0, row=0, columnspan=1, rowspan=1)
		else:
			# if this is not the first time setup, then reset the existing object
			self.wc_tileProps.Reset()

		# tile skins page
		if self.wc_tileSkins is None:
			# create the skins page
			self.wc_tileSkins = GuiTileSkins(self.wc_notebookPageFrames[2], column=0, row=0, columnspan=1, rowspan=1)
		else:
			# if this is not the first time setup, then reset the existing object
			self.wc_tileSkins.Reset()
		
	def _Read(self) -> None:
		# read a selected json file
		filePath: str = filedialog.askopenfilename(initialdir=jns.PATH_ASSETS_TEXTURES_LEVELTILES, filetypes=[("JSON files", "*.json")])
		print(f"opening file: \"{filePath}\"")

		with open(filePath, "r") as jsonFile:
			data: dict[str, str | dict[str, str] | dict[str, bool | float]] = json.load(jsonFile)
			jns.PrintDict(data)
			self.wc_tileInfo.SetTileInfo(data[KEY_INFO])
			self.wc_tileProps.SetPropData(data[KEY_PROPS])
			self.wc_tileSkins.SetSkinData(data[KEY_SKINS])

	def _Write(self) -> None:
		# there needs to be a name in order to save the file
		assert len(self.wc_tileInfo.GetTileName()) > 0 # TODO: if this assert gets triggered, then there needs to be a popup alerting the user

		#                  tile info            properties              skins
		#               vvvvvvvvvvvvvv   vvvvvvvvvvvvvvvvvvvvvvv   vvvvvvvvvvvvvv
		data: dict[str, dict[str, str] | dict[str, float | bool] | dict[str, str]] = {
			KEY_INFO: self.wc_tileInfo.GetData(),
			KEY_PROPS: self.wc_tileProps.GetData(),
			KEY_SKINS: self.wc_tileSkins.GetData()
		}
		filename: str = jns.ConvertToCamelCase(self.wc_tileInfo.GetTileName()) + ".json"
		print(f"filename: \"{filename}\"")
		filePath: str = os.path.join(jns.PATH_ASSETS_TEXTURES_LEVELTILES, filename)
		print(f"filePath: \"{filePath}\"")
		with open(filePath, "w") as jsonFile:
			json.dump(data, jsonFile, indent=4)
			print(f"successfully wrote to \"{filePath}\"")

	def Run(self) -> None:
		self.root.mainloop()


if __name__ == "__main__":
	app: GuiTileDataEditor = GuiTileDataEditor()
	app.Run()