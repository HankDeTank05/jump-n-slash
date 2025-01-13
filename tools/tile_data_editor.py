# language imports
import tkinter as tk
import tkinter.ttk as ttk

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

class GuiTileProperties:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int) -> None:
		############################
		# create the non-gui stuff #
		############################

		# code goes here
		
		########################
		# create the gui stuff #
		########################

		print(parent)
		
		# create the damage labelframe
		self.w_dmgLFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Damage")
		self.w_dmgLFrame.grid(column=0, row=0, sticky="NSEW")

		# create the stuff inside the damage labelframe
		self.w_dmg_label_toPlayer: ttk.Label = ttk.Label(self.w_dmgLFrame, text="To Player")
		self.w_dmg_label_toPlayer.grid(column=0, row=0, sticky="W")
		self.w_dmg_counter_toPlayer: ttk.Spinbox = ttk.Spinbox(self.w_dmgLFrame) # TODO: make this do something
		self.w_dmg_counter_toPlayer.grid(column=1, row=0, sticky="E")

		self.w_dmg_label_toEnemies: ttk.Label = ttk.Label(self.w_dmgLFrame, text="To Enemies")
		self.w_dmg_label_toEnemies.grid(column=0, row=1, sticky="W")
		self.w_dmg_counter_toEnemies: ttk.Spinbox = ttk.Spinbox(self.w_dmgLFrame) # TODO: make this do something
		self.w_dmg_counter_toEnemies.grid(column=1, row=1, sticky="E")
		
		self.w_dmg_label_toNPCs: ttk.Label = ttk.Label(self.w_dmgLFrame, text="To NPCs")
		self.w_dmg_label_toNPCs.grid(column=0, row=2, sticky="W")
		self.w_dmg_counter_toNPCs: ttk.Spinbox = ttk.Spinbox(self.w_dmgLFrame) # TODO: make this do something
		self.w_dmg_counter_toNPCs.grid(column=1, row=2, sticky="E")

		# create the collision labelframe
		self.w_colLFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Collision")
		self.w_colLFrame.grid(column=0, row=1, sticky="NSEW")

		# create the stuff inside the collision labelframe
		self.w_col_label_solidTop: ttk.Label = ttk.Label(self.w_colLFrame, text="Solid on top")
		self.w_col_label_solidTop.grid(column=0, row=0, sticky="W")
		self.w_col_check_solidTop: ttk.Checkbutton = ttk.Checkbutton(self.w_colLFrame) # TODO: make this do something
		self.w_col_check_solidTop.grid(column=1, row=0, sticky="E")

		self.w_col_label_solidSides: ttk.Label = ttk.Label(self.w_colLFrame, text="Solid on sides")
		self.w_col_label_solidSides.grid(column=0, row=1, sticky="W")
		self.w_col_check_solidSides: ttk.Checkbutton = ttk.Checkbutton(self.w_colLFrame) # TODO: make this do something
		self.w_col_check_solidSides.grid(column=1, row=1, sticky="E")
		
		self.w_col_label_solidBottom: ttk.Label = ttk.Label(self.w_colLFrame, text="Solid on bottom")
		self.w_col_label_solidBottom.grid(column=0, row=2, sticky="W")
		self.w_col_check_solidBottom: ttk.Checkbutton = ttk.Checkbutton(self.w_colLFrame) # TODO: make this do something
		self.w_col_check_solidBottom.grid(column=1, row=2, sticky="E")

class GuiTileSkins:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int) -> None:
		pass

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
		self.notebookPageNames: list[str] = ["Properties", "Skins"]
		self.wc_notebookPageFrames: list[ttk.Frame] = []
		for name in self.notebookPageNames:
			self._AddNotebookPage(name)

		# create the properties page
		self.wc_tileProps: GuiTileProperties = GuiTileProperties(self.wc_notebookPageFrames[0], column=0, row=0, columnspan=1, rowspan=1)

		# create the skins page
		self.wc_tileSkins: GuiTileSkins = GuiTileSkins(self.wc_notebookPageFrames[1], column=0, row=0, columnspan=1, rowspan=1)

	def _AddNotebookPage(self, pageName: str) -> None:
		frame: ttk.Frame = ttk.Frame(self.w_notebook)
		frame.grid(column=0, row=0)
		self.w_notebook.add(frame, text=pageName)
		self.wc_notebookPageFrames.append(frame)
		print(self.wc_notebookPageFrames)

	def _Read(self) -> None:
		assert False

	def _Write(self) -> None:
		assert False

	def Run(self) -> None:
		self.root.mainloop()


if __name__ == "__main__":
	app: GuiTileDataEditor = GuiTileDataEditor()
	app.Run()