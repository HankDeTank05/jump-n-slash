import os
import os.path
from tkinter import *

GRID_WIDTH = 8
GRID_HEIGHT = 8
WINDOW_NAME = "Hello World!"

tile_read_path = os.path.join("..", "jumpnslash-cpp", "Jump-n-Slash", "assets", "textures", "leveltiles")
tile_fnames = []

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
            print(tile_fnames[-1])

create_grid(GRID_WIDTH, GRID_HEIGHT)
get_tiles()

root = Tk()
root.title(WINDOW_NAME)
root.minsize(1280, 720)

text = Label(root, text="Henry")
text.pack()
text2 = Label(root, text="Holman")
text2.pack()

image = PhotoImage(file=tile_fnames[0])
img = Label(root, image=image)
img.pack()

root.mainloop()

'''
def run():
    # pre-creation setup
    create_grid(GRID_WIDTH, GRID_HEIGHT)
    get_tiles()
    
    # create the application
    root = Tk()
    root.title("Hello World")
    root.minsize(1280, 720)

    # create widgets here
    
    root.mainloop()

def create_widgets():
    # create the main frame, in which everything will be organized
    mainframe = ttk.Frame(root)
    mainframe.grid(column=0, row=0)

    # create the grid view on the top
    gridView = ttk.Frame(mainframe)
    gridView.grid(column=0, row=0)

    create_grid_view()

    # create the palette view on the bottom
    paletteView = ttk.Frame(mainframe)
    paletteView.grid(column=0, row=1)

    images = []
    imgLabels = []
    for i in range(len(tile_fnames)):
        images.append(PhotoImage(file=tile_fnames[i]))
        imgLabels.append(ttk.Label(paletteView))
        imgLabels[i]['image'] = images[i]
        imgLabels[i].grid(column=i, row=0)

def create_grid_view():
    pass

def create_palette_view():
    pass

run()
'''
