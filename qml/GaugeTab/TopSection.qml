import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

import Definition 1.0
import TypeEnums 1.0

import "../StyledControls"
import "../MyControls" as MyControls

ColumnLayout {
    id: root
    spacing: 0


    required property GaugeDefinition gaugeDef
    required property int gaugeType
    required property bool isSecondaryTemp

    RowLayout {
        spacing: 10

        Text {
            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground

            text: "Title"
        }

        TextField {
            id: titleText
            Layout.preferredWidth: 150

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            selectByMouse: true
            maximumLength: 64

            text: root.gaugeDef.title

            onTextEdited: function() {
                root.gaugeDef.title = titleText.text;
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Text {
            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground

            text: "Min"
        }

        TextField {
            id: minValField

            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            selectByMouse: true

            text: root.gaugeDef.minValue

            onEditingFinished: function() {
                if (minValField.text === "" || minValField.text === "-" || !minValField.acceptableInput) {
                    const minVal = root.gaugeDef.minValue;
                    root.gaugeDef.minValue = minVal;
                }
            }

            onTextEdited: function() {
                if (minValField.text === "" || minValField.text === "-")
                    return;

                const completeVal = Number(minValField.text);

                if (isNaN(completeVal)) {
                    console.log(minValField.text + " is not a number");
                    minValField.undo();
                    return;
                }
                if (completeVal > root.gaugeDef.maxValue) {
                    console.log(minValField.text + " is greater than max");
                    minValField.undo();
                    return;
                }

                root.gaugeDef.minValue = completeVal;
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Text {
            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground

            text: "Max"
        }

        TextField {
            id: maxValField

            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            selectByMouse: true

            text: root.gaugeDef.maxValue

            Component.onCompleted: function() {
                ensureVisible(0);
            }

            onEditingFinished: function() {
                if (maxValField.text === "" || maxValField.text === "-" || !maxValField.acceptableInput) {
                    const maxVal = root.gaugeDef.maxValue;
                    root.gaugeDef.maxValue = maxVal;
                }
            }

            onTextEdited: function() {
                if (maxValField.text === "" || maxValField.text === "-")
                    return;

                const completeVal = Number(maxValField.text);

                if (isNaN(completeVal)) {
                    console.log(maxValField.text + " is not a number");
                    maxValField.undo();
                    return;
                }
                if (completeVal > root.gaugeDef.minValue) {
                    console.log(maxValField.text + " is smaller than min");
                    maxValField.undo();
                    return;
                }

                root.gaugeDef.maxValue = completeVal;
            }
        }

        Item {
            Layout.fillWidth: true
        }


        Text {
            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground

            text: "No Text"
        }

        CheckBox {
            id: noTextSwitch

            spacing: 0
            bottomPadding: 8
            topPadding: 8

            font.pointSize: 11

            checked: root.gaugeDef.noText
        }
    }

    RowLayout {
        spacing: 10

        Text {
            text: "Unit"

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground
        }

        MyControls.UnitBox {
            id: unitBox

            Layout.preferredWidth: 150
            model: root.gaugeDef.unitModel

            textRole: "longText"
            valueRole: "unitId"

            font.pointSize: 11

            Component.onCompleted: function() {
                unitBox.currentIndex = unitBox.indexOfValue(root.gaugeDef.unit)
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

            Layout.preferredWidth: 70

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            selectByMouse: true
            maximumLength: 16

            text: root.gaugeDef.unitString

            onTextEdited: function() {
                root.gaugeDef.unitString = unitText.text;
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Text {
            font.family: "Roboto"
            font.pointSize: 11

            color: noTextSwitch.checked ? Material.hintTextColor : Material.foreground
            text: "Increment"
        }

        TextField {
            id: incrementVal

            enabled: !noTextSwitch.checked

            Layout.preferredWidth: 70

            leftPadding: 5
            rightPadding: 5

            validator: DoubleValidator{}
            selectByMouse: true
            font.pointSize: 11

            text: root.gaugeDef.textIncrement

            onEditingFinished: function() {
                if (incrementVal.text === "" || incrementVal.text === "-" || !incrementVal.acceptableInput) {
                    const val = root.gaugeDef.textIncrement;
                    root.gaugeDef.textIncrement = val;
                }
            }

            onTextEdited: function() {
                if (incrementVal.text === "" || incrementVal.text === "-")
                    return;

                const completeVal = Number(incrementVal.text);

                if (isNaN(completeVal)) {
                    console.log(incrementVal.text + " is not a number");
                    incrementVal.undo();
                    return;
                }
                if (completeVal < 0) {
                    console.log("incrementval cannot be negative");
                    incrementVal.undo();
                    return;
                }

                root.gaugeDef.textIncrement = completeVal;
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Text {
            font.family: "Roboto"
            font.pointSize: 11

            color: noTextSwitch.checked ? Material.hintTextColor : Material.foreground
            text: "Precision"
        }

        TextField {
            id: numDecimalsVal

            enabled: !noTextSwitch.checked

            Layout.preferredWidth: 70

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            validator: IntValidator { bottom: 0; top: 5 }
            selectByMouse: true

            text: root.gaugeDef.textNumDigits

            onTextEdited: function() {
                if (numDecimalsVal.text === "" || numDecimalsVal.text === "-")
                    return;

                const completeVal = Number(numDecimalsVal.text);

                if (isNaN(completeVal)) {
                    console.log(numDecimalsVal.text + " is not a number");
                    numDecimalsVal.undo();
                    return;
                }
                if (!Number.isInteger(completeVal)) {
                    console.log(numDecimalsVal.text + " is not an integer");
                    numDecimalsVal.undo();
                    return;
                }
                if (completeVal < 0) {
                    console.log("precision cannot be negative");
                    numDecimalsVal.undo();
                    return;
                }

                root.gaugeDef.textNumDigits = completeVal;
            }

            onEditingFinished: function() {
                if (numDecimalsVal.text === "" || numDecimalsVal.text === "-" || !numDecimalsVal.acceptableInput) {
                    const val = root.gaugeDef.textNumDigits;
                    root.gaugeDef.textNumDigits = val;
                }
                if (parseInt(numDecimalsVal.text) > 0) {
                    root.gaugeDef.textIncrement = 1 / Math.pow(10, parseInt(numDecimalsVal.text));
                    root.gaugeDef.textNumDigits = parseInt(numDecimalsVal.text);
                }
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }
    }

    RowLayout {
        spacing: 5

        Text {
            font.pointSize: 11
            font.family: "Roboto"

            color: Material.foreground

            text: "Low Red Blink"
        }

        CheckBox {
            id: lowEnabledBox

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: root.gaugeDef.hasMinRedBlink
        }

        TextField {
            id: lowThresholdField

            enabled: lowEnabledBox.checked

            Layout.preferredWidth: 80

            leftPadding: 5
            rightPadding: 5

            validator: DoubleValidator { }

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "Threshold"
            text: root.gaugeDef.minRedBlinkThreshold

            onEditingFinished: function() {
                if (lowThresholdField.text === "" || lowThresholdField.text === "-" || !lowThresholdField.acceptableInput) {
                    const val = root.gaugeDef.minRedBlinkThreshold;
                    root.gaugeDef.minRedBlinkThreshold = val;
                }
            }

            onTextEdited: function() {
                if (lowThresholdField.text === "" || lowThresholdField.text === "-")
                    return;

                const completeVal = Number(lowThresholdField.text);

                if (isNaN(completeVal)) {
                    console.log(lowThresholdField.text + " is not a number");
                    lowThresholdField.undo();
                    return;
                }

                root.gaugeDef.minRedBlinkThreshold = completeVal;
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Text {
            font.pointSize: 11
            font.family: "Roboto"

            color: Material.foreground

            text: "High Red Blink"
        }

        CheckBox {
            id: highEnabledBox

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: root.gaugeDef.hasMaxRedBlink
        }

        TextField {
            id: highThresholdField

            enabled: highEnabledBox.checked

            Layout.preferredWidth: 80

            leftPadding: 5
            rightPadding: 5

            validator: DoubleValidator { }

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "Threshold"
            text: root.gaugeDef.maxRedBlinkThreshold

            onEditingFinished: function() {
                if (highThresholdField.text === "" || highThresholdField.text === "-" || !highThresholdField.acceptableInput) {
                    const val = root.gaugeDef.maxRedBlinkThreshold;
                    root.gaugeDef.maxRedBlinkThreshold = val;
                }
            }

            onTextEdited: function() {
                if (highThresholdField.text === "" || highThresholdField.text === "-")
                    return;

                const completeVal = Number(highThresholdField.text);

                if (isNaN(completeVal)) {
                    console.log(highThresholdField.text + " is not a number");
                    highThresholdField.undo();
                    return;
                }

                root.gaugeDef.maxRedBlinkThreshold = completeVal;
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }


        Item {
            Layout.fillWidth: true
        }

        Text {
            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground

            text: "Force Text Color"
        }

        CheckBox {
            id: forceColorBox

            spacing: 0
            bottomPadding: 8
            topPadding: 8

            font.pointSize: 11

            checked: root.gaugeDef.forceTextColor
        }

        Rectangle {
            Layout.preferredWidth: 34
            Layout.preferredHeight: 34

            visible: root.gaugeDef.forceTextColor

            color: root.gaugeDef.textForcedColor

            border.width: 1
            border.color: "black"

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                acceptedButtons: Qt.LeftButton
                hoverEnabled: true

                onClicked: function(mouse) {
                    colorDialog.open();
                    mouse.accepted = true;
                }
            }

            ColorDialog {
                id: colorDialog
                title: "Please choose a color"
                modality: Qt.WindowModal
                onAccepted: function() {
                    root.gaugeDef.textForcedColor = colorDialog.color;
                }
                Component.onCompleted: color = "#FFFFFF"
            }
        }


    }

    RowLayout {
        spacing: 10

        Text {
            text: "Type"

            visible: root.gaugeType == SwitchingGaugeType.ENGINE_TEMP || root.isSecondaryTemp

            // anchors.verticalCenter: typeBox.verticalCenter

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
                    typeBox.currentIndex = typeBox.indexOfValue(AircraftDefinition.engineTempType);
                else if (root.isSecondaryTemp)
                    typeBox.currentIndex = typeBox.indexOfValue(AircraftDefinition.secondaryTempType);
            }

            Connections {
                enabled: root.gaugeType === SwitchingGaugeType.ENGINE_TEMP
                target: AircraftDefinition
                function onEngineTempTypeChanged() {
                    typeBox.currentIndex = typeBox.indexOfValue(AircraftDefinition.engineTempType);
                }
            }

            Connections {
                enabled: root.isSecondaryTemp
                target: AircraftDefinition
                function onSecondaryTempTypeChanged() {
                    typeBox.currentIndex = typeBox.indexOfValue(AircraftDefinition.secondaryTempType);
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

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground
        }

        TextField {
            id: maxPowerValue

            visible: root.gaugeType == SwitchingGaugeType.POWER && unitBox.currentText === "Percent"

            width: 70

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            selectByMouse: true

            text: AircraftDefinition.maxPower

            validator: DoubleValidator{}

            onEditingFinished: function() {
                if (maxPowerValue.text === "" || maxPowerValue.text === "-" || !maxPowerValue.acceptableInput) {
                    const val = AircraftDefinition.maxPower;
                    AircraftDefinition.maxPower = val;
                }
            }

            onTextEdited: function() {
                if (maxPowerValue.text === "" || maxPowerValue.text === "-")
                    return;

                const completeVal = Number(maxPowerValue.text);

                if (isNaN(completeVal)) {
                    console.log(maxPowerValue.text + " is not a number");
                    maxPowerValue.undo();
                    return;
                }
                if (completeVal < 0) {
                    console.log("power cannot be negative");
                    maxPowerValue.undo();
                    return;
                }

                AircraftDefinition.maxPower = completeVal;
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }

        Text {
            text: "hp (l)"

            Layout.leftMargin: -10

            visible: root.gaugeType == SwitchingGaugeType.POWER && unitBox.currentText === "Percent"

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground
        }


        Text {
            text: "Max Torque"

            visible: root.gaugeType == SwitchingGaugeType.TORQUE && AircraftDefinition.type === AircraftType.PROP && unitBox.currentText === "Percent"

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground
        }

        TextField {
            id: maxTorqueValue

            visible: root.gaugeType === SwitchingGaugeType.TORQUE && AircraftDefinition.type === AircraftType.PROP && unitBox.currentText === "Percent"

            width: 70

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            selectByMouse: true

            text: AircraftDefinition.maxTorque

            validator: DoubleValidator{}

            onEditingFinished: function() {
                if (maxTorqueValue.text === "" || maxTorqueValue.text === "-" || !maxTorqueValue.acceptableInput) {
                    const val = AircraftDefinition.maxTorque;
                    AircraftDefinition.maxTorque = val;
                }
            }

            onTextEdited: function() {
                if (maxTorqueValue.text === "" || maxTorqueValue.text === "-")
                    return;

                const completeVal = Number(maxTorqueValue.text);

                if (isNaN(completeVal)) {
                    console.log(maxTorqueValue.text + " is not a number");
                    maxTorqueValue.undo();
                    return;
                }
                if (completeVal < 0) {
                    console.log("torque cannot be negative");
                    maxTorqueValue.undo();
                    return;
                }

                AircraftDefinition.maxTorque = completeVal;
            }

            Component.onCompleted: function() {
                ensureVisible(0);
            }
        }

        Text {
            text: "N·M"

            Layout.leftMargin: -10

            visible: root.gaugeType == SwitchingGaugeType.TORQUE && AircraftDefinition.type === AircraftType.PROP && unitBox.currentText === "Percent"

            font.family: "Roboto"
            font.pointSize: 11

            color: Material.foreground
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

    Binding {
        target: root.gaugeDef
        property: "forceTextColor"
        value: forceColorBox.checked
    }

}
