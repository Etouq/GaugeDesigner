import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml 2.15
import "StyledControls"
import "Dialogs"
import "PreviewPopup"

Rectangle {
    id: root
    height: 20
    color: "#0085cb"



    Connections {
        target: aircraftInterface
        function onImageChanged() { unsavedImageChange = true; }
    }

    property bool unsavedChanges: false
    property bool unsavedImageChange: false

    property bool connected: false
    property bool everythingValid: false

    signal saveDataClicked()
    signal positionResetNeeded()

    property string lastKey: ""
    property bool openModeActive: false

    SingleSelectionDialog {
        id: openDialog
        infoText: "Please select an aircraft to edit"
        onAccepted: function() {
            positionResetNeeded();
            openModeActive = true;
            lastKey = selectedItem;
            aircraftManager.loadAircraft(selectedItem);
            unsavedImageChange = false;
        }
    }

    SingleSelectionDialog {
        id: copyDialog
        infoText: "Please select an aircraft to copy"
        onAccepted: function() {
            openModeActive = true;
            positionResetNeeded();
            lastKey = selectedItem + " (Copy)";
            aircraftManager.copyAircraft(selectedItem);
            unsavedImageChange = false;
        }
    }

    MultiSelectionDialog {
        id: deleteLocalDialog
        useLocalFiles: true
        infoText: "Please make a selection of aircraft to delete from local storage"
        onAccepted: function() {
            positionResetNeeded();
            for (let i = 0; i < selection.length; i++) {
                aircraftManager.removeAircraft(selection[i]);
                if(selection[i] === aircraftInterface.getName()) {
                    aircraftInterface.newAircraft();
                    unsavedImageChange = false;
                }
            }
        }
    }

    MultiSelectionDialog {
        id: deleteClientDialog
        useLocalFiles: false
        infoText: "Please make a selection of aircraft to delete from the client"
        onAccepted: function() {
            netInterface.removeClientAircraft(selection);
        }
    }

    MultiSelectionDialog {
        id: loadDialog
        useLocalFiles: false
        infoText: "Please make a selection of aircraft to load (and save) from the client"
        onAccepted: function() {
            netInterface.loadClientAircraft(selection);
        }
    }

    MultiSelectionDialog {
        id: sendDialog
        useLocalFiles: true
        infoText: "Please make a selection of aircraft to send to the client"
        onAccepted: function() {
            aircraftManager.sendAircraft(selection);
        }
    }

    PreviewPopup {
        id: previewWindow
    }


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
                root.openModeActive = false;
                root.positionResetNeeded();
                aircraftInterface.newAircraft();
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
                openDialog.open();
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
                copyDialog.open();
            }
        }
        StyledToolBarButton {
            id: saveButton
            text: unsavedChanges || unsavedImageChange ? "Save*" : "Save"
            enabled: everythingValid
            ToolTip {
                text: "Save the current aircraft (only saves edits locally)"
                visible: parent.hovered
                delay: 500
            }
            onClicked: function() {
                root.saveDataClicked();
                unsavedImageChange = false;
            }

            Shortcut {
                sequence: StandardKey.Save
                onActivated: function() {
                    root.saveDataClicked();
                    unsavedImageChange = false;
                }
            }
        }
        StyledToolBarButton {
            id: deleteLocalButton
            text: "Delete Local"
            ToolTip {
                text: "Delete aircraft from local storage"
                visible: parent.hovered
                delay: 500
            }
            onClicked: function() {
                deleteLocalDialog.open();
            }
        }
        StyledToolBarButton {
            id: deleteClientButton
            text: "Delete from Client"
            enabled: netInterface.connected
            ToolTip {
                text: "Delete aircraft from client storage"
                visible: parent.hovered
                delay: 500
            }
            onClicked: function() {
                deleteClientDialog.open();
            }
        }
        StyledToolBarButton {
            id: loadButton
            text: "Load"
            enabled: netInterface.connected
            ToolTip {
                text: "Load (and save) aircraft from the client"
                visible: parent.hovered
                delay: 500
            }
            onClicked: function() {
                loadDialog.open();
            }
        }
        StyledToolBarButton {
            id: sendButton
            text: "Send"
            enabled: netInterface.connected
            ToolTip {
                text: "Send aircraft to the client (use this to send saved edits to the client)"
                visible: parent.hovered
                delay: 500
            }
            onClicked: function() {
                sendDialog.open();
            }
        }
        StyledToolBarButton {
            id: previewButton
            text: "Preview"
            enabled: everythingValid
            ToolTip {
                text: "Create preview of the current gauge settings (also saves)"
                visible: parent.hovered
                delay: 500
            }
            onClicked: function() {
                root.saveDataClicked();
                unsavedImageChange = false;
                if (!previewWindow.visible)
                    previewWindow.show();
                else
                    previewWindow.raise();
                previewWindow.requestActivate();
                aircraftInterface.createPreview();
            }

        }
    }


}
