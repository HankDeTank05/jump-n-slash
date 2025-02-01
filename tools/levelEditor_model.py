# language imports
import tkinter as tk

# game imports
import jnscommon as jns

class Model:

	def __init__(self) -> None:
		#               filename    corresponding image to be used
		#                    vvv  vvvvvvvvvvvvv
		self._tileImgs: dict[str, tk.PhotoImage] # TODO: at some point we need to switch from tk.PhotoImage over to PIL images

		# the filename of the currently selected tile to be used to edit the map
		self._brushTileName: str

		self._tileData: dict # TODO: (len) specify type hint more in detail

	# TODO: (henry) tile palette data code
	# TODO: (len) tile details data code