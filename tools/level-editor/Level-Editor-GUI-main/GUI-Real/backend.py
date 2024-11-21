from PyQt6.QtCore import QObject, pyqtSignal, pyqtSlot, pyqtProperty # type: ignore
import json


class Backend(QObject):
    # Signals for notifying QML of changes
    selectedSpriteChanged = pyqtSignal()
    gridUpdated = pyqtSignal()
    messageLogged = pyqtSignal(str)

    def __init__(self, grid_width=100, grid_height=100):
        super().__init__()
        self.grid_width = grid_width
        self.grid_height = grid_height

        # Default selected sprite (an empty tile)
        self._selectedSprite = "assets/empty.png"

        # Initialize grid data with default sprite
        self.grid_data = [[self._selectedSprite for _ in range(self.grid_width)] for _ in range(self.grid_height)]

    # Selected sprite management
    @pyqtSlot(str)
    def setSelectedSprite(self, sprite):
        """Set the currently selected sprite."""
        if self._selectedSprite != sprite:
            self._selectedSprite = sprite
            self.selectedSpriteChanged.emit()
            self.logMessage(f"Selected sprite set to: {sprite}")

    @pyqtProperty(str, notify=selectedSpriteChanged)
    def selectedSprite(self):
        """Return the currently selected sprite."""
        return self._selectedSprite

    # Tile management
    @pyqtSlot(int)
    def setTileSprite(self, index):
        """Set a tile's sprite based on the selected sprite."""
        row, col = divmod(index, self.grid_width)
        if 0 <= row < self.grid_height and 0 <= col < self.grid_width:
            self.grid_data[row][col] = self._selectedSprite
            self.gridUpdated.emit()
            self.logMessage(f"Tile at index {index} set to sprite {self._selectedSprite}")
        else:
            self.logMessage("Invalid tile index!")

    @pyqtSlot(int, result=str)
    def getTileSprite(self, index):
        """Get the sprite at a specific tile index."""
        row, col = divmod(index, self.grid_width)
        if 0 <= row < self.grid_height and 0 <= col < self.grid_width:
            return self.grid_data[row][col]
        self.logMessage("Invalid tile index!")
        return "assets/empty.png"

    # Grid management
    @pyqtSlot()
    def clearLevel(self):
        """Clear the entire grid."""
        self.grid_data = [[self._selectedSprite for _ in range(self.grid_width)] for _ in range(self.grid_height)]
        self.gridUpdated.emit()
        self.logMessage("Grid cleared.")

    # File operations
    @pyqtSlot()
    def saveToFile(self):
        """Save the grid data to a JSON file."""
        try:
            with open('level_data.json', 'w') as f:
                json.dump(self.grid_data, f)
            self.logMessage("Grid data saved to level_data.json.")
        except Exception as e:
            self.logMessage(f"Error saving grid data: {str(e)}")

    @pyqtSlot()
    def loadFromFile(self):
        """Load the grid data from a JSON file."""
        try:
            with open('level_data.json', 'r') as f:
                self.grid_data = json.load(f)
            self.gridUpdated.emit()
            self.logMessage("Grid data loaded from level_data.json.")
        except FileNotFoundError:
            self.logMessage("Error: level_data.json not found.")
        except json.JSONDecodeError:
            self.logMessage("Error: Failed to decode level_data.json.")
        except Exception as e:
            self.logMessage(f"Error loading grid data: {str(e)}")

    # Utility methods
    @pyqtSlot(str)
    def logMessage(self, message):
        """Log a message to the console and notify QML."""
        print(message)
        self.messageLogged.emit(message)