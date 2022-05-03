import QtQuick 2.15
import QtQuick.Shapes 1.15
import "gauges"

Item {
    anchors.fill: parent
    clip: true


    property int numTanks: 1

    Component.onCompleted: {
        fuelTankGaugeLoader.setSource(numTanks == 1 ? "qrc:/PreviewPopup/gauges/FuelSingleTankGauge.qml" : "qrc:/PreviewPopup/gauges/FuelDoubleTankGauge.qml", { "centerX": 105, "yTop": 445.5 });
        if (aircraftInterface.getHasSpoilers())
            flapsGaugeLoader.setSource("qrc:/PreviewPopup/gauges/FlapsSpoilersGauge.qml", { "yStart": 909.6 });
        else if(aircraftInterface.getHasFlaps())
            flapsGaugeLoader.setSource("qrc:/PreviewPopup/gauges/FlapsGauge.qml", { "yStart": 909.6 });
        else
            flapsGaugeLoader.setSource("");

    }

    Item {
        id: rpmGaugeParent

        CircularGauge {
            id: rpmGaugeLeft
            startAngle: rpmInterface.getStartAngle()
            endAngle: rpmInterface.getEndAngle()
            radius: 75
            centerX: 97.5
            centerY: 135

            valueTextSize: 26
            
            minValue: rpmInterface.getMinValue()
            maxValue: rpmInterface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: rpmInterface.engineAngle
            textValue: rpmInterface.engineValue
            textColor: rpmInterface.engineColor
            redBlink: rpmInterface.engineRedBlink

            Component.onCompleted: {
                initModels(rpmInterface);
            }
        }

        CircularGauge {
            id: rpmGaugeRight
            startAngle: rpmInterface.getStartAngle()
            endAngle: rpmInterface.getEndAngle()
            radius: 75
            centerX: 322.5
            centerY: 135

            valueTextSize: 26
            
            minValue: rpmInterface.getMinValue()
            maxValue: rpmInterface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: rpmInterface.engineAngle
            textValue: rpmInterface.engineValue
            textColor: rpmInterface.engineColor
            redBlink: rpmInterface.engineRedBlink

            Component.onCompleted: {
                initModels(rpmInterface);
            }
        }

        Text {
            anchors.horizontalCenter: parent.left
            anchors.horizontalCenterOffset: 210
            y: 60
            lineHeight: 0.8
            horizontalAlignment: Text.AlignHCenter
            color: "white"
            font.pixelSize: 26
            font.family: "Roboto Mono"
            font.bold: true
            text: rpmInterface.getTitle() + '\n' + rpmInterface.getUnitString()
        }
    }

    Item {
        id: secondGaugeParent

        CircularGauge {
            id: secondGaugeLeft
            startAngle: secondInterface.getStartAngle()
            endAngle: secondInterface.getEndAngle()
            radius: 75
            centerX: 97.5
            centerY: 315

            valueTextSize: 26
            
            minValue: secondInterface.getMinValue()
            maxValue: secondInterface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: secondInterface.engineAngle
            textValue: secondInterface.engineValue
            textColor: secondInterface.engineColor
            redBlink: secondInterface.engineRedBlink

            Component.onCompleted: {
                initModels(secondInterface);
            }
        }

        CircularGauge {
            id: secondGaugeRight
            startAngle: secondInterface.getStartAngle()
            endAngle: secondInterface.getEndAngle()
            radius: 75
            centerX: 322.5
            centerY: 315

            valueTextSize: 26
            
            minValue: secondInterface.getMinValue()
            maxValue: secondInterface.getMaxValue()

            title: ""
            unit: ""

            cursorAngle: secondInterface.engineAngle
            textValue: secondInterface.engineValue
            textColor: secondInterface.engineColor
            redBlink: secondInterface.engineRedBlink

            Component.onCompleted: {
                initModels(secondInterface);
            }
        }

        Text {
            anchors.horizontalCenter: parent.left
            anchors.horizontalCenterOffset: 210
            y: 240
            lineHeight: 0.8
            horizontalAlignment: Text.AlignHCenter
            color: "white"
            font.pixelSize: 26
            font.family: "Roboto Mono"
            font.bold: true
            text: secondInterface.getTitle() + '\n' + secondInterface.getUnitString()
        }
    }

    Loader {
        id: fuelTankGaugeLoader
    }

    VerticalDoubleGauge {
        id: fuelFlowGauge
        centerX: 315
        yTop: 445.5

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
        topBaseline: 622.5
    }

    VerticalDoubleGauge {
        id: oilTempGauge
        centerX: aircraftInterface.getHasEgt() ?  82.5 : 120
        yTop: 730.5

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
        yTop: 730.5

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
            yTop: 730.5

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
        elevTop: 1020
    }

}
