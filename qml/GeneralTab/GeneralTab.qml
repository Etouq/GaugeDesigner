import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Definition 1.0
import TypeEnums 1.0

import "../StyledControls"

Item {
    id: root

    TextField {
        id: nameField
        width: 260

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 15
        anchors.topMargin: 10

        placeholderText: "Name"
        text: AircraftDefinition.name
    }

    // Connections {
    //     target: aircraftInterface
    //     function onUpdateImage() {
    //         selectedImg.source = "file:" + aircraftInterface.getImagePath();
    //     }
    // }




    Text {
        id: selectedImgText
        color: Material.foreground
        text: "Image (click to edit)"
        anchors.topMargin: 15
        anchors.left: selectedImg.left
        anchors.top: parent.top
        font.family: "Roboto"
        font.pointSize: 11
        anchors.leftMargin: 2
    }

    Image {
        id: selectedImg
        anchors.top: selectedImgText.bottom
        width: 300
        height: 108
        anchors.right: parent.right
        source: "qrc:/DefaultImage.png"
        anchors.rightMargin: 15
        anchors.topMargin: 5
        cache: false

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: aircraftInterface.selectImage();
        }
    }


    AirspeedColors {
        id: airspeedColors
        y: 201
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.top: groupBoxColumn.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
    }

    CheckBoxColumn {
        id: checkBoxes
        x: 417
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.top: airspeedColors.top
        anchors.topMargin: 0
    }

    ComboBox {
        id: typeBox
        x: 495
        anchors.right: nameField.right
        anchors.top: nameField.bottom
        font.pointSize: 11
        anchors.rightMargin: 0
        anchors.topMargin: 10
        model: ["Jet", "Propeller", "Turboprop"]
        currentIndex: 0

        onActivated: function (index) {
            if (index === 0) {
                AircraftDefinition.type = AircraftType.JET;
            } else if (index === 1) {
                AircraftDefinition.type = AircraftType.PROP;
            } else if (index === 2) {
                AircraftDefinition.type = AircraftType.TURBOPROP;
            }
            else {
                console.log("invalid type");
                AircraftDefinition.type = AircraftType.INVALID;
            }
        }
    }

    ComboBox {
        id: numEngineBox

        anchors.top: typeBox.bottom
        anchors.right: nameField.right
        anchors.topMargin: 10
        anchors.rightMargin: 0

        font.pointSize: 11

        model: [1, 2, 4]
        currentIndex: 0

        onActivated: function (index) {
            if (index === 0) {
                AircraftDefinition.numEngines = 1;
            } else if (index === 1) {
                AircraftDefinition.numEngines = 2;
            } else if (index === 2) {
                AircraftDefinition.numEngines = 4;
            }
        }
    }

    Text {
        color: Material.foreground
        text: "Aircraft Type"
        anchors.verticalCenter: typeBox.verticalCenter
        anchors.left: parent.left
        verticalAlignment: Text.AlignVCenter
        anchors.leftMargin: 15
        Layout.fillHeight: false
        Layout.topMargin: 10
        font.pointSize: 11
        font.family: "Roboto"
        Layout.fillWidth: true
        textFormat: Text.PlainText
    }

    Text {
        id: numEngineText
        color: Material.foreground
        text: "Number of Engines"
        anchors.verticalCenter: numEngineBox.verticalCenter
        anchors.left: parent.left
        verticalAlignment: Text.AlignVCenter
        anchors.leftMargin: 15
        anchors.verticalCenterOffset: 0
        Layout.fillHeight: false
        Layout.topMargin: 10
        font.pointSize: 11
        font.family: "Roboto"
        Layout.fillWidth: true
        textFormat: Text.PlainText
    }


    Binding {
        target: AircraftDefinition
        property: "name"
        value: nameField.text
    }

    Component.onCompleted: function() {
        switch (AircraftDefinition.type) {
            case AircraftType.JET:
                typeBox.currentIndex = 0;
                break;
            case AircraftType.PROP:
                typeBox.currentIndex = 1;
                break;
            case AircraftType.TURBOPROP:
                typeBox.currentIndex = 2;
                break;
            default:
                typeBox.currentIndex = 0;
                break;
        }
        switch (AircraftDefinition.numEngines) {
            case 1:
                numEngineBox.currentIndex = 0;
                break;
            case 2:
                numEngineBox.currentIndex = 1;
                break;
            case 4:
                numEngineBox.currentIndex = 2;
                break;
            default:
                numEngineBox.currentIndex = 0;
                break;
        }
    }

    Connections {
        target: AircraftDefinition
        function onTypeChanged() {
            switch (AircraftDefinition.type) {
                case AircraftType.JET:
                    typeBox.currentIndex = 0;
                    break;
                case AircraftType.PROP:
                    typeBox.currentIndex = 1;
                    break;
                case AircraftType.TURBOPROP:
                    typeBox.currentIndex = 2;
                    break;
                default:
                    typeBox.currentIndex = 0;
                    break;
            }
        }
    }

    Connections {
        target: AircraftDefinition
        function onNumEnginesChanged() {
            switch (AircraftDefinition.numEngines) {
                case 1:
                    numEngineBox.currentIndex = 0;
                    break;
                case 2:
                    numEngineBox.currentIndex = 1;
                    break;
                case 4:
                    numEngineBox.currentIndex = 2;
                    break;
                default:
                    numEngineBox.currentIndex = 0;
                    break;
            }
        }
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:5}D{i:12}
}
##^##*/
