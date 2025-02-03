# language imports
import tkinter as tk
import tkinter.ttk as ttk

class MenuBar:

	def __init__(self, parent: tk.Tk) -> None:
		# create the menu bar
		parent.option_add("*tearOff", tk.FALSE)
		self.menuBar: tk.Menu = tk.Menu(parent)
		parent.config(menu=self.menuBar)

		self._menu_opts: list[MenuCascade] = [
			MenuBarCascade("File", self.menuBar, [
				MenuCommand("New"),
				MenuSeparator(),
				MenuCommand("Save"),
				MenuCommand("Save as..."),
				MenuSeparator(),
				MenuCommand("Open"),
				MenuCascade("Open recent", [
					MenuCommand("Recent 1"),
					MenuCommand("Recent 2"),
					MenuCommand("Recent 3")
				])
			]),
			MenuBarCascade("Edit", self.menuBar, [
				MenuCommand("Copy"),
				MenuCommand("Cut"),
				MenuCommand("Paste"),
				MenuCommand("Clear"),
				MenuSeparator(),
				MenuCommand("Undo"),
				MenuCommand("Redo"),
				MenuSeparator(),
				MenuCascade("Brush mode", MenuRadioSet(tk.IntVar(), [
					MenuCommand("Normal"),
					MenuCommand("Fill"),
					MenuCommand("Line"),
					MenuCommand("Rectangle"),
					MenuCommand("Circle")
				])),
				MenuSeparator(),
				MenuCommand("Switch to layer above"),
				MenuCommand("Switch to layer below"),
				MenuCommand("Switch to palette left"),
				MenuCommand("Switch to palette right")
			]),
			MenuBarCascade("View", self.menuBar, [
				MenuCommand("Zoom in"),
				MenuCommand("Zoom out"),
				MenuCommand("Reset zoom"),
				MenuSeparator(),
				MenuChecker("Show gridlines", tk.BooleanVar()),
				MenuCascade("Show coordinates", MenuRadioSet(tk.IntVar(), [
					MenuCommand("Never"),
					MenuCommand("On mouse-over"),
					MenuCommand("Always"),
					MenuCommand("Hybrid")
				]))
			])
		]

	##################
	# setup funcions #
	##################

	def _SetupFileMenu(self, parent: tk.Tk) -> None:
		self._fileMenu: tk.Menu = tk.Menu(self.menuBar)
		self.menuBar.add_cascade(label="File", menu=self._fileMenu)

		self._file_new: MenuCommand = MenuCommand(label="New", accelerator="Ctrl N", kbShortcut="<Control-n>")
		self._file_new.AddToParent(parentMenu=self._fileMenu, enabled=False)
		# TODO: bind the keyboard shortcut for file>new

		self._fileMenu.add_separator()

		self._file_save: MenuCommand = MenuCommand(label="Save", accelerator="Ctrl S", kbShortcut="<Control-s>")
		self._file_save.AddToParent(parentMenu=self._fileMenu, enabled=True)
		# TODO: bind the keyboard shortcut for file>save
		
		self._file_saveAs: MenuCommand = MenuCommand(label="Save As...", accelerator="Ctrl Shift S", kbShortcut="<Control-Shift-s>")
		self._file_saveAs.AddToParent(parentMenu=self._fileMenu, enabled=False)
		# TODO: bind the keyboard shortcut for file>save as

		self._fileMenu.add_separator()

		self._file_open: MenuCommand = MenuCommand(label="Open", accelerator="Ctrl O", kbShortcut="<Control-o>")
		self._file_open.AddToParent(parentMenu=self._fileMenu, enabled=True)
		# TODO: bind the keyboard shortcut for file>open

		self.openRecentMenu: tk.Menu = tk.Menu(self._fileMenu) # create the recent files submenu
		self._fileMenu.add_cascade(label="Open Recent", menu=self.openRecentMenu)
		self.openRecentMenu.add_command(label="1st most recent file goes here", state="disabled", accelerator="Ctrl Alt 1") # TODO: add a command to make this do something
		# TODO: bind the keyboard shortcut for file>open recent>recent 1
		self.openRecentMenu.add_command(label="2nd most recent file goes here", state="disabled", accelerator="Ctrl Alt 2") # TODO: add a command to make this do something
		# TODO: bind the keyboard shortcut for file>open recent>recent 2
		self.openRecentMenu.add_command(label="3rd most recent file goes here", state="disabled", accelerator="Ctrl Alt 3") # TODO: add a command to make this do something
		# TODO: bind the keyboard shortcut for file>open recent>recent 3

		self._fileMenu.add_separator()

		self._file_quit: MenuCommand = MenuCommand(label="Quit", accelerator="Ctrl Q", kbShortcut="<Control-q>")
		self._file_quit.AddToParent(parentMenu=self._fileMenu, enabled=False)
		# TODO: bind the keyboard shortcut for file>quit

	def _SetupEditMenu(self, parent: tk.Tk) -> None:
		self.editMenu: tk.Menu = tk.Menu(self.menuBar)

		self.editMenu.add_command(label="Copy", state='disabled', accelerator="Ctrl C") # TODO: add a command to make this do something
		# TODO: bind ctrl+c to the "Copy" command
		self.editMenu.add_command(label="Cut", state='disabled', accelerator="Ctrl X") # TODO: add a command to make this do something
		# TODO: bind ctrl+x to the "Cut" command
		self.editMenu.add_command(label="Paste", state='disabled', accelerator="Ctrl V") # TODO: add a command to make this do something
		# TODO: bind ctrl+v to the "Paste" command
		self.editMenu.add_separator()

		self.editMenu.add_command(label="Undo", state='disabled', accelerator="Ctrl Z") # TODO: add a command to make this do something
		# TODO: bind ctrl+z to the "Undo" command
		self.editMenu.add_command(label="Redo", state='disabled', accelerator="Ctrl Y") # TODO: add a command to make this do something
		# TODO: bind ctrl+y to the "Redo" command
		self.editMenu.add_separator()

		self.editMenu.add_command(label="Clear", command=self.wc_gridView.InitCanvas, accelerator="Ctrl E") # TODO: add a popup warning if changes are unsaved
		parent.bind("<Control-e>", self.KbShortClear)
		self.editMenu.add_separator()

		self.brushModeMenu: tk.Menu = tk.Menu(self.editMenu) # create the cursor mode menu
		self.editMenu.add_cascade(label="Brush Mode", menu=self.brushModeMenu)
		self.brushModeMenu_selection: tk.IntVar = tk.IntVar(value=1)
		self.brushModeMenu.add_radiobutton(label="Normal", variable=self.brushModeMenu_selection, value=1, accelerator="Ctrl 1") # TODO: add a command to make this do something
		# TODO: bind ctrl+1 to the "Cursor Mode: Normal" command
		self.brushModeMenu.add_radiobutton(label="Fill", variable=self.brushModeMenu_selection, value=2, state='disabled', accelerator="Ctrl 2") # TODO: add a command to make this do something
		# TODO: bind ctrl+2 to the "Cursor Mode: Fill" command
		self.brushModeMenu.add_radiobutton(label="Line", variable=self.brushModeMenu_selection, value=3, state='disabled', accelerator="Ctrl 3") # TODO: add a command to make this do something
		# TODO: bind ctrl+3 to the "Cursor Mode: Line" command
		self.brushModeMenu.add_radiobutton(label="Rectangle", variable=self.brushModeMenu_selection, value=4, state='disabled', accelerator="Ctrl 4") # TODO: add a command to make this do something
		# TODO: bind ctrl+4 to the "Cursor Mode: Rectangle" command
		self.brushModeMenu.add_radiobutton(label="Circle", variable=self.brushModeMenu_selection, value=5, state='disabled', accelerator="Ctrl 5") # TODO: add a command to make this do something
		# TODO: bind ctrl+5 to the "Cursor Mode: Circle" command
		self.editMenu.add_separator()

		self.editMenu.add_command(label="Resize Map...", state='disabled') # TODO: add a command to make this do something
		self.editMenu.add_separator()

		self.editMenu.add_command(label="Switch to layer above", state='disabled', accelerator="Ctrl Up") # TODO: add a command to make this do something
		# TODO: bind ctrl+up to the "Switch to Layer Above" command
		self.editMenu.add_command(label="Switch to layer below", state='disabled', accelerator="Ctrl Down") # TODO: add a command to make this do something
		# TODO: bind ctrl+down to the "Switch to Layer Below" command
		self.editMenu.add_command(label="Switch to palette left", state='disabled', accelerator="Ctrl Left") # TODO: add a command to make this do something
		# TODO: bind ctrl+left to the "Switch to Palette Left" command
		self.editMenu.add_command(label="Switch to palette right", state='disabled', accelerator="Ctrl Right") # TODO: add a command to make this do something
		# TODO: bind ctrl+right to the "Switch to Palette Right" command

		# add the above options to the edit menu
		self.menuBar.add_cascade(label="Edit", menu=self.editMenu)

	def _SetupViewMenu(self, parent: tk.Tk) -> None:
		self.viewMenu: tk.Menu = tk.Menu(self.menuBar)

		self.viewMenu.add_command(label="Zoom In", state='disabled', accelerator="Ctrl =") # TODO: add a command to make this do something
		# TODO: bind ctrl+= to the "Zoom In" command
		self.viewMenu.add_command(label="Zoom Out", state='disabled', accelerator="Ctrl -") # TODO: add a command to make this do something
		# TODO: bind ctrl+- to the "Zoom Out" command
		self.viewMenu.add_command(label="Reset Zoom", state='disabled', accelerator="Ctrl R") # TODO: add a command to make this do something
		# TODO: bind ctrl+r to the "Reset Zoom" command
		self.viewMenu.add_separator()

		self.viewMenu_showGridlinesVar: tk.BooleanVar = tk.BooleanVar(value=self.DEFAULT_SHOW_GRIDLINES)
		self.viewMenu.add_checkbutton(label="Show Gridlines", variable=self.viewMenu_showGridlinesVar, onvalue=tk.TRUE, offvalue=tk.FALSE, command=self.wc_gridView.ToggleGridlines)

		self.showCoordsMenu: tk.Menu = tk.Menu(self.viewMenu)
		self.viewMenu.add_cascade(label="Show Coordinates", menu=self.showCoordsMenu)
		self.showCoordsMenu_showTileCoordsVar: tk.IntVar = tk.IntVar(value=self.DEFAULT_SHOW_COORDS)
		self.showCoordsMenu.add_radiobutton(label="Never", variable=self.showCoordsMenu_showTileCoordsVar,			value=0, command=self.wc_gridView.SetCoordsLevel0)
		self.showCoordsMenu.add_radiobutton(label="On Mouse-Over", variable=self.showCoordsMenu_showTileCoordsVar,	value=1, command=self.wc_gridView.SetCoordsLevel1)
		self.showCoordsMenu.add_radiobutton(label="Always", variable=self.showCoordsMenu_showTileCoordsVar,			value=2, command=self.wc_gridView.SetCoordsLevel2)

		# add the above options to the view menu
		self.menuBar.add_cascade(label="View", menu=self.viewMenu)

	#####################
	# binding functions #
	#####################

	def BindKbShortNew(self, parent: tk.Tk, callback) -> None:
		self._file_new.Bind(parent, callback)

	def BindKbShortSave(self, parent: tk.Tk, callback) -> None:
		self._file_save.Bind(parent, callback)

	# TODO: (henry) find a better way to bind these keyboard shortcuts

