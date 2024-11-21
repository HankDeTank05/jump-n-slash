import sys
from PyQt6.QtWidgets import QApplication
from PyQt6.QtQml import QQmlApplicationEngine
from PyQt6.QtCore import QUrl
from backend import Backend

if __name__ == "__main__":
    # Create application
    app = QApplication(sys.argv)
    engine = QQmlApplicationEngine()

    # Create backend and expose to QML
    backend = Backend()
    engine.rootContext().setContextProperty("backend", backend)

    # Load the QML file
    engine.load(QUrl("tools/level-editor/Level-Editor-GUI-main/UntitledProject/UntitledProjectContent/App.qml"))

    # Check if QML loaded correctly
    if not engine.rootObjects():
        sys.exit(-1)

    # Execute application
    sys.exit(app.exec())