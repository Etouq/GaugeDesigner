import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    id: root
    font.pixelSize: 11
    //title: "Please Select An Aircraft"
    modal: true
    padding: 10

    width: columnRoot.width + 20
    height: implicitHeaderHeight + columnRoot.height + 20
    x: (parent.width - width) / 2
    y: (500 - height) / 2

    property string selectedItem: ""

    property string infoText: ""

    background: Rectangle {
        anchors.fill: parent
        color: "#e0e0e0"

        MouseArea {
            anchors.fill: parent
            onClicked: (mouse) => {
                if (mouse.y < root.implicitHeaderHeight)
                    return;
                lastSelectedIndex = -1;
            }
        }
    }

    ListModel {
        id: aircraftNames
    }

    property int lastSelectedIndex: -1


    onAboutToShow: {
        selectedItem = "";
        lastSelectedIndex = -1;
        aircraftNames.clear();
        let keys = aircraftManager.getKeys();

        for (let i = 0; i < keys.length; i++)
        {
            aircraftNames.append({ "dataText": keys[i] });
        }
    }

    onAccepted: {
        selectedItem = aircraftNames.get(lastSelectedIndex).dataText;
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
            text: infoText
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
                        onClicked: (mouse) => {
                            if (mouse.button !== Qt.LeftButton)
                                return;

                            lastSelectedIndex = index;
                        }
                    }

                    Rectangle {
                        anchors.fill: parent
                        color: "#6ae6ff"
                        visible: selectionArea.containsMouse || lastSelectedIndex === index
                    }

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        text: dataText
                        width: parent.width - 20
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

                enabled: lastSelectedIndex >= 0

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

                onClicked: () => {
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
                onClicked: () => {
                    root.reject();
                }
            }
        }
    }




}
