import os.path
import json
import tkinter as tk
import tkinter.ttk as ttk

import jnscommon as jns

class Point:

	def __init__(self, name, x, y):
		self.name = name
		self.x = x
		self.y = y

	def GetDict(self) -> dict[str, float]:
		return {
			"posX": self.x,
			"posY": self.y
		}

class PointData:

	def __init__(self, filePath):
		self.filePath = filePath
		#           filename  list of points
		#               vvv  vvvvvvvvvvv
		self.data: dict[str, list[Point]]
		#        filename   point name
		#             vvv       vvv       vvv
		rawData: dict[str, dict[str, dict[str, float]]]
		if os.path.exists(filePath):
			print(f"Reading json file at path: {filePath}")
			with open(self.filepath, 'r') as jsonFile:
				rawData = json.loads(jsonFile)
			print("Successfully read!")
			
		else:
			print(f"Json file at the following path does not extist: {filePath}")
			with open(self.filePath, 'x'):
				print("Creating it now...")
			print("Created!")

	def Write(self):
		assert False

class EntityEditor:

	def __init__(self) -> None:

		############################
		# create non-gui variables #
		############################

		# constants

		self.POINT_DATA_FILENAME: str = "points.json"

		# other variables

		self.path = os.path.abspath(os.path.join("..", "jumpnslash-cpp", "Jump-n-Slash", "assets", "textures", "player"))
		self.pointData: PointData = PointData(os.path.join(self.path, self.POINT_DATA_FILENAME))

		#####################
		# create gui window #
		#####################
		
		self.root: tk.Tk = tk.Tk()
		self.root.title("Entity Editor")

	def Run(self) -> None:
		self.root.mainloop()

editor: EntityEditor = EntityEditor()
editor.Run()