# language imports
import os.path
import tkinter as tk

# game imports
import jnscommon as jns

class Model:
	
	def __init__(self) -> None:
		# lists
		self._entityList: list[str] = jns.GetFoldersAtPath(jns.READ_LOCATION_TEXTURES_ENTITIES)
		self._animList: list[str] = []
		# selections
		self._selectedEntity: str = ""
		self._selectedAnim: str = ""

	def GetEntityList(self) -> list[str]:
		return self._entityList

	def GetAnimList(self) -> list[str]:
		return self._animList

	def SelectEntity(self, entityName: str) -> None:
		if entityName != self._selectedEntity:
			self._selectedEntity = entityName
			self._animList = [] # clear the animation list before re-generating it

			# generate a list of animations for the current entity
			entityPath: str = os.path.join(jns.READ_LOCATION_TEXTURES_ENTITIES, entityName)
			entityFilenames: list[str] = jns.GetFilesWithConvention(entityPath, jns.CONVENTION_SPR_ENTITY)

			for entityFilename in entityFilenames:
				# get the animation name from the filename
				animName: str = entityFilename.split("_")[0] # TODO: come up with a better way to get the animation name from the filename
				if animName not in self._selectionOptions:
				# only add unique animation names to the selection options list
					self._animList.append(animName)

	
class EntitySelectorModel:

	def __init__(self, basePath: str) -> None:
		self._entityList: list[str] = jns.GetFoldersAtPath(basePath)

	def GetEntityList(self) -> list[str]:
		return self._entityList
	
class AnimationSelectorModel:

	def __init__(self) -> None:
		self._selectedEntity: str = ""
		self._selectionOptions: list[str] = []
		

	def GetSelectionOptions(self, entityName: str) -> list[str]:
		if entityName != self._selectedEntity:
			# clear the list before re-generating it
			self._selectedEntity = entityName
			self._selectionOptions = []

			# generate a list of animations for the current entity
			entityPath: str = os.path.join(jns.READ_LOCATION_TEXTURES_ENTITIES, entityName)
			entityFilenames: list[str] = jns.GetFilesWithConvention(entityPath, jns.CONVENTION_SPR_ENTITY)

			for entityFilename in entityFilenames:
				# get the animation name from the filename
				animName: str = entityFilename.split("_")[0] # TODO: come up with a better way to get the animation name from the filename
				if animName not in self._selectionOptions:
				# only add unique animation names to the selection options list
					self._selectionOptions.append(animName)

		return self._selectionOptions
