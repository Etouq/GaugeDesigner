import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Button {
    id: root
    height: 20
    opacity: enabled ? 1 : 0.38
    width: textContent.contentWidth + 15

    contentItem: Item {
        anchors.fill: parent

        Text {
            id: textContent
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.family: "Roboto"
            font.pixelSize: 14
            font.bold: true
            text: root.text
            color: Material.foreground//"white"
        }

        Rectangle {
            anchors.fill: parent
            color: "white"
            opacity: root.hovered ? 0.08 : 0
        }

        Rectangle {
            anchors.fill: parent
            color: "white"
            opacity: root.visualFocus ? 0.24 : 0
        }

    }


    background: Item { }
}
