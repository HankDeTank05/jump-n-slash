import QtQuick 6.7
import QtQuick.Controls 6.7
import untitledproject

Rectangle {
    id: rectangle
    x: 0
    y: 2
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor
    property color selectedColor: "white"
    property int selectedTileIndex: -1

    // need these for App.qml interface
    property alias savingbutton: savingbutton
    property alias loadingbutton: loadingbutton
    property alias clearbutton: clearbutton

    // Level Name and Metadata Fields
    Text {
        id: label
        font.family: Constants.font.family
        anchors.topMargin: 45
        anchors.horizontalCenter: parent.horizontalCenter
    }

    DropArea {
        id: dropArea
        x: 0
        y: 1
        width: 1920
        height: 1079

        Rectangle {
            id: rectangle1
            x: 0
            y: 0
            width: 1918
            height: 33
            color: "#fff6f3"

            // Control Buttons
            Button {
                id: savingbutton
                text: qsTr("Save")
                x: 0
                y: 0
                width: 82
                height: 33
            }
            Button {
                id: loadingbutton
                text: qsTr("Load")
                x: 88
                y: 0
                width: 84
                height: 33
            }
            Button {
                id: undobutton
                text: qsTr("Undo")
                x: 178
                y: 0
                width: 87
                height: 33
            }
            Button {
                id: redobutton
                text: qsTr("Redo")
                x: 271
                y: 0
                width: 82
                height: 33
            }
            Button {
                id: clearbutton
                text: qsTr("Clear")
                x: 359
                y: 0
                width: 80
                height: 33
            }
        }

        Rectangle {
            id: canvas
            x: 0
            y: 34
            width: 1920
            height: 776
            color: "#ffffff"

            // Sprite Palette for Selection
            GridView {
                id: palette
                x: 0
                y: 781
                width: 1500
                height: 264
                cellWidth: 70
                cellHeight: 70

                model: ListModel {
                    ListElement {
                        name: "Block Hazard 32"
                        imageSource: "assets/block_hazard_32.png"
                    }
                    ListElement {
                        name: "Block Solid 32"
                        imageSource: "assets/block_solid_32.png"
                    }
                }

                delegate: Rectangle {
                    width: 70
                    height: 70
                    border.color: "black"

                    Column {
                        spacing: 5
                        Image {
                            width: 40
                            height: 40
                            source: imageSource
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Text {
                            text: name
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }
            }

            // Map Canvas as a Grid of Tiles
            GridView {
                id: map
                x: 0
                y: 0
                width: 1920
                height: 776
                cellWidth: 32
                cellHeight: 32
                model: 100 * 100

                delegate: Rectangle {
                    width: 32
                    height: 32
                    property string imageSource: backend.selectedSprite

                    Image {
                        anchors.fill: parent
                        source: imageSource
                    }

                    border.color: "lightgrey"
                }
            }
        }

        Rectangle {
            id: rectangle4
            x: 1504
            y: 816
            width: 416
            height: 263
            color: "#ffffff"

            Text {
                id: levelname
                text: qsTr("Level Name")
                font.pixelSize: 12
                x: 0
                y: 0
                width: 408
                height: 91
            }
            Text {
                id: levelmetadata
                text: qsTr("Level size")
                font.pixelSize: 12
                x: 0
                y: 97
                width: 416
                height: 166
            }
        }
    }
}
