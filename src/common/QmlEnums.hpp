#ifndef __QML_ENUMS_HPP__
#define __QML_ENUMS_HPP__

#include "TypeEnums.hpp"

#include <QObject>


class QmlAircraftTypeClass
{
    Q_GADGET

public:

    enum class Value
    {
        JET = static_cast<int>(AircraftType::JET),
        PROP = static_cast<int>(AircraftType::PROP),
        TURBOPROP = static_cast<int>(AircraftType::TURBOPROP),
        INVALID = static_cast<int>(AircraftType::INVALID)
    };
    Q_ENUM(Value)

private:

    explicit QmlAircraftTypeClass();
};

typedef QmlAircraftTypeClass::Value QmlAircraftType;

class QmlTemperatureGaugeTypeClass
{
    Q_GADGET

public:

    enum class Value
    {
        EGT = static_cast<int>(TemperatureGaugeType::EGT),
        ITT = static_cast<int>(TemperatureGaugeType::ITT),
        CHT = static_cast<int>(TemperatureGaugeType::CHT),
        TIT = static_cast<int>(TemperatureGaugeType::TIT)  // hehe 'tit'
    };
    Q_ENUM(Value)

private:

    explicit QmlTemperatureGaugeTypeClass();
};

typedef QmlTemperatureGaugeTypeClass::Value QmlTemperatureGaugeType;

class QmlSwitchingGaugeTypeClass
{
    Q_GADGET

public:

    enum class Value
    {
        NONE = static_cast<int>(SwitchingGaugeType::NONE),
        N1 = static_cast<int>(SwitchingGaugeType::N1),
        N2 = static_cast<int>(SwitchingGaugeType::N2),
        ENGINE_TEMP = static_cast<int>(SwitchingGaugeType::ENGINE_TEMP),
        RPM = static_cast<int>(SwitchingGaugeType::RPM),
        PROP_RPM = static_cast<int>(SwitchingGaugeType::PROP_RPM),
        POWER = static_cast<int>(SwitchingGaugeType::POWER),
        MANIFOLD_PRESSURE = static_cast<int>(SwitchingGaugeType::MANIFOLD_PRESSURE),
        TORQUE = static_cast<int>(SwitchingGaugeType::TORQUE)
    };
    Q_ENUM(Value)

private:

    explicit QmlSwitchingGaugeTypeClass();
};

typedef QmlSwitchingGaugeTypeClass::Value QmlSwitchingGaugeType;


#endif  // __QML_ENUMS_HPP__
