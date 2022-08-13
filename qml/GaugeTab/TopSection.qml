import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Definition 1.0
import TypeEnums 1.0

import "../StyledControls"

Item {
    id: root
    width: 630
    height: childrenRect.height


    required property GaugeDefinition gaugeDef
    required property int gaugeType
    required property bool isSecondaryTemp

    Row {
        id: topRow

        x: 10
        y: 10
        spacing: 10

        Text {
            anchors.verticalCenter: titleText.verticalCenter

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground

            text: "Title"
        }

        TextField {
            id: titleText
            width: 150

            font.pointSize: 11

            selectByMouse: true

            text: root.gaugeDef.title

            onTextChanged: function() {
                root.gaugeDef.title = titleText.text;
            }
        }

        Text {
            anchors.verticalCenter: minValField.verticalCenter

            leftPadding: 10

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground

            text: "Min"
        }

        TextField {
            id: minValField

            width: 80

            font.pointSize: 11

            validator: DoubleValidator { top: root.gaugeDef.maxValue }
            selectByMouse: true

            text: root.gaugeDef.minValue

            onTextChanged: function() {
                if (acceptableInput)
                {
                    root.gaugeDef.minValue = parseFloat(minValField.text);
                }
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }

        Text {
            anchors.verticalCenter: maxValField.verticalCenter

            leftPadding: 10

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground

            text: "Max"
        }

        TextField {
            id: maxValField

            width: 80

            font.pointSize: 11

            validator: DoubleValidator { bottom: root.gaugeDef.minValue }
            selectByMouse: true

            text: root.gaugeDef.maxValue

            Component.onCompleted: function() {
                ensureVisible(0);
            }

            onTextChanged: function() {
                if (acceptableInput)
                {
                    root.gaugeDef.maxValue = parseFloat(maxValField.text);
                }
            }
        }


        Text {
            anchors.verticalCenter: noTextSwitch.verticalCenter

            leftPadding: 10

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground

            text: "No Text"
        }

        CheckBox {
            id: noTextSwitch

            anchors.verticalCenter: maxValField.verticalCenter

            spacing: 0
            bottomPadding: 8
            topPadding: 8

            font.pointSize: 11

            checked: root.gaugeDef.noText
        }
    }

    Row {
        id: botRow
        x: 10
        anchors.top: topRow.bottom
        spacing: 10

        Text {
            text: "Unit"

            anchors.verticalCenter: unitBox.verticalCenter

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground
        }

        ComboBox {
            id: unitBox

            width: 150
            model: root.gaugeDef.unitModel

            textRole: "longText"
            valueRole: "unitId"

            font.pointSize: 11

            Component.onCompleted: function() {
                currentIndex = unitBox.indexOfValue(root.gaugeDef.unit)
            }

            Connections {
                target: root.gaugeDef
                function onUnitChanged() {
                    unitBox.currentIndex = unitBox.indexOfValue(root.gaugeDef.unit)
                }
            }

            onActivated: function(index) {
                root.gaugeDef.unit = currentValue;
                root.gaugeDef.unitString = gaugeDef.unitModel.getShortText(index);
            }
        }

        TextField {
            id: unitText

            width: 70

            font.pointSize: 11

            selectByMouse: true

            text: root.gaugeDef.unitString

            onTextChanged: function() {
                root.gaugeDef.unitString = unitText.text;
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }


        Text {
            text: "Increment"

            font.family: "Roboto"
            font.pointSize: 11

            anchors.verticalCenter: incrementVal.verticalCenter

            color: noTextSwitch.checked ? Material.hintTextColor : Material.foreground

            leftPadding: 10
        }

        TextField {
            id: incrementVal

            enabled: !noTextSwitch.checked

            width: 70

            validator: DoubleValidator{}
            selectByMouse: true
            font.pointSize: 11

            text: root.gaugeDef.textIncrement

            onTextChanged: function() {
                if (acceptableInput)
                {
                    root.gaugeDef.textIncrement = parseFloat(incrementVal.text);
                }
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }

            // background: Rectangle {
            //     border.width: parent.activeFocus ? 2 : 1
            //     color: parent.palette.base
            //     border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
            // }
        }

        Text {
            text: "Precision"

            font.family: "Roboto"
            font.pointSize: 11

            anchors.verticalCenter: numDecimalsVal.verticalCenter

            color: noTextSwitch.checked ? Material.hintTextColor : Material.foreground

            leftPadding: 10
        }

        TextField {
            id: numDecimalsVal

            enabled: !noTextSwitch.checked

            width: 70

            font.pointSize: 11

            validator: IntValidator { bottom: 0; top: 5 }
            selectByMouse: true

            text: root.gaugeDef.textNumDigits

            // background: Rectangle {
            //     border.width: parent.activeFocus ? 2 : 1
            //     color: parent.palette.base
            //     border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
            // }

            onEditingFinished: function() {
                if (parseInt(numDecimalsVal.text) > 0) {
                    incrementVal.text = 1 / Math.pow(10, parseInt(numDecimalsVal.text));
                    root.gaugeDef.textNumDigits = parseInt(numDecimalsVal.text);
                }
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }

            property bool isValid: !enabled || (acceptableInput && length > 0)
        }
    }

    Row {
        x: 10
        anchors.top: botRow.bottom
        spacing: 10

        Text {
            text: "Type"

            visible: root.gaugeType == SwitchingGaugeType.ENGINE_TEMP || root.isSecondaryTemp

            anchors.verticalCenter: typeBox.verticalCenter

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground
        }

        ComboBox {
            id: typeBox

            visible: root.gaugeType == SwitchingGaugeType.ENGINE_TEMP || root.isSecondaryTemp

            width: 105
            model: AircraftDefinition.type === AircraftType.PROP ? [ { text: "CHT", value: TemperatureGaugeType.CHT }, { text: "EGT", value: TemperatureGaugeType.EGT } ] : [ { text: "ITT", value: TemperatureGaugeType.ITT }, { text: "EGT", value: TemperatureGaugeType.EGT }, { text: "TIT", value: TemperatureGaugeType.TIT } ]

            textRole: "text"
            valueRole: "value"

            font.pointSize: 11

            currentIndex: 0


            Component.onCompleted: function() {
                if (root.gaugeType == SwitchingGaugeType.ENGINE_TEMP)
                    currentIndex = indexOfValue(AircraftDefinition.engineTempType);
                else if (root.isSecondaryTemp)
                    currentIndex = indexOfValue(AircraftDefinition.secondaryTempType);
            }

            Connections {
                enabled: root.gaugeType === SwitchingGaugeType.ENGINE_TEMP
                target: AircraftDefinition
                function onEngineTempTypeChanged() {
                    currentIndex = indexOfValue(AircraftDefinition.engineTempType);
                }
            }

            Connections {
                enabled: root.isSecondaryTemp
                target: AircraftDefinition
                function onSecondaryTempTypeChanged() {
                    currentIndex = indexOfValue(AircraftDefinition.secondaryTempType);
                }
            }

            onActivated: function(index) {
                if (root.gaugeType === SwitchingGaugeType.ENGINE_TEMP) {
                    AircraftDefinition.engineTempType = currentValue;
                }
                else if (root.isSecondaryTemp) {
                    AircraftDefinition.secondaryTempType = currentValue;
                }
            }
        }

        Text {
            text: "Max Power"

            visible: root.gaugeType == SwitchingGaugeType.POWER && unitBox.currentText === "Percent"

            anchors.verticalCenter: maxPowerValue.verticalCenter

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground

            leftPadding: 10
        }

        TextField {
            id: maxPowerValue

            visible: root.gaugeType == SwitchingGaugeType.POWER && unitBox.currentText === "Percent"

            width: 70

            font.pointSize: 11

            selectByMouse: true

            text: AircraftDefinition.maxPower

            validator: DoubleValidator{}

            onTextChanged: function() {
                if (maxPowerValue.acceptableInput) {
                    AircraftDefinition.maxPower = parseFloat(maxPowerValue.text);
                }
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }


        Text {
            text: "Max Torque"

            visible: root.gaugeType == SwitchingGaugeType.TORQUE && AircraftDefinition.type === AircraftType.PROP && unitBox.currentText === "Percent"

            anchors.verticalCenter: maxTorqueValue.verticalCenter

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground

            leftPadding: 10
        }

        TextField {
            id: maxTorqueValue

            visible: root.gaugeType === SwitchingGaugeType.TORQUE && AircraftDefinition.type === AircraftType.PROP && unitBox.currentText === "Percent"

            width: 70

            font.pointSize: 11

            selectByMouse: true

            text: AircraftDefinition.maxTorque

            validator: DoubleValidator{}

            onTextChanged: function() {
                if (maxTorqueValue.acceptableInput) {
                    AircraftDefinition.maxTorque = parseFloat(maxTorqueValue.text);
                }
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }
    }

    GridLayout {
        anchors.right: parent.right
        anchors.top: botRow.bottom

        columns: 3

        Text {
            Layout.fillWidth: true

            font.pointSize: 11
            font.family: "Roboto"

            color: Material.foreground

            text: "Low Red Blink"
        }

        CheckBox {
            id: lowEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: root.gaugeDef.hasMinRedBlink
        }

        TextField {
            id: lowThresholdField

            enabled: lowEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 80

            validator: DoubleValidator { }

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "Threshold"
            text: root.gaugeDef.minRedBlinkThreshold

            onTextChanged: function() {
                if (lowThresholdField.acceptableInput)
                {
                    root.gaugeDef.minRedBlinkThreshold = parseFloat(lowThresholdField.text);
                }
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }

        Text {
            Layout.fillWidth: true

            font.pointSize: 11
            font.family: "Roboto"

            color: Material.foreground

            text: "High Red Blink"
        }

        CheckBox {
            id: highEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: root.gaugeDef.hasMaxRedBlink
        }

        TextField {
            id: highThresholdField

            enabled: highEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 80

            validator: DoubleValidator { }

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            placeholderText: "Threshold"
            text: root.gaugeDef.maxRedBlinkThreshold

            onTextChanged: function() {
                if (highThresholdField.acceptableInput)
                {
                    root.gaugeDef.maxRedBlinkThreshold = parseFloat(highThresholdField.text);
                }
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }
    }



    Binding {
        target: root.gaugeDef
        property: "noText"
        value: noTextSwitch.checked
    }

    Binding {
        target: root.gaugeDef
        property: "hasMinRedBlink"
        value: lowEnabledBox.checked
    }

    Binding {
        target: root.gaugeDef
        property: "hasMaxRedBlink"
        value: highEnabledBox.checked
    }

}
