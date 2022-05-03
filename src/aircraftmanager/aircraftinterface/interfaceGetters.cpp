#include "aircraftinterface.hpp"

int AircraftInterface::getType() const
{
    return static_cast<int>(def.type);
}

QString AircraftInterface::getName() const
{
    return def.name;
}

QString AircraftInterface::getImagePath() const
{
    return imagePath;
}

bool AircraftInterface::getHasFlaps() const
{
    return def.hasFlaps;
}

bool AircraftInterface::getHasSpoilers() const
{
    return def.hasSpoilers;
}

bool AircraftInterface::getHasElevTrim() const
{
    return def.hasElevatorTrim;
}

bool AircraftInterface::getHasRudderTrim() const
{
    return def.hasRudderTrim;
}

bool AircraftInterface::getHasAileronTrim() const
{
    return def.hasAileronTrim;
}

int AircraftInterface::getNumEngines() const
{
    return def.numEngines;
}

int AircraftInterface::getNumTanks() const
{
    return def.numTanks;
}

float AircraftInterface::getLowLimit() const
{
    return def.lowLimit;
}

float AircraftInterface::getFlapsBegin() const
{
    return def.flapsBegin;
}

float AircraftInterface::getFlapsEnd() const
{
    return def.flapsEnd;
}

float AircraftInterface::getGreenBegin() const
{
    return def.greenBegin;
}

float AircraftInterface::getGreenEnd() const
{
    return def.greenEnd;
}

float AircraftInterface::getYellowBegin() const
{
    return def.yellowBegin;
}

float AircraftInterface::getYellowEnd() const
{
    return def.yellowEnd;
}

float AircraftInterface::getRedBegin() const
{
    return def.redBegin;
}

float AircraftInterface::getRedEnd() const
{
    return def.redEnd;
}

float AircraftInterface::getHighLimit() const
{
    return def.highLimit;
}

bool AircraftInterface::getNoColors() const
{
    return def.noColors;
}

bool AircraftInterface::getDynamicBarberpole() const
{
    return def.dynamicBarberpole;
}

bool AircraftInterface::getHasApu() const
{
    if (def.type != AircraftDefinition::AircraftType::JET)
        return false;

    JetDefinition jetDef = def.currentType.value<JetDefinition>();
    return jetDef.hasApu;
}

bool AircraftInterface::getEgtReplacesItt() const
{
    if (def.type != AircraftDefinition::AircraftType::JET)
        return false;

    JetDefinition jetDef = def.currentType.value<JetDefinition>();
    return jetDef.egtReplacesItt;
}

bool AircraftInterface::getHasEgt() const
{
    if (def.type == AircraftDefinition::AircraftType::PROP)
    {
        PropDefinition propDef = def.currentType.value<PropDefinition>();
        return propDef.hasEgt;
    }
    if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
    {
        TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
        return turbopropDef.hasEgt;
    }
    return false;
}

bool AircraftInterface::getUsePropRpm() const
{
    if (def.type == AircraftDefinition::AircraftType::PROP)
    {
        PropDefinition propDef = def.currentType.value<PropDefinition>();
        return propDef.usePropRpm;
    }
    if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
    {
        TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
        return turbopropDef.usePropRpm;
    }
    return false;
}

bool AircraftInterface::getSecondIsLoad() const
{
    if (def.type != AircraftDefinition::AircraftType::PROP)
        return false;
    PropDefinition propDef = def.currentType.value<PropDefinition>();
    return propDef.secondIsLoad;
}

double AircraftInterface::getMaxHp() const
{
    if (def.type != AircraftDefinition::AircraftType::PROP)
        return 1.0;
    PropDefinition propDef = def.currentType.value<PropDefinition>();
    return propDef.maxHp;
}
