# language imports
import tkinter as tk

# app imports
from spriteConnectorEditor_model import Model
from spriteConnectorEditor_view import View
from spriteConnectorEditor_model import Point

class Controller:
	
	def __init__(self, model: Model, view: View) -> None:
		self.model: Model = model
		self.view: View = view

		entityList: list[str] = self.model.GetEntityList()
		self.view.entitySelector.PopulateButtonList(entityList, self.SelectEntity)

		self.view.ptSelector.SetAddPointCommand(self.AddPoint)

	def SelectEntity(self, entityName: str) -> None:
		self.model.SelectEntity(entityName)
		animList: list[str] = self.model.GetAnimList()
		self.view.animSelector.PopulateButtonList(animList, self.SelectAnim) # populate the animation selector
		self.view.sprSelector.DepopulateButtonList() # depopulate the sprite selector
		self.view.ptSelector.DepopulateItemList() # depopulate the point selector
		# TODO: clear the point editor

	def SelectAnim(self, animName: str) -> None:
		self.model.SelectAnim(animName)
		sprNameList: list[str] = self.model.GetSprNameList()
		sprImgList: list[tk.PhotoImage] = self.model.GetSprImgList()
		self.view.sprSelector.PopulateButtonList(sprNameList, sprImgList, self.SelectSpr) # populate the sprite selector
		self.view.ptSelector.DepopulateItemList() # depopulate point selector
		# TODO: depopulate the point editor

	def SelectSpr(self, sprFilename: str) -> None:
		self.model.SelectSpr(sprFilename)
		ptList: list[Point] = self.model.GetPtList()
		self.view.ptSelector.PopulateItemList(ptList) # populate the point list
		# TODO: populate the point editor in "awaiting point selection" mode

	def SelectPoint(self, ptName: str) -> None:
		pass

	def AddPoint(self, ptName: str) -> None:
		self.model.AddPoint(ptName) # add the point
		ptList: list[Point] = self.model.GetPtList() # get the new point list
		self.view.ptSelector.PopulateItemList(ptList) # re-populate the item list now that we've added a new point