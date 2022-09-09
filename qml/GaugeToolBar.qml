import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml 2.15

import Definition 1.0

import "MyControls" as MyControls
import "PreviewPopup"
import "AircraftSelectionPopup"

Rectangle {
    id: root
    height: 20
    color: Qt.darker(Material.primary, 2)

    signal positionResetNeeded()

    property string lastKey: ""
    property bool openModeActive: false




    Row {
        anchors.fill: parent

        MyControls.ToolbarButton {
            id: newButton
            text: "New"
            tooltipText: "Create a new aircraft"

            onClicked: function() {
                AircraftManager.newAircraft();
            }
        }
        MyControls.ToolbarButton {
            id: openButton
            text: "Open"
            tooltipText: "Open an aircraft for editing"

            onClicked: function() {
                selectionPopup.aircraftSelected.connect(root.loadAircraft);
                selectionPopup.show();
            }
        }
        MyControls.ToolbarButton {
            id: copyButton
            text: "Copy"
            tooltipText: "Copy an aircraft and edit that copy"

            onClicked: function() {
                selectionPopup.aircraftSelected.connect(root.copyAircraft);
                selectionPopup.show();
            }
        }
        MyControls.ToolbarButton {
            id: saveButton
            text: AircraftDefinition.unsavedChanges || AircraftManager.unsavedThumbnail ? "Save*" : "Save"
            tooltipText: "Save the current aircraft"

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
        MyControls.ToolbarButton {
            id: deleteLocalButton
            text: "Delete"
            tooltipText: "Select an aircraft to delete"

            onClicked: function() {
                selectionPopup.aircraftSelected.connect(root.deleteAircraft);
                selectionPopup.show();
            }
        }
        MyControls.ToolbarButton {
            id: previewButton
            text: "Preview"
            tooltipText: "Create preview of the current gauge settings"

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
