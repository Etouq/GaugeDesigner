import QtQuick 2.15
import QtQuick.Shapes 1.15
import "gauges"

Item {
    anchors.fill: parent
    /*antialiasing: true
    layer.enabled: true
    layer.samples: 8*/
    clip: true

    //property real scaleFactor: 1
    property int numTanks: 1

    Component.onCompleted: {
        fuelTankGaugeLoader.setSource(numTanks == 1 ? "qrc:/PreviewPopup/gauges/FuelSingleTankGauge.qml" : "qrc:/PreviewPopup/gauges/FuelDoubleTankGauge.qml", { "centerX": 97.5, "yTop": 558 });
        if (aircraftInterface.getHasSpoilers())
            flapsGaugeLoader.setSource("qrc:/PreviewPopup/gauges/FlapsSpoilersGauge.qml", { "yStart": 954.6 });
        else if(aircraftInterface.getHasFlaps())
            flapsGaugeLoader.setSource("qrc:/PreviewPopup/gauges/FlapsGauge.qml", { "yStart": 954.6 });
        else
            flapsGaugeLoader.setSource("");

    }


    Item {
        id: n1GaugeParent

        VerticalGauge {
            centerX: 61.5
            yTop: 40.5
            valuePos: 2

            minValue: n1Interface.getMinValue()
            maxValue: n1Interface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: n1Interface.engineTransformValue
            textValue: n1Interface.engineValue
            textColor: n1Interface.engineColor
            redBlink: n1Interface.engineRedBlink

            Component.onCompleted: {
                initModels(n1Interface);
            }
        }

        VerticalGauge {
            centerX: 160.5
            yTop: 40.5
            valuePos: 2

            minValue: n1Interface.getMinValue()
            maxValue: n1Interface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: n1Interface.engineTransformValue
            textValue: n1Interface.engineValue
            textColor: n1Interface.engineColor
            redBlink: n1Interface.engineRedBlink

            Component.onCompleted: {
                initModels(n1Interface);
            }
        }

        VerticalGauge {
            centerX: 259.5
            yTop: 40.5
            valuePos: 2

            minValue: n1Interface.getMinValue()
            maxValue: n1Interface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: n1Interface.engineTransformValue
            textValue: n1Interface.engineValue
            textColor: n1Interface.engineColor
            redBlink: n1Interface.engineRedBlink

            Component.onCompleted: {
                initModels(n1Interface);
            }
        }

        VerticalGauge {
            centerX: 358.5
            yTop: 40.5
            valuePos: 2

            minValue: n1Interface.getMinValue()
            maxValue: n1Interface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: n1Interface.engineTransformValue
            textValue: n1Interface.engineValue
            textColor: n1Interface.engineColor
            redBlink: n1Interface.engineRedBlink

            Component.onCompleted: {
                initModels(n1Interface);
            }
        }

        Text {
            anchors.horizontalCenter: parent.left
            anchors.horizontalCenterOffset: 210
            anchors.baseline: parent.top
            anchors.baselineOffset: 30
            color: "white"
            font.pixelSize: 23
            font.family: "Roboto Mono"
            font.bold: true
            text: n1Interface.getTitle() + ' ' + n1Interface.getUnitString()
        }
    }

    Item {
        id: n2GaugeParent

        VerticalGauge {
            centerX: 61.5
            yTop: 209.25
            valuePos: 2

            minValue: n2Interface.getMinValue()
            maxValue: n2Interface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: n2Interface.engineTransformValue
            textValue: n2Interface.engineValue
            textColor: n2Interface.engineColor
            redBlink: n2Interface.engineRedBlink

            Component.onCompleted: {
                initModels(n2Interface);
            }
        }

        VerticalGauge {
            centerX: 160.5
            yTop: 209.25
            valuePos: 2

            minValue: n2Interface.getMinValue()
            maxValue: n2Interface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: n2Interface.engineTransformValue
            textValue: n2Interface.engineValue
            textColor: n2Interface.engineColor
            redBlink: n2Interface.engineRedBlink

            Component.onCompleted: {
                initModels(n2Interface);
            }
        }

        VerticalGauge {
            centerX: 259.5
            yTop: 209.25
            valuePos: 2

            minValue: n2Interface.getMinValue()
            maxValue: n2Interface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: n2Interface.engineTransformValue
            textValue: n2Interface.engineValue
            textColor: n2Interface.engineColor
            redBlink: n2Interface.engineRedBlink

            Component.onCompleted: {
                initModels(n2Interface);
            }
        }

        VerticalGauge {
            centerX: 358.5
            yTop: 209.25
            valuePos: 2

            minValue: n2Interface.getMinValue()
            maxValue: n2Interface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: n2Interface.engineTransformValue
            textValue: n2Interface.engineValue
            textColor: n2Interface.engineColor
            redBlink: n2Interface.engineRedBlink

            Component.onCompleted: {
                initModels(n2Interface);
            }
        }

        Text {
            anchors.horizontalCenter: parent.left
            anchors.horizontalCenterOffset: 210
            anchors.baseline: parent.top
            anchors.baselineOffset: 198.75
            color: "white"
            font.pixelSize: 23
            font.family: "Roboto Mono"
            font.bold: true
            text: n2Interface.getTitle() + ' ' + n2Interface.getUnitString()
        }
    }

    Item {
        id: ittGaugeParent

        VerticalGauge {
            centerX: 61.5
            yTop: 378
            valuePos: 2

            minValue: ittInterface.getMinValue()
            maxValue: ittInterface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: ittInterface.engineTransformValue
            textValue: ittInterface.engineValue
            textColor: ittInterface.engineColor
            redBlink: ittInterface.engineRedBlink

            Component.onCompleted: {
                initModels(ittInterface);
            }
        }

        VerticalGauge {
            centerX: 160.5
            yTop: 378
            valuePos: 2

            minValue: ittInterface.getMinValue()
            maxValue: ittInterface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: ittInterface.engineTransformValue
            textValue: ittInterface.engineValue
            textColor: ittInterface.engineColor
            redBlink: ittInterface.engineRedBlink

            Component.onCompleted: {
                initModels(ittInterface);
            }
        }

        VerticalGauge {
            centerX: 259.5
            yTop: 378
            valuePos: 2

            minValue: ittInterface.getMinValue()
            maxValue: ittInterface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: ittInterface.engineTransformValue
            textValue: ittInterface.engineValue
            textColor: ittInterface.engineColor
            redBlink: ittInterface.engineRedBlink

            Component.onCompleted: {
                initModels(ittInterface);
            }
        }

        VerticalGauge {
            centerX: 358.5
            yTop: 378
            valuePos: 2

            minValue: ittInterface.getMinValue()
            maxValue: ittInterface.getMaxValue()

            title: ""
            unit: ""

            cursorTransformValue: ittInterface.engineTransformValue
            textValue: ittInterface.engineValue
            textColor: ittInterface.engineColor
            redBlink: ittInterface.engineRedBlink

            Component.onCompleted: {
                initModels(ittInterface);
            }
        }

        Text {
            anchors.horizontalCenter: parent.left
            anchors.horizontalCenterOffset: 210
            anchors.baseline: parent.top
            anchors.baselineOffset: 367.5
            color: "white"
            font.pixelSize: 23
            font.family: "Roboto Mono"
            font.bold: true
            text: ittInterface.getTitle() + ' ' + ittInterface.getUnitString()
        }
    }

    Loader {
        id: fuelTankGaugeLoader
    }

    VerticalDoubleGauge {
        id: fuelFlowGauge
        centerX: 322.5
        yTop: 558

        extraWide: fuelFlowInterface.needsExtraWide()

        minValue: fuelFlowInterface.getMinValue()
        maxValue: fuelFlowInterface.getMaxValue()

        title: fuelFlowInterface.getTitle()
        unit: fuelFlowInterface.getUnitString()

        leftCursorTransformValue: fuelFlowInterface.engineTransformValue
        leftTextValue: fuelFlowInterface.engineValue
        leftTextColor: fuelFlowInterface.engineColor
        leftRedBlink: fuelFlowInterface.engineRedBlink

        rightCursorTransformValue: fuelFlowInterface.engineTransformValue
        rightTextValue: fuelFlowInterface.engineValue
        rightTextColor: fuelFlowInterface.engineColor
        rightRedBlink: fuelFlowInterface.engineRedBlink

        Component.onCompleted: {
            initModels(fuelFlowInterface);
        }
    }

    FuelText {
        id: fuelTextGauge
        topBaseline: 705
    }

    VerticalDoubleGauge {
        id: oilTempGauge
        centerX: 120
        yTop: 780

        extraWide: oilTempInterface.needsExtraWide()

        minValue: oilTempInterface.getMinValue()
        maxValue: oilTempInterface.getMaxValue()

        title: oilTempInterface.getTitle()
        unit: oilTempInterface.getUnitString()

        leftCursorTransformValue: oilTempInterface.engineTransformValue
        leftTextValue: oilTempInterface.engineValue
        leftTextColor: oilTempInterface.engineColor
        leftRedBlink: oilTempInterface.engineRedBlink

        rightCursorTransformValue: oilTempInterface.engineTransformValue
        rightTextValue: oilTempInterface.engineValue
        rightTextColor: oilTempInterface.engineColor
        rightRedBlink: oilTempInterface.engineRedBlink

        Component.onCompleted: {
            initModels(oilTempInterface);
        }
    }

    VerticalDoubleGauge {
        id: oilPressGauge
        centerX: 300
        yTop: 780

        extraWide: oilPressInterface.needsExtraWide()

        minValue: oilPressInterface.getMinValue()
        maxValue: oilPressInterface.getMaxValue()

        title: oilPressInterface.getTitle()
        unit: oilPressInterface.getUnitString()

        leftCursorTransformValue: oilPressInterface.engineTransformValue
        leftTextValue: oilPressInterface.engineValue
        leftTextColor: oilPressInterface.engineColor
        leftRedBlink: oilPressInterface.engineRedBlink

        rightCursorTransformValue: oilPressInterface.engineTransformValue
        rightTextValue: oilPressInterface.engineValue
        rightTextColor: oilPressInterface.engineColor
        rightRedBlink: oilPressInterface.engineRedBlink

        Component.onCompleted: {
            initModels(oilPressInterface);
        }
    }

    Loader {
        id: flapsGaugeLoader
    }

    TrimGauges {
        elevTop: 1057.5
    }
}
