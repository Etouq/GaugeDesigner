import QtQuick 2.15
import "StyledControls"

Rectangle {
    id: gaugeTabBar
    width: parent.width
    height: 30
    color: "#00b4ff"

    property int activeType: 0
    property bool egtReplacesItt: false
    property bool loadReplacesMan: false
    property bool hasEgt: false

    property int activeIndex: 0

    function resetPosition()
    {
        layout.activeItem = generalTab;
        gaugeTabBar.activeIndex = 0;
    }

    Item {
        x: Math.max(Math.min(gaugeTabBar.width / 2 - layout.activeItem.x - layout.activeItem.width / 2, 0), gaugeTabBar.width - layout.childrenRect.width)
        y: 0
        width: gaugeTabBar.width
        height: 30

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


            StyledTabButton {
                id: generalTab
                isActiveItem: layout.activeItem == generalTab
                text: "GENERAL"
                onClicked: function() { layout.activeItem = generalTab; gaugeTabBar.activeIndex = 0; }
            }

            StyledTabButton {
                id: n1Tab
                isActiveItem: layout.activeItem == n1Tab
                text: "N1"
                visible: activeType != 1
                onClicked: function() { layout.activeItem = n1Tab; gaugeTabBar.activeIndex = 1; }
            }

            StyledTabButton {
                id: n2Tab
                isActiveItem: layout.activeItem == n2Tab
                text: "N2"
                visible: activeType == 0
                onClicked: function() { layout.activeItem = n2Tab; gaugeTabBar.activeIndex = 2; }
            }

            StyledTabButton {
                id: trqTab
                isActiveItem: layout.activeItem == trqTab
                text: "TORQUE"
                visible: activeType == 2
                onClicked: function() { layout.activeItem = trqTab; gaugeTabBar.activeIndex = 3; }
            }

            StyledTabButton {
                id: ittTab
                isActiveItem: layout.activeItem == ittTab
                text: gaugeTabBar.egtReplacesItt ? "EGT" : "ITT"
                visible: activeType != 1
                onClicked: function() { layout.activeItem = ittTab; gaugeTabBar.activeIndex = 4; }
            }

            StyledTabButton {
                id: rpmTab
                isActiveItem: layout.activeItem == rpmTab
                text: "RPM"
                visible: activeType != 0
                onClicked: function() { layout.activeItem = rpmTab; gaugeTabBar.activeIndex = 5; }
            }

            StyledTabButton {
                id: secondTab
                isActiveItem: layout.activeItem == secondTab
                text: gaugeTabBar.loadReplacesMan ? "LOAD" : "MANIFOLD"
                visible: activeType == 1
                onClicked: function() { layout.activeItem = secondTab; gaugeTabBar.activeIndex = 6; }
            }

            StyledTabButton {
                id: fuelQtyTab
                isActiveItem: layout.activeItem == fuelQtyTab
                text: "FUEL QUANTITY"
                onClicked: function() { layout.activeItem = fuelQtyTab; gaugeTabBar.activeIndex = 7; }
            }

            StyledTabButton {
                id: fuelFlowTab
                isActiveItem: layout.activeItem == fuelFlowTab
                text: "FUEL FLOW"
                onClicked: function() { layout.activeItem = fuelFlowTab; gaugeTabBar.activeIndex = 8; }
            }

            StyledTabButton {
                id: oilTempTab
                isActiveItem: layout.activeItem == oilTempTab
                text: "OIL TEMPERATURE"
                onClicked: function() { layout.activeItem = oilTempTab; gaugeTabBar.activeIndex = 9; }
            }

            StyledTabButton {
                id: oilPressTab
                isActiveItem: layout.activeItem == oilPressTab
                text: "OIL PRESSURE"
                onClicked: function() { layout.activeItem = oilPressTab; gaugeTabBar.activeIndex = 10; }
            }

            StyledTabButton {
                id: egtTab
                isActiveItem: layout.activeItem == egtTab
                text: "EGT"
                visible: activeType != 0 && gaugeTabBar.hasEgt
                onClicked: function() { layout.activeItem = egtTab; gaugeTabBar.activeIndex = 11; }
            }
        }

        Rectangle {
            width: layout.activeItem.width
            height: 2
            anchors.bottom: layout.bottom
            x: layout.activeItem.x
            color: "white"
            Behavior on x {
                NumberAnimation { duration: 250 }
            }
            Behavior on width {
                NumberAnimation { duration: 250 }
            }
        }

    }





}
