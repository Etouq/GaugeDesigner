import QtQuick 2.15
import QtQuick.Shapes 1.15
import "gauges"

Item {
    anchors.fill: parent
    clip: true

    property int numTanks: 1

    Component.onCompleted: {
        fuelTankGaugeLoader.setSource(numTanks == 1 ? "qrc:/PreviewPopup/gauges/FuelSingleTankGauge.qml" : "qrc:/PreviewPopup/gauges/FuelDoubleTankGauge.qml", { "centerX": 97.5, "yTop": 480 });
        if (aircraftInterface.getHasSpoilers())
            flapsGaugeLoader.setSource("qrc:/PreviewPopup/gauges/FlapsSpoilersGauge.qml", { "yStart": 924.6 });
        else if(aircraftInterface.getHasFlaps())
            flapsGaugeLoader.setSource("qrc:/PreviewPopup/gauges/FlapsGauge.qml", { "yStart": 924.6 });
        else
            flapsGaugeLoader.setSource("");

    }

    Item {
        id: n1GaugeParent

        CircularGauge {
            id: n1GaugeLeft
            startAngle: n1Interface.getStartAngle()
            endAngle: n1Interface.getEndAngle()
            radius: 70.5
            centerX: 97.5
            centerY: 82.5

            valueTextSize: 26

            minValue: n1Interface.getMinValue()
            maxValue: n1Interface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: n1Interface.engineAngle
            textValue: n1Interface.engineValue
            textColor: n1Interface.engineColor
            redBlink: n1Interface.engineRedBlink

            Component.onCompleted: {
                initModels(n1Interface);
            }
        }

        CircularGauge {
            id: n1GaugeRight
            startAngle: n1Interface.getStartAngle()
            endAngle: n1Interface.getEndAngle()
            radius: 70.5
            centerX: 322.5
            centerY: 82.5

            valueTextSize: 26
            
            minValue: n1Interface.getMinValue()
            maxValue: n1Interface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: n1Interface.engineAngle
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
            y: 10.5
            lineHeight: 0.8
            horizontalAlignment: Text.AlignHCenter
            color: "white"
            font.pixelSize: 26
            font.family: "Roboto Mono"
            font.bold: true
            text: n1Interface.getTitle() + '\n' + n1Interface.getUnitString()
        }
    }

    Item {
        id: n2GaugeParent

        CircularGauge {
            id: n2GaugeLeft
            startAngle: n2Interface.getStartAngle()
            endAngle: n2Interface.getEndAngle()
            radius: 70.5
            centerX: 97.5
            centerY: 217.5

            valueTextSize: 26
            
            minValue: n2Interface.getMinValue()
            maxValue: n2Interface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: n2Interface.engineAngle
            textValue: n2Interface.engineValue
            textColor: n2Interface.engineColor
            redBlink: n2Interface.engineRedBlink

            Component.onCompleted: {
                initModels(n2Interface);
            }
        }

        CircularGauge {
            id: n2GaugeRight
            startAngle: n2Interface.getStartAngle()
            endAngle: n2Interface.getEndAngle()
            radius: 70.5
            centerX: 322.5
            centerY: 217.5

            valueTextSize: 26
            
            minValue: n2Interface.getMinValue()
            maxValue: n2Interface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: n2Interface.engineAngle
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
            y: 145.5
            lineHeight: 0.8
            horizontalAlignment: Text.AlignHCenter
            color: "white"
            font.pixelSize: 26
            font.family: "Roboto Mono"
            font.bold: true
            text: n2Interface.getTitle() + '\n' + n2Interface.getUnitString()
        }
    }

    Item {
        id: ittGaugeParent

        CircularGauge {
            id: ittGaugeLeft
            startAngle: ittInterface.getStartAngle()
            endAngle: ittInterface.getEndAngle()
            radius: 70.5
            centerX: 97.5
            centerY: 352.5

            valueTextSize: 26
            
            minValue: ittInterface.getMinValue()
            maxValue: ittInterface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: ittInterface.engineAngle
            textValue: ittInterface.engineValue
            textColor: ittInterface.engineColor
            redBlink: ittInterface.engineRedBlink

            Component.onCompleted: {
                initModels(ittInterface);
            }
        }

        CircularGauge {
            id: ittGaugeRight
            startAngle: ittInterface.getStartAngle()
            endAngle: ittInterface.getEndAngle()
            radius: 70.5
            centerX: 322.5
            centerY: 352.5

            valueTextSize: 26
            
            minValue: ittInterface.getMinValue()
            maxValue: ittInterface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: ittInterface.engineAngle
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
            y: 280.5
            lineHeight: 0.8
            horizontalAlignment: Text.AlignHCenter
            color: "white"
            font.pixelSize: 26
            font.family: "Roboto Mono"
            font.bold: true
            text: ittInterface.getTitle() + '\n' + ittInterface.getUnitString()
        }
    }

    Loader {
        id: fuelTankGaugeLoader
    }

    VerticalDoubleGauge {
        id: fuelFlowGauge
        centerX: 322.5
        yTop: 480

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
        topBaseline: 660
    }

    VerticalDoubleGauge {
        id: oilTempGauge
        centerX: 120
        yTop: 750

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
        yTop: 750

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
        elevTop: 1027.5
    }


}
