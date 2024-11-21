import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QGridLayout, QPushButton, QVBoxLayout, QScrollArea
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QColor

class LevelEditor(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Level Editor')
        self.setGeometry(100, 100, 800, 600)

        self.selected_color = QColor(Qt.white)

        # Create the central widget and layout
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        main_layout = QVBoxLayout(central_widget)

        # Create the color palette
        self.create_palette(main_layout)

        # Create the map area with scroll functionality
        self.create_map_area(main_layout)

    def create_palette(self, layout):
        colors = [Qt.red, Qt.green, Qt.blue, Qt.gray]
        palette_layout = QGridLayout()
        
        for index, color in enumerate(colors):
            button = QPushButton()
            button.setStyleSheet(f"background-color: {color.name()}; border: none;")
            button.setFixedSize(40, 40)
            button.clicked.connect(lambda _, col=color: self.select_color(col))
            palette_layout.addWidget(button, 0, index)

        layout.addLayout(palette_layout)

    def create_map_area(self, layout):
        # Scroll Area to contain the grid layout
        scroll_area = QScrollArea()
        scroll_area.setWidgetResizable(True)
        
        # Container widget for the grid
        map_container = QWidget()
        self.grid_layout = QGridLayout(map_container)
        scroll_area.setWidget(map_container)
        
        # Example grid size (10x10)
        grid_size = 10
        self.tile_buttons = []

        for row in range(grid_size):
            row_buttons = []
            for col in range(grid_size):
                button = QPushButton()
                button.setFixedSize(40, 40)
                button.setStyleSheet("background-color: white; border: 1px solid lightgrey;")
                button.clicked.connect(lambda _, r=row, c=col: self.color_tile(r, c))
                self.grid_layout.addWidget(button, row, col)
                row_buttons.append(button)
            self.tile_buttons.append(row_buttons)

        layout.addWidget(scroll_area)

    def select_color(self, color):
        self.selected_color = color

    def color_tile(self, row, col):
        button = self.tile_buttons[row][col]
        button.setStyleSheet(f"background-color: {self.selected_color.name()}; border: 1px solid lightgrey;")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    editor = LevelEditor()
    editor.show()
    sys.exit(app.exec_())