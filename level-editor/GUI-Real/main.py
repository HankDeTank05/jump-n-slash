import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QGridLayout, QWidget
from PyQt5.QtGui import QColor
from PyQt5.QtCore import Qt

class LevelEditor(QMainWindow):
    def __init__(self):
        super().__init__()

        self.selected_color = QColor(Qt.white)

        # Central widget
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Layout for the central widget
        layout = QGridLayout(central_widget)

        # Palette Buttons
        colors = [Qt.red, Qt.green, Qt.blue, Qt.gray]
        for index, color in enumerate(colors):
            button = QPushButton()
            button.setStyleSheet(f"background-color: {color.name()}")
            button.clicked.connect(lambda _, col=color: self.select_color(col))
            layout.addWidget(button, 0, index)

        # Map grid
        self.map_buttons = []
        grid_size = 10  # 10x10 grid for example
        for row in range(grid_size):
            row_buttons = []
            for col in range(grid_size):
                button = QPushButton()
                button.setStyleSheet("background-color: white")
                button.clicked.connect(lambda _, r=row, c=col: self.color_tile(r, c))
                layout.addWidget(button, row + 1, col)
                row_buttons.append(button)
            self.map_buttons.append(row_buttons)

        self.setWindowTitle('Level Editor')
        self.setGeometry(100, 100, 800, 600)

    def select_color(self, color):
        self.selected_color = color

    def color_tile(self, row, col):
        button = self.map_buttons[row][col]
        button.setStyleSheet(f"background-color: {self.selected_color.name()}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    editor = LevelEditor()
    editor.show()
    sys.exit(app.exec_())