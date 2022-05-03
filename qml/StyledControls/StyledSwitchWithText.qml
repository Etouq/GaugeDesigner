import QtQuick 2.15

Item {
    implicitWidth: 100
    implicitHeight: 20

    property alias leftMargin: textItem.anchors.leftMargin
    property alias rightMargin: switchItem.anchors.rightMargin
    property alias text: textItem.text
    property alias checked: switchItem.checked
    property bool showItem: true

    Text {
        id: textItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        visible: showItem
        font.pixelSize: 11
    }

    StyledSwitch {
        id: switchItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        visible: showItem
    }
}
