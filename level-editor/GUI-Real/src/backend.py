from PyQt5.QtCore import QObject, pyqtSlot, pyqtProperty, pyqtSignal
from PyQt5.QtCore import QUrl
from PyQt5.QtQml import qmlRegisterType
import json

class Backend(QObject):
    colorSelected = pyqtSignal(str)#need to implement in qml
    tileSelected = pyqtSignal(int)

    def __init__(self):
        super().__init__()
        self._selectedColor = "white"
        self.grid_data = [["white" for _ in range(100)] for _ in range(100)]

    @pyqtProperty(str)
    def selectedColor(self):
        return self._selectedColor

    @selectedColor.setter
    def selectedColor(self, value):
        self._selectedColor = value

    @pyqtSlot(str)
    def setSelectedColor(self, color):
        self.selectedColor = color
        print(f"Selected color set to: {color}")

    @pyqtSlot(int)
    def setTileColor(self, index):
        # Calculate row and column from index.
        row = index // 100  # Example size, can change if needed.
        col = index % 100
        self.grid_data[row][col] = self.selectedColor
        print(f"Tile {index} set to color {self.selectedColor}")

    @pyqtSlot()
    def saveToFile(self):
        with open('path_to_file/level_data.txt', 'w') as f:
            for row in self.grid_data:
                f.write(" ".join(row) + "\n")
        print("Level data saved.")

    @pyqtSlot()
    def loadFromFile(self):#want to make this better, choose file maybe?
        with open('path_to_file/level_data.txt', 'r') as f:
            for row_idx, line in enumerate(f):
                colors = line.strip().split()
                for col_idx, color in enumerate(colors):
                    self.grid_data[row_idx][col_idx] = color
        print("Level data loaded.")