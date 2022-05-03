import QtQuick 2.15
import QtQuick.Controls 2.15
import "../StyledControls"

Column {
    width: 200
    height: childrenRect.height


    property int activeType: -1

    property bool unsavedChanges: lastFlapsChecked != hasFlapsSwitch.checked || (hasSpoilersSwitch.enabled && lastSpoilersChecked != hasSpoilersSwitch.checked) || lastElevTrimChecked != hasElevTrimSwitch.checked || lastRudderTrimChecked != hasRudderTrimSwitch.checked || lastAilTrimChecked != hasAilTrimSwitch.checked || lastNoColorsChecked != noColorsSwitch.checked || (dynamicBarberpoleSwitch.enabled && lastDynamicMaxChecked != dynamicBarberpoleSwitch.checked) || (egtReplacesIttSwitch.enabled && lastEgtReplacesIttChecked != egtReplacesIttSwitch.checked) || (hasApuSwitch.enabled && lastApuChecked != hasApuSwitch.checked) || (usePropRpmSwitch.enabled && lastPropRpmChecked != usePropRpmSwitch.checked) || (hasEgtSwitch.enabled && lastEgtChecked != hasEgtSwitch.checked) || (loadReplacesManSwitch.enabled && lastLoadReplacesManChecked != loadReplacesManSwitch.checked) || (maxHpField.enabled && lastMaxHpVal != maxHpField.text)

    property alias isValid: maxHpField.isValid
    property alias noColorsChecked: noColorsSwitch.checked
    property alias hasEgt: hasEgtSwitch.checked
    property alias loadReplacesMan: loadReplacesManSwitch.checked
    property alias egtReplacesItt: egtReplacesIttSwitch.checked


    // last saved state data
    property bool lastFlapsChecked: false
    property bool lastSpoilersChecked: false
    property bool lastElevTrimChecked: false
    property bool lastRudderTrimChecked: false
    property bool lastAilTrimChecked: false
    property bool lastNoColorsChecked: false
    property bool lastDynamicMaxChecked: false
    property bool lastEgtReplacesIttChecked: false
    property bool lastApuChecked: false
    property bool lastPropRpmChecked: false
    property bool lastEgtChecked: false
    property bool lastLoadReplacesManChecked: false
    property string lastMaxHpVal: ""


    function saveData() {
        aircraftInterface.setHasFlaps(hasFlapsSwitch.checked);
        aircraftInterface.setHasSpoilers(hasFlapsSwitch.checked && hasSpoilersSwitch.checked);

        aircraftInterface.setHasElevTrim(hasElevTrimSwitch.checked);
        aircraftInterface.setHasRudderTrim(hasRudderTrimSwitch.checked);
        aircraftInterface.setHasAileronTrim(hasAilTrimSwitch.checked);

        aircraftInterface.setNoColors(noColorsSwitch.checked);

        if (!noColorsSwitch.checked)
            aircraftInterface.setDynamicBarberpole(dynamicBarberpoleSwitch.checked);

        if (activeType == 0) {
            aircraftInterface.setEgtReplacesItt(egtReplacesIttSwitch.checked);
            aircraftInterface.setHasApu(hasApuSwitch.checked);
        }
        else if (activeType == 1) {
            aircraftInterface.setUsePropRpm(usePropRpmSwitch.checked);
            aircraftInterface.setHasEgt(hasEgtSwitch.checked);
            aircraftInterface.setSecondIsLoad(loadReplacesManSwitch.checked);
            if (loadReplacesManSwitch.checked)
                aircraftInterface.setMaxHp(parseFloat(maxHpField.text));
        }
        else {
            aircraftInterface.setUsePropRpm(usePropRpmSwitch.checked);
            aircraftInterface.setHasEgt(hasEgtSwitch.checked);
        }


        lastFlapsChecked = hasFlapsSwitch.checked;
        lastSpoilersChecked = hasSpoilersSwitch.checked;
        lastElevTrimChecked = hasElevTrimSwitch.checked;
        lastRudderTrimChecked = hasRudderTrimSwitch.checked;
        lastAilTrimChecked = hasAilTrimSwitch.checked;
        lastNoColorsChecked = noColorsSwitch.checked;
        lastDynamicMaxChecked = dynamicBarberpoleSwitch.checked;
        lastEgtReplacesIttChecked = egtReplacesIttSwitch.checked;
        lastApuChecked = hasApuSwitch.checked;
        lastPropRpmChecked = usePropRpmSwitch.checked;
        lastEgtChecked = hasEgtSwitch.checked;
        lastLoadReplacesManChecked = loadReplacesManSwitch.checked;
        lastMaxHpVal = maxHpField.text;

    }

    function updateData() {
        hasFlapsSwitch.checked = aircraftInterface.getHasFlaps();
        hasSpoilersSwitch.checked = aircraftInterface.getHasSpoilers();

        hasElevTrimSwitch.checked = aircraftInterface.getHasElevTrim();
        hasRudderTrimSwitch.checked = aircraftInterface.getHasRudderTrim();
        hasAilTrimSwitch.checked = aircraftInterface.getHasAileronTrim();

        noColorsSwitch.checked = aircraftInterface.getNoColors();
        dynamicBarberpoleSwitch.checked = aircraftInterface.getDynamicBarberpole();

        let type = aircraftInterface.getType();
        if (type === 0) {
            egtReplacesIttSwitch.checked = aircraftInterface.getEgtReplacesItt();
            hasApuSwitch.checked = aircraftInterface.getHasApu();
        }
        else if (type === 1) {
            loadReplacesManSwitch.checked = aircraftInterface.getSecondIsLoad();
            usePropRpmSwitch.checked = aircraftInterface.getUsePropRpm();
            hasEgtSwitch.checked = aircraftInterface.getHasEgt();
            maxHpField.text = aircraftInterface.getMaxHp();
            maxHpField.ensureVisible(0);
        }
        else {
            usePropRpmSwitch.checked = aircraftInterface.getUsePropRpm();
            hasEgtSwitch.checked = aircraftInterface.getHasEgt();
        }

        lastFlapsChecked = hasFlapsSwitch.checked;
        lastSpoilersChecked = hasSpoilersSwitch.checked;
        lastElevTrimChecked = hasElevTrimSwitch.checked;
        lastRudderTrimChecked = hasRudderTrimSwitch.checked;
        lastAilTrimChecked = hasAilTrimSwitch.checked;
        lastNoColorsChecked = noColorsSwitch.checked;
        lastDynamicMaxChecked = dynamicBarberpoleSwitch.checked;
        lastEgtReplacesIttChecked = egtReplacesIttSwitch.checked;
        lastApuChecked = hasApuSwitch.checked;
        lastPropRpmChecked = usePropRpmSwitch.checked;
        lastEgtChecked = hasEgtSwitch.checked;
        lastLoadReplacesManChecked = loadReplacesManSwitch.checked;
        lastMaxHpVal = maxHpField.text;
    }



    StyledSwitchWithText {
        id: hasFlapsSwitch
        height: 30
        text: "Has Flaps"
        anchors.left: parent.left
        anchors.right: parent.right
        checked: true
        rightMargin: 5
        leftMargin: 5
        anchors.rightMargin: 0
        anchors.leftMargin: 0
    }

    StyledSwitchWithText {
        id: hasSpoilersSwitch
        height: 30
        text: "Has Spoilers"
        anchors.left: parent.left
        anchors.right: parent.right
        rightMargin: 5
        leftMargin: 5
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        showItem: hasFlapsSwitch.checked
    }

    Item {
        height: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.leftMargin: 0
    }

    StyledSwitchWithText {
        id: hasElevTrimSwitch
        height: 30
        text: "Has Elevator Trim"
        anchors.left: parent.left
        anchors.right: parent.right
        checked: true
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        rightMargin: 5
        leftMargin: 5
    }

    StyledSwitchWithText {
        id: hasRudderTrimSwitch
        height: 30
        text: "Has Rudder Trim"
        anchors.left: parent.left
        anchors.right: parent.right
        checked: true
        rightMargin: 5
        leftMargin: 5
        anchors.rightMargin: 0
        anchors.leftMargin: 0
    }

    StyledSwitchWithText {
        id: hasAilTrimSwitch
        height: 30
        text: "Has Aileron Trim"
        anchors.left: parent.left
        anchors.right: parent.right
        checked: true
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        rightMargin: 5
        leftMargin: 5
    }

    Item {
        height: 10
        anchors.left: parent.left
        anchors.right: parent.right
    }

    StyledSwitchWithText {
        id: noColorsSwitch
        height: 30
        text: "No Airspeed Colors"
        anchors.left: parent.left
        anchors.right: parent.right
        rightMargin: 5
        leftMargin: 5
    }

    StyledSwitchWithText {
        id: dynamicBarberpoleSwitch
        height: 30
        text: "Dynamic (upper) Barberpole"
        anchors.left: parent.left
        anchors.right: parent.right
        rightMargin: 5
        leftMargin: 5
        visible: !noColorsSwitch.checked
    }

    Item {
        height: 10
        anchors.left: parent.left
        anchors.right: parent.right
    }

    StyledSwitchWithText {
        id: egtReplacesIttSwitch
        height: 30
        text: "EGT instead of ITT"
        anchors.left: parent.left
        anchors.right: parent.right
        rightMargin: 5
        leftMargin: 5
        visible: activeType == 0
    }

    StyledSwitchWithText {
        id: hasApuSwitch
        height: 30
        text: "Has APU"
        anchors.left: parent.left
        anchors.right: parent.right
        rightMargin: 5
        leftMargin: 5
        visible: activeType == 0
    }

    StyledSwitchWithText {
        id: usePropRpmSwitch
        height: 30
        text: "Use Propeller RPM"
        anchors.left: parent.left
        anchors.right: parent.right
        checked: true
        rightMargin: 5
        leftMargin: 5
        visible: activeType != 0
    }

    StyledSwitchWithText {
        id: hasEgtSwitch
        height: 30
        text: "Has EGT"
        anchors.left: parent.left
        anchors.right: parent.right
        rightMargin: 5
        leftMargin: 5
        visible: activeType != 0
    }

    StyledSwitchWithText {
        id: loadReplacesManSwitch
        height: 30
        text: "Load Instead of Manifold"
        anchors.left: parent.left
        anchors.right: parent.right
        rightMargin: 5
        leftMargin: 5
        visible: activeType == 1
    }

    Item {
        height: 30
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        visible: activeType == 1 && loadReplacesManSwitch.checked

        Text {
            text: "Max Horsepower"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            font.pixelSize: 12
        }

        TextField {
            id: maxHpField
            width: 70
            height: 25
            text: "1.0"
            validator: DoubleValidator { bottom: 1 }
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            padding: 2
            leftPadding: 5
            selectByMouse: true

            property bool isValid: !enabled || (acceptableInput && length > 0)

            background: Rectangle {
                border.width: parent.activeFocus ? 2 : 1
                color: parent.palette.base
                border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
            }
        }
    }

}

