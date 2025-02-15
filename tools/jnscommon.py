import copy
import os
import os.path
import re

'''
IMPORTANT NOTE!
please use python type hints!!
more about python type hints: https://docs.python.org/3/library/typing.html
python type hints cheat sheet: https://mypy.readthedocs.io/en/stable/cheat_sheet_py3.html
'''

_PATH_ASSETS_REL: str = os.path.join("..", "jumpnslash-cpp", "Jump-n-Slash", "assets")
PATH_ASSETS: str = os.path.abspath(_PATH_ASSETS_REL)
PATH_ASSETS_LEVELS: str = os.path.join(PATH_ASSETS, "levels")
PATH_ASSETS_TEXTURES: str = os.path.join(PATH_ASSETS, "textures")
PATH_ASSETS_TEXTURES_LEVELTILES: str = os.path.join(PATH_ASSETS_TEXTURES, "leveltiles")
PATH_ASSETS_TEXTURES_ENTITIES: str = os.path.join(PATH_ASSETS_TEXTURES, "entities")
_GAME_PATH_ASSETS_TEXTURES_ENTITIES: str = os.path.join("entities")
_GAME_PATH_ASSETS_TEXTURES_LEVELTILES: str = os.path.join("leveltiles")

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

# 1st level keys
_CATEGORY_SPR: str = "spr"
_CATEGORY_DATA: str = "data"

# 2nd level keys
_OBJ_ENTITY: str = "entity"
_OBJ_TILE: str = "tile"
_OBJ_LEVEL: str = "level"

# 3rd level keys
PART_PALETTENAME: str = "palette"
_PART_JOINER: str = "joiner"
PART_TILENAME: str = "tile"
PART_FILEEXT: str = "file extension"

conventions: dict = {
	_CATEGORY_SPR: {
		_OBJ_ENTITY: {},
		_OBJ_TILE: {
			PART_PALETTENAME: "[a-zA-Z]+",
			_PART_JOINER: "(_){1}",
			PART_TILENAME: "[a-zA-Z0-9]+",
			PART_FILEEXT: "([.]png){1}"
		}
	},
	_CATEGORY_DATA: {
		_OBJ_TILE: {},
		_OBJ_LEVEL: {}
	}
}

#####################
# file system stuff #
#####################

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

################
# string stuff #
################

def GetAdjustedFilename(toAdjust: str) -> str:
	result: str = copy.deepcopy(toAdjust)

	# replace underscores with spaces
	while "_" in result:
		i: int = result.index("_")
		result = result[:i] + " " + result[i+1:]
		print(result)

	if "." in result:
		# remove file extension
		i: int = len(result) - 1
		while result[i] != ".":
			i -= 1
		assert result[i] == "."
		result = result[:i]
		print(result)
	
	return result

def ConvertToCamelCase(toConvert: str) -> str:
	# convert the string to all lowercase
	result: str = toConvert.lower()
	print(f"\"{result}\" will be converted to camelCase")
	while True:
		try:
			spaceIndex: int = result.index(" ")
		except ValueError:
			break
		else:
			if spaceIndex == len(result) - 1:
				result = result[:spaceIndex]
			else:
				result = result[:spaceIndex] + result[spaceIndex+1].upper() + result[spaceIndex+2:]
			print(f"\"{result}\"")
	
	return result

# TODO: this function does not work yet
def ConvertFromCamelCase(toConvert: str) -> str:
	assert False

###############
# conventions #
###############

'''
returns the regex pattern for the entity sprite naming convention
'''
def GetConventionSprEntity() -> str:
	pass

def GetConventionSprTile(part: str | None = None) -> str:
	conv: dict = conventions[_CATEGORY_SPR][_OBJ_TILE]

	palName: str = conv[PART_PALETTENAME]
	joiner: str = conv[_PART_JOINER]
	tileName: str = conv[PART_TILENAME]
	fileExt: str = conv[PART_FILEEXT]

	if part is None:
		return palName + joiner + tileName + fileExt
	elif part == PART_PALETTENAME:
		return palName + joiner
	elif part == PART_TILENAME:
		return joiner + tileName
	elif part == PART_FILEEXT:
		return fileExt
	else:
		assert False
	
def GetSprTilePartialName(fullName: str, partName: str) -> None:
	conv: str = GetConventionSprTile()
	# make sure the name they gave matches the naming convention for tile sprite filenames
	assert re.match(conv, fullName) is not None

	partConv: str = GetConventionSprTile(partName)

	# make sure the partial convention they gave is indeed a partial convention
	assert partConv in conv

	print(fullName)
	print(partConv)
	match: re.Match[str] | None = re.match(partConv, fullName)
	print(match)
	assert match is not None
	partialName: str = match[0]

	return partialName

def GetConventionDataTile() -> str:
	pass

def GetConventionDataLevel() -> str:
	pass

def GetPartialConvention(fullConvention, partConvention: str) -> str:
	pass

def GetPartialName(fullName: str, fullConvention: str, partName: str) -> str:
	assert re.match(fullConvention, fullName) is not None
	if fullConvention == CONVENTION_SPR_ENTITY:
		pass
	elif fullConvention == CONVENTION_SPR_LEVELTILE:
		if partName.lower() == "palette name":
			re.match()
		elif partName.lower() == "tile name":
			re.match()
		elif partName.lower() == "file extension" or partName.lower() == "file type":
			pass
	elif fullConvention == CONVENTION_DATA_LEVELTILE:
		pass
	elif fullConvention == CONVENTION_DATA_LEVELDATA:
		pass

#########################
# packages/dependencies #
#########################

"""DOES NOT CURRENTLY WORK"""
def CreateVirtualEnvironment() -> None:
	assert False, "CreateVirtualEnvironment function does not work yet!"

"""DOES NOT CURRENTLY WORK"""
def PipInstall(pkgName: str) -> None:
	assert False, "PipInstall function does not work yet!"
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

