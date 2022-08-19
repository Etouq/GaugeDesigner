import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml 2.15

import Definition 1.0

import "StyledControls"
import "Dialogs"
import "PreviewPopup"
import "AircraftSelectionPopup"

Rectangle {
    id: root
    height: 20
    color: Qt.darker(Material.primary, 2)//"#0085cb"



    // Connections {
    //     target: aircraftInterface
    //     function onImageChanged() { unsavedImageChange = true; }
    // }


    signal saveDataClicked()
    signal positionResetNeeded()

    property string lastKey: ""
    property bool openModeActive: false




    Row {
        anchors.fill: parent

        StyledToolBarButton {
            id: newButton
            text: "New"
            ToolTip {
                text: "Create a new aircraft"
                visible: parent.hovered
                delay: 500
            }
            onClicked: function() {
                AircraftManager.newAircraft();
            }
        }
        StyledToolBarButton {
            id: openButton
            text: "Open"

            ToolTip {
                text: "Open an aircraft for editing"
                visible: parent.hovered
                delay: 500
            }

            onClicked: function() {
                selectionPopup.aircraftSelected.connect(root.loadAircraft);
                selectionPopup.show();
            }
        }
        StyledToolBarButton {
            id: copyButton
            text: "Copy"
            ToolTip {
                text: "Copy an aircraft and edit that copy"
                visible: parent.hovered
                delay: 500
            }
            onClicked: function() {
                selectionPopup.aircraftSelected.connect(root.copyAircraft);
                selectionPopup.show();
            }
        }
        StyledToolBarButton {
            id: saveButton
            text: AircraftDefinition.unsavedChanges || AircraftManager.unsavedThumbnail ? "Save*" : "Save"
            ToolTip {
                text: "Save the current aircraft"
                visible: parent.hovered
                delay: 500
            }
            onClicked: function() {
                AircraftManager.saveCurrentDefinition();
            }

            Shortcut {
                sequence: StandardKey.Save
                onActivated: function() {
                    AircraftManager.saveCurrentDefinition();
                }
            }
        }
        StyledToolBarButton {
            id: deleteLocalButton
            text: "Delete"
            ToolTip {
                text: "Select an aircraft to delete"
                visible: parent.hovered
                delay: 500
            }
            onClicked: function() {
                selectionPopup.aircraftSelected.connect(root.deleteAircraft);
                selectionPopup.show();
            }
        }
        StyledToolBarButton {
            id: previewButton
            text: "Preview"
            ToolTip {
                text: "Create preview of the current gauge settings (also saves)"
                visible: parent.hovered
                delay: 500
            }
            onClicked: function() {
                AircraftManager.previewCurrentDefinition();
                previewWindow.show();
            }

        }
    }

    AircraftSelectionPopup {
        id: selectionPopup
    }

    PreviewPopup {
        id: previewWindow
    }

    function loadAircraft(key) {
        selectionPopup.aircraftSelected.disconnect(root.loadAircraft);
        selectionPopup.close();
        AircraftManager.selectAircraft(key);
    }

    function copyAircraft(key) {
        selectionPopup.aircraftSelected.disconnect(root.copyAircraft);
        selectionPopup.close();
        AircraftManager.copyAircraft(key);
    }

    function deleteAircraft(key) {
        selectionPopup.aircraftSelected.disconnect(root.deleteAircraft);
        selectionPopup.close();
        AircraftManager.deleteAircraft(key);
    }


}
