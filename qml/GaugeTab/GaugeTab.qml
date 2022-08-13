import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15

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

    property var gaugeObject: null


    signal changeMade()

    Connections {
        target: gaugeObject
        function onUpdateGauge() {
            updateData();
        }
    }


    function updateData() {
        colorInputTable.updateModel(gaugeObject);
        gradInputTable.updateModel(gaugeObject);
        textGradInputTable.updateModel(gaugeObject);

        topSection.updateData();

        forceTextColorSwitch.checked = gaugeObject.getForceTextColor();
        textForcedColorRect.color = gaugeObject.getTextForcedColor();

        hasMinBlinkSwitch.checked = gaugeObject.getHasMinRedBlink();
        minBlinkVal.text = gaugeObject.getMinRedBlinkThreshold();
        minBlinkVal.ensureVisible(0);
        hasMaxBlinkSwitch.checked = gaugeObject.getHasMaxRedBlink();
        maxBlinkVal.text = gaugeObject.getMaxRedBlinkThreshold();
        maxBlinkVal.ensureVisible(0);

        lastMinBlinkChecked = hasMinBlinkSwitch.checked;
        lastMinBlinkValue = minBlinkVal.text;
        lastMaxBlinkChecked = hasMaxBlinkSwitch.checked;
        lastMaxBlinkValue = maxBlinkVal.text;
        lastForceTextChecked = forceTextColorSwitch.checked;
        lastForceTextColor = textForcedColorRect.color;
    }

    function saveData() {
        topSection.saveData();

        colorInputTable.saveData(gaugeObject);
        gradInputTable.saveData(gaugeObject);
        textGradInputTable.saveData(gaugeObject);

        gaugeObject.setForceTextColor(forceTextColorSwitch.checked, textForcedColorRect.color.toString());
        gaugeObject.setMinBlink(hasMinBlinkSwitch.checked, hasMinBlinkSwitch.checked ? parseFloat(minBlinkVal.text) : 0);
        gaugeObject.setMaxBlink(hasMaxBlinkSwitch.checked, hasMaxBlinkSwitch.checked ? parseFloat(maxBlinkVal.text) : 0);

        lastMinBlinkChecked = hasMinBlinkSwitch.checked;
        if (lastMinBlinkChecked)
            lastMinBlinkValue = minBlinkVal.text;

        lastMaxBlinkChecked = hasMaxBlinkSwitch.checked;
        if (lastMaxBlinkChecked)
            lastMaxBlinkValue = maxBlinkVal.text;

        lastForceTextChecked = forceTextColorSwitch.checked;
        if (lastForceTextChecked)
            lastForceTextColor = textForcedColorRect.color;


        gaugeObject.updateComplete();
    }


    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        modality: Qt.WindowModal
        onAccepted: function() {
            textForcedColorRect.color = colorDialog.color;
        }
        Component.onCompleted: color = "#FFFFFF"
    }

    TopSection {
        id: topSection

        gaugeDef: root.gaugeDef
        gaugeType: root.gaugeType
        isSecondaryTemp: root.isSecondaryTemp

        // onMaxValChanged: function() {
        //     gradInputTable.maxValue = maxVal;
        //     textGradInputTable.maxValue = maxVal;
        // }
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

            Layout.fillHeight: true
        }
        Rectangle {
            width: 2
            color: "black"

            Layout.fillHeight: true
        }
        GradTable {
            id: gradInputTable

            Layout.fillHeight: true
        }
        Rectangle {
            width: 2
            color: "black"

            Layout.fillHeight: true
        }
        TextGradTable {
            id: textGradInputTable

            Layout.fillHeight: true
        }
    }







}
