import QtQuick 2.15

VerticalGauge {
    centerX: 0
    yTop: 0
    valuePos: 1

    minValue: fuelQtyInterface.getMinValue()
    maxValue: fuelQtyInterface.getMaxValue()

    title: fuelQtyInterface.getTitle()
    unit: fuelQtyInterface.getUnitString()

    cursorTransformValue: fuelQtyInterface.engineTransformValue
    textValue: fuelQtyInterface.engineValue
    textColor: fuelQtyInterface.engineColor
    redBlink: fuelQtyInterface.engineRedBlink

    Component.onCompleted: {
        initModels(fuelQtyInterface);
    }
}
