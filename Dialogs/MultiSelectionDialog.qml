import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    id: root
    font.pixelSize: 11
    //title: "Make A Selection"
    modal: true
    padding: 10
    width: columnRoot.width + 20
    height: implicitHeaderHeight + columnRoot.height + 20
    x: (parent.width - width) / 2
    y: (500 - height) / 2

    property var selection: []

    property bool useLocalFiles: true
    property string infoText: ""


    background: Rectangle {
        anchors.fill: parent
        color: "#e0e0e0"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (mouse.y < root.implicitHeaderHeight)
                    return;
                for (let i = 0; i < aircraftNames.count; i++)
                    aircraftNames.set(i, { "selected": false });
                anyItemsSelected = false;
            }
        }

    }

    ListModel {
        id: aircraftNames
    }

    property int lastSelectedIndex: 0

    property bool anyItemsSelected: false

    onAboutToShow: {
        selection = [];
        aircraftNames.clear();

        let keys = [];

        if (useLocalFiles)
            keys = aircraftManager.getKeys();
        else
            keys = aircraftManager.getClientKeys();


        for (let i = 0; i < keys.length; i++)
        {
            aircraftNames.append({ "dataText": keys[i], "selected": false });
        }
    }

    onAccepted: {
        for (let i = 0; i < aircraftNames.count; i++)
        {
            if (aircraftNames.get(i).selected)
                selection.push(aircraftNames.get(i).dataText);
        }
    }

    Column {
        id: columnRoot
        spacing: 5
        width: 180
        height: extraDescriptionText.height + itemList.height + 40

        Text {
            id: extraDescriptionText
            font.family: "Roboto"
            width: parent.width
            wrapMode: Text.WordWrap
            font.pixelSize: 11
            text: (infoText == "" ? "" : infoText + "\n") + "Make a Selection using: Click, Ctrl + Click, Shift + Click"
        }

        ScrollView {
            id: itemList
            clip: true
            width: parent.width
            height: 251
            padding: 0
            ScrollBar.vertical.policy: view.contentHeight > height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            background: Rectangle {
                color: "white"
            }
            ListView {
                id: view
                anchors.fill: parent
                model: aircraftNames
                spacing: 1

                delegate: Item {
                    width: view.width
                    height: 20
                    MouseArea {
                        id: selectionArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            if (mouse.button != Qt.LeftButton)
                                return;
                            if (mouse.modifiers == Qt.ShiftModifier) {
                                let minIdx = Math.min(lastSelectedIndex, index);
                                let maxIdx = Math.max(lastSelectedIndex, index);
                                for (let i = 0; i < aircraftNames.count; i++)
                                    aircraftNames.set(i, { "selected": (i >= minIdx && i <= maxIdx) });
                                anyItemsSelected = true;
                                return;
                            }
                            if (mouse.modifiers == Qt.NoModifier) {
                                for (let i = 0; i < aircraftNames.count; i++)
                                    aircraftNames.set(i, { "selected": i == index });

                                anyItemsSelected = true;
                                lastSelectedIndex = index;
                                return;
                            }
                            if (mouse.modifiers == Qt.ControlModifier) {
                                aircraftNames.set(index, { "selected": !selected });

                                lastSelectedIndex = index;

                                for (let i = 0; i < aircraftNames.count; i++)
                                    if (aircraftNames.get(i).selected)
                                    {
                                        anyItemsSelected = true;
                                        return;
                                    }

                                anyItemsSelected = false;
                                return;
                            }


                        }

                        onDoubleClicked: {
                            for (let i = 0; i < aircraftNames.count; i++)
                                aircraftNames.set(i, { "selected": i == index });

                            anyItemsSelected = true;
                            lastSelectedIndex = index;
                            root.accept();
                        }
                    }

                    Rectangle {
                        anchors.fill: parent
                        color: "#6ae6ff"
                        visible: selectionArea.containsMouse || selected
                    }

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        text: dataText
                        width: parent.width - 20
                        font.pixelSize: 11
                    }
                }
            }
        }

        Item {
            width: parent.width
            height: 30

            Button {
                anchors.left: parent.left
                width: (parent.width - 10) / 2
                height: parent.height

                enabled: anyItemsSelected

                background: Rectangle {
                    color: parent.enabled ? (parent.hovered ? Qt.darker("#00b4ff", 1.1) : "#00b4ff") : Qt.darker("#00b4ff", 2)
                }

                contentItem: Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "Ok"
                    font.bold: true
                    color: parent.enabled ? (parent.hovered ? Qt.darker("white", 1.1) : "white") : Qt.darker("white", 2)
                    font.pixelSize: 13
                }
                onClicked: {
                    root.accept();
                }
            }

            Button {
                anchors.right: parent.right
                width: (parent.width - 10) / 2
                height: parent.height

                background: Rectangle {
                    color: parent.enabled ? (parent.hovered ? Qt.darker("#00b4ff", 1.1) : "#00b4ff") : Qt.darker("#00b4ff", 2)
                }

                contentItem: Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "Cancel"
                    font.bold: true
                    color: parent.enabled ? (parent.hovered ? Qt.darker("white", 1.1) : "white") : Qt.darker("white", 2)
                    font.pixelSize: 13
                }
                onClicked: {
                    root.reject();
                }
            }
        }
    }




}
