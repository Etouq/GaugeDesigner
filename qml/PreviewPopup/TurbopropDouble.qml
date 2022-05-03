import QtQuick 2.15
import QtQuick.Shapes 1.15
import "gauges"

Item {
    anchors.fill: parent
    clip: true

    property int numTanks: 1

    Component.onCompleted: {
        fuelTankGaugeLoader.setSource(numTanks == 1 ? "qrc:/PreviewPopup/gauges/FuelSingleTankGauge.qml" : "qrc:/PreviewPopup/gauges/FuelDoubleTankGauge.qml", { "centerX": 97.5, "yTop": 499.5 });
        if (aircraftInterface.getHasSpoilers())
            flapsGaugeLoader.setSource("qrc:/PreviewPopup/gauges/FlapsSpoilersGauge.qml", { "yStart": 939.6 });
        else if(aircraftInterface.getHasFlaps())
            flapsGaugeLoader.setSource("qrc:/PreviewPopup/gauges/FlapsGauge.qml", { "yStart": 939.6 });
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
        id: trqGaugeParent

        CircularGauge {
            id: trqGaugeLeft
            startAngle: trqInterface.getStartAngle()
            endAngle: trqInterface.getEndAngle()
            radius: 70.5
            centerX: 97.5
            centerY: 217.5

            valueTextSize: 26
            
            minValue: trqInterface.getMinValue()
            maxValue: trqInterface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: trqInterface.engineAngle
            textValue: trqInterface.engineValue
            textColor: trqInterface.engineColor
            redBlink: trqInterface.engineRedBlink

            Component.onCompleted: {
                initModels(trqInterface);
            }
        }

        CircularGauge {
            id: trqGaugeRight
            startAngle: trqInterface.getStartAngle()
            endAngle: trqInterface.getEndAngle()
            radius: 70.5
            centerX: 322.5
            centerY: 217.5

            valueTextSize: 26
            
            minValue: trqInterface.getMinValue()
            maxValue: trqInterface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: trqInterface.engineAngle
            textValue: trqInterface.engineValue
            textColor: trqInterface.engineColor
            redBlink: trqInterface.engineRedBlink

            Component.onCompleted: {
                initModels(trqInterface);
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
            text: trqInterface.getTitle() + '\n' + trqInterface.getUnitString()
        }
    }

    VerticalDoubleGauge {
        id: ittGauge
        centerX: 97.5
        yTop: 318

        extraWide: ittInterface.needsExtraWide()

        minValue: ittInterface.getMinValue()
        maxValue: ittInterface.getMaxValue()

        title: ittInterface.getTitle()
        unit: ittInterface.getUnitString()

        leftCursorTransformValue: ittInterface.engineTransformValue
        leftTextValue: ittInterface.engineValue
        leftTextColor: ittInterface.engineColor
        leftRedBlink: ittInterface.engineRedBlink

        rightCursorTransformValue: ittInterface.engineTransformValue
        rightTextValue: ittInterface.engineValue
        rightTextColor: ittInterface.engineColor
        rightRedBlink: ittInterface.engineRedBlink

        Component.onCompleted: {
            initModels(ittInterface);
        }
    }

    VerticalDoubleGauge {
        id: rpmGauge
        centerX: 322.5
        yTop: 318

        extraWide: rpmInterface.needsExtraWide()

        minValue: rpmInterface.getMinValue()
        maxValue: rpmInterface.getMaxValue()

        title: rpmInterface.getTitle()
        unit: rpmInterface.getUnitString()

        leftCursorTransformValue: rpmInterface.engineTransformValue
        leftTextValue: rpmInterface.engineValue
        leftTextColor: rpmInterface.engineColor
        leftRedBlink: rpmInterface.engineRedBlink

        rightCursorTransformValue: rpmInterface.engineTransformValue
        rightTextValue: rpmInterface.engineValue
        rightTextColor: rpmInterface.engineColor
        rightRedBlink: rpmInterface.engineRedBlink

        Component.onCompleted: {
            initModels(rpmInterface);
        }
    }

    Loader {
        id: fuelTankGaugeLoader
    }

    VerticalDoubleGauge {
        id: fuelFlowGauge
        centerX: 322.5
        yTop: 499.5

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
        topBaseline: 675
    }

    VerticalDoubleGauge {
        id: oilTempGauge
        centerX: aircraftInterface.getHasEgt() ?  82.5 : 120
        yTop: 765

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
        centerX: aircraftInterface.getHasEgt() ?  337.5 : 300
        yTop: 765

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

    Component {
        id: egtGaugeComp
        VerticalDoubleGauge {
            centerX: 210
            yTop: 765

            extraWide: egtInterface.needsExtraWide()

            minValue: egtInterface.getMinValue()
            maxValue: egtInterface.getMaxValue()

            title: egtInterface.getTitle()
            unit: egtInterface.getUnitString()

            leftCursorTransformValue: egtInterface.engineTransformValue
            leftTextValue: egtInterface.engineValue
            leftTextColor: egtInterface.engineColor
            leftRedBlink: egtInterface.engineRedBlink

            rightCursorTransformValue: egtInterface.engineTransformValue
            rightTextValue: egtInterface.engineValue
            rightTextColor: egtInterface.engineColor
            rightRedBlink: egtInterface.engineRedBlink

            Component.onCompleted: {
                initModels(egtInterface);
            }
        }
    }

    Loader {
        id: egtLoader
        sourceComponent: aircraftInterface.getHasEgt() ? egtGaugeComp : undefined
    }

    Loader {
        id: flapsGaugeLoader
    }

    TrimGauges {
        elevTop: 1042.5
    }


}
