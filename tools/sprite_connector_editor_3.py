import os.path
import json
import tkinter as tk
import tkinter.ttk as ttk
from functools import partial

import jnscommon as jns

# constant variables
POINT_DATA_FILENAME: str = "points.json"

class Point:

	def __init__(self, name: str, x: float, y: float):
		self.name: str = name
		self.x: float = x
		self.y: float = y

	def __repr__(self) -> str:
		return f"({self.x}, {self.y}) : {self.name}"

	def GetDict(self) -> dict[str, float]:
		return {
			"posX": self.x,
			"posY": self.y
		}

class PointData:

	def __init__(self, readPath: str):
		self.readPath: str = readPath
		self.filePath: str = os.path.join(self.readPath, POINT_DATA_FILENAME)

		#           filename  list of points
		#               vvv  vvvvvvvvvvv
		self.data: dict[str, list[Point]]

		#        filename   point name  "posX"/"posY"
		#             vvv       vvv       vvv
		rawData: dict[str, dict[str, dict[str, float]]] = None

		if os.path.exists(self.filePath):
			# read the data from the json file
			print(f"Reading json file at path: {self.filePath}")
			with open(self.filePath, 'r') as jsonFile:
				rawData = json.load(jsonFile)
			print("Successfully read!")

			# convert the json data to python format
			assert rawData is not None
			self.data = self.ConvertJsonToPython(rawData)
			print("Converted json data to python format")
			print("The following data has been read:")
			jns.PrintDict(self.data)
			
		else:
			print(f"Json file at the following path does not extist: {self.filePath}")
			with open(self.filePath, 'x') as jsonFile:
				print("Creating it now...")
				json.dump({}, jsonFile) # write an empty dict to the points file
			print("Created!")
			self.data = self.CreateEmptyPythonData()

	def __repr__(self) -> str:
		return jns.PrintDict(self.data, printResult=False)

	def CreateEmptyPythonData(self) -> dict:
		pyData: dict = {}
		filenames: list[str] = jns.GetFilesWithConvention(self.readPath, jns.CONVENTION_SPRITE_ENTITY)
		for filename in filenames:
			pyData[filename] = []
		return pyData

	def ConvertJsonToPython(self, rawData: dict) -> dict:
		pyData: dict = {}
		for filename in rawData.keys():
			pyData[filename] = []
			for pointName in rawData[filename].keys():
				xPos: float = rawData[filename]["posX"]
				yPos: float = rawData[filename]["posY"]
				pyData[filename].append(Point(pointName, xPos, yPos))
		return pyData

	def ConvertPythonToJson(self, pyData: dict) -> dict:
		rawData: dict = {}
		for filename in pyData.keys():
			rawData[filename] = {}
			for point in pyData[filename]:
				pointName: str = point.name
				rawData[filename][pointName] = point.GetDict()
		return rawData

	def GetPoints(self, sprFilename: str) -> list[Point]:
		# print(sprFilename)
		# jns.PrintDict(self.data)
		assert sprFilename in self.data.keys()
		return self.data[sprFilename]

	def Write(self) -> None:
		# convert the python data to json format
		rawData: dict = self.ConvertPythonToJson(self.data)
		print("Converted python data to json format")
		print("The following data will be written:")
		jns.PrintDict(rawData)
		with open(self.filePath, 'w') as jsonFile:
			json.dump(rawData, jsonFile)

class GuiSpriteSelector:

	def __init__(self, readPath: str, parent, sprSelectCallback) -> None:
		# create non-widget variables
		self.readPath: str = readPath
		self.filenames: list[str] = jns.GetFilesWithConvention(self.readPath, jns.CONVENTION_SPRITE_ENTITY)
		assert(len(self.filenames) > 0) # make sure there are filenames in the list
		self.currSpr = self.filenames[0]
		self.sprSelectCallback = sprSelectCallback

		# create widgets

		# label frame to contain everything
		self.w_container: ttk.LabelFrame = ttk.LabelFrame(parent, text="Sprite Selector")
		self.w_container.grid(column=0, row=0) # TODO: make it so the r/c position are arguments passed to the constructor

		# canvas to contain all the buttons
		self.w_canvas: tk.Canvas = tk.Canvas(self.w_container)
		self.w_canvas.grid(column=0, row=0)

		# list of buttons on the canvas
		self.sprBtnList: list[ttk.Button] = []
		for i in range(len(self.filenames)):
			filename: str = self.filenames[i]
			button: ttk.Button = ttk.Button(self.w_canvas, text=filename, command=partial(self.SelectSprite, filename))
			button.grid(column=0, row=i)
			self.sprBtnList.append(button)

		# TODO: scrollbar for the canvas

	def SelectSprite(self, sprFilename: str) -> None:
		self.currSpr = sprFilename
		self.sprSelectCallback()

	def GetCurrentSprite(self) -> str:
		return self.currSpr
	
