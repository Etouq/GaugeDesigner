import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    property real posVal: 0
    property string textVal: "0"
    property int idx: 0
    width: 160
    height: 30

    signal posChanged(int itemIdx, real val)
    signal textChanged(int itemIdx, string val)

    onPosValChanged: {
        posChanged(idx, posVal);
    }
    onTextValChanged: {
        textChanged(idx, textVal);
    }

    function resetCursors()
    {
        posText.ensureVisible(0);
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
        spacing: 0

        TextField {
            id: posText
            Layout.preferredWidth: 70
            Layout.preferredHeight: 30
            text: "0.0"
            selectByMouse: true
            validator: DoubleValidator{}
            font.pixelSize: 11

            onEditingFinished: {
                if (text == "" || text == "-" || !acceptableInput)
                    text = "0";
            }

            onTextEdited: {
                if (posText.text == "" || posText.text == "-")
                    return;
                posVal = parseFloat(posText.text);
            }
            Layout.rightMargin: 10

            Component.onCompleted: {
                text = posVal
            }
        }
        TextField {
            id: gradText
            Layout.preferredWidth: 70
            Layout.preferredHeight: 30
            text: "0"
            selectByMouse: true
            font.pixelSize: 11

            onTextEdited: {
                textVal = text;
            }

            Component.onCompleted: {
                text = textVal;
            }
        }

    }
}
