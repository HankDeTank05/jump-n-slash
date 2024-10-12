import sys
from PyQt5.QtWidgets import QApplication
from PyQt5.QtQml import QQmlApplicationEngine
from backend import Backend


if __name__ == "__main__":

    app = QApplication(sys.argv)
    
    engine = QQmlApplicationEngine()

    backend = Backend()
    
    # Expose the backend object
    engine.rootContext().setContextProperty('backend', backend)
    
    engine.load(QUrl.fromLocalFile('ui.qml'))
    
    if not engine.rootObjects():
        sys.exit(-1)
    
    rootObject = engine.rootObjects()[0]
    
    class UIUpdater(QObject):
        def __init__(self, rootObject):
            super().__init__()
            self.rootObject = rootObject

        @pyqtSlot()
        def refreshMap(self):
            # Find the GridView with the objectName "map"
            map_view = self.rootObject.findChild(QObject, "map")
            if map_view:
                # Refresh the model to force the GridView to update
                current_model = map_view.property("model")
                map_view.setProperty("model", current_model)
                print("Map GridView refreshed.")
            else:
                print("Could not find 'map' GridView to refresh.")
    
    uiUpdater = UIUpdater(rootObject)
    
    backend.levelChanged.connect(uiUpdater.refreshMap)
    
    sys.exit(app.exec_())