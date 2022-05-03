import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../StyledControls"

Item {
    id: root
    width: 630
    height: 450

    property alias activeType: groupBoxColumn.activeType
    property alias egtReplacesItt: switchColumn.egtReplacesItt
    property alias loadReplacesMan: switchColumn.loadReplacesMan
    property alias hasEgt: switchColumn.hasEgt
    property alias numEngines: groupBoxColumn.numEngines
    property alias numTanks: groupBoxColumn.numTanks
    property alias name: nameField.text


    property bool unsavedChanges: lastNameText != nameField.text || airspeedColors.unsavedChanges || groupBoxColumn.unsavedChanges || switchColumn.unsavedChanges
    property bool isValid: nameField.acceptableInput && nameField.length > 0 && airspeedColors.isValid && switchColumn.isValid


    property string lastNameText: ""

    Connections {
        target: aircraftInterface
        function onUpdateQml() {
            updateData();
        }
    }

    Connections {
        target: aircraftInterface
        function onUpdateImage() {
            selectedImg.source = "file:" + aircraftInterface.getImagePath();
        }
    }

    function saveData() {
        groupBoxColumn.saveData();
        aircraftInterface.setName(nameField.text);

        if (!switchColumn.noColorsChecked)
            airspeedColors.saveData();

        switchColumn.saveData();

        lastNameText = nameField.text;

    }

    function updateData() {
        groupBoxColumn.updateData();

        airspeedColors.updateData();

        nameField.text = aircraftInterface.getName();
        nameField.ensureVisible(0);

        switchColumn.updateData();

        selectedImg.source = "file:" + aircraftInterface.getImagePath();

        lastNameText = nameField.text;
    }


    Text {
        id: nameText
        text: "Name"
        anchors.left: selectedImgText.left
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

        background: Rectangle {
            border.width: parent.activeFocus ? 2 : 1
            color: parent.palette.base
            border.color: parent.activeFocus ? parent.palette.highlight : parent.acceptableInput && parent.length > 0 ? parent.palette.mid : "red"
        }


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
            onClicked: aircraftInterface.selectImage();
        }
    }


    AirspeedColors {
        id: airspeedColors
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.top: groupBoxColumn.top
        enabled: !switchColumn.noColorsChecked
    }


    GroupBoxColumn {
        id: groupBoxColumn
        y: 200

        anchors.right: switchColumn.left
        anchors.rightMargin: 20
    }



    SwitchColumn {
        id: switchColumn
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 40

        activeType: groupBoxColumn.activeType
    }



}
