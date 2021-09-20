import QtQuick 2.15
import QtQuick.Controls 2.15

GroupBox {
    width: 250

    title: "Airspeed Colors"
    topPadding: 5
    leftPadding: 5
    rightPadding: 5
    bottomPadding: 5



    property bool unsavedChanges: enabled && (lastMinSpeed != lowLimitField.text || lastFlapsStart != flapsStart.text || lastFlapsEnd != flapsEnd.text || lastGreenStart != greenStart.text || lastGreenEnd != greenEnd.text || lastYellowStart != yellowStart.text || lastYellowEnd != yellowEnd.text || lastRedStart != redStart.text || lastRedEnd != redEnd.text || lastMaxSpeed != highLimitField.text)
    property bool isValid: lowLimitField.isValid && flapsStart.isValid && flapsEnd.isValid && greenStart.isValid && greenEnd.isValid && yellowStart.isValid && yellowEnd.isValid && redStart.isValid && redEnd.isValid && highLimitField.isValid



    // last saved state data
    property string lastMinSpeed: ""
    property string lastFlapsStart: ""
    property string lastFlapsEnd: ""
    property string lastGreenStart: ""
    property string lastGreenEnd: ""
    property string lastYellowStart: ""
    property string lastYellowEnd: ""
    property string lastRedStart: ""
    property string lastRedEnd: ""
    property string lastMaxSpeed: ""


    function saveData() {
        aircraftInterface.setLowLimit(parseFloat(lowLimitField.text));
        aircraftInterface.setFlapsBegin(parseFloat(flapsStart.text));
        aircraftInterface.setFlapsEnd(parseFloat(flapsEnd.text));
        aircraftInterface.setGreenBegin(parseFloat(greenStart.text));
        aircraftInterface.setGreenEnd(parseFloat(greenEnd.text));
        aircraftInterface.setYellowBegin(parseFloat(yellowStart.text));
        aircraftInterface.setYellowEnd(parseFloat(yellowEnd.text));
        aircraftInterface.setRedBegin(parseFloat(redStart.text));
        aircraftInterface.setRedEnd(parseFloat(redEnd.text));
        aircraftInterface.setHighLimit(parseFloat(highLimitField.text));

        lastMinSpeed = lowLimitField.text;
        lastFlapsStart = flapsStart.text;
        lastFlapsEnd = flapsEnd.text;
        lastGreenStart = greenStart.text;
        lastGreenEnd = greenEnd.text;
        lastYellowStart = yellowStart.text;
        lastYellowEnd = yellowEnd.text;
        lastRedStart = redStart.text;
        lastRedEnd = redEnd.text;
        lastMaxSpeed = highLimitField.text;
    }

    function updateData() {
        lowLimitField.text = aircraftInterface.getLowLimit();
        flapsStart.text = aircraftInterface.getFlapsBegin();
        flapsEnd.text = aircraftInterface.getFlapsEnd();
        greenStart.text = aircraftInterface.getGreenBegin();
        greenEnd.text = aircraftInterface.getGreenEnd();
        yellowStart.text = aircraftInterface.getYellowBegin();
        yellowEnd.text = aircraftInterface.getYellowEnd();
        redStart.text = aircraftInterface.getRedBegin();
        redEnd.text = aircraftInterface.getRedEnd();
        highLimitField.text = aircraftInterface.getHighLimit();

        lowLimitField.ensureVisible(0);
        flapsStart.ensureVisible(0);
        flapsEnd.ensureVisible(0);
        greenStart.ensureVisible(0);
        greenEnd.ensureVisible(0);
        yellowStart.ensureVisible(0);
        yellowEnd.ensureVisible(0);
        redStart.ensureVisible(0);
        redEnd.ensureVisible(0);
        highLimitField.ensureVisible(0);

        lastMinSpeed = lowLimitField.text;
        lastFlapsStart = flapsStart.text;
        lastFlapsEnd = flapsEnd.text;
        lastGreenStart = greenStart.text;
        lastGreenEnd = greenEnd.text;
        lastYellowStart = yellowStart.text;
        lastYellowEnd = yellowEnd.text;
        lastRedStart = redStart.text;
        lastRedEnd = redEnd.text;
        lastMaxSpeed = highLimitField.text;
    }

    label: Label {
        x: parent.leftPadding
        text: parent.title
        anchors.bottomMargin: 4
    }

    Component.onCompleted: label.anchors.bottom = background.top

    Column {
        anchors.fill: parent

        Item {
            height: 25
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                text: "Start"
                font.pixelSize: 12
                height: 25
                width: 70
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.right: colorEndText.left
                anchors.rightMargin: 5
            }

            Text {
                id: colorEndText
                text: "End"
                font.pixelSize: 12
                height: 25
                width: 70
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.right: parent.right
            }
        }

        Item {
            height: 30
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                text: "Lower Barberpole"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                color: enabled ? "black" : "#bdbebf"
            }

            TextField {
                id: lowLimitField
                width: 70
                height: 25
                text: "0.0"
                validator: DoubleValidator { bottom: 0 }
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                padding: 2
                leftPadding: 5
                selectByMouse: true

                property bool isValid: !enabled || (acceptableInput && length > 0)

                background: Rectangle {
                    border.width: parent.activeFocus ? 2 : 1
                    color: parent.palette.base
                    border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
                }
            }
        }



        Item {
            height: 30
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                text: "Flaps (white)"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                color: enabled ? "black" : "#bdbebf"
            }

            TextField {
                id: flapsStart
                width: 70
                height: 25
                text: "0.0"
                validator: DoubleValidator { bottom: 0 }
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: flapsEnd.left
                anchors.rightMargin: 5
                padding: 2
                leftPadding: 5
                selectByMouse: true

                property bool isValid: !enabled || (acceptableInput && length > 0)

                background: Rectangle {
                    border.width: parent.activeFocus ? 2 : 1
                    color: parent.palette.base
                    border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
                }
            }

            TextField {
                id: flapsEnd
                width: 70
                height: 25
                text: "0.0"
                validator: DoubleValidator { bottom: 0 }
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                padding: 2
                leftPadding: 5
                selectByMouse: true

                property bool isValid: !enabled || (acceptableInput && length > 0)

                background: Rectangle {
                    border.width: parent.activeFocus ? 2 : 1
                    color: parent.palette.base
                    border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
                }
            }
        }

        Item {
            height: 30
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                text: "Green"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                color: enabled ? "black" : "#bdbebf"
            }

            TextField {
                id: greenStart
                width: 70
                height: 25
                text: "0.0"
                validator: DoubleValidator { bottom: 0 }
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: greenEnd.left
                anchors.rightMargin: 5
                padding: 2
                leftPadding: 5
                selectByMouse: true

                property bool isValid: !enabled || (acceptableInput && length > 0)

                background: Rectangle {
                    border.width: parent.activeFocus ? 2 : 1
                    color: parent.palette.base
                    border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
                }
            }

            TextField {
                id: greenEnd
                width: 70
                height: 25
                text: "0.0"
                validator: DoubleValidator { bottom: 0 }
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                padding: 2
                leftPadding: 5
                selectByMouse: true

                property bool isValid: !enabled || (acceptableInput && length > 0)

                background: Rectangle {
                    border.width: parent.activeFocus ? 2 : 1
                    color: parent.palette.base
                    border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
                }
            }
        }

        Item {
            height: 30
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                text: "Yellow"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                color: enabled ? "black" : "#bdbebf"
            }

            TextField {
                id: yellowStart
                width: 70
                height: 25
                text: "0.0"
                validator: DoubleValidator { bottom: 0 }
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: yellowEnd.left
                anchors.rightMargin: 5
                padding: 2
                leftPadding: 5
                selectByMouse: true

                property bool isValid: !enabled || (acceptableInput && length > 0)

                background: Rectangle {
                    border.width: parent.activeFocus ? 2 : 1
                    color: parent.palette.base
                    border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
                }
            }

            TextField {
                id: yellowEnd
                width: 70
                height: 25
                text: "0.0"
                validator: DoubleValidator { bottom: 0 }
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                padding: 2
                leftPadding: 5
                selectByMouse: true

                property bool isValid: !enabled || (acceptableInput && length > 0)

                background: Rectangle {
                    border.width: parent.activeFocus ? 2 : 1
                    color: parent.palette.base
                    border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
                }
            }
        }

        Item {
            height: 30
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                text: "Red"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                color: enabled ? "black" : "#bdbebf"
            }

            TextField {
                id: redStart
                width: 70
                height: 25
                text: "0.0"
                validator: DoubleValidator { bottom: 0 }
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: redEnd.left
                anchors.rightMargin: 5
                padding: 2
                leftPadding: 5
                selectByMouse: true

                property bool isValid: !enabled || (acceptableInput && length > 0)

                background: Rectangle {
                    border.width: parent.activeFocus ? 2 : 1
                    color: parent.palette.base
                    border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
                }
            }

            TextField {
                id: redEnd
                width: 70
                height: 25
                text: "0.0"
                validator: DoubleValidator { bottom: 0 }
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                padding: 2
                leftPadding: 5
                selectByMouse: true

                property bool isValid: !enabled || (acceptableInput && length > 0)

                background: Rectangle {
                    border.width: parent.activeFocus ? 2 : 1
                    color: parent.palette.base
                    border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
                }
            }
        }

        Item {
            height: 30
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                text: "Upper Barberpole"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                color: enabled ? "black" : "#bdbebf"
            }

            TextField {
                id: highLimitField
                width: 70
                height: 25
                text: "0.0"
                validator: DoubleValidator { bottom: 0 }
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 75
                padding: 2
                leftPadding: 5
                selectByMouse: true

                property bool isValid: !enabled || (acceptableInput && length > 0)

                background: Rectangle {
                    border.width: parent.activeFocus ? 2 : 1
                    color: parent.palette.base
                    border.color: parent.activeFocus ? parent.palette.highlight : parent.isValid ? parent.palette.mid : "red"
                }
            }
        }
    }
}
