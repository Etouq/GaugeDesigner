import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

import Definition 1.0
import TypeEnums 1.0

import "ColorZoneTable"
import "GradTable"
import "TextGradTable"
import "../StyledControls"

Item {
    id: root

    property GaugeDefinition gaugeDef
    property int gaugeType: SwitchingGaugeType.NONE
    property bool isSecondaryTemp: false

    TopSection {
        id: topSection

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.topMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        gaugeDef: root.gaugeDef
        gaugeType: root.gaugeType
        isSecondaryTemp: root.isSecondaryTemp
    }


    RowLayout {
        id: vectorInputs
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: topSection.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.topMargin: 10

        ColorZoneTable {
            id: colorInputTable

            Layout.fillWidth: true
            Layout.fillHeight: true

            gaugeDef: root.gaugeDef
        }
        Rectangle {
            width: 2
            color: Material.foreground

            Layout.fillHeight: true
        }
        GradTable {
            id: gradInputTable

            Layout.fillWidth: true
            Layout.fillHeight: true

            gaugeDef: root.gaugeDef
        }
        Rectangle {
            width: 2
            color: Material.foreground

            Layout.fillHeight: true
        }
        TextGradTable {
            id: textGradInputTable

            Layout.fillWidth: true
            Layout.fillHeight: true

            gaugeDef: root.gaugeDef
        }
    }







}
