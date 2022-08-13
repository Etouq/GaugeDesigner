#include "QmlAircraftDefinition.hpp"

void QmlAircraftDefinition::setGauge4Type(QmlSwitchingGaugeType gauge4Type)
{
    SwitchingGaugeType type = static_cast<SwitchingGaugeType>(gauge4Type);

    if (d_definition.gauge4Type == type)
        return;

    if (d_definition.gauge1Type == type)
    {
        std::swap(d_definition.fourthGauge, d_definition.firstGauge);
        std::swap(d_definition.gauge4Type, d_definition.gauge1Type);

        d_gauge4.changeDefinition(&d_definition.fourthGauge, gaugeTypeToModel(d_definition.gauge4Type));
        d_gauge1.changeDefinition(&d_definition.firstGauge, gaugeTypeToModel(d_definition.gauge1Type));

        emit gauge4TypeChanged();
        emit gauge1TypeChanged();

        checkForUnsavedChanges();
        return;
    }
    if (d_definition.gauge2Type == type)
    {
        std::swap(d_definition.fourthGauge, d_definition.secondGauge);
        std::swap(d_definition.gauge4Type, d_definition.gauge2Type);

        d_gauge4.changeDefinition(&d_definition.fourthGauge, gaugeTypeToModel(d_definition.gauge4Type));
        d_gauge2.changeDefinition(&d_definition.secondGauge, gaugeTypeToModel(d_definition.gauge2Type));

        emit gauge4TypeChanged();
        emit gauge2TypeChanged();

        checkForUnsavedChanges();
        return;
    }
    if (d_definition.gauge3Type == type && type != SwitchingGaugeType::NONE)
    {
        std::swap(d_definition.fourthGauge, d_definition.thirdGauge);
        std::swap(d_definition.gauge4Type, d_definition.gauge3Type);

        d_gauge4.changeDefinition(&d_definition.fourthGauge, gaugeTypeToModel(d_definition.gauge4Type));
        d_gauge3.changeDefinition(&d_definition.thirdGauge, gaugeTypeToModel(d_definition.gauge3Type));

        emit gauge4TypeChanged();
        emit gauge3TypeChanged();

        checkForUnsavedChanges();
        return;
    }

    d_definition.gauge4Type = type;
    d_gauge4.changeType(d_definition.gauge4Type,
                        d_definition.engineTempType,
                        gaugeTypeToModel(d_definition.gauge4Type));
    emit gauge4TypeChanged();

    checkForUnsavedChanges();
}
