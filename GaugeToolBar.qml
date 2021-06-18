import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3
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
        function onUpdateComplete() { saveButton.text = "Save"; }
    }

    Connections {
        target: aircraftInterface
        function onImageChanged() { saveButton.text = "Save*"; }
    }

    function unsavedChangesMade() {
        saveButton.text = "Save*";
    }

    property bool connected: false
    property bool everythingValid: false

    signal saveDataClicked()
    signal positionResetNeeded()

    property string lastKey: ""
    property bool openModeActive: false

    SingleSelectionDialog {
        id: openDialog
        infoText: "Please select an aircraft to edit"
        onAccepted: {
            positionResetNeeded();
            openModeActive = true;
            lastKey = selectedItem;
            aircraftManager.loadAircraft(selectedItem);
            saveButton.text = "Save"
        }
    }

    SingleSelectionDialog {
        id: copyDialog
        infoText: "Please select an aircraft to copy"
        onAccepted: {
            openModeActive = true;
            positionResetNeeded();
            lastKey = selectedItem + " (Copy)";
            aircraftManager.copyAircraft(selectedItem);
            saveButton.text = "Save"
        }
    }

    MultiSelectionDialog {
        id: deleteLocalDialog
        useLocalFiles: true
        infoText: "Please make a selection of aircraft to delete from local storage"
        onAccepted: {
            positionResetNeeded();
            for (let i = 0; i < selection.length; i++) {
                aircraftManager.removeAircraft(selection[i]);
                if(selection[i] === aircraftInterface.getName()) {
                    aircraftInterface.newAircraft();
                    saveButton.text = "Save"
                }
            }
        }
    }

    MultiSelectionDialog {
        id: deleteClientDialog
        useLocalFiles: false
        infoText: "Please make a selection of aircraft to delete from the client"
        onAccepted: {
            netInterface.removeClientAircraft(selection);
        }
    }

    MultiSelectionDialog {
        id: loadDialog
        useLocalFiles: false
        infoText: "Please make a selection of aircraft to load (and save) from the client"
        onAccepted: {
            netInterface.loadClientAircraft(selection);
        }
    }

    MultiSelectionDialog {
        id: sendDialog
        useLocalFiles: true
        infoText: "Please make a selection of aircraft to send to the client"
        onAccepted: {
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
            onClicked: {
                root.openModeActive = false;
                root.positionResetNeeded();
                aircraftInterface.newAircraft();
                saveButton.text = "Save"
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
            onClicked: {
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
            onClicked: {
                copyDialog.open();
            }
        }
        StyledToolBarButton {
            id: saveButton
            text: "Save"
            enabled: everythingValid
            ToolTip {
                text: "Save the current aircraft (only saves edits locally)"
                visible: parent.hovered
                delay: 500
            }
            onClicked: {
                root.saveDataClicked();
                saveButton.text = "Save"
            }

            Shortcut {
                sequence: StandardKey.Save
                onActivated: {
                    root.saveDataClicked();
                    saveButton.text = "Save"
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
            onClicked: {
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
            onClicked: {
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
            onClicked: {
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
            onClicked: {
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
            onClicked: {
                root.saveDataClicked();
                saveButton.text = "Save"
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
