import tkinter as tk
from tkinter import ttk, filedialog, messagebox
import json
from PIL import Image, ImageTk
import jnscommon as jns

"""
NOTE: IF RUNNING FROM VSCODE, "cd" TO THE FOLDER CONTAINING THIS FILE BEFORE RUNNING TO AVOID PATHING ISSUES
- any class that is a GUI element, prepend "Gui" to the name of the class
    - any class that is a GUI element(s) should take a column, row, columnspan, and rowspan as four ints in their constructor
    - member variables of a class that are a widget should follow this convention: "self.w_<variableName>"
    - member variables of a class that are a collection of widgets should follow this convention "self.wc_<variableName>"
- variable names should always be in camelCase
- always do type hints when declaring variables
- use assert statements LIBERALLY
- use TODO (and regular) comments liberally
    - remember: use comments to describe the meaning of the code, not a restated version of the logic
"""

class Map:
    def __init__(self):
        self.tiles: dict[tuple[int, int], int] = {}  # Store tile data: dict[tuple(int, int), int]
        self.is_saved: bool = True  # Track if the map has been saved

        # Map dimensions
        self.x_min = 0
        self.x_max = 0
        self.y_min = 0
        self.y_max = 0
        self.rows = 1
        self.cols = 1

    def remember_position(self, position):
        x, y = position
        self.x_min = min(x, self.x_min)
        self.x_max = max(x, self.x_max)
        self.y_min = min(y, self.y_min)
        self.y_max = max(y, self.y_max)
        self.rows = self.y_max - self.y_min + 1
        self.cols = self.x_max - self.x_min + 1

    def add_tile(self, position, tile_index):
        self.remember_position(position)
        self.tiles[position] = tile_index
        self.is_saved = False

    def remove_tile(self, position):
        if position in self.tiles:
            self.tiles.pop(position)
            self.is_saved = False

    def save(self, filename):
        data = {
            "size": {
                "rows": self.rows,
                "cols": self.cols
            },
            "tiles": [
                {"position": position, "tile_index": tile_index}
                for position, tile_index in self.tiles.items()
            ]
        }
        with open(filename, "w") as file:
            json.dump(data, file, indent=4)
        self.is_saved = True

    def load(self, filename):
        with open(filename, "r") as file:
            data = json.load(file)
        self.tiles = {}
        self.rows = data["size"]["rows"]
        self.cols = data["size"]["cols"]
        for tile in data["tiles"]:
            position = tuple(tile["position"])
            tile_index = tile["tile_index"]
            self.tiles[position] = tile_index
        self.is_saved = True

class Editor(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("2D Platformer Level Editor")
        self.geometry("1920x1080")

        self.map = Map()
        self.camera_pos = (0, 0)
        self.brush_index = 0
        filenames = jns.GetFilesWithConvention("../jumpnslash-cpp/Jump-n-Slash/Assets/textures/leveltiles",jns.CONVENTION_SPRITE_LEVELTILE)
        print (filenames)

        self.tile_images = [
            ImageTk.PhotoImage(Image.open("sprites/leveltiles/block_solid_32.png")),
            ImageTk.PhotoImage(Image.open("sprites/leveltiles/block_breakable_32.png")),
            ImageTk.PhotoImage(Image.open("sprites/leveltiles/block_hazard_32.png")),
            ImageTk.PhotoImage(Image.open("sprites/leveltiles/platform_semisolid_32.png")),
        ]
        [
            ]

        self.brush_labels = [
            "Solid Block",
            "Breakable Block",
            "Hazard Block",
            "Semisolid Platform",
        ]

        self.protocol("WM_DELETE_WINDOW", self.on_exit)

        self.main_frame = ttk.Frame(self)
        self.main_frame.pack(fill=tk.BOTH, expand=True)

        self.canvas = tk.Canvas(self.main_frame, bg="white", width=1000, height=1000)
        self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        self.side_frame = ttk.Frame(self.main_frame)
        self.side_frame.pack(side=tk.RIGHT, fill=tk.Y)

        self.save_button = ttk.Button(self.side_frame, text="Save", command=self.save_map)
        self.save_button.pack(pady=10)

        self.load_button = ttk.Button(self.side_frame, text="Load", command=self.load_map)
        self.load_button.pack(pady=10)

        self.new_button = ttk.Button(self.side_frame, text="New", command=self.new_map)
        self.new_button.pack(pady=10)

        self.left_brush_button = ttk.Button(self.side_frame, text="<", command=self.select_left_brush)
        self.left_brush_button.pack(pady=5)

        self.tile_label = tk.Label(self.side_frame)
        self.tile_label.pack(pady=5)

        self.tile_preview = tk.Label(self.side_frame)
        self.tile_preview.pack(pady=10)

        self.right_brush_button = ttk.Button(self.side_frame, text=">", command=self.select_right_brush)
        self.right_brush_button.pack(pady=5)

        self.clear_button = ttk.Button(self.side_frame, text="Clear", command=self.clear_map)
        self.clear_button.pack(pady=10)

        self.update_tile_image()
        self.canvas.bind("<Button-1>", self.on_canvas_click)
        self.draw_grid()

    def draw_grid(self):
        self.canvas.delete("grid_line")
        for x in range(0, 1000, 32):
            self.canvas.create_line(x, 0, x, 1000, fill="black", tags="grid_line")
        for y in range(0, 1000, 32):
            self.canvas.create_line(0, y, 1000, y, fill="black", tags="grid_line")

    def on_canvas_click(self, event):
        x = (event.x // 32)
        y = (event.y // 32)
        position = (self.camera_pos[0] + x, self.camera_pos[1] + y)
        self.map.add_tile(position, self.brush_index)
        self.draw_tiles()

    def draw_tiles(self):
        self.canvas.delete("tile")
        for (position, tile_index) in self.map.tiles.items():
            x, y = position
            x = (x - self.camera_pos[0]) * 32
            y = (y - self.camera_pos[1]) * 32
            self.canvas.create_image(x, y, anchor=tk.NW, image=self.tile_images[tile_index], tags="tile")

    def save_map(self):
        filename = filedialog.asksaveasfilename(defaultextension=".json", filetypes=[("JSON Files", "*.json")])
        if filename:
            self.map.save(filename)

    def load_map(self):
        filename = filedialog.askopenfilename(filetypes=[("JSON Files", "*.json")])
        if filename:
            self.map.load(filename)
            self.draw_tiles()

    def new_map(self):
        self.map = Map()
        self.draw_tiles()

    def clear_map(self):
        if messagebox.askyesno("Clear Map", "Are you sure you want to clear the map? This action cannot be undone."):
            self.map = Map()
            self.draw_tiles()

    def select_left_brush(self):
        self.brush_index = (self.brush_index - 1) % len(self.tile_images)
        self.update_tile_image()

    def select_right_brush(self):
        self.brush_index = (self.brush_index + 1) % len(self.tile_images)
        self.update_tile_image()

    def update_tile_image(self):
        self.tile_label.config(text=self.brush_labels[self.brush_index])
        self.tile_preview.config(image=self.tile_images[self.brush_index])

    def on_exit(self):
        if not self.map.is_saved:
            if messagebox.askyesno("Exit", "You have unsaved changes. Do you want to exit without saving?"):
                self.destroy()
        else:
            self.destroy()

if __name__ == "__main__":
    app = Editor()
    app.mainloop()
