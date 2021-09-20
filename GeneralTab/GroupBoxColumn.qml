import QtQuick 2.15
import QtQuick.Controls 2.15
import "../StyledControls"

Column {
    id: boxColumn

    topPadding: 0
    leftPadding: 0
    rightPadding: 0
    bottomPadding: 0
    spacing: 25


    property int activeType: jetRadio.checked ? 0 : propRadio.checked ? 1 : 2
    property int numEngines: oneEngRadio.checked ? 1 : twinEngRadio.checked ? 2 : 4
    property int numTanks: oneTankRadio.checked ? 1 : 2

    property bool unsavedChanges: lastActiveType != activeType || lastNumEngines != numEngines || lastNumTanks != numTanks

    onActiveTypeChanged: {
        if (numEngines == 4)
            twinEngRadio.checked = tru
    }

    // last saved state data
    property int lastActiveType: -1
    property int lastNumEngines: 0
    property int lastNumTanks: 0

    function saveData() {
        aircraftInterface.setType(activeType);
        aircraftInterface.setNumEngines(numEngines);
        aircraftInterface.setNumTanks(numTanks);

        lastActiveType = activeType;
        lastNumEngines = numEngines;
        lastNumTanks = numTanks;
    }

    function updateData() {
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

        lastActiveType = type;
        lastNumEngines = engineCount;
        lastNumTanks = tankCount;
    }


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
                text: "1"
                rightMargin: 5
                leftMargin: 5
            }

            StyledRadioButtonWithText {
                id: twinTankRadio
                height: 20
                width: 45
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
