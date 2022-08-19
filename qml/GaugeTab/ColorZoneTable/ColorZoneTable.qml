import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

import Definition 1.0

Item {
    id: root
    property int activeIndex: -1

    required property GaugeDefinition gaugeDef


    Menu {
        id: contextMenu
        MenuItem {
            text: "Insert"
            onTriggered: {
                gaugeDef.colorZoneModel.insertNewRow(activeIndex);
            }
        }
        MenuItem {
            text: "Delete"
            onTriggered: {
                gaugeDef.colorZoneModel.deleteRow(activeIndex);
            }
        }
        onAboutToHide: activeIndex = -1;
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Text {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.family: "Roboto"
            font.pointSize: 11
            font.bold: true

            color: Material.foreground

            text: "Color Zones"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 5
            Layout.rightMargin: 5

            Text {
                Layout.fillWidth: true
                Layout.preferredWidth: 70
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.family: "Roboto"
                font.pointSize: 11

                color: Material.foreground

                text: "Start"
            }

            Item {
                Layout.preferredWidth: 10
                Layout.fillWidth: true
            }

            Text {
                Layout.fillWidth: true
                Layout.preferredWidth: 70
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.family: "Roboto"
                font.pointSize: 11

                color: Material.foreground

                text: "End"
            }

            Item {
                Layout.preferredWidth: 10
                Layout.fillWidth: true
            }

            Text {
                Layout.fillWidth: true
                Layout.preferredWidth: 30
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.family: "Roboto"
                font.pointSize: 11

                color: Material.foreground

                text: "Color"
            }

        }




        MouseArea {
            Layout.fillWidth: true
            Layout.fillHeight: true

            acceptedButtons: Qt.RightButton
            propagateComposedEvents: true

            onClicked: function(mouse) {
                activeIndex = view.indexAt(mouse.x, mouse.y);
                if (activeIndex != -1)
                    contextMenu.popup();
            }


            ListView {
                id: view

                anchors.fill: parent

                clip: true

                model: gaugeDef.colorZoneModel
                interactive: true
                spacing: 5

                ScrollBar.vertical: ScrollBar {
                    parent: view.parent
                    anchors.top: view.top
                    anchors.left: view.right
                    anchors.bottom: view.bottom

                    policy: view.contentHeight > view.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

                    width: 10

                    contentItem: Rectangle {
                        implicitWidth: 6
                        implicitHeight: 100
                        radius: width / 2
                        color: Material.accent
                    }
                }

                delegate: ColorZoneRow {
                    width: view.width
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.bottomMargin: -3

            Button {
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                enabled: view.count < 10

                text: "Add"

                onReleased: function() {
                    gaugeDef.colorZoneModel.appendNewRow();
                }
            }

            Button {
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                enabled: view.count > 0

                text: "Remove"

                onReleased: function() {
                    gaugeDef.colorZoneModel.deleteRow(gaugeDef.colorZoneModel.rowCount() - 1);
                }
            }
        }
    }



}
