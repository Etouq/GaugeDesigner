import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Item {
    id: root
    property color activeColor: "#FFFFFF"
    property real startVal: 0
    property real endVal: 100
    property int idx: 0
    width: 210
    height: 30

    signal colorActivated(int itemIdx)
    signal startChanged(int itemIdx, real val)
    signal endChanged(int itemIdx, real val)

    onStartValChanged: {
        startText.text = startVal;
        startChanged(idx, startVal);
    }
    onEndValChanged: {
        endText.text = endVal;
        endChanged(idx, endVal);
    }

    function resetCursors()
    {
        startText.ensureVisible(0);
        endText.ensureVisible(0);
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
            id: startText
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
                if (startText.text == "" || startText.text == "-")
                    return;
                startVal = parseFloat(startText.text);
                if (startVal > endVal)
                    endVal = startVal;
            }
            Layout.rightMargin: 10

            Component.onCompleted: {
                text = startVal;
            }
        }
        TextField {
            id: endText
            Layout.preferredWidth: 70
            Layout.preferredHeight: 30
            text: "100.0"
            selectByMouse: true
            validator: DoubleValidator{}
            leftPadding: 5
            font.pixelSize: 11

            onEditingFinished: {
                if (text == "" || text == "-" || !acceptableInput)
                    text = "0";
            }

            onTextEdited: {
                if (endText.text == "" || endText.text == "-")
                    return;
                endVal = parseFloat(endText.text);
                if (endVal < startVal)
                    startVal = endVal;
            }
            Layout.rightMargin: 10

            Component.onCompleted: {
                text = endVal;
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