class MenuCommand:

	def __init__(self, label: str, accelerator: str | None = None, kbShortcut: str | None = None) -> None:
		self._label = label
		self._accel = accelerator
		self._short = kbShortcut

	def AddToParent(self, parentMenu: tk.Menu, enabled: bool) -> None:
		parentMenu.add_command(label=self._label, accelerator=self._accel)
		if enabled:
			self.EnableMenuOption(parentMenu)
		else:
			self.DisableMenuOption(parentMenu)

	def Bind(self, root: tk.Tk, callback) -> None:
		assert self._accel is not None and self._short is not None
		root.bind(self._short, callback)

	# TODO: add a function to unbind a keyboard shortcut

	def EnableMenuOption(self, parentMenu: tk.Menu) -> None:
		parentMenu.entryconfigure(self._label, state=tk.NORMAL)

	def DisableMenuOption(self, parentMenu: tk.Menu) -> None:
		parentMenu.entryconfigure(self._label, state=tk.DISABLED)

	def ToggleEnabled(self, parentMenu: tk.Menu) -> None:
		assert False

class MenuSeparator:

	def __init__(self):
		pass

	def Add(self, parentMenu: tk.Menu) -> None:
		parentMenu.add_separator()

class MenuChecker:

	def __init__(self, label: str, var: tk.BooleanVar) -> None:
		self._label: str = label

