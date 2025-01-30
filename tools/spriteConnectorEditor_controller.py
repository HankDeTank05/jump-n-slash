# app imports
from spriteConnectorEditor_model import Model
from spriteConnectorEditor_view import View

class Controller:
	
	def __init__(self, model: Model, view: View) -> None:
		self.model: Model = model
		self.view: View = view

		# set the buttons for the entity selector
		entityList: list[str] = self.model.entitySelector.GetEntityList()
		callback: function = self.SelectEntity
		self.view.entitySelector.PopulateButtonList(entityList, callback)

	def SelectEntity(self, entityName: str) -> None:
		animList: list[str] = self.model.animSelector.GetSelectionOptions(entityName)
		self.view.animationSelector.PopulateButtonList(animList)

	def SelectAnim(self, animName: str) -> None:
		pass

	def SelectSpr(self, sprName: str) -> None:
		pass

	def SelectPoint(self, pointName: str) -> None:
		pass