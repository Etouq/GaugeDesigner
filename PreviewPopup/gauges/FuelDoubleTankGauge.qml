import QtQuick 2.15

VerticalDoubleGauge {
    centerX: 0
    yTop: 0

    extraWide: fuelQtyInterface.needsExtraWide()

    minValue: fuelQtyInterface.getMinValue()
    maxValue: fuelQtyInterface.getMaxValue()

    title: fuelQtyInterface.getTitle()
    unit: fuelQtyInterface.getUnitString()

    leftCursorTransformValue: fuelQtyInterface.engineTransformValue
    leftTextValue: fuelQtyInterface.engineValue
    leftTextColor: fuelQtyInterface.engineColor
    leftRedBlink: fuelQtyInterface.engineRedBlink

    rightCursorTransformValue: fuelQtyInterface.engineTransformValue
    rightTextValue: fuelQtyInterface.engineValue
    rightTextColor: fuelQtyInterface.engineColor
    rightRedBlink: fuelQtyInterface.engineRedBlink

    Component.onCompleted: {
        initModels(fuelQtyInterface);
    }
}
