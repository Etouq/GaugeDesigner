import QtQuick 2.15
import QtQuick.Shapes 1.15
import "gauges"


Item {
    anchors.fill: parent
    clip: true

    //property real scaleFactor: 1
    property int numTanks: 2

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
        radius: 120
        centerX: 210
        centerY: 135

        titleSize: 30
        unitSize: 30
        
        valueTextSize: 38
        
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
        id: n2Gauge
        startAngle: n2Interface.getStartAngle()
        endAngle: n2Interface.getEndAngle()
        radius: 90
        centerX: 105
        centerY: 315

        titleSize: 23
        unitSize: 23
        
        valueTextSize: 30
        
        minValue: n2Interface.getMinValue()
        maxValue: n2Interface.getMaxValue()

        arcWidth: 3.5
        colorZoneWidth: 7
        gradScaleFactor: 1.2

        title: n2Interface.getTitle()
        unit: n2Interface.getUnitString()

        cursorAngle: n2Interface.engineAngle
        textValue: n2Interface.engineValue
        textColor: n2Interface.engineColor
        redBlink: n2Interface.engineRedBlink

        Component.onCompleted: {
            initModels(n2Interface);
        }
    }

    CircularGauge {
        id: ittGauge
        startAngle: ittInterface.getStartAngle()
        endAngle: ittInterface.getEndAngle()
        radius: 90
        centerX: 315
        centerY: 315

        titleSize: 23
        unitSize: 23
        
        valueTextSize: 30
        
        minValue: ittInterface.getMinValue()
        maxValue: ittInterface.getMaxValue()

        arcWidth: 3.5
        colorZoneWidth: 7
        gradScaleFactor: 1.2

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
        centerX: 120
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
        centerX: 300
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

    Loader {
        id: flapsGaugeLoader
    }

    TrimGauges {
        elevTop: 1020
    }

}
