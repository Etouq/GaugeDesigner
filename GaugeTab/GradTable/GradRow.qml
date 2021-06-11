import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../../StyledControls"

Item {
    id: root
    property color activeColor: "#FFFFFF"
    property bool isBig: false
    property real position: 0
    property int idx: 0
    width: 196
    height: 30

    signal colorActivated(int itemIdx)

    signal posChanged(int itemIdx, real newPos)
    signal bigChanged(int itemIdx, bool newVal)

    onIsBigChanged: bigChanged(idx, isBig)
    onPositionChanged: posChanged(idx, position)

    function resetCursors()
    {
        positionText.ensureVisible(0);
    }

    MouseArea {
        id: hoverArea
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true
    }


    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.16
        visible: hoverArea.containsMouse
    }

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        id: layoutItem
        height: 30

        TextField {
            id: positionText
            Layout.preferredWidth: 70
            Layout.preferredHeight: 30
            text: "0.0"
            selectByMouse: true
            validator: DoubleValidator{}
            leftPadding: 5
            font.pixelSize: 11

            onEditingFinished: {
                if (text == "" || text == "-" || !acceptableInput)
                    text = "0";
            }

            onTextEdited: {
                if (positionText.text == "" || positionText.text == "-" || positionText.text == ".")
                    return;
                position = parseFloat(positionText.text);
            }
            Layout.rightMargin: 10

            Component.onCompleted: text = position;
        }

        Item {
            Layout.preferredWidth: 56
            Layout.preferredHeight: 30
            Layout.rightMargin: 10

            StyledSwitch {
                anchors.centerIn: parent
                onToggled: isBig = checked
                Component.onCompleted: checked = isBig
            }
        }

        Rectangle {
            Layout.preferredWidth: 30
            Layout.preferredHeight: 30
            color: activeColor
            border.width: 1
            border.color: "black"
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                acceptedButtons: Qt.AllButtons
                hoverEnabled: true
                onClicked: {
                    if (mouse.button == Qt.LeftButton)
                        root.colorActivated(idx);
                    mouse.accepted = true;
                }
            }
        }

    }

}
