#include "QmlAircraftDefinition.hpp"

QmlAircraftType QmlAircraftDefinition::type() const
{
    return static_cast<QmlAircraftType>(d_definition.type);
}

const QString &QmlAircraftDefinition::name() const
{
    return d_definition.name;
}

QmlSwitchingGaugeType QmlAircraftDefinition::gauge1Type() const
{
    return static_cast<QmlSwitchingGaugeType>(d_definition.gauge1Type);
}

QmlSwitchingGaugeType QmlAircraftDefinition::gauge2Type() const
{
    return static_cast<QmlSwitchingGaugeType>(d_definition.gauge2Type);
}

QmlSwitchingGaugeType QmlAircraftDefinition::gauge3Type() const
{
    return static_cast<QmlSwitchingGaugeType>(d_definition.gauge3Type);
}

QmlSwitchingGaugeType QmlAircraftDefinition::gauge4Type() const
{
    return static_cast<QmlSwitchingGaugeType>(d_definition.gauge4Type);
}

QmlTemperatureGaugeType QmlAircraftDefinition::engineTempType() const
{
    return static_cast<QmlTemperatureGaugeType>(d_definition.engineTempType);
}

double QmlAircraftDefinition::maxPower() const
{
    return d_definition.maxPower;
}

double QmlAircraftDefinition::maxTorque() const
{
    return d_definition.maxTorque;
}

bool QmlAircraftDefinition::hasApu() const
{
    return d_definition.hasApu;
}

bool QmlAircraftDefinition::hasFlaps() const
{
    return d_definition.hasFlaps;
}

bool QmlAircraftDefinition::hasSpoilers() const
{
    return d_definition.hasSpoilers;
}

bool QmlAircraftDefinition::hasElevatorTrim() const
{
    return d_definition.hasElevatorTrim;
}

bool QmlAircraftDefinition::hasRudderTrim() const
{
    return d_definition.hasRudderTrim;
}

bool QmlAircraftDefinition::hasAileronTrim() const
{
    return d_definition.hasAileronTrim;
}

bool QmlAircraftDefinition::hasSecondaryTempGauge() const
{
    return d_definition.hasSecondaryTempGauge;
}

QmlTemperatureGaugeType QmlAircraftDefinition::secondaryTempType() const
{
    return static_cast<QmlTemperatureGaugeType>(d_definition.secondaryTempType);
}

int QmlAircraftDefinition::numEngines() const
{
    return d_definition.numEngines;
}

bool QmlAircraftDefinition::singleTank() const
{
    return d_definition.singleTank;
}

float QmlAircraftDefinition::lowLimit() const
{
    return d_definition.lowLimit;
}

float QmlAircraftDefinition::flapsBegin() const
{
    return d_definition.flapsBegin;
}

float QmlAircraftDefinition::flapsEnd() const
{
    return d_definition.flapsEnd;
}

float QmlAircraftDefinition::greenBegin() const
{
    return d_definition.greenBegin;
}

float QmlAircraftDefinition::greenEnd() const
{
    return d_definition.greenEnd;
}

float QmlAircraftDefinition::yellowBegin() const
{
    return d_definition.yellowBegin;
}

float QmlAircraftDefinition::yellowEnd() const
{
    return d_definition.yellowEnd;
}

float QmlAircraftDefinition::redBegin() const
{
    return d_definition.redBegin;
}

float QmlAircraftDefinition::redEnd() const
{
    return d_definition.redEnd;
}

float QmlAircraftDefinition::highLimit() const
{
    return d_definition.highLimit;
}

bool QmlAircraftDefinition::noColors() const
{
    return d_definition.noColors;
}

bool QmlAircraftDefinition::dynamicBarberpole() const
{
    return d_definition.dynamicBarberpole;
}

bool QmlAircraftDefinition::hasLowLimit() const
{
    return d_definition.hasLowLimit;
}

bool QmlAircraftDefinition::hasFlapsSpeed() const
{
    return d_definition.hasFlapsSpeed;
}

bool QmlAircraftDefinition::hasGreenSpeed() const
{
    return d_definition.hasGreenSpeed;
}

bool QmlAircraftDefinition::hasYellowSpeed() const
{
    return d_definition.hasYellowSpeed;
}

bool QmlAircraftDefinition::hasRedSpeed() const
{
    return d_definition.hasRedSpeed;
}

bool QmlAircraftDefinition::hasHighLimit() const
{
    return d_definition.hasHighLimit;
}

bool QmlAircraftDefinition::unsavedChanges() const
{
    return d_unsavedChanges;
}