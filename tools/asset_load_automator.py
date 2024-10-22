from PIL import Image
import os.path
import re

read_location = os.path.join("..","jumpnslash-cpp","Jump-n-Slash","assets")

asset_folder_contents = os.listdir(read_location)

# check this out if you forgot how regex works: https://www.dataquest.io/wp-content/uploads/2019/03/python-regular-expressions-cheat-sheet.pdf
texture_actor_naming_convention = "[a-z]+(_){1}[0-9]+([.]png){1}"
texture_tile_naming_convention = ""
leveldata_naming_convention = "[a-z0-9]+([.]txt){1}"

ACTOR_FOLDERS = ["player", "sword", "enemy"]

test_mode_enabled = True
print_texture_actor_output = False
print_texture_tile_output = True
print_leveldata_output = True
print_final_cmds = True

normal_file_suffix = ""
testing_file_suffix = "_test"

current_file_suffix = None
if test_mode_enabled is True:
    current_file_suffix = testing_file_suffix
elif test_mode_enabled is False:
    current_file_suffix = normal_file_suffix
assert current_file_suffix is not None # crash if the suffix wasn't set properly

def print_folder(path, tabs=0):
    contents = os.listdir(path)
    for item in contents:
        current_path = os.path.join(path, item)

        # if it's a file, print it with the given amount of tabs
        if os.path.isfile(current_path):
            for t in range(tabs):
                print("\t", end="")
            print(item)
        
        # if it's a file, print it with the given amount of tabs and recursively print contents
        elif os.path.isdir(current_path):
            for t in range(tabs):
                print("\t", end="")
            print(item)
            print_folder(current_path, tabs + 1)

def get_subfolders(path):
    return [item for item in os.listdir(path) if os.path.isdir(os.path.join(path, item))]

def get_files(path):
    return [item for item in os.listdir(path) if os.path.isfile(os.path.join(path, item))]

def generate_texture_command(texKey, filename, isSmooth):
    return f"texture \"{texKey}\" \"{filename}\" {str(isSmooth).lower()}"

def generate_sprite_command(sprKey, texKey, texX, texY, sprW, sprH):
    return f"sprite \"{sprKey}\" \"{texKey}\" {texX} {texY} {sprW} {sprH}"

def generate_animation_command(animKey, sprKeyList, isLooping):
    out_str = f"animation \"{animKey}\" ["

    # add each key in the list
    for key in sprKeyList:
        out_str += f"\"{key}\""
        if key != sprKeyList[-1]: # only add a trailing space if key is not the last one in the list
            out_str += " "
    
    out_str += f"] {str(isLooping).lower()}"
    return out_str

def generate_grid_command(gridKey, grid_fname):
    return f"grid \"{gridKey}\" \"{grid_fname}\""

