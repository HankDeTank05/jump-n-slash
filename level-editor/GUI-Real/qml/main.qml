
/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.7
import QtQuick.Controls 6.7
import GUIPrototype

Rectangle {
    id: rectangle
    x: 0
    y: 2
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor
    property color selectedColor: "white"
    property int selectedTileIndex: -1

    Text {
        id: label
        font.family: Constants.font.family
        anchors.topMargin: 45
        anchors.horizontalCenter: parent.horizontalCenter

        SequentialAnimation {
            id: animation

            ColorAnimation {
                id: colorAnimation1
                target: rectangle
                property: "color"
                to: "#2294c6"
                from: Constants.backgroundColor
            }

            ColorAnimation {
                id: colorAnimation2
                target: rectangle
                property: "color"
                to: Constants.backgroundColor
                from: "#2294c6"
            }
        }
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

            Button {
                id: savingbutton
                x: 0
                y: 0
                width: 82
                height: 33
                text: qsTr("Save")
            }

            Button {
                id: loadingbutton
                x: 88
                y: 0
                width: 84
                height: 33
                text: qsTr("Load")
            }

            Button {
                id: undobutton
                x: 178
                y: 0
                width: 87
                height: 33
                text: qsTr("Undo")
            }

            Button {
                id: redobutton
                x: 271
                y: 0
                width: 82
                height: 33
                text: qsTr("Redo")
            }

            Button {
                id: clearbutton
                x: 359
                y: 0
                width: 80
                height: 33
                text: qsTr("Clear")
            }
        }

        Rectangle {
            id: canvas
            x: 0
            y: 34
            width: 1920
            height: 776
            color: "#ffffff"

            // Updated Palette GridView to display sprites
            GridView {
                id: pallete
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
                    ListElement {
                        name: "Breakable Block 8"
                        imageSource: "assets/breakable_block_8.png"
                    }
                    ListElement {
                        name: "Enemy Spawn Left"
                        imageSource: "assets/enemy_spawn_left.png"
                    }
                    ListElement {
                        name: "Enemy Spawn Right"
                        imageSource: "assets/enemy_spawn_right.png"
                    }
                    ListElement {
                        name: "Hazard Block 8"
                        imageSource: "assets/hazard_block_8.png"
                    }
                    ListElement {
                        name: "Indicator Room Height 32"
                        imageSource: "assets/indicator_room_height_32.png"
                    }
                    ListElement {
                        name: "Indicator Room Origin 32"
                        imageSource: "assets/indicator_room_origin_32.png"
                    }
                    ListElement {
                        name: "Indicator Room Origin Start"
                        imageSource: "assets/indicator_room_origin_start.png"
                    }
                    ListElement {
                        name: "Indicator Room Width 32"
                        imageSource: "assets/indicator_room_width_32.png"
                    }
                    ListElement {
                        name: "Indicator Spawn Enemy Left"
                        imageSource: "assets/indicator_spawn_enemy_left.png"
                    }
                    ListElement {
                        name: "Indicator Spawn Enemy Right"
                        imageSource: "assets/indicator_spawn_enemy_right.png"
                    }
                    ListElement {
                        name: "Indicator Spawn Player Left"
                        imageSource: "assets/indicator_spawn_player_left.png"
                    }
                    ListElement {
                        name: "Indicator Spawn Player Right"
                        imageSource: "assets/indicator_spawn_player_right.png"
                    }
                    ListElement {
                        name: "Platform Semisolid 32"
                        imageSource: "assets/platform_semisolid_32.png"
                    }
                    ListElement {
                        name: "Player Spawn Left"
                        imageSource: "assets/player_spawn_left.png"
                    }
                    ListElement {
                        name: "Player Spawn Right"
                        imageSource: "assets/player_spawn_right.png"
                    }
                    ListElement {
                        name: "Room Height Indicator 8"
                        imageSource: "assets/room_height_indicator_8.png"
                    }
                    ListElement {
                        name: "Room Origin Indicator 8"
                        imageSource: "assets/room_origin_indicator_8.png"
                    }
                    ListElement {
                        name: "Room Width Indicator 8"
                        imageSource: "assets/room_width_indicator_8.png"
                    }
                    ListElement {
                        name: "Semisolid Platform 8"
                        imageSource: "assets/semisolid_platform_8.png"
                    }
                    ListElement {
                        name: "Solid Block 8"
                        imageSource: "assets/solid_block_8.png"
                    }
                    ListElement {
                        name: "Start Room Origin Indicator"
                        imageSource: "assets/start_room_origin_indicator.png"
                    }
                }

                delegate: Rectangle {
                    x: 5
                    height: 50
                    width: 70
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
                            x: 5
                            text: name
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }

                // MouseArea for palette interactions (if needed)
                // You might need to handle interactions via backend due to constraints
            }

            // Map GridView remains the same
            GridView {
                id: map
                objectName: "map"
                x: 0
                y: 0
                width: 1920
                height: 776
                cellWidth: 32
                cellHeight: 32
                model: 100 * 100 // Example grid size, 100x100 tiles

                delegate: Rectangle {
                    id: tileItem
                    width: 32
                    height: 32
                    property string imageSource: "assets/empty.png" // Default empty tile image

                    Image {
                        anchors.fill: parent
                        source: imageSource
                    }

                    border.color: "lightgrey"
                }

                // ScrollView (if needed)
                // ScrollView {
                //     id: scrollView
                //     x: 0
                //     y: 0
                //     width: 1920
                //     height: 776
                // }
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
                x: 0
                y: 0
                width: 408
                height: 91
                text: qsTr("Level Name")
                font.pixelSize: 12
            }

            Text {
                id: levelmetadata
                x: 0
                y: 97
                width: 416
                height: 166
                text: qsTr("Level size")
                font.pixelSize: 12
            }
        }
    }

    MouseArea {
        id: maptouchscreen
        x: 0
        y: 38
        width: 1920
        height: 772
    }
    states: [
        State {
            name: "clicked"

            PropertyChanges {
                target: label
                text: qsTr("Button Checked")
            }
        }
    ]
}