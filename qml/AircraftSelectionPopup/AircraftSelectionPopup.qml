import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

import Definition 1.0

ApplicationWindow {
    id: aircraftPopupRoot

    width: 800
    height: 500

    title: "Select Aircraft"
    flags: Qt.Dialog
    modality: Qt.ApplicationModal

    signal aircraftSelected(key: string)

    Loader {
        active: aircraftPopupRoot.visible
        anchors.fill: parent
        asynchronous: true
        sourceComponent: ScrollView {

            anchors {
                top: parent.top
                right: parent.right
                bottom: parent.bottom
                left: parent.left

                margins: 20
            }

            contentWidth: availableWidth
            contentHeight: thumbColumn.height

            clip: true

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

            Column {
                id: thumbColumn
                anchors.left: parent.left
                anchors.right: parent.right

                spacing: 8

                // n_min = ⌈(width + spacing) / (maxWidth + spacing)⌉
                // n_max = ⌊(width + spacing) / (minWidth + spacing)⌋
                readonly property int thumbnailColumnCount: Math.max(1, Math.floor((thumbColumn.width + 10) / (300 + 10)))

                AircraftGroupHeader {
                    id: jetHeader

                    anchors.left: parent.left
                    anchors.right: parent.right

                    text: "Jet"

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        onClicked: function() {
                            jetLayout.expanded = !jetLayout.expanded
                        }
                    }
                }

                AircraftGroupLayout {
                    id: jetLayout

                    anchors.left: parent.left
                    anchors.right: parent.right

                    columns: thumbColumn.thumbnailColumnCount
                    collapseToggle: jetHeader.collapseToggle

                    Repeater {
                        model: AircraftManager.getNumJets()

                        AircraftSelectionItem {
                            required property int index

                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Layout.minimumHeight: minHeight
                            Layout.minimumWidth: 300

                            key: AircraftManager.getJetKey(index)

                            onAircraftSelected: function(key) {
                                aircraftPopupRoot.aircraftSelected(key);
                            }
                        }
                    }
                }

                AircraftGroupHeader {
                    id: turbopropHeader

                    anchors.left: parent.left
                    anchors.right: parent.right

                    text: "Turboprop"

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        onClicked: function() {
                            turbopropLayout.expanded = !turbopropLayout.expanded
                        }
                    }
                }

                AircraftGroupLayout {
                    id: turbopropLayout

                    anchors.left: parent.left
                    anchors.right: parent.right

                    columns: thumbColumn.thumbnailColumnCount
                    collapseToggle: turbopropHeader.collapseToggle

                    Repeater {
                        model: AircraftManager.getNumTurboprop()

                        AircraftSelectionItem {
                            required property int index

                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Layout.minimumHeight: minHeight
                            Layout.minimumWidth: 300

                            key: AircraftManager.getTurbopropKey(index)

                            onAircraftSelected: function(key) {
                                aircraftPopupRoot.aircraftSelected(key);
                            }
                        }
                    }
                }

                AircraftGroupHeader {
                    id: propHeader

                    anchors.left: parent.left
                    anchors.right: parent.right

                    text: "Propeller"

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        onClicked: function() {
                            propLayout.expanded = !propLayout.expanded
                        }
                    }
                }

                AircraftGroupLayout {
                    id: propLayout

                    anchors.left: parent.left
                    anchors.right: parent.right

                    columns: thumbColumn.thumbnailColumnCount
                    collapseToggle: propHeader.collapseToggle

                    Repeater {
                        model: AircraftManager.getNumProp()

                        AircraftSelectionItem {
                            required property int index

                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Layout.minimumHeight: minHeight
                            Layout.minimumWidth: 300

                            key: AircraftManager.getPropKey(index)

                            onAircraftSelected: function(key) {
                                aircraftPopupRoot.aircraftSelected(key);
                            }
                        }
                    }
                }

            }

        }
    }


}
