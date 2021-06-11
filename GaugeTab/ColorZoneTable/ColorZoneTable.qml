import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15

Item {
    id: root
    property int activeIndex: -1;
    width: 230
    clip: true
    height: 200

    signal changeMade()

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        modality: Qt.WindowModal
        onAccepted: {
            view.itemAtIndex(activeIndex).activeColor = colorDialog.color;
            zoneModel.get(activeIndex).color = colorDialog.color.toString();
            activeIndex = -1;
            root.changeMade();
        }
        onRejected: {
            activeIndex = -1;
        }
        Component.onCompleted: color = "#FFFFFF"
    }

    Menu {
        id: contextMenu
        MenuItem {
            text: "Insert"
            onTriggered: {
                zoneModel.insert(activeIndex, { "start": 0, "end": 0, "color": "#008000" });
            }
        }
        MenuItem {
            text: "Delete"
            onTriggered: {
                zoneModel.remove(activeIndex);
            }
        }
        onClosed: activeIndex = -1;
    }

    function updateModel(gaugeObject) {
        zoneModel.clear();
        for (let i = 0; i < gaugeObject.numColorZones(); i++) {
            zoneModel.append({ "start": gaugeObject.colorZoneStartAt(i), "end": gaugeObject.colorZoneEndAt(i), "color": gaugeObject.colorZoneColorAt(i).toString() })
        }
    }

    function saveData(gaugeObject) {
        gaugeObject.setNumColorZones(zoneModel.count);
        for (let i = 0; i < zoneModel.count; i++) {
            let zone = zoneModel.get(i);
            gaugeObject.setColorZoneAt(i, zone.start, zone.end, zone.color);
        }
    }

    signal colorTriggered(int idx)
    signal startChanged(int idx, real val)
    signal endChanged(int idx, real val)

    onColorTriggered: {
        activeIndex = idx;
        colorDialog.open();
    }

    onStartChanged: {
        zoneModel.get(idx).start = val;
        root.changeMade();
    }
    onEndChanged: {
        zoneModel.get(idx).end = val;
        root.changeMade();
    }

    ListModel {
        id: zoneModel
    }



    Column {
        x: 10
        Text {
            height: 20
            width: 210
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            text: "Color Zones"
            font.pixelSize: 12
        }

        Item {
            height: 20
            width: 210
            x: 5

            Text {
                anchors.horizontalCenter: parent.left
                anchors.horizontalCenterOffset: 35
                anchors.verticalCenter: parent.verticalCenter
                text: "Start"
                font.pixelSize: 11
            }
            Text {
                anchors.horizontalCenter: parent.left
                anchors.horizontalCenterOffset: 120
                anchors.verticalCenter: parent.verticalCenter
                text: "End"
                font.pixelSize: 11
            }
            Text {
                anchors.horizontalCenter: parent.left
                anchors.horizontalCenterOffset: 185
                anchors.verticalCenter: parent.verticalCenter
                text: "Color"
                font.pixelSize: 11
            }
        }


        ScrollView {
            y: 20
            width: 220
            height: 135
            clip: true

            background: MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                propagateComposedEvents: true
                onClicked: {
                    activeIndex = view.indexAt(mouse.x, mouse.y);
                    if (activeIndex != -1)
                        contextMenu.popup();
                }
            }

            ScrollBar.vertical.policy: view.contentHeight > view.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            Component.onCompleted: {
                ScrollBar.vertical.contentItem.color = "#aeaeae"
            }

            ListView {
                id: view
                model: zoneModel
                interactive: true
                spacing: 5
                anchors.fill: parent

                MouseArea {
                    anchors.fill: parent
                    onClicked: forceActiveFocus(rootItem)
                    z: -1
                }

                delegate: ColorZoneRow {
                    idx: index
                    startVal: start
                    endVal: end
                    activeColor: color
                    Component.onCompleted: {
                        colorActivated.connect(root.colorTriggered);
                        startChanged.connect(root.startChanged);
                        endChanged.connect(root.endChanged);
                        resetCursors();
                    }
                }



            }


        }

    }

    Button {
        id: addRowButton
        y: 180
        x: 15
        width: 95
        height: 20
        padding: 2
        enabled: zoneModel.count < 10

        onReleased: zoneModel.append({ "start": 0, "end": 0, "color": "#008000" })

        background: Rectangle {
            anchors.fill: parent
            color: addRowButton.enabled ? (addRowButton.hovered ? Qt.darker("#00b4ff", 1.1) : "#00b4ff") : Qt.darker("#00b4ff", 2)
        }

        contentItem: Text {
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            text: "Add"
            font.bold: true
            color: addRowButton.enabled ? (addRowButton.hovered ? Qt.darker("white", 1.1) : "white") : Qt.darker("white", 2)
            font.pixelSize: 11
        }

    }

    Button {
        id: removeRowButton
        y: 180
        x: 120
        width: 95
        height: 20
        padding: 2

        enabled: zoneModel.count > 0

        onReleased: zoneModel.remove(zoneModel.count - 1)

        background: Rectangle {
            anchors.fill: parent
            color: removeRowButton.enabled ? (removeRowButton.hovered ? Qt.darker("#00b4ff", 1.1) : "#00b4ff") : Qt.darker("#00b4ff", 2)
        }

        contentItem: Text {
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            text: "Remove"
            font.bold: true
            color: removeRowButton.enabled ? (removeRowButton.hovered ? Qt.darker("white", 1.1) : "white") : Qt.darker("white", 2)
            font.pixelSize: 11
        }

    }



}
