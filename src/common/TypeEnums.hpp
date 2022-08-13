#ifndef __TYPE_ENUMS_HPP__
#define __TYPE_ENUMS_HPP__

#include <cstdint>

enum class AircraftType : uint8_t
{
    JET = 0,
    PROP,
    TURBOPROP,
    INVALID = 255
};

enum class TemperatureGaugeType : uint8_t
{
    EGT = 0,
    ITT,
    CHT,
    TIT
};

enum class SwitchingGaugeType : uint8_t
{
    NONE,
    N1,
    N2,
    ENGINE_TEMP, // itt, egt or cht
    RPM,
    PROP_RPM,
    POWER,
    MANIFOLD_PRESSURE,
    TORQUE
};

#endif  // __TYPE_ENUMS_HPP__