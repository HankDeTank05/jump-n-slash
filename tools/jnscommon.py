import copy
import os
import re
from pathlib import Path

'''
IMPORTANT NOTE!
please use python type hints!!
more about python type hints: https://docs.python.org/3/library/typing.html
python type hints cheat sheet: https://mypy.readthedocs.io/en/stable/cheat_sheet_py3.html
'''

# Get the directory where this script is located (repo/tools)
_TOOLS_DIR = Path(__file__).resolve().parent
# Go up one level to the repo root (repo)
_REPO_ROOT = _TOOLS_DIR.parent

# Define absolute paths based on the repo root
# Structure: repo/jumpnslash-cpp/Jump-n-Slash/assets
# CORRECT PATH: based on user's directory structure `jump-n-slash/jumpnslash-cpp/Jump-n-Slash/assets`
PATH_ASSETS = _REPO_ROOT / "jumpnslash-cpp" / "Jump-n-Slash" / "assets"

PATH_ASSETS_LEVELS = PATH_ASSETS / "levels"
PATH_ASSETS_TEXTURES = PATH_ASSETS / "textures"
PATH_ASSETS_TEXTURES_LEVELTILES = PATH_ASSETS_TEXTURES / "leveltiles"
PATH_ASSETS_TEXTURES_ENTITIES = PATH_ASSETS_TEXTURES / "entities"

# Relative paths for game logic (names only)
_GAME_PATH_ASSETS_TEXTURES_ENTITIES = "entities"
_GAME_PATH_ASSETS_TEXTURES_LEVELTILES = "leveltiles"

# check this out if you forgot how regex works: https://www.dataquest.io/wp-content/uploads/2019/03/python-regular-expressions-cheat-sheet.pdf
"""
Entity sprite naming convention
<animationName>_<frameNumber>.png
"""
_CONVENTION_SPR_ENTITY_ANIM: str = "[a-zA-Z]+"
_CONVENTION_SPR_ENTITY_FRAME: str = "[0-9]+"
_CONVENTION_SPR_ENTITY_FILETYPE: str = "([.]png){1}"
CONVENTION_SPR_ENTITY: str = _CONVENTION_SPR_ENTITY_ANIM + "(_){1}" + _CONVENTION_SPR_ENTITY_FRAME + _CONVENTION_SPR_ENTITY_FILETYPE

"""
Level tile sprite naming convention
<paletteName>_<tileName>.png
"""
_CONVENTION_SPR_LEVELTILE_PALETTE: str = "[a-zA-Z]+"
_CONVENTION_SPR_LEVELTILE_NAME: str = "[a-zA-Z0-9]+"
_CONVENTION_SPR_LEVELTILE_FILETYPE: str = "([.]png){1}"
CONVENTION_SPR_LEVELTILE: str = _CONVENTION_SPR_LEVELTILE_PALETTE + "(_){1}" + _CONVENTION_SPR_LEVELTILE_NAME + _CONVENTION_SPR_LEVELTILE_FILETYPE

"""
Level tile data naming convention
<tileName>_data.json
"""
_CONVENTION_DATA_LEVELTILE_NAME: str = "[a-zA-Z]+"
_CONVENTION_DATA_LEVELTILE_FILETYPE: str = "([.]json){1}"
CONVENTION_DATA_LEVELTILE: str = _CONVENTION_DATA_LEVELTILE_NAME + "(_data){1}" + _CONVENTION_DATA_LEVELTILE_FILETYPE

"""
Level data naming convention
<levelName>.txt
"""
_CONVENTION_DATA_LEVELDATA_NAME: str = "[a-zA-Z0-9]+"
_CONVENTION_DATA_LEVELDATA_FILETYPE: str = "([.]txt){1}"
CONVENTION_DATA_LEVELDATA: str = _CONVENTION_DATA_LEVELDATA_NAME + _CONVENTION_DATA_LEVELDATA_FILETYPE

#####################
# file system stuff #
#####################

def GetItemsAtPath(path: str | Path) -> list[str]:
    return os.listdir(str(path))

def GetFilesAtPath(path: str | Path) -> list[str]:
    p = Path(path)
    if not p.exists():
        return []
    return [item.name for item in p.iterdir() if item.is_file()]

def GetFoldersAtPath(path: str | Path) -> list[str]:
    p = Path(path)
    if not p.exists():
        return []
    return [item.name for item in p.iterdir() if item.is_dir()]

def GetFileType(path: str | Path) -> str:
    return Path(path).suffix

def GetFilesWithConvention(path: str | Path, namingConvention: str) -> list[str]:
    fileList: list[str] = GetFilesAtPath(path)
    return [file for file in fileList if re.match(namingConvention, file)]

################
# string stuff #
################

def GetAdjustedFilename(toAdjust: str) -> str:
    path_obj = Path(toAdjust)
    # Remove extension
    stem = path_obj.stem
    # Replace underscores with spaces
    return stem.replace("_", " ")

def ConvertToCamelCase(toConvert: str) -> str:
    # convert the string to all lowercase
    result: str = toConvert.lower()
    # split by space
    words = result.split(" ")
    if not words:
        return ""
    
    # first word stays lower, others get capitalized
    camel_case = words[0] + "".join(word.capitalize() for word in words[1:])
    print(f"\"{toConvert}\" converted to \"{camel_case}\"")
    return camel_case

# TODO: this function does not work yet
def ConvertFromCamelCase(toConvert: str) -> str:
    # Placeholder for future implementation
    pass

#########################
# packages/dependencies #
#########################

"""DOES NOT CURRENTLY WORK"""
def CreateVirtualEnvironment() -> None:
    print("CreateVirtualEnvironment function does not work yet!")

"""DOES NOT CURRENTLY WORK"""
def PipInstall(pkgName: str) -> None:
    print(f"PipInstall function does not work yet! (Requested: {pkgName})")
    # os.system(f"pip install {pkgName}")

#############################
# debugging/printing/output #
#############################

def PrintDict(data: dict, indent: int = 0, printResult: bool = True) -> str:
    output: str = ""
    for key in data.keys():
        output += "\t" * indent
        output += f"{key}: "
        if isinstance(data[key], dict):
            output += "{\n"
            output += PrintDict(data[key], indent + 1, printResult=False)
            output += "\t" * indent
            output += "}\n"
        else:
            output += f"{data[key]}\n"
    
    # print the resulting string
    if printResult == True:
        print(output)

    # return the resulting string
    return output
