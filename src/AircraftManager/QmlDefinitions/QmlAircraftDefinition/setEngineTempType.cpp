#include "QmlAircraftDefinition.hpp"

void QmlAircraftDefinition::setEngineTempType(QmlTemperatureGaugeType engineTempType)
{
    TemperatureGaugeType type = static_cast<TemperatureGaugeType>(engineTempType);
    if (d_definition.engineTempType == type)
        return;

    d_definition.engineTempType = type;

    if (d_definition.gauge1Type == SwitchingGaugeType::ENGINE_TEMP)
    {
        d_gauge1.changeType(d_definition.engineTempType);
        emit engineTempTypeChanged();

        checkForUnsavedChanges();
    }
    else if (d_definition.gauge2Type == SwitchingGaugeType::ENGINE_TEMP)
    {
        d_gauge2.changeType(d_definition.engineTempType);
        emit engineTempTypeChanged();

        checkForUnsavedChanges();
    }
    else if (d_definition.gauge3Type == SwitchingGaugeType::ENGINE_TEMP)
    {
        d_gauge3.changeType(d_definition.engineTempType);
        emit engineTempTypeChanged();

        checkForUnsavedChanges();
    }
    else if (d_definition.gauge4Type == SwitchingGaugeType::ENGINE_TEMP)
    {
        d_gauge4.changeType(d_definition.engineTempType);
        emit engineTempTypeChanged();

        checkForUnsavedChanges();
    }
}
