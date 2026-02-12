# language imports
import tkinter as tk
import sys
import os

# Set up path to allow importing from parent directory (jnscommon)
current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(current_dir)
sys.path.append(parent_dir)

# game imports
from model import Model
from view import View
from controller import Controller

if __name__ == "__main__":
	root: tk.Tk = tk.Tk()

	model: Model = Model()
	view: View = View(root)
	controller: Controller = Controller(model, view)

	root.mainloop()
