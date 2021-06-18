import QtQuick 2.15
import QtQuick.Shapes 1.15
import "gauges"


Item {
    anchors.fill: parent
    clip: true

    property int numTanks: 2

    Component.onCompleted: {
        fuelTankGaugeLoader.setSource(numTanks == 1 ? "qrc:/PreviewPopup/gauges/FuelSingleTankGauge.qml" : "qrc:/PreviewPopup/gauges/FuelDoubleTankGauge.qml", { "centerX": 105, "yTop": 445.5 });
        if (aircraftInterface.getHasSpoilers()) {
            flapsGaugeLoader.active = true;
            flapsGaugeLoader.setSource("qrc:/PreviewPopup/gauges/FlapsSpoilersGauge.qml", { "yStart": 909.6 });
        }
        else if(aircraftInterface.getHasFlaps()) {
            flapsGaugeLoader.active = true;
            flapsGaugeLoader.setSource("qrc:/PreviewPopup/gauges/FlapsGauge.qml", { "yStart": 909.6 });
        }
        else {
            flapsGaugeLoader.setSource("");
            flapsGaugeLoader.active = false;
        }


    }



    CircularGauge {
        id: rpmGauge
        startAngle: rpmInterface.getStartAngle()
        endAngle: rpmInterface.getEndAngle()
        radius: 120
        centerX: 210
        centerY: 135

        titleSize: 30
        unitSize: 30
        
        valueTextSize: 38
        
        arcWidth: 4
        colorZoneWidth: 8
        gradScaleFactor: 1.3

        minValue: rpmInterface.getMinValue()
        maxValue: rpmInterface.getMaxValue()

        title: rpmInterface.getTitle()
        unit: rpmInterface.getUnitString()

        cursorAngle: rpmInterface.engineAngle
        textValue: rpmInterface.engineValue
        textColor: rpmInterface.engineColor
        redBlink: rpmInterface.engineRedBlink

        Component.onCompleted: {
            initModels(rpmInterface);
        }
    }

    CircularGauge {
        id: secondGauge
        startAngle: secondInterface.getStartAngle()
        endAngle: secondInterface.getEndAngle()
        radius: 120
        centerX: 210
        centerY: 322.5

        titleSize: 30
        unitSize: 30
        
        valueTextSize: 38
        
        minValue: secondInterface.getMinValue()
        maxValue: secondInterface.getMaxValue()

        arcWidth: 4
        colorZoneWidth: 8
        gradScaleFactor: 1.3

        title: secondInterface.getTitle()
        unit: secondInterface.getUnitString()

        cursorAngle: secondInterface.engineAngle
        textValue: secondInterface.engineValue
        textColor: secondInterface.engineColor
        redBlink: secondInterface.engineRedBlink

        Component.onCompleted: {
            initModels(secondInterface);
        }
    }

    Loader {
        id: fuelTankGaugeLoader
    }

    VerticalGauge {
        id: fuelFlowGauge
        centerX: 315
        yTop: 445.5

        valuePos: 1

        minValue: fuelFlowInterface.getMinValue()
        maxValue: fuelFlowInterface.getMaxValue()

        title: fuelFlowInterface.getTitle()
        unit: fuelFlowInterface.getUnitString()

        cursorTransformValue: fuelFlowInterface.engineTransformValue
        textValue: fuelFlowInterface.engineValue
        textColor: fuelFlowInterface.engineColor
        redBlink: fuelFlowInterface.engineRedBlink


        Component.onCompleted: {
            initModels(fuelFlowInterface);
        }
    }

    FuelText {
        id: fuelTextGauge
        topBaseline: 622.5
    }

    VerticalGauge {
        id: oilTempGauge
        centerX: aircraftInterface.getHasEgt() ?  82.5 : 120
        yTop: 730.5

        valuePos: 2

        minValue: oilTempInterface.getMinValue()
        maxValue: oilTempInterface.getMaxValue()

        title: oilTempInterface.getTitle()
        unit: oilTempInterface.getUnitString()

        cursorTransformValue: oilTempInterface.engineTransformValue
        textValue: oilTempInterface.engineValue
        textColor: oilTempInterface.engineColor
        redBlink: oilTempInterface.engineRedBlink

        Component.onCompleted: {
            initModels(oilTempInterface);
        }
    }

    VerticalGauge {
        id: oilPressGauge
        centerX: aircraftInterface.getHasEgt() ?  337.5 : 300
        yTop: 730.5

        valuePos: 2

        minValue: oilPressInterface.getMinValue()
        maxValue: oilPressInterface.getMaxValue()

        title: oilPressInterface.getTitle()
        unit: oilPressInterface.getUnitString()

        cursorTransformValue: oilPressInterface.engineTransformValue
        textValue: oilPressInterface.engineValue
        textColor: oilPressInterface.engineColor
        redBlink: oilPressInterface.engineRedBlink

        Component.onCompleted: {
            initModels(oilPressInterface);
        }
    }

    Component {
        id: egtGaugeComp
        VerticalGauge {
            centerX: 210
            yTop: 730.5

            valuePos: 2

            minValue: egtInterface.getMinValue()
            maxValue: egtInterface.getMaxValue()

            title: egtInterface.getTitle()
            unit: egtInterface.getUnitString()

            cursorTransformValue: egtInterface.engineTransformValue
            textValue: egtInterface.engineValue
            textColor: egtInterface.engineColor
            redBlink: egtInterface.engineRedBlink

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
