import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

import Definition 1.0

Item {
    id: root
    property int activeIndex: -1

    required property GaugeDefinition gaugeDef

    Menu {
        id: contextMenu
        MenuItem {
            text: "Insert"
            onTriggered: {
                gaugeDef.textGradModel.insertNewRow(activeIndex);
            }
        }
        MenuItem {
            text: "Delete"
            onTriggered: {
                gaugeDef.textGradModel.deleteRow(activeIndex);
            }
        }
        onAboutToHide: activeIndex = -1;
    }


    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Text {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.family: "Roboto"
            font.pixelSize: 14
            font.bold: true

            color: Material.foreground

            text: "Graduation Texts"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 5
            Layout.rightMargin: 5

            Text {
                Layout.fillWidth: true
                Layout.preferredWidth: 70
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.family: "Roboto"
                font.pixelSize: 14

                color: Material.foreground

                text: "Position"
            }

            Item {
                Layout.preferredWidth: 10
                Layout.fillWidth: true
            }

            Text {
                Layout.fillWidth: true
                Layout.preferredWidth: 70
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.family: "Roboto"
                font.pixelSize: 14

                color: Material.foreground

                text: "Text"
            }

        }

        MouseArea {
            Layout.fillWidth: true
            Layout.fillHeight: true

            acceptedButtons: Qt.RightButton
            propagateComposedEvents: true

            onClicked: function(mouse) {
                activeIndex = view.indexAt(mouse.x, mouse.y);
                if (activeIndex != -1)
                    contextMenu.popup();
            }

            ListView {
                id: view

                anchors.fill: parent

                clip: true

                model: gaugeDef.textGradModel
                interactive: true
                spacing: 5

                ScrollBar.vertical: ScrollBar {
                    parent: view.parent
                    anchors.top: view.top
                    anchors.left: view.right
                    anchors.bottom: view.bottom

                    policy: view.contentHeight > view.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

                    width: 10

                    contentItem: Rectangle {
                        implicitWidth: 6
                        implicitHeight: 100
                        radius: width / 2
                        color: Material.accent
                    }
                }

                delegate: TextGradRow {
                    width: view.width
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.bottomMargin: -3

            Button {
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                enabled: view.count < 10

                text: "Add"

                onClicked: function() {
                    gaugeDef.textGradModel.appendNewRow();
                }
            }

            Button {
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                enabled: view.count > 0

                text: "Remove"

                onClicked: function() {
                    gaugeDef.textGradModel.deleteRow(gaugeDef.textGradModel.rowCount() - 1);
                }
            }
        }

        Button {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.topMargin: -3
            Layout.bottomMargin: -3

            text: "Generate"

            onClicked: function() {
                popup.open();
            }
        }
    }

    Popup {
        id: popup

        anchors.centerIn: Overlay.overlay

        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        GridLayout {
            columns: 3
            columnSpacing: 10

            Text {
                Layout.preferredWidth: 70
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.family: "Roboto"
                font.pixelSize: 14
                font.bold: true

                color: Material.foreground

                text: "Start"
            }

            Text {
                Layout.preferredWidth: 70
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.family: "Roboto"
                font.pixelSize: 14
                font.bold: true

                color: Material.foreground

                text: "End"
            }

            Text {
                Layout.preferredWidth: 70
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.family: "Roboto"
                font.pixelSize: 14
                font.bold: true

                color: Material.foreground

                text: "Step"
            }

            TextField {
                id: startText

                Layout.preferredWidth: 70
                Layout.fillWidth: true

                leftPadding: 5
                rightPadding: 5

                font.pixelSize: 14

                selectByMouse: true
                validator: DoubleValidator{ }

                text: "0"

                onEditingFinished: function() {
                    if (startText.text === "" || startText.text === "-") {
                        startText.text = "0";
                    }
                }

                onTextEdited: function() {
                    if (startText.text === "" || startText.text === "-")
                        return;

                    const completeVal = Number(startText.text);

                    if (isNaN(completeVal)) {
                        console.log(startText.text + " is not a number");
                        startText.undo();
                        return;
                    }
                }
            }

            TextField {
                id: endText

                Layout.preferredWidth: 70
                Layout.fillWidth: true

                leftPadding: 5
                rightPadding: 5

                font.pixelSize: 14

                selectByMouse: true
                validator: DoubleValidator{ }

                text: "100"

                onEditingFinished: function() {
                    if (endText.text === "" || endText.text === "-") {
                        endText.text = "0";
                    }
                }

                onTextEdited: function() {
                    if (endText.text === "" || endText.text === "-")
                        return;

                    const completeVal = Number(endText.text);

                    if (isNaN(completeVal)) {
                        console.log(endText.text + " is not a number");
                        endText.undo();
                        return;
                    }
                }
            }

            TextField {
                id: stepText

                Layout.preferredWidth: 70
                Layout.fillWidth: true

                leftPadding: 5
                rightPadding: 5

                font.pixelSize: 14

                selectByMouse: true
                validator: DoubleValidator{ }

                text: "10"

                onEditingFinished: function() {
                    if (stepText.text === "" || stepText.text === "-") {
                        endText.text = "0";
                    }
                }

                onTextEdited: function() {
                    if (stepText.text === "" || stepText.text === "-")
                        return;

                    const completeVal = Number(stepText.text);

                    if (isNaN(completeVal)) {
                        console.log(stepText.text + " is not a number");
                        stepText.undo();
                        return;
                    }
                }
            }

            RowLayout {
                Layout.columnSpan: 3
                Layout.fillWidth: true

                Button {
                    Layout.preferredWidth: 100
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    text: "Cancel"

                    onClicked: function() {
                        popup.close();
                    }
                }

                Button {
                    Layout.preferredWidth: 100
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    enabled: parseFloat(startText.text) < parseFloat(endText.text) && parseFloat(stepText.text) > 0 && (parseFloat(endText.text) - parseFloat(startText.text)) / parseFloat(stepText.text) < 256

                    text: "Go"

                    onClicked: function() {
                        gaugeDef.textGradModel.generate(parseFloat(startText.text), parseFloat(endText.text), parseFloat(stepText.text));
                        popup.close();
                    }
                }
            }
        }
    }

}
