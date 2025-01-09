import os
import os.path
import re

'''
IMPORTANT NOTE!
please use python type hints!!
more about python type hints: https://docs.python.org/3/library/typing.html
python type hints cheat sheet: https://mypy.readthedocs.io/en/stable/cheat_sheet_py3.html
'''

READ_LOCATION_REL: str = os.path.join("..", "jumpnslash-cpp", "Jump-n-Slash", "assets")
READ_LOCATION_ABS: str = os.path.abspath(READ_LOCATION_REL)

# check this out if you forgot how regex works: https://www.dataquest.io/wp-content/uploads/2019/03/python-regular-expressions-cheat-sheet.pdf
"""
Entity sprite naming convention
<animationName>_<frameNumber>.png
"""
_CONVENTION_SPRITE_ENTITY_ANIM: str = "[a-z]+"
_CONVENTION_SPRITE_ENTITY_FRAME: str = "[0-9]+"
_CONVENTION_SPRITE_ENTITY_FILETYPE: str = "([.]png){1}"
CONVENTION_SPRITE_ENTITY: str = _CONVENTION_SPRITE_ENTITY_ANIM + "(_){1}" + _CONVENTION_SPRITE_ENTITY_FRAME + _CONVENTION_SPRITE_ENTITY_FILETYPE

"""
Level tile sprite naming convention
<paletteName>_<tileName>.png
"""
_CONVENTION_SPRITE_LEVELTILE_PALETTE: str = "[a-z]+"
_CONVENTION_SPRITE_LEVELTILE_NAME: str = "[a-z0-9]+"
_CONVENTION_SPRITE_LEVELTILE_FILETYPE: str = "([.]png){1}"
CONVENTION_SPRITE_LEVELTILE: str = _CONVENTION_SPRITE_LEVELTILE_PALETTE + "(_){1}" + _CONVENTION_SPRITE_LEVELTILE_NAME + _CONVENTION_SPRITE_LEVELTILE_FILETYPE

"""
Level data naming convention
<levelName>.txt
"""
_CONVENTION_LEVELDATA_NAME: str = "[a-z0-9]+"
_CONVENTION_LEVELDATA_FILETYPE: str = "([.]txt){1}"
CONVENTION_LEVELDATA: str = _CONVENTION_LEVELDATA_NAME + _CONVENTION_LEVELDATA_FILETYPE

#####################
# file system stuff #
#####################

def GetReadPath() -> str:
    return READ_LOCATION_ABS

def GetItemsAtPath(path: str) -> list[str]:
    return os.listdir(path)

def GetFilesAtPath(path: str) -> list[str]:
    absPath: str = os.path.abspath(path)
    items: list[str] = os.listdir(absPath)
    return [item for item in items if os.path.isfile(os.path.join(absPath,item))]

def GetFoldersAtPath(path: str) -> list[str]:
    absPath: str = os.path.abspath(path)
    items: list[str] = os.listdir(absPath)
    return [item for item in items if os.path.isdir(os.path.join(absPath,item))]

def GetFileType(path: str) -> str:
    absPath: str = os.path.abspath(path)
    assert os.path.isfile(absPath)
    extension: str = ""
    i: int = len(path) - 1
    while path[i] != ".":
        i -= 1
    assert path[i] == "."
    return path[i:]

def GetFilesWithConvention(path: str, namingConvention: str) -> list[str]:
    fileList: list[str] = GetFilesAtPath(path)
    return [file for file in fileList if re.match(namingConvention, file)]

#########################
# packages/dependencies #
#########################

"""DOES NOT CURRENTLY WORK"""
def CreateVirtualEnvironment() -> None:
    assert False

"""DOES NOT CURRENTLY WORK"""
def PipInstall(pkgName: str) -> None:
    assert False
    os.system(f"pip install {pkgName}")

#############################
# debugging/printing/output #
#############################

def PrintDict(data: dict, indent: int = 0, printResult: bool = True) -> str:
    output: str = ""
    for key in data.keys():
        for i in range(indent):
            #print("\t", end="")
            output += "\t"
        #print(f"{key}: ", end="")
        output += f"{key}: "
        if isinstance(data[key], dict):
            #print("{")
            output += "{\n"
            output += PrintDict(data[key], indent + 1, printResult=False)
            for i in range(indent):
                #print("\t", end="")
                output += "\t"
            #print("}")
            output += "}\n"
        else:
            #print(data[key])
            output += f"{data[key]}\n"
    
    # print the resulting string
    if printResult == True:
        print(output)

    # return the resulting string
    return output

