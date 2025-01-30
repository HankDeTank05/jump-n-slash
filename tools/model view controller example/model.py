class Model:

	def __init__(self) -> None:
		self.name: str = ""

	def SetName(self, name: str) -> None:
		self.name = name

	def GetName(self) -> str:
		return self.name