from PyQt5.QtCore import QObject, pyqtSlot, pyqtProperty, pyqtSignal # type: ignore
from PyQt5.QtCore import QUrl # type: ignore
from PyQt5.QtQml import qmlRegisterType #type: ignore
import json
#supressing errors never goes wrong...
class Backend(QObject):
    levelChanged = pyqtSignal()

    def __init__(self, grid_width=100, grid_height=100):
        super().__init__()
        self.grid_width = grid_width
        self.grid_height = grid_height
        # Default selected sprite (e.g., an empty tile image)
        self._selectedSprite = "assets/empty.png"
        # Initialize grid data with the default sprite
        self.grid_data = [[self._selectedSprite for _ in range(self.grid_width)] for _ in range(self.grid_height)]

    @pyqtSlot(str)
    def setSelectedSprite(self, imageSource):
        self._selectedSprite = imageSource
        print(f"Selected sprite set to: {imageSource}")

    @pyqtSlot(int)
    def setTileSprite(self, index):
        row = index // self.grid_width
        col = index % self.grid_width
        self.grid_data[row][col] = self._selectedSprite
        print(f"Tile at index {index} set to sprite {self._selectedSprite}")
        # Optionally emit a signal if you want to update individual tiles

    @pyqtSlot(int, result=str)
    def getTileImageSource(self, index):
        row = index // self.grid_width
        col = index % self.grid_width
        return self.grid_data[row][col]

    @pyqtSlot()
    def clearLevel(self):
        self.grid_data = [[self._selectedSprite for _ in range(self.grid_width)] for _ in range(self.grid_height)]
        print("Level cleared.")
        self.levelChanged.emit()

    @pyqtSlot()
    def saveToFile(self):
        with open('level_data.json', 'w') as f:
            json.dump(self.grid_data, f)
        print("Level data saved.")

    @pyqtSlot()
    def loadFromFile(self):
        try:
            with open('level_data.json', 'r') as f:
                self.grid_data = json.load(f)
            print("Level data loaded.")
            self.levelChanged.emit()
        except FileNotFoundError:
            print("No saved level data found.")
        except json.JSONDecodeError:
            print("Error decoding level data.")

    @pyqtProperty(str)
    def selectedSprite(self):
        return self._selectedSprite