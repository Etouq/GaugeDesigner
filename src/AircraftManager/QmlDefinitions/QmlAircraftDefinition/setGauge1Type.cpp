#include "QmlAircraftDefinition.hpp"

void QmlAircraftDefinition::setGauge1Type(QmlSwitchingGaugeType gauge1Type)
{
    SwitchingGaugeType type = static_cast<SwitchingGaugeType>(gauge1Type);

    if (d_definition.gauge1Type == type || type == SwitchingGaugeType::NONE)
        return;

    if (d_definition.gauge2Type == type)
    {
        std::swap(d_definition.firstGauge, d_definition.secondGauge);
        std::swap(d_definition.gauge1Type, d_definition.gauge2Type);

        d_gauge1.changeDefinition(&d_definition.firstGauge, gaugeTypeToModel(d_definition.gauge1Type));
        d_gauge2.changeDefinition(&d_definition.secondGauge, gaugeTypeToModel(d_definition.gauge2Type));

        emit gauge1TypeChanged();
        emit gauge2TypeChanged();

        checkForUnsavedChanges();
        return;
    }
    if (d_definition.gauge3Type == type)
    {
        std::swap(d_definition.firstGauge, d_definition.thirdGauge);
        std::swap(d_definition.gauge1Type, d_definition.gauge3Type);

        d_gauge1.changeDefinition(&d_definition.firstGauge, gaugeTypeToModel(d_definition.gauge1Type));
        d_gauge3.changeDefinition(&d_definition.thirdGauge, gaugeTypeToModel(d_definition.gauge3Type));

        emit gauge1TypeChanged();
        emit gauge3TypeChanged();

        checkForUnsavedChanges();
        return;
    }
    if (d_definition.gauge4Type == type)
    {
        std::swap(d_definition.firstGauge, d_definition.fourthGauge);
        std::swap(d_definition.gauge1Type, d_definition.gauge4Type);

        d_gauge1.changeDefinition(&d_definition.firstGauge, gaugeTypeToModel(d_definition.gauge1Type));
        d_gauge4.changeDefinition(&d_definition.fourthGauge, gaugeTypeToModel(d_definition.gauge4Type));

        emit gauge1TypeChanged();
        emit gauge4TypeChanged();

        checkForUnsavedChanges();
        return;
    }

    d_definition.gauge1Type = type;
    d_gauge1.changeType(d_definition.gauge1Type,
                        d_definition.engineTempType,
                        gaugeTypeToModel(d_definition.gauge1Type));
    emit gauge1TypeChanged();

    checkForUnsavedChanges();
}
