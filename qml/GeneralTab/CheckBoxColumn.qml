import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Definition 1.0

GridLayout {
    id: checkBoxes
    width: 198
    height: 233
    rowSpacing: 0
    columns: 2

    Text {
        color: Material.foreground
        text: "Flaps"
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 11
        Layout.fillWidth: true
        textFormat: Text.PlainText
        font.family: "Roboto"
    }

    CheckBox {
        id: flapsBox
        spacing: 0
        bottomPadding: 8
        topPadding: 8

        checked: AircraftDefinition.hasFlaps
    }

    Text {
        color: spoilersBox.enabled ? Material.foreground : Material.hintTextColor
        text: "Spoilers"
        verticalAlignment: Text.AlignVCenter
        textFormat: Text.PlainText
        font.pointSize: 11
        Layout.fillWidth: true
        font.family: "Roboto"
    }

    CheckBox {
        id: spoilersBox
        spacing: 0
        bottomPadding: 8
        topPadding: 8

        enabled: AircraftDefinition.hasFlaps

        checked: AircraftDefinition.hasSpoilers
    }

    Text {
        color: Material.foreground
        text: "Elevator Trim"
        verticalAlignment: Text.AlignVCenter
        Layout.topMargin: 10
        font.pointSize: 11

        font.family: "Roboto"
        Layout.fillWidth: true
        textFormat: Text.PlainText
    }

    CheckBox {
        id: elevTrimBox
        Layout.topMargin: 10
        spacing: 0
        topPadding: 8
        bottomPadding: 8

        checked: AircraftDefinition.hasElevatorTrim
    }

    Text {
        color: Material.foreground
        text: "Rudder Trim"
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 11

        font.family: "Roboto"
        Layout.fillWidth: true
        textFormat: Text.PlainText
    }

    CheckBox {
        id: ruddTrimBox
        topPadding: 8
        bottomPadding: 8

        spacing: 0

        checked: AircraftDefinition.hasRudderTrim
    }

    Text {
        color: Material.foreground
        text: "Aileron Trim"
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 11

        font.family: "Roboto"
        Layout.fillWidth: true
        textFormat: Text.PlainText
    }

    CheckBox {
        id: ailTrimBox
        topPadding: 8
        bottomPadding: 8

        spacing: 0

        checked: AircraftDefinition.hasAileronTrim
    }

    Text {
        color: Material.foreground
        text: "APU"
        verticalAlignment: Text.AlignVCenter
        Layout.topMargin: 10
        font.pointSize: 11

        font.family: "Roboto"
        Layout.fillWidth: true
        textFormat: Text.PlainText
    }

    CheckBox {
        id: apuBox
        Layout.topMargin: 10
        topPadding: 8
        bottomPadding: 8

        spacing: 0

        checked: AircraftDefinition.hasApu
    }

    Text {
        color: Material.foreground
        text: "Single Fuel Tank"
        verticalAlignment: Text.AlignVCenter
        Layout.topMargin: 10
        font.pointSize: 11

        font.family: "Roboto"
        Layout.fillWidth: true
        textFormat: Text.PlainText
    }

    CheckBox {
        id: singleTankBox
        topPadding: 8
        bottomPadding: 8

        spacing: 0
        Layout.topMargin: 10

        checked: AircraftDefinition.singleTank
    }



    Binding {
        target: AircraftDefinition
        property: "hasFlaps"
        value: flapsBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "hasSpoilers"
        value: spoilersBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "hasElevatorTrim"
        value: elevTrimBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "hasRudderTrim"
        value: ruddTrimBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "hasAileronTrim"
        value: ailTrimBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "hasApu"
        value: apuBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "singleTank"
        value: singleTankBox.checked
    }
}
