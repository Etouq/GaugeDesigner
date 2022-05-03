#include "aircraftinterface.hpp"

void AircraftInterface::setType(int value)
{
    def.type = static_cast<AircraftDefinition::AircraftType>(value);
    switch (def.type)
    {
        case AircraftDefinition::AircraftType::JET:
        {
            JetDefinition jetDef;
            def.currentType.setValue(jetDef);
            break;
        }
        case AircraftDefinition::AircraftType::PROP:
        {
            PropDefinition propDef;
            def.currentType.setValue(propDef);
            break;
        }
        case AircraftDefinition::AircraftType::TURBOPROP:
        {
            TurbopropDefinition turbopropDef;
            def.currentType.setValue(turbopropDef);
            break;
        }
        default:
            break;
    }
}

void AircraftInterface::setHasFlaps(bool value)
{
    def.hasFlaps = value;
}

void AircraftInterface::setHasSpoilers(bool value)
{
    def.hasSpoilers = value;
}

void AircraftInterface::setHasElevTrim(bool value)
{
    def.hasElevatorTrim = value;
}

void AircraftInterface::setHasRudderTrim(bool value)
{
    def.hasRudderTrim = value;
}

void AircraftInterface::setHasAileronTrim(bool value)
{
    def.hasAileronTrim = value;
}

void AircraftInterface::setNumEngines(int value)
{
    def.numEngines = value;
}

void AircraftInterface::setNumTanks(int value)
{
    def.numTanks = value;
}

void AircraftInterface::setLowLimit(float value)
{
    def.lowLimit = value;
}

void AircraftInterface::setFlapsBegin(float value)
{
    def.flapsBegin = value;
}

void AircraftInterface::setFlapsEnd(float value)
{
    def.flapsEnd = value;
}

void AircraftInterface::setGreenBegin(float value)
{
    def.greenBegin = value;
}

void AircraftInterface::setGreenEnd(float value)
{
    def.greenEnd = value;
}

void AircraftInterface::setYellowBegin(float value)
{
    def.yellowBegin = value;
}

void AircraftInterface::setYellowEnd(float value)
{
    def.yellowEnd = value;
}

void AircraftInterface::setRedBegin(float value)
{
    def.redBegin = value;
}

void AircraftInterface::setRedEnd(float value)
{
    def.redEnd = value;
}

void AircraftInterface::setHighLimit(float value)
{
    def.highLimit = value;
}

void AircraftInterface::setNoColors(bool value)
{
    def.noColors = value;
}

void AircraftInterface::setDynamicBarberpole(bool value)
{
    def.dynamicBarberpole = value;
}

void AircraftInterface::setHasApu(bool value)
{
    if (def.type != AircraftDefinition::AircraftType::JET)
        return;

    JetDefinition jetDef = def.currentType.value<JetDefinition>();
    jetDef.hasApu = value;
    def.currentType.setValue(jetDef);
}

void AircraftInterface::setEgtReplacesItt(bool value)
{
    if (def.type != AircraftDefinition::AircraftType::JET)
        return;

    JetDefinition jetDef = def.currentType.value<JetDefinition>();
    jetDef.egtReplacesItt = value;
    def.currentType.setValue(jetDef);
}

void AircraftInterface::setHasEgt(bool value)
{
    if (def.type == AircraftDefinition::AircraftType::PROP)
    {
        PropDefinition propDef = def.currentType.value<PropDefinition>();
        propDef.hasEgt = value;
        def.currentType.setValue(propDef);
    }
    if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
    {
        TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
        turbopropDef.hasEgt = value;
        def.currentType.setValue(turbopropDef);
    }
}

void AircraftInterface::setUsePropRpm(bool value)
{
    if (def.type == AircraftDefinition::AircraftType::PROP)
    {
        PropDefinition propDef = def.currentType.value<PropDefinition>();
        propDef.usePropRpm = value;
        def.currentType.setValue(propDef);
    }
    if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
    {
        TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
        turbopropDef.usePropRpm = value;
        def.currentType.setValue(turbopropDef);
    }
}

void AircraftInterface::setSecondIsLoad(bool value)
{
    if (def.type != AircraftDefinition::AircraftType::PROP)
        return;
    PropDefinition propDef = def.currentType.value<PropDefinition>();
    propDef.secondIsLoad = value;
    def.currentType.setValue(propDef);
}

void AircraftInterface::setMaxHp(double value)
{
    if (def.type != AircraftDefinition::AircraftType::PROP)
        return;
    PropDefinition propDef = def.currentType.value<PropDefinition>();
    propDef.maxHp = value;
    def.currentType.setValue(propDef);
}
