import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Shapes 1.15

Item {
    id: root
    property int activeIndex: -1
    width: 216
    clip: true
    height: 338

    signal changeMade()

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        modality: Qt.WindowModal
        onAccepted: {
            view.itemAtIndex(activeIndex).activeColor = colorDialog.color;
            gradModel.get(activeIndex).color = colorDialog.color.toString();
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
                gradModel.insert(activeIndex, { "pos": 0, "bigGrad": false, "color": "#ffffff" });
            }
        }
        MenuItem {
            text: "Delete"
            onTriggered: {
                gradModel.remove(activeIndex);
            }
        }
        onClosed: activeIndex = -1;
    }

    function updateModel(gaugeObject) {
        gradModel.clear();
        for (let i = 0; i < gaugeObject.numGrads(); i++) {
            gradModel.append({ "pos": gaugeObject.gradValAt(i), "bigGrad": gaugeObject.gradIsBigAt(i), "color": gaugeObject.gradColorAt(i).toString() })
        }
    }

    function fillModel(_gradDist, _gradStart)
    {
        gradModel.clear();
        for (let i = _gradStart; i < maxValue; i += _gradDist) {
            gradModel.append({ "pos": i, "bigGrad": false, "color": "#ffffff" });
            if (gradModel.count > 250)
                break;
        }
    }

    function saveData(gaugeObject) {
        gaugeObject.setNumGrads(gradModel.count);
        for (let i = 0; i < gradModel.count; i++) {
            let grad = gradModel.get(i);
            gaugeObject.setGradAt(i, grad.pos, grad.bigGrad, grad.color);
        }
    }

    signal colorTriggered(int idx)

    signal isBigChanged(int idx, bool newVal)
    signal posChanged(int idx, real newVal)


    property real maxValue: 100

    ListModel {
        id: gradModel
    }

    onColorTriggered: {
        activeIndex = idx;
        colorDialog.open();
    }

    onIsBigChanged: {
        gradModel.get(idx).bigGrad = newVal;
        root.changeMade();
    }

    onPosChanged: {
        gradModel.get(idx).pos = newVal;
        root.changeMade();
    }


    Column {
        x: 10
        Text {
            height: 20
            width: 196
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            text: "Graduations"
            font.pixelSize: 12
        }
        Item {
            height: 20
            width: 206

            Text {
                anchors.horizontalCenter: parent.left
                anchors.horizontalCenterOffset: 40
                anchors.verticalCenter: parent.verticalCenter
                text: "Position"
                font.pixelSize: 11
            }
            Text {
                anchors.horizontalCenter: parent.left
                anchors.horizontalCenterOffset: 118
                anchors.verticalCenter: parent.verticalCenter
                text: "Big"
                font.pixelSize: 11
            }
            Text {
                anchors.horizontalCenter: parent.left
                anchors.horizontalCenterOffset: 176
                anchors.verticalCenter: parent.verticalCenter
                text: "Color"
                font.pixelSize: 11
            }
        }


        ScrollView {
            y: 20
            width: 206
            height: 205
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

            ScrollBar.vertical.policy: view.contentHeight > height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            Component.onCompleted: {
                ScrollBar.vertical.contentItem.color = "#aeaeae"
            }
            ListView {
                id: view
                model: gradModel
                interactive: true
                spacing: 5
                anchors.fill: parent

                MouseArea {
                    anchors.fill: parent
                    onClicked: forceActiveFocus(rootItem)
                    z: -1
                }

                delegate: GradRow {
                    idx: index
                    position: pos
                    isBig: bigGrad
                    activeColor: color
                    Component.onCompleted: {
                        colorActivated.connect(root.colorTriggered);
                        bigChanged.connect(root.isBigChanged);
                        posChanged.connect(root.posChanged);
                        resetCursors();
                    }
                }



            }
        }

    }

    Button {
        id: addRowButton
        y: 250
        x: 15
        width: 88
        height: 20
        padding: 2
        enabled: gradModel.count < 250

        onReleased: gradModel.append({ "pos": 0, "bigGrad": false, "color": "#ffffff" })

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
        y: 250
        x: 113
        width: 88
        height: 20
        padding: 2

        enabled: gradModel.count > 0

        onReleased: gradModel.remove(gradModel.count - 1)

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

    Text {
        id: gradDistText
        anchors.top: addRowButton.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: addRowButton.horizontalCenter
        text: "Grad Distance"
        font.pixelSize: 11
    }

    TextField {
        id: gradDist
        anchors.top: gradDistText.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: addRowButton.horizontalCenter
        width: 88
        height: 20
        text: "10.0"
        selectByMouse: true
        validator: DoubleValidator{ bottom: 0.000001 }
        padding: 2
        font.pixelSize: 11
    }

    Text {
        id: gradStartText
        anchors.top: removeRowButton.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: removeRowButton.horizontalCenter
        text: "Grad Start"
        font.pixelSize: 11
    }

    TextField {
        id: gradStart
        anchors.top: gradStartText.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: removeRowButton.horizontalCenter
        width: 88
        height: 20
        text: "0.0"
        selectByMouse: true
        validator: DoubleValidator{}
        padding: 2
        font.pixelSize: 11

    }

    Button {
        anchors.top: gradDist.bottom
        anchors.topMargin: 5
        x: 15
        width: 186
        height: 20
        padding: 2
        enabled: gradDist.acceptableInput && gradStart.acceptableInput
        onClicked: fillModel(parseFloat(gradDist.text), parseFloat(gradStart.text))

        background: Rectangle {
            anchors.fill: parent
            color: parent.enabled ? (parent.hovered ? Qt.darker("#00b4ff", 1.1) : "#00b4ff") : Qt.darker("#00b4ff", 2)
        }

        contentItem: Text {
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            text: "Generate"
            font.bold: true
            color: parent.enabled ? (parent.hovered ? Qt.darker("white", 1.1) : "white") : Qt.darker("white", 2)
            font.pixelSize: 11
        }
    }
}
