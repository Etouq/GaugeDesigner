import QtQuick
import QtQuick.Controls 6
import Qt.labs.platform
import QtQuick.Shapes
import QtQuick.Layouts

Item {
    id: root
    property int activeIndex: -1;
    width: 230
    clip: true
    height: 200

    property bool unsavedChanges: false

    // listmodel to check if data changed
    ListModel {
        id: lastListModel
    }

    function checkModelsEqual() {
        if (lastListModel.count != zoneModel.count)
            return false;

        for (let i = 0; i < lastListModel.count; ++i) {
            let savedEntry = lastListModel.get(i);
            let newEntry = zoneModel.get(i);

            if (savedEntry.start !== newEntry.start || savedEntry.end !== newEntry.end || savedEntry.color !== newEntry.color)
                return false;
        }

        return true;
    }

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        modality: Qt.WindowModal
        onAccepted: {
            view.itemAtIndex(activeIndex).activeColor = colorDialog.color;
            zoneModel.get(activeIndex).color = colorDialog.color.toString();
            activeIndex = -1;
            unsavedChanges = !checkModelsEqual();
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
                unsavedChanges = !checkModelsEqual();
            }
        }
        MenuItem {
            text: "Delete"
            onTriggered: {
                zoneModel.remove(activeIndex);
                unsavedChanges = !checkModelsEqual();
            }
        }
        onAboutToHide: activeIndex = -1;
    }

    function updateModel(gaugeObject) {
        zoneModel.clear();
        lastListModel.clear();

        for (let i = 0; i < gaugeObject.numColorZones(); i++) {
            let colorZoneStart = gaugeObject.colorZoneStartAt(i);
            let colorZoneEnd = gaugeObject.colorZoneEndAt(i);
            let colorZoneColor = gaugeObject.colorZoneColorAt(i).toString();

            zoneModel.append({ "start": colorZoneStart, "end": colorZoneEnd, "color": colorZoneColor });
            lastListModel.append({ "start": colorZoneStart, "end": colorZoneEnd, "color": colorZoneColor });
        }

        unsavedChanges = false;
    }

    function saveData(gaugeObject) {
        gaugeObject.setNumColorZones(zoneModel.count);
        lastListModel.clear();

        for (let i = 0; i < zoneModel.count; i++) {
            let zone = zoneModel.get(i);
            gaugeObject.setColorZoneAt(i, zone.start, zone.end, zone.color);
            lastListModel.append({ "start": zone.start, "end": zone.end, "color": zone.color });
        }

        unsavedChanges = false;
    }

    signal colorTriggered(int idx)
    signal startChanged(int idx, real val)
    signal endChanged(int idx, real val)

    onColorTriggered: function(idx) {
        activeIndex = idx;
        colorDialog.open();
    }

    onStartChanged: function(idx, val) {
        zoneModel.get(idx).start = val;
        unsavedChanges = !checkModelsEqual();
    }
    onEndChanged: function(idx, val) {
        zoneModel.get(idx).end = val;
        unsavedChanges = !checkModelsEqual();
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
                onClicked: function(mouse) {
                    activeIndex = view.indexAt(mouse.x, mouse.y);
                    if (activeIndex != -1)
                        contextMenu.popup();
                }
            }

            ScrollBar.vertical.policy: view.contentHeight > view.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            Component.onCompleted: function() {
                //ScrollBar.vertical.contentItem.color = "#aeaeae"
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
                    Component.onCompleted: function() {
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

        onReleased: function() {
            zoneModel.append({ "start": 0, "end": 0, "color": "#008000" });
            unsavedChanges = !checkModelsEqual();
        }

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

        onReleased: function() {
            zoneModel.remove(zoneModel.count - 1);
            unsavedChanges = !checkModelsEqual();
        }

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
