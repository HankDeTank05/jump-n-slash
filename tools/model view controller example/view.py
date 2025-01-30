import tkinter as tk

class View:

	def __init__(self, master) -> None:
		self.master = master
		self.master.title("MVC Example")

		self.label: tk.Label = tk.Label(master, text="Enter your name:")
		self.label.pack()

		self.entry: tk.Entry = tk.Entry(master)
		self.entry.pack()

		self.button: tk.Button = tk.Button(master, text="Greet", command=None) # NOTE: controller will set the command
		self.button.pack()

		self.greetingLabel: tk.Label = tk.Label(master, text="")
		self.greetingLabel.pack()

	def GetName(self) -> str:
		return self.entry.get()
	
	def SetGreeting(self, message: str) -> None:
		self.greetingLabel.config(text=message)

	def SetButtonCommand(self, command) -> None:
		self.button.config(command=command)