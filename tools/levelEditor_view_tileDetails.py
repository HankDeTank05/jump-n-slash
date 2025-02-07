# language imports
import tkinter as tk
import tkinter.ttk as ttk

# game imports
import jnscommon as jns

class TileDetailsView:

	def __init__(self, parent: tk.Tk, column: int, row: int, columnspan: int = 1, rowspan: int = 1, sticky: str = "NSEW") -> None:
		 
   
   		# Create the parent frame
		self.w_parentFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Tile Details Panel")
		self.w_parentFrame.grid(column=column, row=row,
								columnspan=columnspan, rowspan=rowspan,
								padx=padx, pady=pady, sticky=sticky)
  #shit. I'll need to import pad as well.

		# Tile Icon
		self.w_tileIcon = tk.Label(self.w_parentFrame, text="No Image", width=10, height=5, relief="solid")
		self.w_tileIcon.grid(column=0, row=0, columnspan=2, pady=10)

		# Tile Name
		self.w_nameLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Name:")
		self.w_nameLabel.grid(column=0, row=1, sticky="W", padx=10, pady=5)
		self.w_nameValue: ttk.Label = ttk.Label(self.w_parentFrame, text="N/A")
		self.w_nameValue.grid(column=1, row=1, sticky="W", padx=10, pady=5)

		# Damage to Player
		self.w_damagePlayerLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Damage to Player:")
		self.w_damagePlayerLabel.grid(column=0, row=2, sticky="W", padx=10, pady=5)
		self.w_damagePlayerValue: ttk.Label = ttk.Label(self.w_parentFrame, text="0")
		self.w_damagePlayerValue.grid(column=1, row=2, sticky="W", padx=10, pady=5)

        # Damage to Enemies
		self.w_damageEnemiesLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Damage to Enemies:")
		self.w_damageEnemiesLabel.grid(column=0, row=3, sticky="W", padx=10, pady=5)
		self.w_damageEnemiesValue: ttk.Label = ttk.Label(self.w_parentFrame, text="0")
		self.w_damageEnemiesValue.grid(column=1, row=3, sticky="W", padx=10, pady=5)

        # Breakable Status
		self.w_breakableLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Breakable:")
		self.w_breakableLabel.grid(column=0, row=4, sticky="W", padx=10, pady=5)
		self.w_breakableValue: ttk.Label = ttk.Label(self.w_parentFrame, text="No")
		self.w_breakableValue.grid(column=1, row=4, sticky="W", padx=10, pady=5)

        # Solid Status
		self.w_solidLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="Solid:")
		self.w_solidLabel.grid(column=0, row=5, sticky="W", padx=10, pady=5)
		self.w_solidValue: ttk.Label = ttk.Label(self.w_parentFrame, text="No")
		self.w_solidValue.grid(column=1, row=5, sticky="W", padx=10, pady=5)

    #############################
    # Update Tile Details Panel #
    #############################

	def update_tile_details(self, tile_data: dict, img: tk.PhotoImage) -> None:

		self.w_nameValue.config(text=tile_data.get("name", "Unknown"))
		self.w_damagePlayerValue.config(text=str(tile_data.get("damage to player", 0)))
		self.w_damageEnemiesValue.config(text=str(tile_data.get("damage to enemies", 0)))
		self.w_breakableValue.config(text="Yes" if tile_data.get("breakable", False) else "No")
		self.w_solidValue.config(text="Yes" if tile_data.get("solid on sides", False) else "No")

        # Update the displayed tile icon
		self.w_tileIcon.config(image=img)
		self.w_tileIcon.image = img  # Keep reference