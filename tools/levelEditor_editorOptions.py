# language imports
import tkinter.ttk as ttk

class GuiEditorOptions:

	def __init__(self, parent: any, column: int, row: int, columnspan: int, rowspan: int, padx: int, pady: int, sticky: str) -> None:
		############################
		# create the non-gui stuff #
		############################

		# code goes here

		########################
		# create the gui stuff #
		########################
		
		# create the parent frame
		self.w_parentFrame: ttk.LabelFrame = ttk.LabelFrame(parent, text="Editor Options")
		self.w_parentFrame.grid(column=column, row=row,
						  columnspan=columnspan, rowspan=rowspan,
						  padx=padx, pady=pady,
						  sticky=sticky)


		self.w_placeholderLabel: ttk.Label = ttk.Label(self.w_parentFrame, text="coming soon")
		self.w_placeholderLabel.grid(column=0, row=0)
