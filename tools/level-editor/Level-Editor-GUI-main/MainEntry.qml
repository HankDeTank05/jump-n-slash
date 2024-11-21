import QtQuick 6.7
import QtQuick.Controls 6.7

ApplicationWindow {
    visible: true
    width: 1024
    height: 768

    Loader {
        id: screenLoader
        anchors.fill: parent
        source: "C:/Users/Len/Documents/GitHub/Level-Editor-GUI/GUIPrototypeContent/Screen01.ui.qml"
    }

    Connections {
        target: screenLoader.item
        onSelectedColorChanged: backend.setSelectedSprite(screenLoader.item.selectedColor)
        onClearButtonClicked: backend.clearLevel()
        onSaveButtonClicked: backend.saveToFile()
        onLoadButtonClicked: backend.loadFromFile()
    }
}