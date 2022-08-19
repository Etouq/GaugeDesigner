#include "QmlAircraftDefinition.hpp"

void QmlAircraftDefinition::setGauge3Type(QmlSwitchingGaugeType gauge3Type)
{
    SwitchingGaugeType type = static_cast<SwitchingGaugeType>(gauge3Type);

    if (d_definition.gauge3Type == type)
        return;

    if (d_definition.gauge1Type == type)
    {
        std::swap(d_definition.thirdGauge, d_definition.firstGauge);
        std::swap(d_definition.gauge3Type, d_definition.gauge1Type);

        d_gauge3.changeDefinition(&d_definition.thirdGauge, gaugeTypeToModel(d_definition.gauge3Type));
        d_gauge1.changeDefinition(&d_definition.firstGauge, gaugeTypeToModel(d_definition.gauge1Type));

        emit gauge3TypeChanged();
        emit gauge1TypeChanged();

        checkForUnsavedChanges();
        return;
    }
    if (d_definition.gauge2Type == type)
    {
        std::swap(d_definition.thirdGauge, d_definition.secondGauge);
        std::swap(d_definition.gauge3Type, d_definition.gauge2Type);

        d_gauge3.changeDefinition(&d_definition.thirdGauge, gaugeTypeToModel(d_definition.gauge3Type));
        d_gauge2.changeDefinition(&d_definition.secondGauge, gaugeTypeToModel(d_definition.gauge2Type));

        emit gauge3TypeChanged();
        emit gauge2TypeChanged();

        checkForUnsavedChanges();
        return;
    }
    if (d_definition.gauge4Type == type && type != SwitchingGaugeType::NONE)
    {
        std::swap(d_definition.thirdGauge, d_definition.fourthGauge);
        std::swap(d_definition.gauge3Type, d_definition.gauge4Type);

        d_gauge3.changeDefinition(&d_definition.thirdGauge, gaugeTypeToModel(d_definition.gauge3Type));
        d_gauge4.changeDefinition(&d_definition.fourthGauge, gaugeTypeToModel(d_definition.gauge4Type));

        emit gauge3TypeChanged();
        emit gauge4TypeChanged();

        checkForUnsavedChanges();
        return;
    }

    d_definition.gauge3Type = type;
    d_gauge3.changeType(d_definition.gauge3Type,
                        d_definition.engineTempType,
                        gaugeTypeToModel(d_definition.gauge3Type));
    emit gauge3TypeChanged();

    if (type == SwitchingGaugeType::NONE && d_definition.gauge4Type != SwitchingGaugeType::NONE)
    {
        d_definition.gauge4Type = SwitchingGaugeType::NONE;
        d_gauge4.changeType(d_definition.gauge4Type,
                            d_definition.engineTempType,
                            gaugeTypeToModel(d_definition.gauge4Type));
        emit gauge4TypeChanged();
    }

    checkForUnsavedChanges();
}
