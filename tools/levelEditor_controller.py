# game imports
from levelEditor_model import Model
from levelEditor_view import View

class Controller:

	def __init__(self, model: Model, view: View) -> None:
		self.model: Model = model
		self.view: View = view

	# TODO: (henry) tile palette controller code
	# TODO: (len) tile details controller code
