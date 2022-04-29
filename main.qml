import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Qt.labs.platform as LabPlatform
import QtQuick.Shapes 2.15
import QtQuick.Layouts 2.15
import "GeneralTab"
import "GaugeTab"
import "StyledControls"
import "PreviewPopup"


ApplicationWindow {
    id: rootItem
    width: 630
    height: 500
    visible: true
    color: "black"
    title: Qt.application.displayName


    property real maxScaleFactor: Math.min(Screen.desktopAvailableWidth / 630, Screen.desktopAvailableHeight / 500)

    maximumWidth: 630 * maxScaleFactor
    maximumHeight: 500 * maxScaleFactor

    onWidthChanged: refitTimer.restart()
    onHeightChanged: refitTimer.restart()

    property bool jetValid: generalTab.activeType != 0 || (n1Tab.isValid && n2Tab.isValid && ittTab.isValid)
    property bool propValid: generalTab.activeType != 1 || (rpmTab.isValid && secondTab.isValid && (!generalTab.hasEgt || egtTab.isValid))
    property bool turbopropValid: generalTab.activeType != 2 || (n1Tab.isValid && trqTab.isValid && ittTab.isValid && rpmTab.isValid && (!generalTab.hasEgt || egtTab.isValid))
    property bool allValid: generalTab.isValid && jetValid && propValid && turbopropValid && fuelQtyTab.isValid && fuelFlowTab.isValid && oilTempTab.isValid && oilPressTab.isValid

    Timer {
        id: refitTimer
        running: true
        interval: 1000
        repeat: false
        onTriggered: {
            if (Math.abs(rootItem.height - contentRoot.scale * 500) > 0.5)
                rootItem.height = contentRoot.scale * 500;
            else if (Math.abs(rootItem.width - contentRoot.scale * 630) > 0.5)
                rootItem.width = contentRoot.scale * 630;
        }
    }

    function saveDataMain() {
        generalTab.saveData();

        if (generalTab.activeType == 0) {
            n1Tab.saveData();
            n2Tab.saveData();
            ittTab.saveData();
        }
        else if (generalTab.activeType == 1) {
            rpmTab.saveData();
            secondTab.saveData();
            if (generalTab.hasEgt)
                egtTab.saveData();
        }
        else {
            n1Tab.saveData();
            trqTab.saveData();
            ittTab.saveData();
            rpmTab.saveData()
            if (generalTab.hasEgt)
                egtTab.saveData();
        }
        fuelQtyTab.saveData();
        fuelFlowTab.saveData();
        oilTempTab.saveData();
        oilPressTab.saveData();

        aircraftInterface.saveAircraft();

        if (toolbar.openModeActive && (toolbar.lastKey !== generalTab.name))
        {
            aircraftManager.removeAircraft(toolbar.lastKey);
            toolbar.lastKey = generalTab.name;
        }
    }


    Rectangle {
        id: contentRoot
        width: 630
        height: 500
        transformOrigin: Item.TopLeft
        scale: Math.min(rootItem.width / 630, rootItem.height / 500)
        clip: true
        color: "#eeeeee"

        MouseArea {
            anchors.fill: parent
            onClicked: forceActiveFocus(rootItem)
        }


        StackLayout {
            anchors.bottom: parent.bottom
            width: parent.width
            anchors.top: gaugeTabBar.bottom
            currentIndex: gaugeTabBar.activeIndex
            GeneralTab {
                id: generalTab
            }
            GaugeTab {
                id: n1Tab
                defaultTitle: "N1"
                unitTypes: [1]
                gaugeObject: n1Interface
            }
            GaugeTab {
                id: n2Tab
                defaultTitle: "N2"
                unitTypes: [1]
                gaugeObject: n2Interface
            }
            GaugeTab {
                id: trqTab
                defaultTitle: "TRQ"
                unitTypes: [1, 5]
                gaugeObject: trqInterface
            }
            GaugeTab {
                id: ittTab
                defaultTitle: generalTab.egtReplacesItt ? "EGT" : "ITT"
                unitTypes: [3]
                gaugeObject: ittInterface
            }
            GaugeTab {
                id: rpmTab
                defaultTitle: "RPM"
                unitTypes: [2]
                gaugeObject: rpmInterface
            }
            GaugeTab {
                id: secondTab
                defaultTitle: generalTab.loadReplacesMan ? "LOAD" : "MAN"
                unitTypes: generalTab.loadReplacesMan ? [1] : [4]
                gaugeObject: secondInterface
            }
            GaugeTab {
                id: fuelQtyTab
                defaultTitle: generalTab.numTanks == 1 ? "FUEL QTY" : "L FUEL QTY R"
                unitTypes: [6, 7]
                gaugeObject: fuelQtyInterface
            }
            GaugeTab {
                id: fuelFlowTab
                defaultTitle: generalTab.numEngines == 1 ? "FUEL FLOW" : "L FUEL FLOW R"
                unitTypes: [8, 9, 10, 11, 12, 13]
                gaugeObject: fuelFlowInterface
            }
            GaugeTab {
                id: oilTempTab
                defaultTitle: generalTab.numEngines == 1 ? "OIL TEMP" : "L OIL TEMP R"
                unitTypes: [3]
                gaugeObject: oilTempInterface
            }
            GaugeTab {
                id: oilPressTab
                defaultTitle: generalTab.numEngines == 1 ? "OIL PRESS" : "L OIL PRESS R"
                unitTypes: [4]
                gaugeObject: oilPressInterface
            }
            GaugeTab {
                id: egtTab
                defaultTitle: generalTab.numEngines == 1 ? "EGT" : "L EGT R"
                unitTypes: [3]
                gaugeObject: egtInterface
            }
        }


        GaugeTabBar {
            id: gaugeTabBar
            anchors.top: toolbar.bottom
            activeType: generalTab.activeType
            egtReplacesItt: generalTab.egtReplacesItt
            loadReplacesMan: generalTab.loadReplacesMan
            hasEgt: generalTab.hasEgt
        }

        GaugeToolBar {
            id: toolbar
            anchors.top: parent.top
            width: parent.width
            everythingValid: allValid

            unsavedChanges: generalTab.unsavedChanges || (generalTab.activeType == 0 ? n1Tab.unsavedChanges || n2Tab.unsavedChanges || ittTab.unsavedChanges : generalTab.activeType == 1 ? rpmTab.unsavedChanges || secondTab.unsavedChanges || (generalTab.hasEgt && egtTab.unsavedChanges) : n1Tab.unsavedChanges || trqTab.unsavedChanges || ittTab.unsavedChanges || rpmTab.unsavedChanges || (generalTab.hasEgt && egtTab.unsavedChanges)) || fuelQtyTab.unsavedChanges || fuelFlowTab.unsavedChanges || oilTempTab.unsavedChanges || oilPressTab.unsavedChanges

            onSaveDataClicked: saveDataMain()

            onPositionResetNeeded: gaugeTabBar.resetPosition()
        }



    }

    Connections {
        target: netInterface
        function onShowPopupError(msg) {
            errorPopup.text = msg;
            errorPopup.open();
        }
    }


    LabPlatform.MessageDialog {
        id: errorPopup
//        icon: StandardIcon.Critical
        title: "Error"
        buttons: LabPlatform.MessageDialog.Ok
    }







}
