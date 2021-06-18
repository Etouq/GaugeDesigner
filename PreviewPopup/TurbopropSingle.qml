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

    CircularGauge {
        id: n1Gauge
        startAngle: n1Interface.getStartAngle()
        endAngle: n1Interface.getEndAngle()
        radius: 90
        centerX: 105
        centerY: 105

        titleSize: 23
        unitSize: 23
        
        valueTextSize: 30
        
        arcWidth: 4
        colorZoneWidth: 8
        gradScaleFactor: 1.3

        minValue: n1Interface.getMinValue()
        maxValue: n1Interface.getMaxValue()

        title: n1Interface.getTitle()
        unit: n1Interface.getUnitString()

        cursorAngle: n1Interface.engineAngle
        textValue: n1Interface.engineValue
        textColor: n1Interface.engineColor
        redBlink: n1Interface.engineRedBlink

        Component.onCompleted: {
            initModels(n1Interface);
        }
    }

    CircularGauge {
        id: trqGauge
        startAngle: trqInterface.getStartAngle()
        endAngle: trqInterface.getEndAngle()
        radius: 90
        centerX: 315
        centerY: 105

        titleSize: 23
        unitSize: 23
        
        valueTextSize: 30
        
        arcWidth: 4
        colorZoneWidth: 8
        gradScaleFactor: 1.3

        minValue: trqInterface.getMinValue()
        maxValue: trqInterface.getMaxValue()

        title: trqInterface.getTitle()
        unit: trqInterface.getUnitString()

        cursorAngle: trqInterface.engineAngle
        textValue: trqInterface.engineValue
        textColor: trqInterface.engineColor
        redBlink: trqInterface.engineRedBlink

        Component.onCompleted: {
            initModels(trqInterface);
        }
    }

    CircularGauge {
        id: ittGauge
        startAngle: ittInterface.getStartAngle()
        endAngle: ittInterface.getEndAngle()
        radius: 90
        centerX: 105
        centerY: 315

        titleSize: 23
        unitSize: 23
        
        valueTextSize: 30
        
        arcWidth: 4
        colorZoneWidth: 8
        gradScaleFactor: 1.3

        minValue: ittInterface.getMinValue()
        maxValue: ittInterface.getMaxValue()

        title: ittInterface.getTitle()
        unit: ittInterface.getUnitString()

        cursorAngle: ittInterface.engineAngle
        textValue: ittInterface.engineValue
        textColor: ittInterface.engineColor
        redBlink: ittInterface.engineRedBlink

        Component.onCompleted: {
            initModels(ittInterface);
        }
    }

    CircularGauge {
        id: rpmGauge
        startAngle: rpmInterface.getStartAngle()
        endAngle: rpmInterface.getEndAngle()
        radius: 90
        centerX: 315
        centerY: 315

        titleSize: 23
        unitSize: 23
        
        valueTextSize: 30
        
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
