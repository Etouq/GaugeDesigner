import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import "ColorZoneTable"
import "GradTable"
import "TextGradTable"
import "../StyledControls"

Item {
    id: root
    width: 630
    height: 450
    visible: true

    property string defaultTitle: ""
    property var unitTypes: [0] // 0: none, 1: percent, 2: rpm, 3: temperature, 4: pressure, 5: torque, 6: weight, 7: volume, 8: weight per hour, 9: volume per hour, 10: weight per minute, 11: volume per minute, 12: weight per second, 13: volume per second

    property real minVal: 0
    property real maxVal: 100

    property var gaugeObject: null

    property bool isValid: minValField.acceptableInput && minValField.length > 0 && maxValField.acceptableInput && maxValField.length > 0 && (!hasMinBlinkSwitch.checked || (minBlinkVal.acceptableInput && minBlinkVal.length > 0)) && (!hasMaxBlinkSwitch.checked || (maxBlinkVal.acceptableInput && maxBlinkVal.length > 0)) && (noTextSwitch.checked || (incrementVal.acceptableInput && numDecimalsVal.acceptableInput && incrementVal.length > 0 && numDecimalsVal.length > 0))

    onDefaultTitleChanged: titleText.text = defaultTitle

    signal changeMade()

    Connections {
        target: gaugeObject
        function onUpdateGauge() {
            titleText.text = gaugeObject.getTitle();
            titleText.ensureVisible(0);
            let unitInt = gaugeObject.getUnit();
            for (let i = 0; i < unitModel.count; i++) {
                if (unitModel.get(i).unitId === unitInt) {
                    unitBox.currentIndex = i;
                    unitBox.contentString = unitModel.get(i).longString
                }
            }
            unitText.text = gaugeObject.getUnitString();
            unitText.ensureVisible(0);
            minValField.text = gaugeObject.getMinValue();
            minValField.ensureVisible(0);
            maxValField.text = gaugeObject.getMaxValue();
            maxValField.ensureVisible(0);

            colorInputTable.updateModel(gaugeObject);
            gradInputTable.updateModel(gaugeObject);
            textGradInputTable.updateModel(gaugeObject);

            incrementVal.text = gaugeObject.getTextIncrement();
            incrementVal.ensureVisible(0);
            numDecimalsVal.text = gaugeObject.getTextNumDigits();
            numDecimalsVal.ensureVisible(0);

            forceTextColorSwitch.checked = gaugeObject.getForceTextColor();
            textForcedColorRect.color = gaugeObject.getTextForcedColor();

            hasMinBlinkSwitch.checked = gaugeObject.getHasMinRedBlink();
            minBlinkVal.text = gaugeObject.getMinRedBlinkThreshold();
            minBlinkVal.ensureVisible(0);
            hasMaxBlinkSwitch.checked = gaugeObject.getHasMaxRedBlink();
            maxBlinkVal.text = gaugeObject.getMaxRedBlinkThreshold();
            maxBlinkVal.ensureVisible(0);

            noTextSwitch.checked = gaugeObject.getNoText();
        }
    }

    onMaxValChanged: {
        gradInputTable.maxValue = maxVal;
        textGradInputTable.maxValue = maxVal;
    }

    Component.onCompleted: {
        unitModel.clear();
        let hasSections = unitTypes.length > 1;

        for (let i = 0; i < unitTypes.length; i++) {
            let units = converter.getAllowedUnits(unitTypes[i]);
            let sectHeader = hasSections ? converter.getSectionHeader(unitTypes[i]) : "";

            for (let j = 0; j < units.length; j++)
                unitModel.append({ "longString": converter.convertToLongString(units[j]), "unitId": units[j], "shortString": converter.convertToShortString(units[j]), "sect": sectHeader });
        }

        let unitList = converter.getAllowedUnits(unitTypes[0]);
        unitBox.currentIndex = 0;
        unitBox.contentString = converter.convertToLongString(unitList[0]);
        unitText.text = converter.convertToShortString(unitList[0]);
    }

    onUnitTypesChanged: {
        unitModel.clear();
        let hasSections = unitTypes.length > 1;

        for (let i = 0; i < unitTypes.length; i++) {
            let units = converter.getAllowedUnits(unitTypes[i]);
            let sectHeader = hasSections ? converter.getSectionHeader(unitTypes[i]) : "";

            for (let j = 0; j < units.length; j++)
                unitModel.append({ "longString": converter.convertToLongString(units[j]), "unitId": units[j], "shortString": converter.convertToShortString(units[j]), "sect": sectHeader });
        }

        let unitList = converter.getAllowedUnits(unitTypes[0]);
        unitBox.currentIndex = 0;
        unitBox.contentString = converter.convertToLongString(unitList[0]);
        unitText.text = converter.convertToShortString(unitList[0]);
    }

    function saveData() {
        gaugeObject.setTitleAndUnit(titleText.text, unitModel.get(unitBox.currentIndex).unitId, unitText.text);
        gaugeObject.setRange(minVal, maxVal);
        colorInputTable.saveData(gaugeObject);
        gradInputTable.saveData(gaugeObject);
        textGradInputTable.saveData(gaugeObject);
        gaugeObject.setTextIncrement(noTextSwitch.checked ? 1 : parseFloat(incrementVal.text), noTextSwitch.checked ? 0 : parseInt(numDecimalsVal.text));
        gaugeObject.setForceTextColor(forceTextColorSwitch.checked, textForcedColorRect.color.toString());
        gaugeObject.setMinBlink(hasMinBlinkSwitch.checked, hasMinBlinkSwitch.checked ? parseFloat(minBlinkVal.text) : 0);
        gaugeObject.setMaxBlink(hasMaxBlinkSwitch.checked, hasMaxBlinkSwitch.checked ? parseFloat(maxBlinkVal.text) : 0);
        gaugeObject.setNoText(noTextSwitch.checked);
        gaugeObject.updateComplete();
    }


    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        modality: Qt.WindowModal
        onAccepted: {
            textForcedColorRect.color = colorDialog.color;
            root.changeMade();
        }
        Component.onCompleted: color = "#FFFFFF"
    }




    Row {
        id: vectorInputs
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        ColorZoneTable {
            id: colorInputTable
            anchors.bottom: parent.bottom
            onChangeMade: root.changeMade();
        }
        Rectangle {
            width: 2
            color: "black"
            anchors.top: gradInputTable.top
            anchors.bottom: parent.bottom
        }
        GradTable {
            id: gradInputTable
            anchors.bottom: parent.bottom
            onChangeMade: root.changeMade();
        }
        Rectangle {
            width: 2
            color: "black"
            anchors.top: gradInputTable.top
            anchors.bottom: parent.bottom
        }
        TextGradTable {
            id: textGradInputTable
            anchors.bottom: parent.bottom
            onChangeMade: root.changeMade();
        }
    }

    TextField {
        id: minValField
        x: 80
        y: 12
        width: 70
        height: 25
        text: "0.0"
        selectByMouse: true
        validator: DoubleValidator{ top: maxVal }
        leftPadding: 5
        font.pixelSize: 11
        onTextChanged: {
            if (acceptableInput)
            {
                minVal = parseFloat(text);
                root.changeMade();
            }
        }
    }

    TextField {
        id: maxValField
        x: 231
        y: 12
        width: 70
        height: 25
        text: "100.0"
        selectByMouse: true
        validator: DoubleValidator{ bottom: minVal }
        leftPadding: 5
        font.pixelSize: 11
        onTextChanged: {
            if (acceptableInput)
            {
                maxVal = parseFloat(text);
            }
        }
        onTextEdited: root.changeMade();
    }


    TextField {
        id: titleText
        x: 14
        y: 60
        width: 100
        height: 25
        leftPadding: 5
        padding: 2
        bottomPadding: 2
        topPadding: 2
        font.pixelSize: 11
        selectByMouse: true
        onTextEdited: root.changeMade();
    }

    Text {
        y: 24
        text: "Title"
        anchors.left: titleText.left
        anchors.bottom: titleText.top
        font.pixelSize: 12
        anchors.bottomMargin: 3
        anchors.leftMargin: 5
    }

    TextField {
        id: unitText
        x: 240
        y: 30
        width: 70
        height: 25
        anchors.verticalCenter: titleText.verticalCenter
        topPadding: 2
        bottomPadding: 2
        padding: 2
        leftPadding: 5
        font.pixelSize: 11
        selectByMouse: true
        onTextEdited: root.changeMade();
    }

    Text {
        y: 35
        text: "Unit (text)"
        anchors.left: unitText.left
        anchors.bottom: unitText.top
        font.pixelSize: 12
        anchors.leftMargin: 5
        anchors.bottomMargin: 3
    }

    ListModel {
        id: unitModel
    }


    StyledComboBox {
        id: unitBox
        x: 120
        y: 30
        width: 105
        anchors.verticalCenter: titleText.verticalCenter
        model: unitModel
        onActivated: {
            unitText.text = unitModel.get(index).shortString
            unitBox.contentString = unitModel.get(index).longString
        }
        onCurrentIndexChanged: root.changeMade();
    }

    Text {
        y: 24
        text: "Unit"
        anchors.left: unitBox.left
        anchors.bottom: unitBox.top
        font.pixelSize: 12
        anchors.leftMargin: 5
        anchors.bottomMargin: 3
    }

    TextField {
        id: incrementVal
        x: 335
        y: 30
        width: 70
        height: 25
        text: "0.0"
        anchors.verticalCenter: titleText.verticalCenter
        selectByMouse: true
        validator: DoubleValidator{}
        leftPadding: 5
        font.pixelSize: 11
        enabled: !noTextSwitch.checked
        onTextEdited: root.changeMade();
    }

    TextField {
        id: numDecimalsVal
        x: 430
        y: 30
        width: 70
        height: 25
        text: "0"
        anchors.verticalCenter: titleText.verticalCenter
        validator: IntValidator{ bottom: 0; top: 5 }
        leftPadding: 5
        selectByMouse: true
        font.pixelSize: 11
        enabled: !noTextSwitch.checked
        onTextEdited: root.changeMade();
    }

    Text {
        text: "No Text"
        anchors.verticalCenter: numDecimalsVal.verticalCenter
        anchors.right: noTextSwitch.left
        font.pixelSize: 12
        anchors.rightMargin: 15
    }

    StyledSwitch {
        id: noTextSwitch
        width: 42
        anchors.verticalCenter: numDecimalsVal.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 15
        onCheckedChanged: root.changeMade();
    }

    Text {
        x: 346
        y: 24
        text: "Text Increment"
        anchors.bottom: incrementVal.top
        font.pixelSize: 12
        anchors.horizontalCenter: incrementVal.horizontalCenter
        anchors.bottomMargin: 3
        color: noTextSwitch.checked ? "#bdbebf" : "black"
    }

    Text {
        x: 458
        y: 24
        text: "Num Decimals"
        anchors.bottom: numDecimalsVal.top
        font.pixelSize: 12
        anchors.horizontalCenter: numDecimalsVal.horizontalCenter
        anchors.bottomMargin: 3
        color: noTextSwitch.checked ? "#bdbebf" : "black"
    }

    Column {
        x: 0
        y: 126
        width: 230
        height: 144
        anchors.bottom: vectorInputs.bottom
        anchors.bottomMargin: colorInputTable.height
        spacing: 5

        Item {
            width: 230
            height: 21

            Text {
                text: "Has Low Red Blink"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 15
            }

            StyledSwitch {
                id: hasMinBlinkSwitch
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 15
                onCheckedChanged: root.changeMade();
            }
        }

        Item {
            width: 230
            height: 25

            Text {
                visible: hasMinBlinkSwitch.checked
                text: "Low Threshold"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 15
            }

            TextField {
                id: minBlinkVal
                width: 70
                height: 25
                visible: hasMinBlinkSwitch.checked
                validator: DoubleValidator{}
                text: "0.0"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                rightPadding: 2
                bottomPadding: 2
                topPadding: 2
                leftPadding: 5
                anchors.rightMargin: 15
                selectByMouse: true
                onTextEdited: root.changeMade();
            }
        }

        Item {
            width: 230
            height: 21

            Text {
                text: "Has High Red Blink"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 15
            }

            StyledSwitch {
                id: hasMaxBlinkSwitch
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 15
                onCheckedChanged: root.changeMade();
            }
        }

        Item {
            width: 230
            height: 25

            Text {
                visible: hasMaxBlinkSwitch.checked
                text: "High Threshold"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 15
            }

            TextField {
                id: maxBlinkVal
                width: 70
                height: 25
                visible: hasMaxBlinkSwitch.checked
                validator: DoubleValidator{}
                text: "0.0"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                rightPadding: 2
                bottomPadding: 2
                topPadding: 2
                leftPadding: 5
                anchors.rightMargin: 15
                font.pixelSize: 11
                selectByMouse: true
                onTextEdited: root.changeMade();
            }
        }

        Item {
            width: 230
            height: 21
            enabled: !noTextSwitch.checked
            visible: !noTextSwitch.checked




            StyledSwitch {
                id: forceTextColorSwitch
                //x: 553
                //y: 84
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: textForcedColorRect.left
                anchors.rightMargin: 5
                onCheckedChanged: root.changeMade();
            }

            Text {
                x: 251
                y: 172
                text: "Force Text Color"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 15
            }

            Rectangle {
                id: textForcedColorRect
                width: 25
                height: 25
                visible: forceTextColorSwitch.checked
                color: "#ffffff"
                border.color: "black"
                border.width: 1
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 15
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: colorDialog.open()
                }
            }
        }

    }

    Text {
        text: "Minimum"
        anchors.verticalCenter: minValField.verticalCenter
        anchors.right: minValField.left
        font.pixelSize: 12
        anchors.rightMargin: 15
    }

    Text {
        text: "Maximum"
        anchors.verticalCenter: maxValField.verticalCenter
        anchors.right: maxValField.left
        font.pixelSize: 12
        anchors.rightMargin: 15
    }




}
