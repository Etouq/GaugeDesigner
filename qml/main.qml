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
import "AircraftSelectionPopup"


ApplicationWindow {
    id: rootItem
    width: 700
    height: 600
    visible: true
    title: Qt.application.displayName

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

        onPositionResetNeeded: gaugeTabBar.resetPosition()
    }

}
