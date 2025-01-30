# language imports
import os.path
import tkinter as tk

# game imports
import jnscommon as jns

class Model:
	
	def __init__(self) -> None:
		self.entitySelector: EntitySelectorModel = EntitySelectorModel(jns.READ_LOCATION_TEXTURES_ENTITIES)
		self.animSelector: AnimationSelectorModel = AnimationSelectorModel(self.entitySelector.GetEntityList())
	
class EntitySelectorModel:

	def __init__(self, basePath: str) -> None:
		self._entityList: list[str] = jns.GetFoldersAtPath(basePath)

	def GetEntityList(self) -> list[str]:
		return self._entityList
	
class AnimationSelectorModel:

	def __init__(self, entityList: list[str]) -> None:
		# key: entity name
		# value: list of animations for that entity
		self._selectionOptions: dict[str, list[str]] = {}

		# generate selection options
		for entityName in entityList:
			self._selectionOptions[entityName] = []
			
			# generate a list of animations for the current entity
			entityPath: str = os.path.join(jns.READ_LOCATION_TEXTURES_ENTITIES, entityName)
			entityFilenames: list[str] = jns.GetFilesWithConvention(entityPath, jns.CONVENTION_SPR_ENTITY)

			for entityFilename in entityFilenames:
				# get the animation name from the filename
				animName: str = entityFilename.split("_")[0] # TODO: come up with a better way to get the animation name from the filename
				if animName not in self._selectionOptions[entityName]:
				# only add unique animation names to the selection options list
					self._selectionOptions[entityName].append(animName)
		

	def GetSelectionOptions(self, entityName: str) -> list[str]:
		assert entityName in self._selectionOptions.keys()
		return self._selectionOptions[entityName]
