# language imports
import tkinter as tk
import tkinter.ttk as ttk

class GuiTileDetailsPanel:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, padx: int, pady: int, sticky: str) -> None:
		############################
		# create the non-gui stuff #
		############################

		# hardcoded test. Do not touch.
		self.tile_data = {
            "name": "Breakable Block",
            "damage_to_player": 0,
            "damage_to_enemies": 0,
            "is_breakable": True,
            "is_solid": True
        }

		########################
		# create the gui stuff #
		########################
		
		# create the parent frame
		self.w_parentFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Tile Details Panel")
		self.w_parentFrame.grid(column=column, row=row,
						  columnspan=columnspan, rowspan=rowspan,
						  padx=padx, pady=pady,
						  sticky=sticky)
  
		# Tile Name
		self.w_nameLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Name:")
		self.w_nameLabel.grid(column=0, row=0, sticky="W", padx=10, pady=5)
		self.w_nameValue: ttk.Label = ttk.Label(self.w_parentFrame, text=self.tile_data["name"])
		self.w_nameValue.grid(column=1, row=0, sticky="W", padx=10, pady=5)

        # Damage to Player
		self.w_damagePlayerLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Damage to Player:")
		self.w_damagePlayerLabel.grid(column=0, row=1, sticky="W", padx=10, pady=5)
		self.w_damagePlayerValue: ttk.Label = ttk.Label(self.w_parentFrame, text=self.tile_data["damage_to_player"])
		self.w_damagePlayerValue.grid(column=1, row=1, sticky="W", padx=10, pady=5)

        # Damage to Enemies
		self.w_damageEnemiesLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Damage to Enemies:")
		self.w_damageEnemiesLabel.grid(column=0, row=2, sticky="W", padx=10, pady=5)
		self.w_damageEnemiesValue: ttk.Label = ttk.Label(self.w_parentFrame, text=self.tile_data["damage_to_enemies"])
		self.w_damageEnemiesValue.grid(column=1, row=2, sticky="W", padx=10, pady=5)

        # Breakable Status
		self.w_breakableLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Breakable:")
		self.w_breakableLabel.grid(column=0, row=3, sticky="W", padx=10, pady=5)
		self.w_breakableValue: ttk.Label = ttk.Label(self.w_parentFrame, text="Yes" if self.tile_data["is_breakable"] else "No")
		self.w_breakableValue.grid(column=1, row=3, sticky="W", padx=10, pady=5)

        # Solid Status
		self.w_solidLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Solid:")
		self.w_solidLabel.grid(column=0, row=4, sticky="W", padx=10, pady=5)
		self.w_solidValue: ttk.Label = ttk.Label(self.w_parentFrame, text="Yes" if self.tile_data["is_solid"] else "No")
		self.w_solidValue.grid(column=1, row=4, sticky="W", padx=10, pady=5)

		# TODO: Hard-coded the tile info. Still need to integrate into GUITilePalette.

	def UpdateTileDetails(self, img: tk.PhotoImage) -> None:
		# TODO: finish this function
		# NOTE: currently, this is displaying the filename for the brush tile
		# TODO: we want just the tile name (no "<paletteName>_" prefix, no ".png" suffix) so that we can look for "<tileName>.json" and read the tile's data from there
		# TODO: we also want a second version of the <tileName> that's not in camel case so that the displayed name looks nice in the GUI
		self.w_nameValue.config(text=img.name)
		# self.w_damagePlayerValue.config(text="UPDATED DAMAGE TO PLAYER")
		# self.w_damageEnemiesValue.config(text="UPDATED DAMAGE TO ENEMIES")
		# self.w_breakableValue.config(text="UPDATED BREAKABILITY")
		# self.w_solidValue.config(text="UPDATED SOLIDITY")
