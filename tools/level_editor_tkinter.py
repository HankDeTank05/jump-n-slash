from tkinter import *

class App:

	def __init__(self):
		self.root = Tk()
		self.root.minsize(width=1280, height=720)
		self.grid = Grid(self.root)

	def Run(self):
		self.root.mainloop()

class Grid:

	def __init__(self, parent):
		self.frame = Frame(parent)
		self.frame.grid(column=0, row=0)
		
		self.canvas = Canvas(self.frame)
		self.canvas.grid(column=0, row=0)
		self.buttons = []
		size = 100
		for y in range(size):
			self.buttons.append([])
			for x in range(size):
				self.buttons[y].append(Button(self.canvas, text=f"({x},{y})"))
				self.buttons[y][x].grid(column=x, row=y)

		self.hScroll = Scrollbar(parent, orient="horizontal", command=self.canvas.xview)
		self.hScroll.grid(column=0, row=1, sticky=[E,W])
		self.vScroll = Scrollbar(parent, orient="vertical", command=self.canvas.yview)
		self.vScroll.grid(column=1, row=0, sticky=[N,S])

app = App()
app.Run()
