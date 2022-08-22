import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Material 2.15

Item {
    height: childrenRect.height

    MouseArea {
        id: hoverArea
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true

        Rectangle {
            anchors.fill: parent
            color: Material.foreground
            opacity: 0.16
            visible: hoverArea.containsMouse
        }
    }

    RowLayout {
        id: layoutItem
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        height: startText.height

        TextField {
            id: startText

            Layout.preferredWidth: 70
            Layout.fillWidth: true

            font.pixelSize: 14

            selectByMouse: true
            validator: DoubleValidator{ }

            leftPadding: 5
            rightPadding: 5

            text: model.start

            onEditingFinished: function() {
                if (startText.text === "" || startText.text === "-" || !startText.acceptableInput) {
                    model.start = 0;
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

                model.start = completeVal;
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }

        Item {
            Layout.preferredWidth: 10
            Layout.fillWidth: true
        }

        TextField {
            id: endText

            Layout.preferredWidth: 70
            Layout.fillWidth: true

            font.pixelSize: 14

            selectByMouse: true
            validator: DoubleValidator{ }

            leftPadding: 5
            rightPadding: 5

            text: model.end

            onEditingFinished: function() {
                if (endText.text === "" || endText.text === "-" || !endText.acceptableInput) {
                    model.end = 0;
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

                model.end = completeVal;
            }

            Component.onCompleted: function() {
                endText.ensureVisible(0);
            }

        }

        Item {
            Layout.preferredWidth: 10
            Layout.fillWidth: true
        }

        Rectangle {
            Layout.preferredWidth: 34
            Layout.preferredHeight: 34
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 4
            Layout.bottomMargin: 8

            color: model.color

            border.width: 1
            border.color: "black"

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                acceptedButtons: Qt.LeftButton
                hoverEnabled: true

                onClicked: function(mouse) {
                    rowColorDialog.open();
                    mouse.accepted = true;
                }
            }
        }

        ColorDialog {
            id: rowColorDialog
            title: "Please choose a color"
            modality: Qt.WindowModal
            onAccepted: {
                model.color = rowColorDialog.color;
            }
            Component.onCompleted: color = "#FFFFFF"
        }

    }
}
