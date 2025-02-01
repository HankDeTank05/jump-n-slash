# language imports
import tkinter as tk

# game imports
from levelEditor_model import Model
from levelEditor_view import View
from levelEditor_controller import Controller

if __name__ == "__main__":
	root: tk.Tk = tk.Tk()

	model: Model = Model()
	view: View = View(root)
	controller: Controller = Controller(model, view)

	root.mainloop()