# language imports
import os.path
import json

# module imports
from PIL import Image

# game imports
import jnscommon as jns

class Texture:

	KEY_TEXKEY: str = "key"
	KEY_PATH: str = "path"
	KEY_SMOOTH: str = "smooth"

	def __init__(self, filePath: str, filename: str, smooth: bool) -> None:
		self._texKey: str = jns.GetAdjustedFilename(filename)

		if filename in filePath:
			self._filePath: str = filePath
		else:
			self._filePath: str = os.path.join(filePath, filename)
		
		self._smooth: bool = smooth

	def GetDict(self) -> dict:
		return {
			Texture.KEY_TEXKEY: self._texKey,
			Texture.KEY_PATH: self._filePath,
			Texture.KEY_SMOOTH: self._smooth
		}
	
	def GetKey(self) -> str:
		return self._texKey
	
class Sprite:

	KEY_SPRKEY: str = "key"
	KEY_SRCTEX: str = "source texture key"
	KEY_X: str = "x"
	KEY_Y: str = "y"
	KEY_W: str = "w"
	KEY_H: str = "h"

	def __init__(self, entityName: str, filename: str, srcTexKey: str, x: int, y: int, w: int, h: int) -> None:
		self._sprKey: str = entityName + " " + jns.GetAdjustedFilename(filename)
		self._srcTexKey: str = srcTexKey
		self._x: int = x
		self._y: int = y
		self._w: int = w
		self._h: int = h

	def GetDict(self) -> dict:
		return {
			Sprite.KEY_SPRKEY: self._sprKey,
			Sprite.KEY_SRCTEX: self._srcTexKey,
			Sprite.KEY_X: self._x,
			Sprite.KEY_Y: self._y,
			Sprite.KEY_W: self._w,
			Sprite.KEY_H: self._h
		}

"""
generate a spritesheet for an entity given an entity name and a list of filenames
this will generate a spritesheet where each row in the sheet contains the frames of a single animation in order
the returned data will include the filename, and the locations of all the sprites in the sheet
"""
def GenerateEntitySpritesheet(entityName: str, filenames: list[str]) -> dict:
	pass

class EntitySpritesheet:

	def __init__(self, entityName: str, filenames: list[str]) -> None:
		self._filenames: list[str] = filenames
		self._filenames.sort() # sorted, so that later ops are easier
		print(self._filenames)

		# dictionary where the key is the filename, and the value is a tuple containing x/y/w/h in that order
		self._data: dict[str, tuple[int, int, int, int]] = {}
		
		# overall width and height of the spritesheet
		self._width: int = 0
		self._height: int = 0

		self._outputFilename: str = f"{entityName}_spritesheet.png"

		self._outputFilePath: str = os.path.join(jns.PATH_ASSETS_TEXTURES_ENTITIES, entityName)
		#			NOTE: make it relative because the game uses relative paths
		#								 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
		self._texture: Texture = Texture(os.path.relpath(self._outputFilePath), self._outputFilename, False) # TODO: don't hard-code this to have no smoothing

		# generate the data for the spritesheet, but don't actually generate the sheet yet

		# make a list of unique animation names
		animNames: list[str] = []
		for filename in self._filenames:
			animName: str = filename.split("_")[0] # TODO: this is bad code. find a better way to do this
			if animName not in animNames:
				animNames.append(animName)

		xPos: int = 0
		yPos: int = 0
		# create the data
		for animName in animNames:
			tallestHeight: int = 0
			for filename in self._filenames: # because self._filenames is sorted, we know the frames of an animation will be in order
				if animName in filename:
					filePath: str = os.path.join(jns.PATH_ASSETS_TEXTURES_ENTITIES, entityName, filename)
					# create and store the x/y/w/h for the image
					with Image.open(filePath) as img:
						x: int = xPos
						y: int = yPos
						w: int = img.size[0]
						h: int = img.size[1]
						self._data[filename] = (x, y, w, h)
					# prep for next image
					xPos += w
					# update tallest image height
					if h > tallestHeight:
						tallestHeight = h
			# update sheet size
			self._width += xPos
			self._height += tallestHeight
			# prep to start a new row
			xPos = 0
			yPos += tallestHeight

	def GetDict(self) -> dict:
		return self._texture.GetDict()
	
	def GetKey(self) -> str:
		return self._texture.GetKey()

	"""
	get the x/y/w/h of a sprite in the sheet by filename
	this will return a tuple of four ints, where each int is x, y, width, height, in that order
	"""
	def GetFileCoords(self, filename: str) -> tuple[int, int, int, int]:
		assert filename in self._filenames, f"File not found in spritesheet: \"{filename}\""
		return self._data[filename]

	"""
	use data generated on construction to actually write or create the spritesheet as an image file in the filesystem
	"""
	def CreateSheet(self) -> None:
		sheet = Image.new(mode="RGBA", size=(self._width, self._height))
		for filename in self._filenames:
			sprFilePath: str = os.path.join(self._outputFilePath, filename)
			coords: tuple[int, int] = (self._data[filename][0], self._data[filename][1])
			with Image.open(sprFilePath) as spr:
				sheet.paste(im=spr, box=coords)
		sheet.save(os.path.join(self._outputFilePath, self._outputFilename))

class TileSpritesheet:

	def __init__(self, filenames: list[str]) -> None:
		pass

def CreateData() -> dict:
	KEY_TEXTURES: str = "textures"
	KEY_SPRITES: str = "sprites"
	KEY_LEVELDATA: str = "leveldata"
	result: dict = {
		KEY_TEXTURES: [],
		KEY_SPRITES: [],
		KEY_LEVELDATA: []
	}

	entityNames: list[str] = jns.GetFoldersAtPath(jns.PATH_ASSETS_TEXTURES_ENTITIES)
	for entityName in entityNames:
		entityPath: str = os.path.join(jns.PATH_ASSETS_TEXTURES_ENTITIES, entityName)
		spriteFilenames: list[str] = jns.GetFilesWithConvention(entityPath, jns.CONVENTION_SPR_ENTITY)
		
		# part 1a: generate texture data for entity sprites
		sheet: EntitySpritesheet = EntitySpritesheet(entityName, spriteFilenames)
		result[KEY_TEXTURES].append(sheet.GetDict())
		sheet.CreateSheet()

		# part 1b: generate sprite data for entity sprites
		for filename in spriteFilenames:
			coords: tuple[int, int, int, int] = sheet.GetFileCoords(filename)
			x: int = coords[0]
			y: int = coords[1]
			w: int = coords[2]
			h: int = coords[3]
			spr: Sprite = Sprite(entityName, filename, sheet.GetKey(), x, y, w, h)
			result[KEY_SPRITES].append(spr.GetDict())

	# part 2a: generate texture data for leveltile sprites
	# part 2b generate sprite data for leveltile sprites

	# TODO: part 3: generate leveldata for maps

	return result

def WriteData(data: dict) -> None:
	FILENAME: str = "assetSetupFile_2.json"
	filePath: str = os.path.join(jns.PATH_ASSETS, FILENAME)
	with open(file=filePath, mode='w') as jsonFile:
		json.dump(data, jsonFile, indent=4)

if __name__ == "__main__":
	WriteData(CreateData())