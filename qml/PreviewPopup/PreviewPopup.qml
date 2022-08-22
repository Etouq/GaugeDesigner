import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import Preview 1.0

ApplicationWindow {
    id: root
    width: (height - animationToggle.height - 7.5) * 0.35
    height: 0.85 * Screen.desktopAvailableHeight

    flags: Qt.Dialog//Qt.WindowTitleHint | Qt.CustomizeWindowHint | Qt.Dialog | Qt.WindowCloseButtonHint

    onWidthChanged: Qt.callLater(updateWidth)
    onHeightChanged: Qt.callLater(updateWidth)

    function updateWidth() {
        const desiredWidth = (height - animationToggle.height - 7.5) * 0.35
        if (Math.abs(width - desiredWidth) > 0.5) {
            width = desiredWidth
        }
    }

    Connections {
        target: PreviewManager
        function onLayoutPathChanged() {
            edLoader.setSource("qrc:/PreviewPopup/EngineDisplay/Gauges/Layouts/" + PreviewManager.layoutPath + ".qml");
        }
    }

    function updateAnimations()
    {
        PreviewManager.update();
        // n1Interface.updateEngineAnimation();
        // n2Interface.updateEngineAnimation();
        // ittInterface.updateEngineAnimation();
        // rpmInterface.updateEngineAnimation();
        // secondInterface.updateEngineAnimation();
        // trqInterface.updateEngineAnimation();
        // fuelQtyInterface.updateEngineAnimation();
        // fuelFlowInterface.updateEngineAnimation();
        // oilTempInterface.updateEngineAnimation();
        // oilPressInterface.updateEngineAnimation();
        // egtInterface.updateEngineAnimation();
        // gaugeInterface.updateMiscAnimations();
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
        height: 1200
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
    }


    Button {
        id: animationToggle
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 7.5
        anchors.rightMargin: 7.5
        anchors.bottomMargin: 7.5


        text: (animTimer.running ? "Stop" : "Start") + " Animation"

        onClicked: animTimer.running = !animTimer.running

    }



}
