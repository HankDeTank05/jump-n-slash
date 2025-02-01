# language imports
import os.path
import tkinter as tk
import json

# game imports
import jnscommon as jns

class Model:
	
	def __init__(self) -> None:
		# selections
		self._selectedEntity: str = ""
		self._selectedAnim: str = ""
		self._selectedSpr: str = ""
		# lists
		self._entityList: list[str] = jns.GetFoldersAtPath(jns.READ_LOCATION_TEXTURES_ENTITIES)
		self._animList: list[str] = []
		self._sprList: list[str] = []
		self._ptList: list[Point] = []
		# dicts
		self._sprImgDict: dict[str, tk.PhotoImage] = {} # key=filename, value=corresponding image
		# point data
		self._pointData: PointData | None = None

	def GetEntityList(self) -> list[str]:
		return self._entityList

	def GetAnimList(self) -> list[str]:
		return self._animList
	
	def GetSprNameList(self) -> list[str]:
		return self._sprList
	
	def GetSprImgList(self) -> list[tk.PhotoImage]:
		imgList: list[tk.PhotoImage] = []
		for filename in self._sprList:
			imgList.append(self._sprImgDict[filename])
		return imgList

	def GetPtList(self) -> list:
		return self._ptList

	def SelectEntity(self, entityName: str) -> None:
		if entityName != self._selectedEntity:
			self._selectedEntity = entityName # set the newly selected entity
			self._selectedAnim = "" # deselect whatever animation we had previously selected
			self._selectedSpr = "" # deselect whatever sprite we had previously selected
			# TODO: deselect whatever point we had previously selected
			self._animList = [] # clear the animation list before re-generating it

			# point data is stored by entity, so we can load point data once the entity has been selected
			if self._pointData is not None:
				assert self._pointData.HasUnsavedChanges() == False # TODO: raise a popup warning about unsaved changes (instead of having this assert)
			entityPath: str = os.path.join(jns.READ_LOCATION_TEXTURES_ENTITIES, entityName)
			self._pointData = PointData(entityPath)

			# generate a list of animations for the current entity
			entityFilenames: list[str] = jns.GetFilesWithConvention(entityPath, jns.CONVENTION_SPR_ENTITY)

			for entityFilename in entityFilenames:
				# get the animation name from the filename
				animName: str = entityFilename.split("_")[0] # TODO: come up with a better way to get the animation name from the filename
				# only add unique animation names to the animation list
				if animName not in self._animList:
					self._animList.append(animName)

	def SelectAnim(self, animName: str) -> None:
		if animName != self._selectedAnim:
			self._selectedAnim = animName # set the newly selected animation
			self._selectedSpr = "" # deselect whatever sprite we had previously selected
			# TODO: deselect whatever point we had previously selected
			self._sprList = [] # clear the sprite list before re-generating it
			# NOTE: we do NOT clear out self._sprImgDict because we may want to access the images multiple times

			# generate a list of sprite filenames for the current animation
			entityPath: str = os.path.join(jns.READ_LOCATION_TEXTURES_ENTITIES, self._selectedEntity)
			entityFilenames: list[str] = jns.GetFilesWithConvention(entityPath, jns.CONVENTION_SPR_ENTITY)

			for entityFilename in entityFilenames:
				# only add the filename to the sprite list if the animation name is found in the filename
				if animName in entityFilename:
					self._sprList.append(entityFilename)
					# only add an image to the dict if it has not already been loaded
					if entityFilename not in self._sprImgDict.keys():
						imgPath: str = os.path.join(entityPath, entityFilename)
						self._sprImgDict[entityFilename] = tk.PhotoImage(file=imgPath, name=entityFilename)
	
	def SelectSpr(self, sprFilename: str) -> None:
		if sprFilename != self._selectedSpr:
			self._selectedSpr = sprFilename # set the newly selected sprite
			# TODO: deselect whatever point we had previously selected
			self._ptList = self._pointData.GetPointsForSprite(self._selectedSpr) # the PointData class will generate this list for us. easy!

	def AddPoint(self, ptName: str) -> None:
		self._pointData.AddPt(self._selectedSpr, ptName)

class Point:

	KEY_X: str = "x"
	KEY_Y: str = "y"

	def __init__(self, name: str, x: float | None = None, y: float | None = None) -> None:
		self.name: str = name
		self.x: float | None = x
		self.y: float | None = y

	def GetDict(self) -> dict[str, dict[str, float | None]]:
		return { self.name: { Point.KEY_X: self.x, Point.KEY_Y: self.y } }

class PointData:

	FILE_NAME: str = "points.json"

	POINT_NAMES_KEY: str = "pointNames"
	SPRITES_KEY: str = "sprites"

	def __init__(self, entityPath: str) -> None:
		self._filePath: str = os.path.join(entityPath, PointData.FILE_NAME)
		self._unsavedChanges: bool = False
		#            sprFilename   pointName
		#                  vvv       vvv
		self._points: dict[str, dict[str, Point]] = {}
		
		if os.path.isfile(self._filePath):
			# load a json file and create points
			print(f"Loading existing point data from {self._filePath}")
			self._LoadJsonData()
		else:
			# create empty point data
			print(f"No existing point data to load from {self._filePath}")
			self._CreateNewData(entityPath)
			self._unsavedChanges = True

	def HasUnsavedChanges(self) -> bool:
		return self._unsavedChanges

	def GetPointsForSprite(self, sprFilename: str) -> list[Point]:
		assert sprFilename in self._points.keys()
		return list(self._points[sprFilename].values())
	
	def AddPt(self, sprFilename: str, ptName: str) -> None:
		assert sprFilename in self._points.keys()
		assert ptName not in self._points[sprFilename].keys()
		self._points[sprFilename][ptName] = Point(ptName)

	def _CreateNewData(self, entityPath: str) -> None:
		assert len(self._points.keys()) == 0 # self._points MUST BE EMPTY when this function is called
		sprFilenames: list[str] = jns.GetFilesWithConvention(entityPath, jns.CONVENTION_SPR_ENTITY)
		for sprFilename in sprFilenames:
			self._points[sprFilename] = {}

	def _LoadJsonData(self) -> None:
		with open(self._filePath, 'r') as jsonFile:
			loadedData: dict = json.load(jsonFile)
		pointNameList: list[str] = loadedData[PointData.POINT_NAMES_KEY]
		print(pointNameList)

	def _SaveJsonData(self) -> None:
		pass
