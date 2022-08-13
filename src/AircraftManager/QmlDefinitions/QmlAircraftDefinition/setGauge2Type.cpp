#include "QmlAircraftDefinition.hpp"

void QmlAircraftDefinition::setGauge2Type(QmlSwitchingGaugeType gauge2Type)
{
    SwitchingGaugeType type = static_cast<SwitchingGaugeType>(gauge2Type);

    if (d_definition.gauge2Type == type || type == SwitchingGaugeType::NONE)
        return;

    if (d_definition.gauge1Type == type)
    {
        std::swap(d_definition.secondGauge, d_definition.firstGauge);
        std::swap(d_definition.gauge2Type, d_definition.gauge1Type);

        d_gauge2.changeDefinition(&d_definition.secondGauge, gaugeTypeToModel(d_definition.gauge2Type));
        d_gauge1.changeDefinition(&d_definition.firstGauge, gaugeTypeToModel(d_definition.gauge1Type));

        emit gauge2TypeChanged();
        emit gauge1TypeChanged();

        checkForUnsavedChanges();
        return;
    }
    if (d_definition.gauge3Type == type)
    {
        std::swap(d_definition.secondGauge, d_definition.thirdGauge);
        std::swap(d_definition.gauge2Type, d_definition.gauge3Type);

        d_gauge2.changeDefinition(&d_definition.secondGauge, gaugeTypeToModel(d_definition.gauge2Type));
        d_gauge3.changeDefinition(&d_definition.thirdGauge, gaugeTypeToModel(d_definition.gauge3Type));

        emit gauge2TypeChanged();
        emit gauge3TypeChanged();

        checkForUnsavedChanges();
        return;
    }
    if (d_definition.gauge4Type == type)
    {
        std::swap(d_definition.secondGauge, d_definition.fourthGauge);
        std::swap(d_definition.gauge2Type, d_definition.gauge4Type);

        d_gauge2.changeDefinition(&d_definition.secondGauge, gaugeTypeToModel(d_definition.gauge2Type));
        d_gauge4.changeDefinition(&d_definition.fourthGauge, gaugeTypeToModel(d_definition.gauge4Type));

        emit gauge2TypeChanged();
        emit gauge4TypeChanged();

        checkForUnsavedChanges();
        return;
    }

    d_definition.gauge2Type = type;
    d_gauge2.changeType(d_definition.gauge2Type,
                        d_definition.engineTempType,
                        gaugeTypeToModel(d_definition.gauge2Type));
    emit gauge2TypeChanged();

    checkForUnsavedChanges();
}
