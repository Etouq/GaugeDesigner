import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Definition 1.0

GroupBox {

    title: "Airspeed Colors"
    topPadding: checkBox.height

    spacing: 0

    label: CheckBox {
        id: checkBox
        leftPadding: 5
        bottomPadding: 15
        rightPadding: 0
        topPadding: 0
        checked: !AircraftDefinition.noColors
        text: parent.title
        font.pointSize: 11
    }

    GridLayout {
        id: gridLayout
        columns: 5
        enabled: checkBox.checked

        Item {
            Layout.fillWidth: true // spacer
        }

        Text {
            text: "Start"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.preferredWidth: 100
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: "Roboto"
            font.pointSize: 11
            color: enabled ? Material.foreground : Material.hintTextColor
        }

        Text {
            text: "End"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.preferredWidth: 100
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: "Roboto"
            font.pointSize: 11
            color: enabled ? Material.foreground : Material.hintTextColor
        }

        Text {
            text: "Enabled"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: "Roboto"
            font.pointSize: 11
            color: enabled ? Material.foreground : Material.hintTextColor
        }

        Text {
            text: "Dynamic"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 11
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: "Roboto"
            Layout.fillWidth: true
            color: enabled ? Material.foreground : Material.hintTextColor
        }

        Text {
            enabled: lowEnabledBox.checked
            color: enabled ? Material.foreground : Material.hintTextColor
            text: "Lower Barberpole"
            Layout.fillWidth: true
            font.pointSize: 11
            font.family: "Roboto"
        }

        Item {
            Layout.preferredWidth: 100
            Layout.fillWidth: true
            Layout.preferredHeight: 0
            // spacer
        }

        TextField {
            id: lowLimitField

            enabled: lowEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "End"
            text: AircraftDefinition.lowLimit

            onEditingFinished: function() {
                if (lowLimitField.text === "" || lowLimitField.text === "-") {
                    const val = AircraftDefinition.lowLimit;
                    AircraftDefinition.lowLimit = val + 5;
                    AircraftDefinition.lowLimit = val;
                }
            }

            onTextEdited: function() {
                if (lowLimitField.text === "" || lowLimitField.text === "-")
                    return;

                const completeVal = Number(lowLimitField.text);

                if(isNaN(completeVal)) {
                    console.log(lowLimitField.text + " is not a number");
                    lowLimitField.undo();
                    return;
                }

                AircraftDefinition.lowLimit = completeVal;
            }
        }

        CheckBox {
            id: lowEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasLowLimit
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        Text {
            enabled: flapsEnabledBox.checked

            Layout.fillWidth: true

            font.pointSize: 11
            font.family: "Roboto"

            color: enabled ? Material.foreground : Material.hintTextColor

            text: "Flaps (white)"
        }

        TextField {
            id: flapsStartField

            enabled: flapsEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "Start"
            text: AircraftDefinition.flapsBegin

            onEditingFinished: function() {
                if (flapsStartField.text === "" || flapsStartField.text === "-") {
                    const val = AircraftDefinition.flapsBegin;
                    AircraftDefinition.flapsBegin = val + 5;
                    AircraftDefinition.flapsBegin = val;
                }
            }

            onTextEdited: function() {
                if (flapsStartField.text === "" || flapsStartField.text === "-")
                    return;

                const completeVal = Number(flapsStartField.text);

                if(isNaN(completeVal)) {
                    console.log(flapsStartField.text + " is not a number");
                    flapsStartField.undo();
                    return;
                }

                AircraftDefinition.flapsBegin = completeVal;
            }
        }

        TextField {
            id: flapsEndField

            enabled: flapsEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "End"
            text: AircraftDefinition.flapsEnd

            onEditingFinished: function() {
                if (flapsEndField.text === "" || flapsEndField.text === "-") {
                    const val = AircraftDefinition.flapsEnd;
                    AircraftDefinition.flapsEnd = val + 5;
                    AircraftDefinition.flapsEnd = val;
                }
            }

            onTextEdited: function() {
                if (flapsEndField.text === "" || flapsEndField.text === "-")
                    return;

                const completeVal = Number(flapsEndField.text);

                if(isNaN(completeVal)) {
                    console.log(flapsEndField.text + " is not a number");
                    flapsEndField.undo();
                    return;
                }

                AircraftDefinition.flapsEnd = completeVal;
            }
        }

        CheckBox {
            id: flapsEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasFlapsSpeed
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        Text {
            enabled: greenEnabledBox.checked
            color: enabled ? Material.foreground : Material.hintTextColor
            text: "Green"
            font.pointSize: 11
            font.family: "Roboto"
            Layout.fillWidth: true
        }

        TextField {
            id: greenStartField

            enabled: greenEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "Start"
            text: AircraftDefinition.greenBegin

            onEditingFinished: function() {
                if (greenStartField.text === "" || greenStartField.text === "-") {
                    const val = AircraftDefinition.greenBegin;
                    AircraftDefinition.greenBegin = val + 5;
                    AircraftDefinition.greenBegin = val;
                }
            }

            onTextEdited: function() {
                if (greenStartField.text === "" || greenStartField.text === "-")
                    return;

                const completeVal = Number(greenStartField.text);

                if(isNaN(completeVal)) {
                    console.log(greenStartField.text + " is not a number");
                    greenStartField.undo();
                    return;
                }

                AircraftDefinition.greenBegin = completeVal;
            }
        }


        TextField {
            id: greenEndField

            enabled: greenEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "End"
            text: AircraftDefinition.greenEnd

            onEditingFinished: function() {
                if (greenEndField.text === "" || greenEndField.text === "-") {
                    const val = AircraftDefinition.greenEnd;
                    AircraftDefinition.greenEnd = val + 5;
                    AircraftDefinition.greenEnd = val;
                }
            }

            onTextEdited: function() {
                if (greenEndField.text === "" || greenEndField.text === "-")
                    return;

                const completeVal = Number(greenEndField.text);

                if(isNaN(completeVal)) {
                    console.log(greenEndField.text + " is not a number");
                    greenEndField.undo();
                    return;
                }

                AircraftDefinition.greenEnd = completeVal;
            }
        }

        CheckBox {
            id: greenEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasGreenSpeed
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        Text {
            enabled: yellowEnabledBox.checked
            color: enabled ? Material.foreground : Material.hintTextColor
            text: "Yellow"
            font.pointSize: 11
            font.family: "Roboto"
            Layout.fillWidth: true
        }

        TextField {
            id: yellowStartField

            enabled: yellowEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "Start"
            text: AircraftDefinition.yellowBegin

            onEditingFinished: function() {
                if (yellowStartField.text === "" || yellowStartField.text === "-") {
                    const val = AircraftDefinition.yellowBegin;
                    AircraftDefinition.yellowBegin = val + 5;
                    AircraftDefinition.yellowBegin = val;
                }
            }

            onTextEdited: function() {
                if (yellowStartField.text === "" || yellowStartField.text === "-")
                    return;

                const completeVal = Number(yellowStartField.text);

                if(isNaN(completeVal)) {
                    console.log(yellowStartField.text + " is not a number");
                    yellowStartField.undo();
                    return;
                }

                AircraftDefinition.yellowBegin = completeVal;
            }
        }

        TextField {
            id: yellowEndField

            enabled: yellowEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "End"
            text: AircraftDefinition.yellowEnd

            onEditingFinished: function() {
                if (yellowEndField.text === "" || yellowEndField.text === "-") {
                    const val = AircraftDefinition.yellowEnd;
                    AircraftDefinition.yellowEnd = val + 5;
                    AircraftDefinition.yellowEnd = val;
                }
            }

            onTextEdited: function() {
                if (yellowEndField.text === "" || yellowEndField.text === "-")
                    return;

                const completeVal = Number(yellowEndField.text);

                if(isNaN(completeVal)) {
                    console.log(yellowEndField.text + " is not a number");
                    yellowEndField.undo();
                    return;
                }

                AircraftDefinition.yellowEnd = completeVal;
            }
        }

        CheckBox {
            id: yellowEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasYellowSpeed
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        Text {
            enabled: redEnabledBox.checked
            color: enabled ? Material.foreground : Material.hintTextColor
            text: "Red"
            font.pointSize: 11
            font.family: "Roboto"
            Layout.fillWidth: true
        }

        TextField {
            id: redStartField

            enabled: redEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "Start"
            text: AircraftDefinition.redBegin

            onEditingFinished: function() {
                if (redStartField.text === "" || redStartField.text === "-") {
                    const val = AircraftDefinition.redBegin;
                    AircraftDefinition.redBegin = val + 5;
                    AircraftDefinition.redBegin = val;
                }
            }

            onTextEdited: function() {
                if (redStartField.text === "" || redStartField.text === "-")
                    return;

                const completeVal = Number(redStartField.text);

                if(isNaN(completeVal)) {
                    console.log(redStartField.text + " is not a number");
                    redStartField.undo();
                    return;
                }

                AircraftDefinition.redBegin = completeVal;
            }
        }

        TextField {
            id: redEndField

            enabled: redEnabledBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "End"
            text: AircraftDefinition.redEnd

            onEditingFinished: function() {
                if (redEndField.text === "" || redEndField.text === "-") {
                    const val = AircraftDefinition.redEnd;
                    AircraftDefinition.redEnd = val + 5;
                    AircraftDefinition.redEnd = val;
                }
            }

            onTextEdited: function() {
                if (redEndField.text === "" || redEndField.text === "-")
                    return;

                const completeVal = Number(redEndField.text);

                if(isNaN(completeVal)) {
                    console.log(redEndField.text + " is not a number");
                    redEndField.undo();
                    return;
                }

                AircraftDefinition.redEnd = completeVal;
            }
        }

        CheckBox {
            id: redEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasRedSpeed
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        Text {
            enabled: highEnabledBox.checked
            color: enabled ? Material.foreground : Material.hintTextColor
            text: "Upper Barberpole"
            font.pointSize: 11
            font.family: "Roboto"
            Layout.fillWidth: true
        }

        TextField {
            id: highLimitField

            enabled: highEnabledBox.checked && !highDynamicBox.checked

            Layout.fillWidth: true
            Layout.preferredWidth: 100

            leftPadding: 5
            rightPadding: 5

            font.pointSize: 11

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            selectByMouse: true

            placeholderText: "Start"
            text: AircraftDefinition.highLimit

            onEditingFinished: function() {
                if (highLimitField.text === "" || highLimitField.text === "-") {
                    const val = AircraftDefinition.highLimit;
                    AircraftDefinition.highLimit = val + 5;
                    AircraftDefinition.highLimit = val;
                }
            }

            onTextEdited: function() {
                if (highLimitField.text === "" || highLimitField.text === "-")
                    return;

                const completeVal = Number(highLimitField.text);

                if(isNaN(completeVal)) {
                    console.log(highLimitField.text + " is not a number");
                    highLimitField.undo();
                    return;
                }

                AircraftDefinition.highLimit = completeVal;
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 0
        }

        CheckBox {
            id: highEnabledBox

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.hasHighLimit
        }

        CheckBox {
            id: highDynamicBox

            enabled: highEnabledBox.checked

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            topPadding: 8
            bottomPadding: 8
            spacing: 0

            text: ""

            checked: AircraftDefinition.dynamicBarberpole
        }

    }

    Binding {
        target: AircraftDefinition
        property: "noColors"
        value: !checkBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "lowLimit"
        value: lowLimitField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasLowLimit"
        value: lowEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "flapsBegin"
        value: flapsStartField.text
    }

    Binding {
        target: AircraftDefinition
        property: "flapsEnd"
        value: flapsEndField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasFlapsSpeed"
        value: flapsEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "greenBegin"
        value: greenStartField.text
    }

    Binding {
        target: AircraftDefinition
        property: "greenEnd"
        value: greenEndField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasGreenSpeed"
        value: greenEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "yellowBegin"
        value: yellowStartField.text
    }

    Binding {
        target: AircraftDefinition
        property: "yellowEnd"
        value: yellowEndField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasYellowSpeed"
        value: yellowEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "redBegin"
        value: redStartField.text
    }

    Binding {
        target: AircraftDefinition
        property: "redEnd"
        value: redEndField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasRedSpeed"
        value: redEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "highLimit"
        value: highLimitField.text
    }

    Binding {
        target: AircraftDefinition
        property: "hasHighLimit"
        value: highEnabledBox.checked
    }

    Binding {
        target: AircraftDefinition
        property: "dynamicBarberpole"
        value: highDynamicBox.checked
    }
}
