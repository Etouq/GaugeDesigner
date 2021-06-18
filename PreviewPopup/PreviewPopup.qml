import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import "../StyledControls"

Window {
    id: root
    width: height / 3
    //height: 840
    height: 0.95 * Screen.desktopAvailableHeight

    flags: Qt.WindowTitleHint | Qt.CustomizeWindowHint | Qt.Dialog | Qt.WindowCloseButtonHint

    color: "#eeeeee"

    onWidthChanged: Qt.callLater(updateWidth)
    onHeightChanged: Qt.callLater(updateWidth)

    function updateWidth() {
        width = height / 3;
    }

    Connections {
        target: gaugeInterface
        function onGaugesLoaded() {
            let typeVal = aircraftInterface.getType();
            if (typeVal === -1)
            {
                edLoader.setSource('');
                return;
            }
            let typeString = typeVal === 0 ? "Jet" : typeVal === 1 ? "Prop" : "Turboprop";
            let engineString = aircraftInterface.getNumEngines() === 1 ? "Single" : aircraftInterface.getNumEngines() === 2 ? "Double" : "Quad";
            edLoader.setSource("qrc:/PreviewPopup/" + typeString + engineString + ".qml", { "numTanks": aircraftInterface.getNumTanks() });
        }
    }

    function updateAnimations()
    {
        n1Interface.updateEngineAnimation();
        n2Interface.updateEngineAnimation();
        ittInterface.updateEngineAnimation();
        rpmInterface.updateEngineAnimation();
        secondInterface.updateEngineAnimation();
        trqInterface.updateEngineAnimation();
        fuelQtyInterface.updateEngineAnimation();
        fuelFlowInterface.updateEngineAnimation();
        oilTempInterface.updateEngineAnimation();
        oilPressInterface.updateEngineAnimation();
        egtInterface.updateEngineAnimation();
        gaugeInterface.updateMiscAnimations();
    }

    Timer {
        id: animTimer
        interval: 20
        repeat: true
        running: false
        onTriggered: updateAnimations()
    }

    Item {
        id: bgItem
        width: 420
        height: 1260
        transformOrigin: Item.TopLeft
        scale: root.width / 420

        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            width: 420
            height: 1200
            color: "#1A1D21"

            Loader {
                id: edLoader
                asynchronous: true
                anchors.fill: parent
            }

        }

        Button {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.leftMargin: 7.5
            anchors.rightMargin: 7.5
            anchors.bottomMargin: 7.5
            height: 45
            hoverEnabled: true

            padding: 0

            onClicked: animTimer.running = !animTimer.running

            background: Rectangle {
                anchors.fill: parent
                color: parent.hovered ? Qt.darker("#00b4ff", 1.1) : "#00b4ff"
            }

            contentItem: Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: (animTimer.running ? "Stop" : "Start") + " Animation"
                font.bold: true
                color: parent.hovered ? Qt.darker("white", 1.1) : "white"
                font.pixelSize: 24
            }

        }
    }



}