class MenuRadioSet:

	def __init__(self, var: tk.IntVar, options: list[MenuCommand]) -> None:
		pass

class MenuCascade:

	def __init__(self, label: str, subOptions: list[MenuCommand] | MenuRadioSet) -> None:
		self._label: str = label

		# TODO: populate the sub-options

	def SetParentMenu(self, parentMenu: tk.Menu) -> None:
		self._menu: tk.Menu = tk.Menu(parentMenu)

class MenuBarCascade:

	def __init__(self, label: str, menuBar: tk.Menu, subOptions: list[MenuCommand | MenuCascade | MenuSeparator]) -> None:
		self._label: str = label
		self._menu: tk.Menu = tk.Menu(menuBar)
		menuBar.add_cascade(label=self._label, menu=self._menu)

		# TODO: populate the sub-options
		# print(self._label)
		for opt in subOptions:
			if isinstance(opt, MenuCommand):
				# print(f"\tcommand: {opt._label}")
				opt.AddToParent(parentMenu=self._menu, enabled=False)
			elif isinstance(opt, MenuCascade):
				# print(f"\tcascade: {opt._label}")
				pass
			elif isinstance(opt, MenuChecker):
				# print(f"\tchecker: {opt._label}")
				pass
			elif isinstance(opt, MenuSeparator):
				# print(f"\tseparator")
				opt.Add(self._menu)
			else:
				assert False