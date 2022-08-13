#include "QmlAircraftDefinition.hpp"

#include <set>

void QmlAircraftDefinition::setType(QmlAircraftType type)
{
    AircraftType newType = static_cast<AircraftType>(type);
    if (d_definition.type == newType || newType == AircraftType::INVALID)
        return;

    d_definition.type = newType;
    emit typeChanged();

    std::set<SwitchingGaugeType> allowedTypes;
    std::set<TemperatureGaugeType> allowedTempTypes;

    if (d_definition.type == AircraftType::JET)
    {
        allowedTypes = { SwitchingGaugeType::N1,
                         SwitchingGaugeType::N2,
                         SwitchingGaugeType::ENGINE_TEMP,
                         SwitchingGaugeType::TORQUE };

        allowedTempTypes = { TemperatureGaugeType::ITT, TemperatureGaugeType::TIT, TemperatureGaugeType::EGT };
    }
    else if (d_definition.type == AircraftType::TURBOPROP)
    {
        allowedTypes = { SwitchingGaugeType::N1,
                         SwitchingGaugeType::N2,
                         SwitchingGaugeType::ENGINE_TEMP,
                         SwitchingGaugeType::PROP_RPM,
                         SwitchingGaugeType::TORQUE };
        allowedTempTypes = { TemperatureGaugeType::ITT, TemperatureGaugeType::TIT, TemperatureGaugeType::EGT };
    }
    else
    {
        allowedTypes = { SwitchingGaugeType::RPM,         SwitchingGaugeType::MANIFOLD_PRESSURE,
                         SwitchingGaugeType::ENGINE_TEMP, SwitchingGaugeType::TORQUE,
                         SwitchingGaugeType::PROP_RPM,    SwitchingGaugeType::POWER };

        allowedTempTypes = { TemperatureGaugeType::EGT, TemperatureGaugeType::CHT };
    }

    auto gauge1Node = allowedTypes.extract(d_definition.gauge1Type);
    auto gauge2Node = allowedTypes.extract(d_definition.gauge2Type);
    auto gauge3Node = allowedTypes.extract(d_definition.gauge3Type);
    auto gauge4Node = allowedTypes.extract(d_definition.gauge4Type);

    if (gauge1Node.empty())
        setGauge1Type(static_cast<QmlSwitchingGaugeType>(allowedTypes.extract(allowedTypes.begin()).value()));
    if (gauge2Node.empty())
        setGauge2Type(static_cast<QmlSwitchingGaugeType>(allowedTypes.extract(allowedTypes.begin()).value()));

    // gauges 3 and 4 are allowed to be unset
    if (gauge3Node.empty() && d_definition.gauge3Type != SwitchingGaugeType::NONE)
        setGauge3Type(static_cast<QmlSwitchingGaugeType>(allowedTypes.extract(allowedTypes.begin()).value()));
    if (gauge4Node.empty() && d_definition.gauge4Type != SwitchingGaugeType::NONE)
        setGauge4Type(static_cast<QmlSwitchingGaugeType>(allowedTypes.extract(allowedTypes.begin()).value()));


    auto engineTempNode = allowedTempTypes.extract(d_definition.engineTempType);
    auto secondaryNode = allowedTempTypes.extract(d_definition.secondaryTempType);

    if (engineTempNode.empty())
        setEngineTempType(
          static_cast<QmlTemperatureGaugeType>(allowedTempTypes.extract(allowedTempTypes.begin()).value()));
    if (secondaryNode.empty())
        setSecondaryTempType(
          static_cast<QmlTemperatureGaugeType>(allowedTempTypes.extract(allowedTempTypes.begin()).value()));


    checkForUnsavedChanges();
}
