import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "StyledControls"

Item {
    id: root
    width: 630
    height: 450

    property int activeType: jetRadio.checked ? 0 : propRadio.checked ? 1 : 2
    property bool egtReplacesItt: egtReplacesIttSwitch.checked
    property bool loadReplacesMan: loadReplacesManSwitch.checked
    property bool hasEgt: hasEgtSwitch.checked
    property int numEngines: oneEngRadio.checked ? 1 : twinEngRadio.checked ? 2 : 4
    property int numTanks: oneTankRadio.checked ? 1 : 2
    property string name: nameField.text

    signal changeMade()

    onActiveTypeChanged: {
        root.changeMade();
        if (numEngines == 4)
            twinEngRadio.checked = true;
    }

    onNumEnginesChanged: root.changeMade();

    onNumTanksChanged: root.changeMade();

    property bool validColors: lowLimitField.acceptableInput && flapsStart.acceptableInput && flapsEnd.acceptableInput && greenStart.acceptableInput && greenEnd.acceptableInput && yellowStart.acceptableInput && yellowEnd.acceptableInput && redStart.acceptableInput && redEnd.acceptableInput && highLimitField.acceptableInput && lowLimitField.length > 0 && flapsStart.length > 0 && flapsEnd.length > 0 && greenStart.length > 0 && greenEnd.length > 0 && yellowStart.length > 0 && yellowEnd.length > 0 && redStart.length > 0 && redEnd.length > 0 && highLimitField.length > 0

    property bool allInputsValid: nameField.text != "" && (noColorsSwitch.checked || validColors) && (!propRadio.checked || !loadReplacesMan || (maxHpField.acceptableInput && maxHpField.length > 0))

    Connections {
        target: aircraftInterface
        function onUpdateQml() {
            let type = aircraftInterface.getType();
            if (type === 0)
                jetRadio.checked = true;
            else if (type === 1)
                propRadio.checked = true;
            else
                turbopropRadio.checked = true;

            let engineCount = aircraftInterface.getNumEngines();
            if (engineCount === 1)
                oneEngRadio.checked = true;
            else if (engineCount === 2)
                twinEngRadio.checked = true;
            else
                quadEngRadio.checked = true;

            let tankCount = aircraftInterface.getNumTanks();
            if (tankCount === 1)
                oneTankRadio.checked = true;
            else
                twinTankRadio.checked = true;

            nameField.text = aircraftInterface.getName();
            nameField.background.border.color = nameField.text == "" ? "red" : "#bdbdbd";
            nameField.ensureVisible(0);

            hasFlapsSwitch.checked = aircraftInterface.getHasFlaps();
            hasSpoilersSwitch.checked = aircraftInterface.getHasSpoilers();

            hasElevTrimSwitch.checked = aircraftInterface.getHasElevTrim();
            hasRudderTrimSwitch.checked = aircraftInterface.getHasRudderTrim();
            hasAilTrimSwitch.checked = aircraftInterface.getHasAileronTrim();

            noColorsSwitch.checked = aircraftInterface.getNoColors();
            dynamicBarberpoleSwitch.checked = aircraftInterface.getDynamicBarberpole();

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

            lowLimitField.text = aircraftInterface.getLowLimit();
            flapsStart.text = aircraftInterface.getFlapsBegin();
            flapsEnd.text = aircraftInterface.getFlapsEnd();
            greenStart.text = aircraftInterface.getGreenBegin();
            greenEnd.text = aircraftInterface.getGreenEnd();
            yellowStart.text = aircraftInterface.getYellowBegin();
            yellowEnd.text = aircraftInterface.getYellowEnd();
            redStart.text = aircraftInterface.getRedBegin();
            redEnd.text = aircraftInterface.getRedEnd();
            highLimitField.text = aircraftInterface.getHighLimit();

            lowLimitField.ensureVisible(0);
            flapsStart.ensureVisible(0);
            flapsEnd.ensureVisible(0);
            greenStart.ensureVisible(0);
            greenEnd.ensureVisible(0);
            yellowStart.ensureVisible(0);
            yellowEnd.ensureVisible(0);
            redStart.ensureVisible(0);
            redEnd.ensureVisible(0);
            highLimitField.ensureVisible(0);

            selectedImg.source = "file:" + aircraftInterface.getImagePath();
        }
    }

    Connections {
        target: aircraftInterface
        function onUpdateImage() {
            selectedImg.source = "file:" + aircraftInterface.getImagePath();
        }
    }

    function saveData()
    {
        aircraftInterface.setType(activeType);
        aircraftInterface.setName(nameField.text);
        aircraftInterface.setHasFlaps(hasFlapsSwitch.checked);
        aircraftInterface.setHasSpoilers(hasFlapsSwitch.checked && hasSpoilersSwitch.checked);
        aircraftInterface.setHasElevTrim(hasElevTrimSwitch.checked);
        aircraftInterface.setHasRudderTrim(hasRudderTrimSwitch.checked);
        aircraftInterface.setHasAileronTrim(hasAilTrimSwitch.checked);
        aircraftInterface.setNumEngines(numEngines);
        aircraftInterface.setNumTanks(numTanks);

        aircraftInterface.setNoColors(noColorsSwitch.checked);
        if (!noColorsSwitch.checked)
        {
            aircraftInterface.setLowLimit(parseFloat(lowLimitField.text));
            aircraftInterface.setFlapsBegin(parseFloat(flapsStart.text));
            aircraftInterface.setFlapsEnd(parseFloat(flapsEnd.text));
            aircraftInterface.setGreenBegin(parseFloat(greenStart.text));
            aircraftInterface.setGreenEnd(parseFloat(greenEnd.text));
            aircraftInterface.setYellowBegin(parseFloat(yellowStart.text));
            aircraftInterface.setYellowEnd(parseFloat(yellowEnd.text));
            aircraftInterface.setRedBegin(parseFloat(redStart.text));
            aircraftInterface.setRedEnd(parseFloat(redEnd.text));
            aircraftInterface.setHighLimit(parseFloat(highLimitField.text));
            aircraftInterface.setDynamicBarberpole(dynamicBarberpoleSwitch.checked);
        }

        if (activeType == 0) {
            aircraftInterface.setHasApu(hasApuSwitch.checked);
            aircraftInterface.setEgtReplacesItt(egtReplacesItt);
        }
        else if (activeType == 1) {
            aircraftInterface.setHasEgt(hasEgt);
            aircraftInterface.setUsePropRpm(usePropRpmSwitch.checked);
            aircraftInterface.setSecondIsLoad(loadReplacesMan);
            if (loadReplacesMan)
                aircraftInterface.setMaxHp(parseFloat(maxHpField.text));
        }
        else {
            aircraftInterface.setHasEgt(hasEgt);
            aircraftInterface.setUsePropRpm(usePropRpmSwitch.checked);
        }


    }

    Column {
        id: boxColumn
        y: 200

        anchors.right: column.left
        anchors.rightMargin: 20
        topPadding: 0
        leftPadding: 0
        rightPadding: 0
        bottomPadding: 0
        spacing: 25

        GroupBox {
            id: typeBox
            title: "Aircraft Type"
            topPadding: 5
            leftPadding: 5
            rightPadding: 5
            bottomPadding: 5



            label: Label {
                x: parent.leftPadding
                text: parent.title
                anchors.bottomMargin: 4
            }

            Component.onCompleted: label.anchors.bottom = background.top

            ButtonGroup {
                buttons: [ jetRadio.button, propRadio.button, turbopropRadio.button ]
            }

            Column {
                anchors.fill: parent
                spacing: 5

                StyledRadioButtonWithText {
                    id: jetRadio
                    height: 25
                    width: 95
                    text: "Jet"
                    rightMargin: 5
                    leftMargin: 5
                    checked: true
                }

                StyledRadioButtonWithText {
                    id: propRadio
                    height: 25
                    width: 95
                    text: "Prop"
                    rightMargin: 5
                    leftMargin: 5
                    checked: false
                }

                StyledRadioButtonWithText {
                    id: turbopropRadio
                    height: 25
                    width: 95
                    text: "Turboprop"
                    rightMargin: 5
                    leftMargin: 5
                }
            }
        }

        GroupBox {
            id: numTanksGroup
            title: "Number of Tanks"
            topPadding: 5
            leftPadding: 5
            rightPadding: 5
            bottomPadding: 5

            label: Label {
                x: parent.leftPadding
                text: parent.title
                anchors.bottomMargin: 4
            }

            Component.onCompleted: label.anchors.bottom = background.top




            ButtonGroup {
                buttons: [ oneTankRadio.button, twinTankRadio.button ]
            }

            Row {
                anchors.fill: parent
                spacing: 5

                StyledRadioButtonWithText {
                    id: oneTankRadio
                    height: 20
                    width: 45
                    //Layout.fillWidth: true
                    text: "1"
                    rightMargin: 5
                    leftMargin: 5
                }

                StyledRadioButtonWithText {
                    id: twinTankRadio
                    height: 20
                    width: 45
                    //Layout.fillWidth: true
                    text: "2"
                    rightMargin: 5
                    leftMargin: 5
                    checked: true
                }
            }
        }

        GroupBox {
            id: numEnginesGroup
            title: "Number of Engines"
            topPadding: 5
            leftPadding: 5
            rightPadding: 5
            bottomPadding: 5

            label: Label {
                x: parent.leftPadding
                text: parent.title
                anchors.bottomMargin: 4
            }

            Component.onCompleted: label.anchors.bottom = background.top

            ButtonGroup {
                buttons: [ oneEngRadio.button, twinEngRadio.button, quadEngRadio.button ]
            }

            Grid {
                anchors.fill: parent
                spacing: 5
                columns: 2

                StyledRadioButtonWithText {
                    id: oneEngRadio
                    height: 20
                    width: 45
                    text: "1"
                    rightMargin: 5
                    leftMargin: 5
                    checked: true
                }

                StyledRadioButtonWithText {
                    id: twinEngRadio
                    height: 20
                    width: 45
                    text: "2"
                    rightMargin: 5
                    leftMargin: 5
                }

                StyledRadioButtonWithText {
                    id: quadEngRadio
                    height: 20
                    width: 45
                    text: "4"
                    rightMargin: 5
                    leftMargin: 5
                    visible: activeType == 0
                }
            }
        }

    }

    Text {
        id: nameText
        text: "Name"
        anchors.left: selectedImg.left
        anchors.leftMargin: 2
        anchors.bottom: selectedImgText.top
        anchors.bottomMargin: 10
        font.pixelSize: 12
    }

    TextField {
        id: nameField
        anchors.verticalCenter: nameText.verticalCenter
        anchors.left: nameText.right
        anchors.leftMargin: 10
        width: 150
        height: 25
        padding: 2
        leftPadding: 5
        rightPadding: 5
        selectByMouse: true
        maximumLength: 64

        Component.onCompleted: {
            background.border.color = "red";
        }

        onEditingFinished: {
            background.border.color = nameField.text == "" ? "red" : "#bdbdbd";
        }

        onTextEdited: root.changeMade();

    }

    Text {
        anchors.left: nameField.right
        anchors.leftMargin: 20
        anchors.verticalCenter: nameField.verticalCenter
        font.pixelSize: 12
        font.family: "Roboto"
        visible: netInterface.address !== "" && netInterface.port > 0
        text: "Running on Address: " + netInterface.address + " And Port: " + netInterface.port
    }


    Text {
        id: selectedImgText
        text: "Image (click to edit)"
        font.pixelSize: 12
        anchors.bottom: selectedImg.top
        anchors.bottomMargin: 5
        anchors.left: selectedImg.left
        anchors.leftMargin: 2
    }

    Image {
        id: selectedImg
        anchors.left: parent.left
        anchors.leftMargin: 15
        y: 60
        width: 300
        height: 108
        source: "qrc:/DefaultImage.png"
        cache: false
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                aircraftInterface.selectImage();
            }
        }
    }

    Column {
        id: column
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 40
        width: 200
        height: childrenRect.height

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
            onCheckedChanged: root.changeMade();
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
            onCheckedChanged: root.changeMade();
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
            onCheckedChanged: root.changeMade();
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
            onCheckedChanged: root.changeMade();
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
            onCheckedChanged: root.changeMade();
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
            onCheckedChanged: root.changeMade();
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
            onCheckedChanged: root.changeMade();
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
            onCheckedChanged: root.changeMade();
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
            onCheckedChanged: root.changeMade();
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
            onCheckedChanged: root.changeMade();
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
            onCheckedChanged: root.changeMade();
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
            onCheckedChanged: root.changeMade();
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
                onTextEdited: root.changeMade();
            }
        }

    }

    GroupBox {
        width: 250
        enabled: !noColorsSwitch.checked
        title: "Airspeed Colors"
        topPadding: 5
        leftPadding: 5
        rightPadding: 5
        bottomPadding: 5
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.top: boxColumn.top
        //anchors.bottom: parent.bottom
        //anchors.bottomMargin: 20

        label: Label {
            x: parent.leftPadding
            text: parent.title
            anchors.bottomMargin: 4
        }

        Component.onCompleted: label.anchors.bottom = background.top

        Column {
            anchors.fill: parent

            Item {
                height: 25
                anchors.left: parent.left
                anchors.right: parent.right

                Text {
                    text: "Start"
                    font.pixelSize: 12
                    height: 25
                    width: 70
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.right: colorEndText.left
                    anchors.rightMargin: 5
                }

                Text {
                    id: colorEndText
                    text: "End"
                    font.pixelSize: 12
                    height: 25
                    width: 70
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.right: parent.right
                }
            }

            Item {
                height: 30
                anchors.left: parent.left
                anchors.right: parent.right

                Text {
                    text: "Lower Barberpole"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    font.pixelSize: 12
                    color: enabled ? "black" : "#bdbebf"
                }

                TextField {
                    id: lowLimitField
                    width: 70
                    height: 25
                    text: "0.0"
                    validator: DoubleValidator { bottom: 0 }
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    padding: 2
                    leftPadding: 5
                    selectByMouse: true
                    onTextEdited: root.changeMade();
                }
            }



            Item {
                height: 30
                anchors.left: parent.left
                anchors.right: parent.right

                Text {
                    text: "Flaps (white)"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    font.pixelSize: 12
                    color: enabled ? "black" : "#bdbebf"
                }

                TextField {
                    id: flapsStart
                    width: 70
                    height: 25
                    text: "0.0"
                    validator: DoubleValidator { bottom: 0 }
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: flapsEnd.left
                    anchors.rightMargin: 5
                    padding: 2
                    leftPadding: 5
                    selectByMouse: true
                    onTextEdited: root.changeMade();
                }

                TextField {
                    id: flapsEnd
                    width: 70
                    height: 25
                    text: "0.0"
                    validator: DoubleValidator { bottom: 0 }
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    padding: 2
                    leftPadding: 5
                    selectByMouse: true
                    onTextEdited: root.changeMade();
                }
            }

            Item {
                height: 30
                anchors.left: parent.left
                anchors.right: parent.right

                Text {
                    text: "Green"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    font.pixelSize: 12
                    color: enabled ? "black" : "#bdbebf"
                }

                TextField {
                    id: greenStart
                    width: 70
                    height: 25
                    text: "0.0"
                    validator: DoubleValidator { bottom: 0 }
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: greenEnd.left
                    anchors.rightMargin: 5
                    padding: 2
                    leftPadding: 5
                    selectByMouse: true
                    onTextEdited: root.changeMade();
                }

                TextField {
                    id: greenEnd
                    width: 70
                    height: 25
                    text: "0.0"
                    validator: DoubleValidator { bottom: 0 }
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    padding: 2
                    leftPadding: 5
                    selectByMouse: true
                    onTextEdited: root.changeMade();
                }
            }

            Item {
                height: 30
                anchors.left: parent.left
                anchors.right: parent.right

                Text {
                    text: "Yellow"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    font.pixelSize: 12
                    color: enabled ? "black" : "#bdbebf"
                }

                TextField {
                    id: yellowStart
                    width: 70
                    height: 25
                    text: "0.0"
                    validator: DoubleValidator { bottom: 0 }
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: yellowEnd.left
                    anchors.rightMargin: 5
                    padding: 2
                    leftPadding: 5
                    selectByMouse: true
                    onTextEdited: root.changeMade();
                }

                TextField {
                    id: yellowEnd
                    width: 70
                    height: 25
                    text: "0.0"
                    validator: DoubleValidator { bottom: 0 }
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    padding: 2
                    leftPadding: 5
                    selectByMouse: true
                    onTextEdited: root.changeMade();
                }
            }

            Item {
                height: 30
                anchors.left: parent.left
                anchors.right: parent.right

                Text {
                    text: "Red"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    font.pixelSize: 12
                    color: enabled ? "black" : "#bdbebf"
                }

                TextField {
                    id: redStart
                    width: 70
                    height: 25
                    text: "0.0"
                    validator: DoubleValidator { bottom: 0 }
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: redEnd.left
                    anchors.rightMargin: 5
                    padding: 2
                    leftPadding: 5
                    selectByMouse: true
                    onTextEdited: root.changeMade();
                }

                TextField {
                    id: redEnd
                    width: 70
                    height: 25
                    text: "0.0"
                    validator: DoubleValidator { bottom: 0 }
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    padding: 2
                    leftPadding: 5
                    selectByMouse: true
                    onTextEdited: root.changeMade();
                }
            }

            Item {
                height: 30
                anchors.left: parent.left
                anchors.right: parent.right

                Text {
                    text: "Upper Barberpole"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    font.pixelSize: 12
                    color: enabled ? "black" : "#bdbebf"
                }

                TextField {
                    id: highLimitField
                    width: 70
                    height: 25
                    text: "0.0"
                    validator: DoubleValidator { bottom: 0 }
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 75
                    padding: 2
                    leftPadding: 5
                    selectByMouse: true
                    onTextEdited: root.changeMade();
                }
            }
        }
    }

}
