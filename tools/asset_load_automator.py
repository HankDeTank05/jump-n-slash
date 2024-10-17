from PIL import Image
import os.path
import re

read_location = os.path.join("..","jumpnslash-cpp","Jump-n-Slash","assets")

asset_folder_contents = os.listdir(read_location)

def print_folder(path, tabs=0):
    contents = os.listdir(path)
    for item in contents:
        current_path = os.path.join(path, item)
        if os.path.isfile(current_path):
            for t in range(tabs):
                print("\t", end="")
            print(item)
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

def process_textures(path):
    commands_to_write = []
    # get all subfolders in the textures folder
    subfolders = get_subfolders(path)
    for folder in subfolders:
        if folder != "leveltiles":
            width = 0 # the overall width of the spritesheet
            height = 0 # the overall height of the spritesheet
            sprites = {} # keep track of which file goes where in the sheet
            # get all the files in a textures subfolder
            files = get_files(os.path.join(path, folder))

            # set up image properties for width, height, and file path
            for file in files:
                # ignore files beginning with an underscore, and ones that don't fit the naming convention
                if file[0] != "_" and re.match("[a-z]+(_){1}[0-9]+([.]png){1}", file):
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
                        
                    print(file + " has been processed")
                    
            pixX = 0 # the x-position of the top left of a sprite in the sheet
            pixY = 0 # the y-position of the top left of a sprite in the sheet
            maxWidth = 0
            
            # set up properties for sprite positioning in spritesheet
            for anim in sprites.keys():
                # each animation (key) gets its own row in the spritesheet
                maxHeight = 0
                for frame_num in sprites[anim].keys():
                    assert sprites[anim][frame_num]["x"] is None
                    assert sprites[anim][frame_num]["y"] is None
                    sprites[anim][frame_num]["x"] = pixX
                    sprites[anim][frame_num]["y"] = pixY
                    """
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

            # place sprites in the sheet
            for anim in sprites.keys():
                for frame_num in sprites[anim].keys():
                    properties = sprites[anim][frame_num]
                    with Image.open(properties["f"]) as img:
                        spritesheet.paste(img, (properties["x"], properties["y"]))
            sheet_fname = "sheet_test.png"
            spritesheet.save(os.path.join(path, folder, sheet_fname))

            # generate a texture command for the newly created spritesheet
            sheetKey = f"{folder} spritesheet"
            cmd = generate_texture_command(sheetKey, os.path.join(folder, sheet_fname), False)
            print(cmd)
            commands_to_write.append(cmd) # add the command to the list of commands to write
            
            # generate sprite commands for each frame of each animation
            for anim in sprites.keys():
                for frame_num in sprites[anim].keys():
                    x = sprites[anim][frame_num]["x"]
                    y = sprites[anim][frame_num]["y"]
                    w = sprites[anim][frame_num]["w"]
                    h = sprites[anim][frame_num]["h"]
                    sprCmd = generate_sprite_command(f"{folder} {anim} {frame_num}", sheetKey, x, y, w, h)
                    print(sprCmd)
                    commands_to_write.append(sprCmd)
    cmds_fname = "assetSetupFile_test.txt"
    with open(os.path.join(path, "..", cmds_fname), "w") as cmd_file:
        for cmd in commands_to_write:
            print(cmd, file=cmd_file)

#print_folder(read_location)
asset_subfolders = get_subfolders(read_location)

for item in asset_subfolders:
    if item.lower() == "textures":
        process_textures(os.path.join(read_location, item))
