import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    implicitWidth: 100
    implicitHeight: 20

    property alias leftMargin: textItem.anchors.leftMargin
    property alias rightMargin: radioButtonItem.anchors.rightMargin
    property alias text: textItem.text
    property alias checked: radioButtonItem.checked
    property alias button: radioButtonItem

    Text {
        id: textItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        font.pixelSize: 11
    }

    StyledRadioButton {
        id: radioButtonItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
    }
}
