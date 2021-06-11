import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: root
    property bool isActiveItem: false
    width: textContent.contentWidth + 32
    height: 30

    contentItem: Item {
        anchors.fill: parent

        Text {
            id: textContent
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.family: "Roboto"
            font.pixelSize: 15
            font.bold: true
            text: root.text
            color: "white"
            opacity: isActiveItem ? 1 : 0.82
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
