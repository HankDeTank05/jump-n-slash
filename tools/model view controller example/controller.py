from model import Model
from view import View

class Controller:

	def __init__(self, model: Model, view: View) -> None:
		self.model: Model = model
		self.view: View = view

		# set the view's button command to the greet function
		self.view.SetButtonCommand(self.Greet)

	def Greet(self) -> None:
		name: str = self.view.GetName()
		self.model.SetName(name)
		greetingMessage: str = f"Hello, {self.model.GetName()}!"
		self.view.SetGreeting(greetingMessage)