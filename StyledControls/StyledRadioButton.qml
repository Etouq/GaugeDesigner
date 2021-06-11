import QtQuick 2.15
import QtQuick.Controls 2.15

RadioButton {
    id: control
    width: 20
    height: width

    indicator: Rectangle {
            width: control.width
            height: width
            anchors.centerIn: control
            radius: width / 2
            color: "transparent"
            border.width: width / 10
            border.color: control.checked ? "#00b4ff" : "#aeaeae"

            Rectangle {
                anchors.centerIn: parent
                width: parent.width / 2
                height: width
                radius: width / 2
                color: "#00b4ff"
                visible: control.checked
            }
        }
}
