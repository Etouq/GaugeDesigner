import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15

Item {
    id: root
    width: 180
    clip: true
    height: 338
    property int activeIndex: -1


    property bool unsavedChanges: false

    // listmodel to check if data changed
    ListModel {
        id: lastListModel
    }

    function checkModelsEqual() {
        if (lastListModel.count != textGradModel.count)
            return false;

        for (let i = 0; i < lastListModel.count; ++i) {
            let savedEntry = lastListModel.get(i);
            let newEntry = textGradModel.get(i);

            if (savedEntry.pos != newEntry.pos || savedEntry.text != newEntry.text)
                return false;
        }

        return true;
    }

    signal posChanged(int idx, real val)
    signal textChanged(int idx, string val)

    function updateModel(gaugeObject) {
        textGradModel.clear();
        lastListModel.clear();

        for (let i = 0; i < gaugeObject.numTextGrads(); i++) {
            let textGradPos = gaugeObject.textGradValAt(i);
            let textGradText = gaugeObject.gradTextAt(i);

            textGradModel.append({ "pos": textGradPos, "text": textGradText });
            lastListModel.append({ "pos": textGradPos, "text": textGradText });
        }

        unsavedChanges = false;
    }

    function fillModel(_gradDist, _gradStart)
    {
        textGradModel.clear();
        for (let i = _gradStart; i <= maxValue; i += _gradDist) {
            textGradModel.append({ "pos": i, "text": i.toString() });
            if (textGradModel.count > 50)
                break;
        }

        unsavedChanges = !checkModelsEqual();
    }

    function saveData(gaugeObject) {
        gaugeObject.setNumTextGrads(textGradModel.count);
        lastListModel.clear();

        for (let i = 0; i < textGradModel.count; i++) {
            let textGrad = textGradModel.get(i);
            gaugeObject.setTextGradAt(i, textGrad.pos, textGrad.text);
            lastListModel.append({ "pos": textGrad.pos, "text": textGrad.text });
        }

        unsavedChanges = false;
    }

    Menu {
        id: contextMenu
        MenuItem {
            text: "Insert"
            onTriggered: {
                textGradModel.insert(activeIndex, { "pos": 0, "text": "0" });
                unsavedChanges = !checkModelsEqual();
            }
        }
        MenuItem {
            text: "Delete"
            onTriggered: {
                textGradModel.remove(activeIndex);
                unsavedChanges = !checkModelsEqual();
            }
        }
        onClosed: activeIndex = -1;
    }

    property real maxValue: 100


    onPosChanged: {
        textGradModel.get(idx).pos = val;
        unsavedChanges = !checkModelsEqual();
    }
    onTextChanged: {
        textGradModel.get(idx).text = val;
        unsavedChanges = !checkModelsEqual();
    }

    ListModel {
        id: textGradModel
    }



    Column {
        x: 10
        Text {
            height: 20
            width: 160
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            text: "Graduation Text"
            font.pixelSize: 12
        }
        Item {
            height: 20
            width: 170

            Text {
                anchors.horizontalCenter: parent.left
                anchors.horizontalCenterOffset: 40
                anchors.verticalCenter: parent.verticalCenter
                text: "Position"
                font.pixelSize: 11
            }
            Text {
                anchors.horizontalCenter: parent.left
                anchors.horizontalCenterOffset: 120
                anchors.verticalCenter: parent.verticalCenter
                text: "Text"
                font.pixelSize: 11
            }
        }


        ScrollView {
            y: 20
            width: 170
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
                model: textGradModel
                interactive: true
                spacing: 5
                anchors.fill: parent

                MouseArea {
                    anchors.fill: parent
                    onClicked: forceActiveFocus(rootItem)
                    z: -1
                }

                delegate: TextGradRow {
                    idx: index
                    posVal: pos
                    textVal: text
                    Component.onCompleted: {
                        posChanged.connect(root.posChanged);
                        textChanged.connect(root.textChanged);
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
        width: 70
        height: 20
        padding: 2
        enabled: textGradModel.count < 50

        onReleased: {
            textGradModel.append({ "pos": 0, "text": "0" });
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
        y: 250
        x: 95
        width: 70
        height: 20
        padding: 2

        enabled: textGradModel.count > 0

        onReleased: {
            textGradModel.remove(textGradModel.count - 1);
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

    Text {
        id: textGradDistText
        anchors.top: addRowButton.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: addRowButton.horizontalCenter
        text: "Grad Distance"
        font.pixelSize: 11
    }

    TextField {
        id: gradDist
        anchors.top: textGradDistText.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: addRowButton.horizontalCenter
        width: 70
        height: 20
        text: "10.0"
        selectByMouse: true
        validator: DoubleValidator{ bottom: 0.000001 }
        padding: 2
        font.pixelSize: 11
    }

    Text {
        id: textGradStartText
        anchors.top: removeRowButton.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: removeRowButton.horizontalCenter
        text: "Grad Start"
        font.pixelSize: 11
    }

    TextField {
        id: gradStart
        anchors.top: textGradStartText.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: removeRowButton.horizontalCenter
        width: 70
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
        width: 150
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
