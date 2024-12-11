import os
import os.path
from guizero import App, Box, PushButton

tile_read_path = os.path.join("..", "jumpnslash-cpp", "Jump-n-Slash", "assets", "textures", "leveltiles")
tile_fnames = []

app = App(title="Hello World", width=1280, height=720)

current_tile = None

level_grid = []

def create_grid(_width, _height):
    for y in range(_height):
        level_grid.append([])
        for x in range(_width):
            level_grid[y].append(None)

# load the tile images used in the editor
def get_tiles():
    items = os.listdir(tile_read_path)
    for i in range(len(items)):
        if os.path.isfile(os.path.join(tile_read_path, items[i])) and items[i][-4:] == ".png" and items[i][0] != "_":
            tile_fnames.append(items[i])

def create_widgets():
    # the grid view representing the level, where edits are made
    gridView = Box(master=app, align="top", layout="grid", border=True)
    gridBtns=[]
    for y in range(len(level_grid)):
        gridBtns.append([])
        for x in range(len(level_grid[y])):
            gridBtns[y].append(PushButton(master=gridView, grid=[x,y], text=f"({x}, {y})"))

    # the palette view, displaying the usable tiles
    paletteView = Box(master=app, align="bottom", layout="grid", border=True)
    picBtns = []
    for i in range(len(tile_fnames)):
        picBtns.append(PushButton(master=paletteView, image=os.path.join(tile_read_path, tile_fnames[i]), grid=[i,0]))
        picBtns[i].update_command(cmd_set_tile, [picBtns[i].image])

# set the tile to be used when drawing on the level grid
def cmd_set_tile(image):
    print(f"set tile {image}")
    current_tile = image

create_grid(8, 8)
get_tiles()
create_widgets()

app.display()
