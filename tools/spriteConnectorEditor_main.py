# language imports
import tkinter as tk
import tkinter.ttk as ttk

# app imports
from spriteConnectorEditor_model import Model
from spriteConnectorEditor_view import View
from spriteConnectorEditor_controller import Controller

if __name__ == "__main__":
	root: tk.Tk = tk.Tk()
	model: Model = Model()
	view: View = View(root)
	controller: Controller = Controller(model, view)

	root.mainloop()