class GuiPointItem:

	def __init__(self, point: Point, column: int, row: int) -> None:
		# create widgets

		# frame to contain everything
		self.w_container: ttk.Frame = ttk.Frame
		self.w_container.grid(column=column, row=row)

		# label for the point name
		self.w_nameLabel: ttk.Label = ttk.Label(self.w_container, text=point.name)
		self.w_nameLabel.grid(column=0, row=0, columnspan=2)

		# label for the point position
		self.w_posLabel: ttk.Label = ttk.Label(self.w_container, text=f"({point.x}, {point.y})") # TODO: make this text show the point pos when it changes
		self.w_posLabel.grid(column=0, row=1, columnspan=2)
		
		# button to set position
		self.w_setBtn: ttk.Button = ttk.Button(self.w_container, text="Set") # TODO: set a command for this button
		self.w_setBtn.grid(column=0, row=2)

		# button to clear position
		self.w_clearBtn: ttk.Button = ttk.Button(self.w_container, text="Clear") # TODO: set a command for this button
		self.w_clearBtn.grid(column=1, row=2)

class GuiPointList:

	def __init__(self, readPath: str, parent, ptSetCallback, ptClearCallback) -> None:
		###############################
		# create non-widget variables #
		###############################

		self.readPath: str = readPath
		self.pointData: PointData = PointData(self.readPath)

		##################
		# create widgets #
		##################

		# label frame to contain everything
		self.w_container: ttk.LabelFrame = ttk.LabelFrame(parent, text="Point List")
		self.w_container.grid(column=1, row=0) # TODO: make it so the r/c position are arguments passed to the constructor

		# canvas to contain all the buttons
		self.w_canvas: tk.Canvas = tk.Canvas(self.w_container)
		self.w_canvas.grid(column=0, row=0)

		# list of point items
		self.ptItemList: list[GuiPointItem] = []

		# "create new point" button
		self.w_newPointBtn: ttk.Button = ttk.Button(self.w_canvas, text="Create New Point", command=partial(self.PopupNewPointOpen)) # TODO: add a command for when this button is clicked

	def PopupNewPointOpen(self) -> None:
		assert False

	def PopupNewPointClose(self) -> None:
		assert False

	def AddPointItem(self, point: Point, column: float, row: float) -> None:
			self.ptItemList.append(GuiPointItem(point, column, row))

	def PopulatePointList(self, sprFilename: str) -> None:
		while len(self.ptItemList) > 0:
			item: GuiPointItem = self.ptItemList.pop()
			item.Destroy()
		
		# populate the item list with point items
		assert len(self.ptItemList) == 0
		pointList: list[Point] = self.pointData.GetPoints(sprFilename)
		for i in range(len(pointList)):
			point: Point = pointList[i]
			self.AddPointItem(point, 0, i)

		# put the "create new point" button at the end
		self.w_newPointBtn.grid(column=0, row=len(self.ptItemList))

	def SelectSprite(self, sprFilename: str) -> None:
		self.PopulatePointList(sprFilename)

class GuiPointEditor:

	def __init__(self) -> None:
		pass

class GuiConnectorEditor:

	def __init__(self) -> None:

		############################
		# create non-gui variables #
		############################

		self.path: str = os.path.abspath(os.path.join("..", "jumpnslash-cpp", "Jump-n-Slash", "assets", "textures", "player"))

		#####################
		# create gui window #
		#####################
		
		self.root: tk.Tk = tk.Tk()
		self.root.title("Entity Editor")
		self.root.protocol("WM_DELETE_WINDOW", self.SaveBeforeClosing) # make sure the application saves data before closing

		# create the sprite selector
		self.sprSelector: GuiSpriteSelector = GuiSpriteSelector(self.path, self.root, self.SelectSprite)
		self.currSpr: str

		# create the point list
		self.ptList: GuiPointList = GuiPointList(self.path, self.root, self.SetPoint, self.ClearPoint)

		# TODO: create the point editor

		##########################
		# set up the application #
		##########################

		self.SelectSprite()

	#################################
	# callbacks for sprite selector #
	#################################
	
	def SelectSprite(self) -> None:
		self.currSpr = self.sprSelector.GetCurrentSprite()
		self.ptList.SelectSprite(self.currSpr)
		print(f"selected {self.currSpr}")

	############################
	# callbacks for point list #
	############################

	def SetPoint(self) -> None:
		pass

	def ClearPoint(self) -> None:
		pass

	###################
	# other functions #
	###################

	def SaveBeforeClosing(self) -> None:
		pointData: PointData = self.ptList.pointData # get the point data
		pointData.Write() # write it
		self.root.destroy() # close the window

	def Run(self) -> None:
		self.root.mainloop()

editor: GuiConnectorEditor = GuiConnectorEditor()
editor.Run()