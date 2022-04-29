import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt.labs.platform
import "ColorZoneTable"
import "GradTable"
import "TextGradTable"
import "../StyledControls"

Item {
    id: root
    width: 630
    height: 450

    property alias defaultTitle: topSection.defaultTitle
    property alias unitTypes: topSection.unitTypes // 0: none, 1: percent, 2: rpm, 3: temperature, 4: pressure, 5: torque, 6: weight, 7: volume, 8: weight per hour, 9: volume per hour, 10: weight per minute, 11: volume per minute, 12: weight per second, 13: volume per second


    property var gaugeObject: null

    property bool isValid: (!hasMinBlinkSwitch.checked || (minBlinkVal.acceptableInput && minBlinkVal.length > 0)) && (!hasMaxBlinkSwitch.checked || (maxBlinkVal.acceptableInput && maxBlinkVal.length > 0)) && topSection.isValid
    property bool unsavedChanges: topSection.unsavedChanges || lastMinBlinkChecked !== hasMinBlinkSwitch.checked || (!hasMinBlinkSwitch.checked && lastMinBlinkValue !== minBlinkVal.text) || lastMaxBlinkChecked !== hasMaxBlinkSwitch.checked || (!hasMaxBlinkSwitch.checked && lastMaxBlinkValue !== maxBlinkVal.text) || lastForceTextChecked !== forceTextColorSwitch.checked || (!forceTextColorSwitch.checked && textForcedColorRect.color !== lastForceTextColor) || colorInputTable.unsavedChanges || gradInputTable.unsavedChanges || textGradInputTable.unsavedChanges


    // last saved state data
    property bool lastMinBlinkChecked: false
    property string lastMinBlinkValue: ""
    property bool lastMaxBlinkChecked: false
    property string lastMaxBlinkValue: ""
    property bool lastForceTextChecked: false
    property string lastForceTextColor: ""


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

        gaugeObject: root.gaugeObject

        onMaxValChanged: function() {
            gradInputTable.maxValue = maxVal;
            textGradInputTable.maxValue = maxVal;
        }
    }


    Row {
        id: vectorInputs
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        ColorZoneTable {
            id: colorInputTable
            anchors.bottom: parent.bottom
        }
        Rectangle {
            width: 2
            color: "black"
            anchors.top: gradInputTable.top
            anchors.bottom: parent.bottom
        }
        GradTable {
            id: gradInputTable
            anchors.bottom: parent.bottom
        }
        Rectangle {
            width: 2
            color: "black"
            anchors.top: gradInputTable.top
            anchors.bottom: parent.bottom
        }
        TextGradTable {
            id: textGradInputTable
            anchors.bottom: parent.bottom
        }
    }


    Column {
        y: 126
        width: 230
        height: 144
        anchors.bottom: vectorInputs.bottom
        anchors.bottomMargin: colorInputTable.height
        spacing: 5

        Item {
            width: 230
            height: 21

            Text {
                text: "Has Low Red Blink"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 15
            }

            StyledSwitch {
                id: hasMinBlinkSwitch
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 15
            }
        }

        Item {
            width: 230
            height: 25

            Text {
                visible: hasMinBlinkSwitch.checked
                text: "Low Threshold"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 15
            }

            TextField {
                id: minBlinkVal
                width: 70
                height: 25
                visible: hasMinBlinkSwitch.checked
                validator: DoubleValidator{}
                text: "0.0"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                rightPadding: 2
                bottomPadding: 2
                topPadding: 2
                leftPadding: 5
                anchors.rightMargin: 15
                selectByMouse: true
            }
        }

        Item {
            width: 230
            height: 21

            Text {
                text: "Has High Red Blink"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 15
            }

            StyledSwitch {
                id: hasMaxBlinkSwitch
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 15
            }
        }

        Item {
            width: 230
            height: 25

            Text {
                visible: hasMaxBlinkSwitch.checked
                text: "High Threshold"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 15
            }

            TextField {
                id: maxBlinkVal
                width: 70
                height: 25
                visible: hasMaxBlinkSwitch.checked
                validator: DoubleValidator{}
                text: "0.0"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                rightPadding: 2
                bottomPadding: 2
                topPadding: 2
                leftPadding: 5
                anchors.rightMargin: 15
                font.pixelSize: 11
                selectByMouse: true
            }
        }

        Item {
            width: 230
            height: 21
            visible: !topSection.noTextChecked




            StyledSwitch {
                id: forceTextColorSwitch
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: textForcedColorRect.left
                anchors.rightMargin: 5
            }

            Text {
                x: 251
                y: 172
                text: "Force Text Color"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 15
            }

            Rectangle {
                id: textForcedColorRect
                width: 25
                height: 25
                visible: forceTextColorSwitch.checked
                color: "#ffffff"
                border.color: "black"
                border.width: 1
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 15
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: colorDialog.open()
                }
            }
        }

    }







}
