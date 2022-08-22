import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
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

        height: posText.height

        TextField {
            id: posText

            Layout.preferredWidth: 70
            Layout.fillWidth: true

            leftPadding: 5
            rightPadding: 5

            font.pixelSize: 14

            selectByMouse: true
            validator: DoubleValidator{ }

            text: model.value

            onEditingFinished: function() {
                if (posText.text === "" || posText.text === "-" || !posText.acceptableInput) {
                    model.value = 0;
                }
            }

            onTextEdited: function() {
                if (posText.text === "" || posText.text === "-")
                    return;

                const completeVal = Number(posText.text);

                if (isNaN(completeVal)) {
                    console.log(posText.text + " is not a number");
                    posText.undo();
                    return;
                }

                model.value = completeVal;
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }

        Item {
            Layout.preferredWidth: 10
            Layout.fillWidth: true
        }

        CheckBox {
            id: bigCheckBox

            Layout.preferredWidth: 34
            Layout.fillWidth: true

            topPadding: 8
            bottomPadding: 8
            spacing: 0
            checked: model.big

            Binding {
                target: model
                property: "big"
                value: bigCheckBox.checked
            }
        }

        Item {
            Layout.preferredWidth: 10
            Layout.fillWidth: true
        }

        Rectangle {
            Layout.preferredWidth: 30
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
                acceptedButtons: Qt.AllButtons
                hoverEnabled: true

                onClicked: function(mouse) {
                    if (mouse.button === Qt.LeftButton)
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
