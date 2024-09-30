import json
import os
import os.path

# get a list of items in the leveltiles directory
def get_tile_files(_tile_read_path, _tile_size, _tile_extension):
    suffix_len = len(str(_tile_size))
    extension_len = len(_tile_extension)
    end_len = suffix_len + extension_len
    
    items = os.listdir(_tile_read_path)
    files = []
    for i in range(len(items)):
        #print(items[i])

        # make sure the item is a file
        if os.path.isfile(os.path.join(_tile_read_path, items[i])):
            file_str = items[i]

            suffix_str = file_str[-end_len:-extension_len]
            extension_str = file_str[-extension_len:]
            end_str = suffix_str + extension_str

            #print("\t" + suffix_str)
            #print("\t" + extension_str)
            #print("\t" + end_str)

            # make sure the file has the proper size suffix and file extension
            if suffix_str == str(_tile_size) and extension_str == _tile_extension:
                files.append(file_str)
                #print("\tadded to file list")
    
    return files

# add each file name and its corresponding tile id to the dicts
def add_file_data_to_dict(_files, _data):
    for i in range(len(files)):
        tile_id = str(i + 1)
        assert(len(tile_id) >= 1) # sanity check

        # if it's a single digit number, prepend a leading zero to the tile id
        if len(tile_id) < 2:
            tile_id = "0" + tile_id
        assert(len(tile_id) == 2) # sanity check

        _data["editorInfo"]["encodeTiles"][files[i]] = tile_id
        _data["gameInfo"]["decodeTiles"][tile_id] = files[i]


editor_tile_read_path = os.path.join("..", "jumpnslash-cpp", "Jump-n-Slash", "assets", "textures", "leveltiles")
editor_level_write_path = os.path.join("..", "jumpnslash-cpp", "Jump-n-Slash", "assets", "leveldata")
game_tile_read_path = os.path.join("..", "assets", "sprites", "leveltiles")
game_level_read_path = os.path.join("..", "assets", "leveldata")
tile_size = 32
tile_extension = ".png"
level_extension = ".txt"

data = {
    "editorInfo": {
        "tileReadPath": editor_tile_read_path,  # NOTE: RELATIVE PATH IS DIFFERENT THAN FOR GAME!!
        "levelWritePath": editor_level_write_path,  # NOTE: RELATIVE PATH IS DIFFERENT THAN FOR GAME!!
        "encodeTiles": {}  # stored as: key = filename, value = 2-digit id
    },
    "gameInfo": {
        "tileReadPath": game_tile_read_path,  # NOTE: RELATIVE PATH IS DIFFERENT THAN FOR EDITOR!!
        "levelReadPath": game_level_read_path,  # NOTE: RELATIVE PATH IS DIFFERENT THAN FOR EDITOR!!
        "decodeTiles": {}  # stored as: key = 2-digit id, value = filename
    },
    "genericInfo": {
        "tileSize": tile_size,
        "tileFileExt": tile_extension,
        "levelFileExt": level_extension
    }
}

files = get_tile_files(editor_tile_read_path, tile_size, tile_extension)
add_file_data_to_dict(files, data)

with open("formatting_rules.json", "w") as json_file:
    json.dump(data, json_file, indent=4)

print("done!")