def process_textures(path):
    # get all subfolders in the textures folder
    commands = []
    subfolders = get_subfolders(path)
    for folder in subfolders:
        if folder == "leveltiles": # process level tiles differently than actors
            pass
        elif folder in ACTOR_FOLDERS: # process actors using animations
            width = 0 # the overall width of the spritesheet
            height = 0 # the overall height of the spritesheet
            sprites = {} # keep track of which file goes where in the sheet
            # get all the files in a textures subfolder
            files = get_files(os.path.join(path, folder))

            # (1) set up image properties for width, height, and file path
            for file in files:
                # ignore files beginning with an underscore, and ones that don't fit the naming convention
                if file[0] != "_" and re.match(texture_actor_naming_convention, file):
                    #print(file + " matches regex naming convention")
                    #print(split_name)
                    split_name = re.split("[_.]", file)
                    anim_name = split_name[0] # the animation name
                    anim_frame = split_name[1] # the animation frame number (as a string)
                    properties = {"x": None, "y": None, "w": None, "h": None, "f": None}
                    file_path = os.path.join(path, folder, file)
                    with Image.open(file_path) as img:
                        properties["w"] = img.size[0]
                        properties["h"] = img.size[1]
                        properties["f"] = file_path
                    assert properties["w"] is not None
                    assert properties["w"] > 0
                    assert properties["h"] is not None
                    assert properties["h"] > 0
                    assert properties["f"] is not None
                    assert len(properties["f"]) > 0
                    # we will set x and y properties later!
                    
                    # add the animation name to the dictionary if it's not already there
                    if anim_name not in sprites.keys():
                        sprites[anim_name] = {}
                    sprites[anim_name][anim_frame] = properties
                    if print_texture_actor_output is True:
                        print(file + " has been processed")
                    
            pixX = 0 # the x-position of the top left of a sprite in the sheet
            pixY = 0 # the y-position of the top left of a sprite in the sheet
            maxWidth = 0
            
            # (2) set up properties for sprite positioning in spritesheet
            for anim in sprites.keys():
                # each animation (key) gets its own row in the spritesheet
                maxHeight = 0
                for frame_num in sprites[anim].keys():
                    assert sprites[anim][frame_num]["x"] is None
                    assert sprites[anim][frame_num]["y"] is None
                    sprites[anim][frame_num]["x"] = pixX
                    sprites[anim][frame_num]["y"] = pixY
                    """ <-- put a leading hashtag at the beginning of this line to enable the code below (for debug)
                    w = sprites[anim][frame_num]["w"]
                    h = sprites[anim][frame_num]["h"]
                    print(f"{anim}_{frame_num} : ({pixX}, {pixY}), w={w} h={h}")
                    #"""
                    pixX += sprites[anim][frame_num]["w"] # increment pixX
                    # update maxHeight
                    if sprites[anim][frame_num]["h"] > maxHeight - pixY:
                        maxHeight = sprites[anim][frame_num]["h"]
                pixY += maxHeight
                if pixX > maxWidth:
                    maxWidth = pixX
                pixX = 0
            height = pixY
            width = maxWidth
            spritesheet = Image.new("RGBA", (width, height))
            print(f"spritesheet size will be w={width}, h={height}")

            # (3) place sprites in the sheet
            for anim in sprites.keys():
                for frame_num in sprites[anim].keys():
                    properties = sprites[anim][frame_num]
                    with Image.open(properties["f"]) as img:
                        spritesheet.paste(img, (properties["x"], properties["y"]))
            sheet_fname = "sheet" + current_file_suffix + ".png"
            spritesheet.save(os.path.join(path, folder, sheet_fname))

            # (4) generate a texture command for the newly created spritesheet
            sheetKey = f"{folder} spritesheet"
            cmd = generate_texture_command(sheetKey, os.path.join(folder, sheet_fname), False)
            if print_texture_actor_output is True:
                print(cmd)
            commands.append(cmd) # add the command to the list of commands to write
            
            # (5) generate sprite commands for each frame of each animation
            for anim in sprites.keys():
                for frame_num in sprites[anim].keys():
                    x = sprites[anim][frame_num]["x"]
                    y = sprites[anim][frame_num]["y"]
                    w = sprites[anim][frame_num]["w"]
                    h = sprites[anim][frame_num]["h"]
                    sprCmd = generate_sprite_command(f"{folder} {anim} {frame_num}", sheetKey, x, y, w, h)
                    if print_texture_actor_output is True:
                        print(sprCmd)
                    commands.append(sprCmd)
            
            # (6) generate animation commands for each animation
            for anim in sprites.keys():
                sprKeyList = []
                for frame_num in sprites[anim].keys():
                    sprKeyList.append(f"{folder} {anim} {frame_num}")
                animCmd = generate_animation_command(f"{folder} {anim}", sprKeyList, True)
                if print_texture_actor_output is True:
                    print(animCmd)
                commands.append(animCmd)

    return commands

def process_leveldata(path):
    commands = []
    files = get_files(path)
    for file in files:
        if file[0] != "_" and re.match(leveldata_naming_convention, file):
            if print_leveldata_output is True:
                print(file + " will be processed")
            split_name = re.split("[_.]", file)
            keyName = ""
            for part in split_name:
                if part != split_name[-1]:
                    keyName += part
                    if part != split_name[-2]:
                        keyName += " "
            commands.append(generate_grid_command(keyName, file))
            
    print(f"{len(commands)} grid commands added")
    return commands

#print_folder(read_location)
asset_subfolders = get_subfolders(read_location)

commands_to_write = []

for folder in asset_subfolders:
    if folder.lower() == "textures":
        commands_to_write += process_textures(os.path.join(read_location, folder))
    elif folder.lower() == "leveldata":
        commands_to_write += process_leveldata(os.path.join(read_location, folder))


cmds_fname = "assetSetupFile" + current_file_suffix + ".txt"
print(f"writing to file: {cmds_fname}")
with open(os.path.join(read_location, cmds_fname), "w") as cmd_file:
    for cmd in commands_to_write:
        print(cmd, file=cmd_file)
        if print_final_cmds is True:
            print(cmd)
