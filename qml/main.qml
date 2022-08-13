import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15

import Definition 1.0

import "GeneralTab"
import "GaugeTab"
import "StyledControls"
import "PreviewPopup"


ApplicationWindow {
    id: rootItem
    width: 700
    height: 600
    visible: true
    title: Qt.application.displayName


    property real maxScaleFactor: Math.min(Screen.desktopAvailableWidth / 700, Screen.desktopAvailableHeight / 600)

    maximumWidth: 700 * maxScaleFactor
    maximumHeight: 600 * maxScaleFactor

    // onWidthChanged: refitTimer.restart()
    // onHeightChanged: refitTimer.restart()


    // Timer {
    //     id: refitTimer
    //     running: true
    //     interval: 1000
    //     repeat: false
    //     onTriggered: {
    //         if (Math.abs(rootItem.height - contentRoot.scale * 600) > 0.5)
    //             rootItem.height = contentRoot.scale * 600;
    //         else if (Math.abs(rootItem.width - contentRoot.scale * 700) > 0.5)
    //             rootItem.width = contentRoot.scale * 700;
    //     }
    // }

    // function saveDataMain() {
    //     generalTab.saveData();

    //     if (generalTab.activeType == 0) {
    //         n1Tab.saveData();
    //         n2Tab.saveData();
    //         ittTab.saveData();
    //     }
    //     else if (generalTab.activeType == 1) {
    //         rpmTab.saveData();
    //         secondTab.saveData();
    //         if (generalTab.hasEgt)
    //             egtTab.saveData();
    //     }
    //     else {
    //         n1Tab.saveData();
    //         trqTab.saveData();
    //         ittTab.saveData();
    //         rpmTab.saveData()
    //         if (generalTab.hasEgt)
    //             egtTab.saveData();
    //     }
    //     fuelQtyTab.saveData();
    //     fuelFlowTab.saveData();
    //     oilTempTab.saveData();
    //     oilPressTab.saveData();

    //     aircraftInterface.saveAircraft();

    //     if (toolbar.openModeActive && (toolbar.lastKey !== generalTab.name))
    //     {
    //         aircraftManager.removeAircraft(toolbar.lastKey);
    //         toolbar.lastKey = generalTab.name;
    //     }
    // }


    Item {
        id: contentRoot
        // width: 700
        // height: 600
        // transformOrigin: Item.TopLeft
        // scale: Math.min(rootItem.width / 700, rootItem.height / 600)
        anchors.fill: parent
        clip: true

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
                id: gauge1Tab

                gaugeDef: AircraftDefinition.gauge1()
                gaugeType: AircraftDefinition.gauge1Type
            }
            GaugeTab {
                id: gauge2Tab

                gaugeDef: AircraftDefinition.gauge2()
                gaugeType: AircraftDefinition.gauge2Type
            }
            GaugeTab {
                id: gauge3Tab

                gaugeDef: AircraftDefinition.gauge3()
                gaugeType: AircraftDefinition.gauge3Type
            }
            GaugeTab {
                id: gauge4Tab

                gaugeDef: AircraftDefinition.gauge4()
                gaugeType: AircraftDefinition.gauge4Type
            }
            GaugeTab {
                id: fuelQtyTab

                gaugeDef: AircraftDefinition.fuelQtyGauge()
            }
            GaugeTab {
                id: fuelFlowTab

                gaugeDef: AircraftDefinition.fuelFlowGauge()
            }
            GaugeTab {
                id: oilTempTab

                gaugeDef: AircraftDefinition.oilTempGauge()
            }
            GaugeTab {
                id: secondaryTempTab

                gaugeDef: AircraftDefinition.secondaryTempGauge()
                isSecondaryTemp: true
            }
            GaugeTab {
                id: oilPressTab

                gaugeDef: AircraftDefinition.oilPressGauge()
            }
        }


        GaugeTabBar {
            id: gaugeTabBar
            anchors.top: toolbar.bottom
        }

        GaugeToolBar {
            id: toolbar
            anchors.top: parent.top
            width: parent.width

            //onSaveDataClicked: saveDataMain()

            onPositionResetNeeded: gaugeTabBar.resetPosition()
        }

    }

}
