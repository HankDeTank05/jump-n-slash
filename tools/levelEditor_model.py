# language imports
import tkinter as tk
import os.path

# game imports
import jnscommon as jns

class Model:

	def __init__(self) -> None:
		#               filename    corresponding image to be used
		#                    vvv  vvvvvvvvvvvvv
		self._tileImgs: dict[str, tk.PhotoImage] = {} # TODO: at some point we need to switch from tk.PhotoImage over to PIL images
		self._LoadAllImages()

		# the filename of the currently selected tile to be used to edit the map
		self._brushTileName: str = list(self._tileImgs.keys())[0]

		self._tileData: dict # TODO: (len) specify type hint more in detail

	######################
	# internal functions #
	######################

	def _LoadAllImages(self) -> None:
		fileList: list[str] = jns.GetFilesWithConvention(jns.READ_LOCATION_TEXTURES_LEVELTILES, jns.CONVENTION_SPR_LEVELTILE)
		for filename in fileList:
			filePath: str = os.path.join(jns.READ_LOCATION_TEXTURES_LEVELTILES, filename)
			self._tileImgs[filename] = tk.PhotoImage(file=filePath, name=filename)

	#############
	# accessors #
	#############

	def GetTileImages(self) -> dict[str, tk.PhotoImage]:
		return self._tileImgs

	############
	# mutators #
	############

	def SelectBrushTile(self, filename: str) -> None:
		assert filename in list(self._tileImgs.keys()), f"Trying to set invalid tile filename as the brush tile: \"{filename}\""
		self._brushTileName = filename

	# TODO: (henry) tile palette data code
	# TODO: (len) tile details data code