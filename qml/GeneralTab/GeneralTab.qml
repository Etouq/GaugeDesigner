import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Dialogs 1.3

import Definition 1.0
import TypeEnums 1.0

ColumnLayout {
    id: root

    spacing: 5

    Layout.maximumWidth: Window.width

    RowLayout {
        id: topRow
        Layout.fillWidth: true
        Layout.topMargin: 10
        Layout.leftMargin: 10
        Layout.rightMargin: 10
        Layout.maximumWidth: Window.width - 20

        spacing: 0

        GridLayout {
            id: mainTypeInputs
            columns: 2
            columnSpacing: 10
            rowSpacing: 5

            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft

            TextField {
                id: nameField

                Layout.columnSpan: 2
                Layout.fillWidth: true

                font.family: "Roboto"
                font.pixelSize: 14

                maximumLength: 64

                leftPadding: 5
                rightPadding: 5

                placeholderText: "Name"
                text: AircraftDefinition.name
            }

            Text {
                Layout.fillWidth: true

                font.family: "Roboto"
                font.pixelSize: 14

                textFormat: Text.PlainText

                color: Material.foreground
                text: "Aircraft Type"
            }

            ComboBox {
                id: typeBox

                Layout.preferredWidth: 130
                Layout.fillWidth: true

                textRole: "text"
                valueRole: "value"

                font.pixelSize: 14

                currentIndex: 0

                model: [
                    { text: "Jet", value: AircraftType.JET },
                    { text: "Propeller", value: AircraftType.PROP },
                    { text: "Turboprop", value: AircraftType.TURBOPROP }
                ]

                onActivated: function() {
                    AircraftDefinition.type = typeBox.currentValue;
                }
            }

            Text {
                Layout.fillWidth: true

                font.family: "Roboto"
                font.pixelSize: 14

                textFormat: Text.PlainText

                color: Material.foreground
                text: "Number of Engines"
            }

            ComboBox {
                id: numEngineBox

                Layout.preferredWidth: 130
                Layout.fillWidth: true

                textRole: "text"
                valueRole: "value"

                font.pixelSize: 14

                currentIndex: 0

                model: [
                    { text: "1", value: 1 },
                    { text: "2", value: 2 },
                    { text: "4", value: 4 }
                ]

                onActivated: function() {
                    AircraftDefinition.numEngines = numEngineBox.currentValue;
                }
            }
        }

        Item {

            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.minimumWidth: 10
        }

        ColumnLayout {
            spacing: 5
            Layout.fillWidth: false
            Layout.fillHeight: false
            Layout.alignment: Qt.AlignTop | Qt.AlignRight

            Text {
                id: selectedImgText

                Layout.leftMargin: 2

                font.family: "Roboto"
                font.pixelSize: 14

                color: Material.foreground
                text: "Thumbnail (click to edit)"
            }

            Image {
                id: selectedImg

                Layout.preferredWidth: 300
                Layout.preferredHeight: 108
                // width: 300
                // height: 108

                fillMode: Image.PreserveAspectFit

                source: AircraftManager.currentThumbnailPath//"qrc:/DefaultImage.png"
                cache: false

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: imageDialog.open();
                }

                FileDialog {
                    id: imageDialog
                    title: "Please choose a thumbnail"
                    nameFilters: [ "Image files (*.jpg *.png *.jpeg)" ]
                    onAccepted: {
                        AircraftManager.selectImage(imageDialog.fileUrl.toString().replace(/^(file:\/{3})/,""));
                    }
                }
            }
        }
    }


    GaugePickers {
        id: gaugePickers

        Layout.fillWidth: true
        Layout.leftMargin: 10
        Layout.rightMargin: 10
    }


    RowLayout {
        id: bottomRow

        spacing: 0

        Layout.fillWidth: true

        Layout.leftMargin: 10
        Layout.rightMargin: 10
        Layout.bottomMargin: 10

        AirspeedColors {
            id: airspeedColors
            Layout.alignment: Qt.AlignBottom | Qt.AlignRight
        }

        Item {

            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.minimumWidth: 10
        }

        CheckBoxColumn {
            id: checkBoxes

            Layout.fillWidth: false
            Layout.alignment: Qt.AlignBottom | Qt.AlignRight
        }
    }


    Binding {
        target: AircraftDefinition
        property: "name"
        value: nameField.text
    }

    Component.onCompleted: function() {
        typeBox.currentIndex = Math.max(typeBox.indexOfValue(AircraftDefinition.type), 0);
        numEngineBox.currentIndex = Math.max(numEngineBox.indexOfValue(AircraftDefinition.numEngines), 0);
    }

    Connections {
        target: AircraftDefinition
        function onTypeChanged() {
            typeBox.currentIndex = Math.max(typeBox.indexOfValue(AircraftDefinition.type), 0);
        }
        function onNumEnginesChanged() {
            numEngineBox.currentIndex = Math.max(numEngineBox.indexOfValue(AircraftDefinition.numEngines), 0);
        }
    }

}
