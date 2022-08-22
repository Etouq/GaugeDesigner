import QtQuick 2.15
import QtQuick.Controls.Material 2.15

import Definition 1.0
import TypeEnums 1.0

import "MyControls" as MyControls

Rectangle {
    id: gaugeTabBar
    width: parent.width
    height: 30
    color: Material.primary//"#00b4ff"

    property int activeIndex: 0

    function resetPosition()
    {
        layout.activeItem = generalTab;
        gaugeTabBar.activeIndex = 0;
    }

    function gaugeTypeToText(type)
    {
        switch (type)
        {
            case SwitchingGaugeType.NONE:
                return "None";
            case SwitchingGaugeType.N1:
                return "N1";
            case SwitchingGaugeType.N2:
                return "N2";
            case SwitchingGaugeType.ENGINE_TEMP:
                return "ENGINE TEMPERATURE";
            case SwitchingGaugeType.RPM:
                return "RPM";
            case SwitchingGaugeType.PROP_RPM:
                return "PROPELLER RPM";
            case SwitchingGaugeType.POWER:
                return "POWER";
            case SwitchingGaugeType.MANIFOLD_PRESSURE:
                return "MANIFOLD";
            case SwitchingGaugeType.TORQUE:
                return "TORQUE";
            default:
                return "UNKNOWN";
        }
    }

    Item {
        id: movingItem
        x: (gaugeTabBar.width - layout.childrenRect.width) / 2
        y: 0
        width: gaugeTabBar.width
        height: 30

        Binding {
            target: movingItem
            property: "x"
            when: layout.childrenRect.width > gaugeTabBar.width
            value: Math.max(Math.min(gaugeTabBar.width / 2 - layout.activeItem.x - layout.activeItem.width / 2, 0), gaugeTabBar.width - layout.childrenRect.width)
        }

        Behavior on x {
            NumberAnimation { duration: 250 }
        }

        Row {
            id: layout
            x: 0
            y: 0
            width: parent.width
            height: 30
            spacing: 0
            property Item activeItem: generalTab


            MyControls.TabButton {
                id: generalTab
                isActiveItem: layout.activeItem == generalTab
                text: "GENERAL"
                onClicked: function() { layout.activeItem = generalTab; gaugeTabBar.activeIndex = 0; }
            }

            MyControls.TabButton {
                id: gauge1Tab
                isActiveItem: layout.activeItem == gauge1Tab
                text: gaugeTypeToText(AircraftDefinition.gauge1Type)
                onClicked: function() { layout.activeItem = gauge1Tab; gaugeTabBar.activeIndex = 1; }
            }

            MyControls.TabButton {
                id: gauge2Tab
                isActiveItem: layout.activeItem == gauge2Tab
                text: gaugeTypeToText(AircraftDefinition.gauge2Type)
                onClicked: function() { layout.activeItem = gauge2Tab; gaugeTabBar.activeIndex = 2; }
            }

            MyControls.TabButton {
                id: gauge3Tab
                isActiveItem: layout.activeItem == gauge3Tab
                text: gaugeTypeToText(AircraftDefinition.gauge3Type)
                visible: AircraftDefinition.gauge3Type != SwitchingGaugeType.NONE
                onClicked: function() { layout.activeItem = gauge3Tab; gaugeTabBar.activeIndex = 3; }
            }

            MyControls.TabButton {
                id: gauge4Tab
                isActiveItem: layout.activeItem == gauge4Tab
                text: gaugeTypeToText(AircraftDefinition.gauge4Type)
                visible: AircraftDefinition.gauge4Type != SwitchingGaugeType.NONE
                onClicked: function() { layout.activeItem = gauge4Tab; gaugeTabBar.activeIndex = 4; }
            }

            MyControls.TabButton {
                id: fuelQtyTab
                isActiveItem: layout.activeItem == fuelQtyTab
                text: "FUEL QUANTITY"
                onClicked: function() { layout.activeItem = fuelQtyTab; gaugeTabBar.activeIndex = 5; }
            }

            MyControls.TabButton {
                id: fuelFlowTab
                isActiveItem: layout.activeItem == fuelFlowTab
                text: "FUEL FLOW"
                onClicked: function() { layout.activeItem = fuelFlowTab; gaugeTabBar.activeIndex = 6; }
            }

            MyControls.TabButton {
                id: oilTempTab
                isActiveItem: layout.activeItem == oilTempTab
                text: "OIL TEMPERATURE"
                onClicked: function() { layout.activeItem = oilTempTab; gaugeTabBar.activeIndex = 7; }
            }

            MyControls.TabButton {
                id: egtTab
                isActiveItem: layout.activeItem == egtTab
                text: "ENGINE TEMPERATURE"
                visible: AircraftDefinition.hasSecondaryTempGauge
                onClicked: function() { layout.activeItem = egtTab; gaugeTabBar.activeIndex = 8; }
            }

            MyControls.TabButton {
                id: oilPressTab
                isActiveItem: layout.activeItem == oilPressTab
                text: "OIL PRESSURE"
                onClicked: function() { layout.activeItem = oilPressTab; gaugeTabBar.activeIndex = 9; }
            }
        }

        Rectangle {
            x: layout.activeItem.x

            width: layout.activeItem.width
            height: 2

            anchors.bottom: layout.bottom

            color: Material.foreground

            Behavior on x {
                NumberAnimation { duration: 250 }
            }
            Behavior on width {
                NumberAnimation { duration: 250 }
            }
        }

    }





}
