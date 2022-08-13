import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Definition 1.0

GroupBox {

    title: "Airspeed Colors"
    topPadding: 5
    leftPadding: 5
    rightPadding: 5
    bottomPadding: 5

    label: CheckBox {
        id: checkBox
        x: -3
        checked: !AircraftDefinition.noColors
        text: parent.title
        font.pointSize: 11
    }

    Component.onCompleted: label.anchors.bottom = background.top

    GridLayout {
        id: gridLayout
        columns: 5
        enabled: checkBox.checked

        Item {
            Layout.fillWidth: true // spacer
        }

        Text {
            text: "Start"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.preferredWidth: 100
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: "Roboto"
            font.pointSize: 11
            color: enabled ? Material.foreground : Material.hintTextColor
        }

        Text {
            text: "End"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.preferredWidth: 100
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: "Roboto"
            font.pointSize: 11
            color: enabled ? Material.foreground : Material.hintTextColor
        }

        Text {
            text: "Enabled"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: "Roboto"
            font.pointSize: 11
            color: enabled ? Material.foreground : Material.hintTextColor
        }

        Text {
            text: "Dynamic"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 11
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: "Roboto"
            Layout.fillWidth: true
            color: enabled ? Material.foreground : Material.hintTextColor
        }

        Text {
            enabled: lowEnabledBox.checked
            color: enabled ? Material.foreground : Material.hintTextColor
            text: "Lower Barberpole"
            Layout.fillWidth: true
            font.pointSize: 11
            font.family: "Roboto"
        }

        Item {
            Layout.preferredWidth: 100
            Layout.fillWidth: true
            Layout.preferredHeight: 0
            // spacer
        }

        TextField {
            id: lowLimitField

            enabled: lowEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "End"
            text: AircraftDefinition.lowLimit
        }

        CheckBox {
            id: lowEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasLowLimit
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        Text {
            enabled: flapsEnabledBox.checked

            Layout.fillWidth: true

            font.pointSize: 11
            font.family: "Roboto"

            color: enabled ? Material.foreground : Material.hintTextColor

            text: "Flaps (white)"
        }

        TextField {
            id: flapsStartField

            enabled: flapsEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "Start"
            text: AircraftDefinition.flapsBegin
        }

        TextField {
            id: flapsEndField

            enabled: flapsEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "End"
            text: AircraftDefinition.flapsEnd
        }

        CheckBox {
            id: flapsEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasFlapsSpeed
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        Text {
            enabled: greenEnabledBox.checked
            color: enabled ? Material.foreground : Material.hintTextColor
            text: "Green"
            font.pointSize: 11
            font.family: "Roboto"
            Layout.fillWidth: true
        }

        TextField {
            id: greenStartField

            enabled: greenEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "Start"
            text: AircraftDefinition.greenBegin
        }


        TextField {
            id: greenEndField

            enabled: greenEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "End"
            text: AircraftDefinition.greenEnd
        }

        CheckBox {
            id: greenEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasGreenSpeed
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        Text {
            enabled: yellowEnabledBox.checked
            color: enabled ? Material.foreground : Material.hintTextColor
            text: "Yellow"
            font.pointSize: 11
            font.family: "Roboto"
            Layout.fillWidth: true
        }

        TextField {
            id: yellowStartField

            enabled: yellowEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "Start"
            text: AircraftDefinition.yellowBegin
        }

        TextField {
            id: yellowEndField

            enabled: yellowEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "End"
            text: AircraftDefinition.yellowEnd
        }

        CheckBox {
            id: yellowEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasYellowSpeed
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        Text {
            enabled: redEnabledBox.checked
            color: enabled ? Material.foreground : Material.hintTextColor
            text: "Red"
            font.pointSize: 11
            font.family: "Roboto"
            Layout.fillWidth: true
        }

        TextField {
            id: redStartField

            enabled: redEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "Start"
            text: AircraftDefinition.redBegin
        }

        TextField {
            id: redEndField

            enabled: redEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "End"
            text: AircraftDefinition.redEnd
        }

        CheckBox {
            id: redEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasRedSpeed
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        Text {
            enabled: highEnabledBox.checked
            color: enabled ? Material.foreground : Material.hintTextColor
            text: "Upper Barberpole"
            font.pointSize: 11
            font.family: "Roboto"
            Layout.fillWidth: true
        }

        TextField {
            id: highLimitField

            enabled: highEnabledBox.checked && !highDynamicBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "Start"
            text: AircraftDefinition.highLimit
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        CheckBox {
            id: highEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasHighLimit
        }

        CheckBox {
            id: highDynamicBox

            enabled: highEnabledBox.checked

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.dynamicBarberpole
        }

    }

    Binding {
        target: AircraftDefinition
        property: "noColors"
        value: !checkBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "lowLimit"
        value: lowLimitField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasLowLimit"
        value: lowEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "flapsBegin"
        value: flapsStartField.text
    }

    Binding {
        target: AircraftDefinition
        property: "flapsEnd"
        value: flapsEndField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasFlapsSpeed"
        value: flapsEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "greenBegin"
        value: greenStartField.text
    }

    Binding {
        target: AircraftDefinition
        property: "greenEnd"
        value: greenEndField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasGreenSpeed"
        value: greenEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "yellowBegin"
        value: yellowStartField.text
    }

    Binding {
        target: AircraftDefinition
        property: "yellowEnd"
        value: yellowEndField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasYellowSpeed"
        value: yellowEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "redBegin"
        value: redStartField.text
    }

    Binding {
        target: AircraftDefinition
        property: "redEnd"
        value: redEndField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasRedSpeed"
        value: redEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "highLimit"
        value: highLimitField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasHighLimit"
        value: highEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "dynamicBarberpole"
        value: highDynamicBox.checked
    }
}

/*##^##
Designer {
    D{i:0;height:296;width:424}D{i:5}D{i:7}D{i:8}D{i:12}D{i:15}D{i:16}D{i:17}D{i:18}D{i:22}
D{i:27}D{i:32}D{i:33}D{i:34}D{i:35}D{i:36}D{i:37}D{i:2}
}
##^##*/
