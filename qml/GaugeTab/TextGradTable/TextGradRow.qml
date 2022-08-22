import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
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

        TextField {
            id: gradText

            Layout.preferredWidth: 70
            Layout.fillWidth: true

            leftPadding: 5
            rightPadding: 5

            font.pixelSize: 14

            selectByMouse: true
            validator: DoubleValidator{ }

            text: model.text

            onTextEdited: function() {
                model.text = posText.text;
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }

    }
}
