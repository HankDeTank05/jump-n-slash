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
CONVENTION_ENTITY_ANIM: str = "[a-z]+"
CONVENTION_ENTITY_FRAME: str = "[0-9]+"
CONVENTION_ENTITY_FILETYPE: str = "([.]png){1}"
CONVENTION_ENTITY: str = CONVENTION_ENTITY_ANIM + "(_){1}" + CONVENTION_ENTITY_FRAME + CONVENTION_ENTITY_FILETYPE
CONVENTION_LEVELTILE: str = "" # TODO: create naming convention for leveltile files
CONVENTION_LEVELDATA: str = "[a-z0-9]+([.]txt){1}"

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

