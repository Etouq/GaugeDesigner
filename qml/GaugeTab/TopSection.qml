import QtQuick 2.15
import QtQuick.Controls 2.15
import "../StyledControls"

Item {
    id: root
    width: 630

    property string defaultTitle: ""
    property var unitTypes: [0] // 0: none, 1: percent, 2: rpm, 3: temperature, 4: pressure, 5: torque, 6: weight, 7: volume, 8: weight per hour, 9: volume per hour, 10: weight per minute, 11: volume per minute, 12: weight per second, 13: volume per second

    property real minVal: 0
    property real maxVal: 100

    property var gaugeObject: null

    property int selectedUnitId: -1

    property bool unsavedChanges: lastMinVal !== minValField.text || lastMaxVal !== maxValField.text || lastTitle !== titleText.text || lastUnitId != selectedUnitId || lastUnitText !== unitText.text || (!noTextSwitch.checked && (lastTextIncrement !== incrementVal.text || lastNumDecimals !== numDecimalsVal.text)) || lastNoTextChecked !== noTextSwitch.checked
    property bool isValid: minValField.isValid && maxValField.isValid && titleText.isValid && incrementVal.isValid && numDecimalsVal.isValid

    property alias noTextChecked: noTextSwitch.checked

    // last saved state data
    property string lastMinVal: ""
    property string lastMaxVal: ""
    property string lastTitle: ""
    property int lastUnitId: -1
    property string lastUnitText: ""
    property string lastTextIncrement: ""
    property string lastNumDecimals: ""
    property bool lastNoTextChecked: false

    function updateData() {
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

        incrementVal.text = gaugeObject.getTextIncrement();
        incrementVal.ensureVisible(0);
        numDecimalsVal.text = gaugeObject.getTextNumDigits();
        numDecimalsVal.ensureVisible(0);

        noTextSwitch.checked = gaugeObject.getNoText();

        selectedUnitId = unitModel.get(unitBox.currentIndex).unitId;

        lastMinVal = minValField.text;
        lastMaxVal = maxValField.text;
        lastTitle = titleText.text;
        lastUnitId = unitModel.get(unitBox.currentIndex).unitId;
        lastUnitText = unitText.text;

        lastTextIncrement = incrementVal.text;
        lastNumDecimals = numDecimalsVal.text;

        lastNoTextChecked = noTextSwitch.checked;
    }

    function saveData() {
        gaugeObject.setTitleAndUnit(titleText.text, unitModel.get(unitBox.currentIndex).unitId, unitText.text);
        gaugeObject.setRange(minVal, maxVal);

        if (!noTextSwitch.checked)
            gaugeObject.setTextIncrement(parseFloat(incrementVal.text), parseInt(numDecimalsVal.text));

        gaugeObject.setNoText(noTextSwitch.checked);

        lastMinVal = minValField.text;
        lastMaxVal = maxValField.text;
        lastTitle = titleText.text;
        lastUnitId = unitModel.get(unitBox.currentIndex).unitId;
        lastUnitText = unitText.text;

        if (!noTextSwitch.checked) {
            lastTextIncrement = incrementVal.text;
            lastNumDecimals = numDecimalsVal.text;
        }

        lastNoTextChecked = noTextSwitch.checked;
    }

    function updateUnitModel() {
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



    Component.onCompleted: updateUnitModel();
    onUnitTypesChanged: updateUnitModel();

    onDefaultTitleChanged: titleText.text = defaultTitle


    Text {
        text: "Minimum"
        anchors.verticalCenter: minValField.verticalCenter
        anchors.right: minValField.left
        font.pixelSize: 12
        anchors.rightMargin: 15
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

        background: Rectangle {
            border.width: parent.activeFocus ? 2 : 1
            color: parent.palette.base
            border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
        }

        onTextChanged: function() {
            if (acceptableInput)
            {
                minVal = parseFloat(text);
            }
        }

        property bool isValid: length > 0 && acceptableInput

    }

    Text {
        text: "Maximum"
        anchors.verticalCenter: maxValField.verticalCenter
        anchors.right: maxValField.left
        font.pixelSize: 12
        anchors.rightMargin: 15
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

        background: Rectangle {
            border.width: parent.activeFocus ? 2 : 1
            color: parent.palette.base
            border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
        }

        onTextChanged: function() {
            if (acceptableInput)
            {
                maxVal = parseFloat(text);
            }
        }

        property bool isValid: length > 0 && acceptableInput
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

        background: Rectangle {
            border.width: parent.activeFocus ? 2 : 1
            color: parent.palette.base
            border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
        }

        property bool isValid: length > 0
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

    StyledComboBox {
        id: unitBox
        x: 120
        y: 30
        width: 105
        anchors.verticalCenter: titleText.verticalCenter
        model: unitModel
        onActivated: function() {
            unitText.text = unitModel.get(index).shortString;
            unitBox.contentString = unitModel.get(index).longString;
            root.selectedUnitId = unitModel.get(unitBox.currentIndex).unitId;
        }
    }

    ListModel {
        id: unitModel
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

        background: Rectangle {
            border.width: parent.activeFocus ? 2 : 1
            color: parent.palette.base
            border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
        }

        property bool isValid: !enabled || (acceptableInput && length > 0)
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

        background: Rectangle {
            border.width: parent.activeFocus ? 2 : 1
            color: parent.palette.base
            border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
        }

        onEditingFinished: function() {
            if (parseInt(text) > 0) {
                incrementVal.text = 1 / Math.pow(10, parseInt(text));
            }
        }

        property bool isValid: !enabled || (acceptableInput && length > 0)
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
    }

}
