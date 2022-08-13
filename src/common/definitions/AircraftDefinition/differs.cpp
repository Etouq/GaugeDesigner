#include "AircraftDefinition.hpp"

namespace definitions
{

bool AircraftDefinition::operator!=(const AircraftDefinition &rhs) const
{
    // invalid aircraft are 'equal' (both in invalid state)
    if (type == rhs.type && type == AircraftType::INVALID)
        return false;

    if (type != rhs.type
      || name != rhs.name

      || gauge1Type != rhs.gauge1Type
      || gauge2Type != rhs.gauge2Type
      || gauge3Type != rhs.gauge3Type
      || gauge4Type != rhs.gauge4Type

      || hasApu != rhs.hasApu

      || hasFlaps != rhs.hasFlaps

      || hasElevatorTrim != rhs.hasElevatorTrim
      || hasRudderTrim != rhs.hasRudderTrim
      || hasAileronTrim != rhs.hasAileronTrim

      || hasSecondaryTempGauge != rhs.hasSecondaryTempGauge

      || numEngines != rhs.numEngines
      || singleTank != rhs.singleTank

      || noColors != rhs.noColors)
        return true;

    if (hasFlaps && hasSpoilers != rhs.hasSpoilers)
        return true;

    if ((gauge1Type == SwitchingGaugeType::ENGINE_TEMP
      || gauge2Type == SwitchingGaugeType::ENGINE_TEMP
      || gauge3Type == SwitchingGaugeType::ENGINE_TEMP
      || gauge4Type == SwitchingGaugeType::ENGINE_TEMP)
      && engineTempType != rhs.engineTempType)
        return true;


    if (((gauge1Type == SwitchingGaugeType::POWER && firstGauge.unit == Units::PERCENT)
      || (gauge2Type == SwitchingGaugeType::POWER && secondGauge.unit == Units::PERCENT)
      || (gauge3Type == SwitchingGaugeType::POWER && thirdGauge.unit == Units::PERCENT)
      || (gauge4Type == SwitchingGaugeType::POWER && fourthGauge.unit == Units::PERCENT))
      && std::abs(maxPower - rhs.maxPower) > EPSILON)
        return true;

    if (type == AircraftType::PROP &&
        ((gauge1Type == SwitchingGaugeType::TORQUE && firstGauge.unit == Units::PERCENT)
      || (gauge2Type == SwitchingGaugeType::TORQUE && secondGauge.unit == Units::PERCENT)
      || (gauge3Type == SwitchingGaugeType::TORQUE && thirdGauge.unit == Units::PERCENT)
      || (gauge4Type == SwitchingGaugeType::TORQUE && fourthGauge.unit == Units::PERCENT))
      && std::abs(maxTorque - rhs.maxTorque) > EPSILON)
        return true;

    if (!noColors)
    {
        if (hasLowLimit != rhs.hasLowLimit
          || hasFlapsSpeed != rhs.hasFlapsSpeed
          || hasGreenSpeed != rhs.hasGreenSpeed
          || hasYellowSpeed != rhs.hasYellowSpeed
          || hasRedSpeed != rhs.hasRedSpeed
          || hasHighLimit != rhs.hasHighLimit)
            return true;

        if (hasLowLimit && std::abs(lowLimit - rhs.lowLimit) > EPSILON)
            return true;

        if (hasFlapsSpeed &&
            (std::abs(flapsBegin - rhs.flapsBegin) > EPSILON || std::abs(flapsEnd - rhs.flapsEnd) > EPSILON))
            return true;

        if (hasGreenSpeed &&
            (std::abs(greenBegin - rhs.greenBegin) > EPSILON || std::abs(greenEnd - rhs.greenEnd) > EPSILON))
            return true;

        if (hasYellowSpeed &&
            (std::abs(yellowBegin - rhs.yellowBegin) > EPSILON || std::abs(yellowEnd - rhs.yellowEnd) > EPSILON))
            return true;

        if (hasRedSpeed &&
            (std::abs(redBegin - rhs.redBegin) > EPSILON || std::abs(redEnd - rhs.redEnd) > EPSILON))
            return true;

        if (hasHighLimit)
        {
            if (dynamicBarberpole != rhs.dynamicBarberpole)
                return true;

            if (dynamicBarberpole && std::abs(highLimit - rhs.highLimit) > EPSILON)
                return true;
        }
    }

    if (refSpeedDefaults != rhs.refSpeedDefaults)
        return true;

    if (gauge1Type != SwitchingGaugeType::NONE && firstGauge != rhs.firstGauge)
        return true;

    if (gauge2Type != SwitchingGaugeType::NONE && secondGauge != rhs.secondGauge)
        return true;

    if (gauge3Type != SwitchingGaugeType::NONE && thirdGauge != rhs.thirdGauge)
        return true;

    if (gauge4Type != SwitchingGaugeType::NONE && fourthGauge != rhs.fourthGauge)
        return true;

    if (fuelQtyGauge != rhs.fuelQtyGauge
      || fuelFlowGauge != rhs.fuelFlowGauge
      || oilTempGauge != rhs.oilTempGauge
      || oilPressGauge != rhs.oilPressGauge)
        return true;

    if (hasSecondaryTempGauge && (
               secondaryTempType != rhs.secondaryTempType
            || secondaryTempGauge != rhs.secondaryTempGauge))
        return true;

    return false;
}


}  // namespace definitions
