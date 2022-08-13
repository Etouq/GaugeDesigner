#include "QmlAircraftDefinition.hpp"

void QmlAircraftDefinition::setName(const QString &name)
{
    if (d_definition.name != name)
    {
        d_definition.name = name;
        emit nameChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setMaxPower(double maxPower)
{
    if (std::abs(d_definition.maxPower - maxPower) > 1e-5)
    {
        d_definition.maxPower = maxPower;
        emit maxPowerChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setMaxTorque(double maxTorque)
{
    if (std::abs(d_definition.maxTorque - maxTorque) > 1e-5)
    {
        d_definition.maxTorque = maxTorque;
        emit maxTorqueChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setHasApu(bool hasApu)
{
    if (d_definition.hasApu != hasApu)
    {
        d_definition.hasApu = hasApu;
        emit hasApuChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setHasFlaps(bool hasFlaps)
{
    if (d_definition.hasFlaps != hasFlaps)
    {
        d_definition.hasFlaps = hasFlaps;
        emit hasFlapsChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setHasSpoilers(bool hasSpoilers)
{
    if (d_definition.hasSpoilers != hasSpoilers)
    {
        d_definition.hasSpoilers = hasSpoilers;
        emit hasSpoilersChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setHasElevatorTrim(bool hasElevatorTrim)
{
    if (d_definition.hasElevatorTrim != hasElevatorTrim)
    {
        d_definition.hasElevatorTrim = hasElevatorTrim;
        emit hasElevatorTrimChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setHasRudderTrim(bool hasRudderTrim)
{
    if (d_definition.hasRudderTrim != hasRudderTrim)
    {
        d_definition.hasRudderTrim = hasRudderTrim;
        emit hasRudderTrimChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setHasAileronTrim(bool hasAileronTrim)
{
    if (d_definition.hasAileronTrim != hasAileronTrim)
    {
        d_definition.hasAileronTrim = hasAileronTrim;
        emit hasAileronTrimChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setHasSecondaryTempGauge(bool hasSecondaryTempGauge)
{
    if (d_definition.hasSecondaryTempGauge != hasSecondaryTempGauge)
    {
        d_definition.hasSecondaryTempGauge = hasSecondaryTempGauge;
        emit hasSecondaryTempGaugeChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setNumEngines(int numEngines)
{
    if (d_definition.numEngines != numEngines)
    {
        d_definition.numEngines = numEngines;
        emit numEnginesChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setSingleTank(bool singleTank)
{
    if (d_definition.singleTank != singleTank)
    {
        d_definition.singleTank = singleTank;
        emit singleTankChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setLowLimit(float lowLimit)
{
    if (std::abs(d_definition.lowLimit - lowLimit) > 1e-5)
    {
        d_definition.lowLimit = lowLimit;
        emit lowLimitChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setFlapsBegin(float flapsBegin)
{
    if (std::abs(d_definition.flapsBegin - flapsBegin) > 1e-5)
    {
        d_definition.flapsBegin = flapsBegin;
        emit flapsBeginChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setFlapsEnd(float flapsEnd)
{
    if (std::abs(d_definition.flapsEnd - flapsEnd) > 1e-5)
    {
        d_definition.flapsEnd = flapsEnd;
        emit flapsEndChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setGreenBegin(float greenBegin)
{
    if (std::abs(d_definition.greenBegin - greenBegin) > 1e-5)
    {
        d_definition.greenBegin = greenBegin;
        emit greenBeginChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setGreenEnd(float greenEnd)
{
    if (std::abs(d_definition.greenEnd - greenEnd) > 1e-5)
    {
        d_definition.greenEnd = greenEnd;
        emit greenEndChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setYellowBegin(float yellowBegin)
{
    if (std::abs(d_definition.yellowBegin - yellowBegin) > 1e-5)
    {
        d_definition.yellowBegin = yellowBegin;
        emit yellowBeginChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setYellowEnd(float yellowEnd)
{
    if (std::abs(d_definition.yellowEnd - yellowEnd) > 1e-5)
    {
        d_definition.yellowEnd = yellowEnd;
        emit yellowEndChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setRedBegin(float redBegin)
{
    if (std::abs(d_definition.redBegin - redBegin) > 1e-5)
    {
        d_definition.redBegin = redBegin;
        emit redBeginChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setRedEnd(float redEnd)
{
    if (std::abs(d_definition.redEnd - redEnd) > 1e-5)
    {
        d_definition.redEnd = redEnd;
        emit redEndChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setHighLimit(float highLimit)
{
    if (std::abs(d_definition.highLimit - highLimit) > 1e-5)
    {
        d_definition.highLimit = highLimit;
        emit highLimitChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setNoColors(bool noColors)
{
    if (d_definition.noColors != noColors)
    {
        d_definition.noColors = noColors;
        emit noColorsChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setDynamicBarberpole(bool dynamicBarberpole)
{
    if (d_definition.dynamicBarberpole != dynamicBarberpole)
    {
        d_definition.dynamicBarberpole = dynamicBarberpole;
        emit dynamicBarberpoleChanged();

        checkForUnsavedChanges();
    }
}

void QmlAircraftDefinition::setHasLowLimit(bool hasLowLimit)
{
    if (d_definition.hasLowLimit != hasLowLimit)
    {
        d_definition.hasLowLimit = hasLowLimit;
        emit hasLowLimitChanged();

        checkForUnsavedChanges();
    }
}
void QmlAircraftDefinition::setHasFlapsSpeed(bool hasFlapsSpeed)
{
    if (d_definition.hasFlapsSpeed != hasFlapsSpeed)
    {
        d_definition.hasFlapsSpeed = hasFlapsSpeed;
        emit hasFlapsSpeedChanged();

        checkForUnsavedChanges();
    }
}
void QmlAircraftDefinition::setHasGreenSpeed(bool hasGreenSpeed)
{
    if (d_definition.hasGreenSpeed != hasGreenSpeed)
    {
        d_definition.hasGreenSpeed = hasGreenSpeed;
        emit hasGreenSpeedChanged();

        checkForUnsavedChanges();
    }
}
void QmlAircraftDefinition::setHasYellowSpeed(bool hasYellowSpeed)
{
    if (d_definition.hasYellowSpeed != hasYellowSpeed)
    {
        d_definition.hasYellowSpeed = hasYellowSpeed;
        emit hasYellowSpeedChanged();

        checkForUnsavedChanges();
    }
}
void QmlAircraftDefinition::setHasRedSpeed(bool hasRedSpeed)
{
    if (d_definition.hasRedSpeed != hasRedSpeed)
    {
        d_definition.hasRedSpeed = hasRedSpeed;
        emit hasRedSpeedChanged();

        checkForUnsavedChanges();
    }
}
void QmlAircraftDefinition::setHasHighLimit(bool hasHighLimit)
{
    if (d_definition.hasHighLimit != hasHighLimit)
    {
        d_definition.hasHighLimit = hasHighLimit;
        emit hasHighLimitChanged();

        checkForUnsavedChanges();
    }
}