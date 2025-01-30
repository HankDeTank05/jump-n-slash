import tkinter as tk
from controller import Controller
from model import Model
from view import View

if __name__ == "__main__":
	root: tk.Tk = tk.Tk()
	model: Model = Model()
	view: View = View(root)
	controller: Controller = Controller(model, view)

	root.mainloop()