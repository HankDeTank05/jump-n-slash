import sys
from PyQt5.QtWidgets import QApplication
from PyQt5.QtQml import QQmlApplicationEngine
from backend import Backend

app = QApplication(sys.argv)
engine = QQmlApplicationEngine()

backend = Backend()
engine.rootContext().setContextProperty('backend', backend)

engine.load('path_to/ui.qml')
app.exec_()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    editor = LevelEditor()
    editor.show()
    sys.exit(app.exec_())