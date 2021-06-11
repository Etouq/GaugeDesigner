#include "aircraftDefinition.h"

QByteArray AircraftDefinition::toBinary() const
{
    QByteArray ret = BinaryUtil::toBinary(static_cast<int8_t>(type));


    switch (type)
    {
        case AircraftType::JET:
        {
            JetDefinition def = currentType.value<JetDefinition>();
            ret += def.toBinary();
            break;
        }
        case AircraftType::PROP:
        {
            PropDefinition def = currentType.value<PropDefinition>();
            ret += def.toBinary();
            break;
        }
        case AircraftType::TURBOPROP:
        {
            TurbopropDefinition def = currentType.value<TurbopropDefinition>();
            ret += def.toBinary();
            break;
        }
        case AircraftType::INVALID:
        default:
            break;
    }

    ret += BinaryUtil::toBinary(name);
    ret += fuelQtyGauge.toBinary();
    ret += fuelFlowGauge.toBinary();
    ret += oilTempGauge.toBinary();
    ret += oilPressGauge.toBinary();

    ret += BinaryUtil::toBinary(hasFlaps);
    ret += BinaryUtil::toBinary(hasSpoilers);

    ret += BinaryUtil::toBinary(hasElevatorTrim);
    ret += BinaryUtil::toBinary(hasRudderTrim);
    ret += BinaryUtil::toBinary(hasAileronTrim);

    ret += BinaryUtil::toBinary(fuelQtyByVolume);
    ret += BinaryUtil::toBinary(fuelFlowByVolume);

    ret += BinaryUtil::toBinary(numEngines);
    ret += BinaryUtil::toBinary(numTanks);

    ret += BinaryUtil::toBinary(lowLimit);
    ret += BinaryUtil::toBinary(flapsBegin);
    ret += BinaryUtil::toBinary(flapsEnd);
    ret += BinaryUtil::toBinary(greenBegin);
    ret += BinaryUtil::toBinary(greenEnd);
    ret += BinaryUtil::toBinary(yellowBegin);
    ret += BinaryUtil::toBinary(yellowEnd);
    ret += BinaryUtil::toBinary(redBegin);
    ret += BinaryUtil::toBinary(redEnd);
    ret += BinaryUtil::toBinary(highLimit);

    ret += BinaryUtil::toBinary(noColors);
    ret += BinaryUtil::toBinary(dynamicBarberpole);

    return ret;
}

AircraftDefinition AircraftDefinition::fromBinaryV1(QIODevice &data, FileVersion version)
{
    AircraftDefinition ret;
    ret.type = AircraftType(BinaryUtil::readInt8_t(data));

    switch (ret.type)
    {
        case AircraftType::JET:
        {
            JetDefinition def = JetDefinition::fromBinary(data, version);
            ret.currentType.setValue(def);
            break;
        }
        case AircraftType::PROP:
        {
            PropDefinition def = PropDefinition::fromBinary(data, version);
            ret.currentType.setValue(def);
            break;
        }
        case AircraftType::TURBOPROP:
        {
            TurbopropDefinition def = TurbopropDefinition::fromBinary(data, version);
            ret.currentType.setValue(def);
            break;
        }
        case AircraftType::INVALID:
        default:
            ret.currentType.clear();
            break;
    }

    ret.name = BinaryUtil::readString(data);
    ret.fuelQtyGauge = GaugeDefinition::fromBinary(data, version);
    ret.fuelFlowGauge = GaugeDefinition::fromBinary(data, version);
    ret.oilTempGauge = GaugeDefinition::fromBinary(data, version);
    ret.oilPressGauge = GaugeDefinition::fromBinary(data, version);

    ret.hasFlaps = BinaryUtil::readBool(data);
    ret.hasSpoilers = BinaryUtil::readBool(data);

    ret.hasElevatorTrim = BinaryUtil::readBool(data);
    ret.hasRudderTrim = BinaryUtil::readBool(data);
    ret.hasAileronTrim = BinaryUtil::readBool(data);

    ret.fuelQtyByVolume = BinaryUtil::readBool(data);
    ret.fuelFlowByVolume = BinaryUtil::readBool(data);

    ret.numEngines = BinaryUtil::readInt8_t(data);
    ret.numTanks = BinaryUtil::readInt8_t(data);

    ret.lowLimit = BinaryUtil::readFloat(data);
    ret.flapsBegin = BinaryUtil::readFloat(data);
    ret.flapsEnd = BinaryUtil::readFloat(data);
    ret.greenBegin = BinaryUtil::readFloat(data);
    ret.greenEnd = BinaryUtil::readFloat(data);
    ret.yellowBegin = BinaryUtil::readFloat(data);
    ret.yellowEnd = BinaryUtil::readFloat(data);
    ret.redBegin = BinaryUtil::readFloat(data);
    ret.redEnd = BinaryUtil::readFloat(data);
    ret.highLimit = BinaryUtil::readFloat(data);

    ret.noColors = BinaryUtil::readBool(data);
    ret.dynamicBarberpole = BinaryUtil::readBool(data);

    return ret;
}

struct ActiveAirplaneSettings
{
    double secondDivFactor = 1;
    bool egtReplacesItt = false;
    bool torqueAsPct = false;
    bool usePropRpm = false;
    bool secondIsLoad = false;
    bool hasApu = false;
    bool hasFlaps = false;
    bool hasSpoilers = false;
    bool hasElevTrim = false;
    bool hasRudderTrim = false;
    bool hasAileronTrim = false;
    bool hasEgt = false;
    bool fuelQtyByVolume = false;
    bool fuelFlowByVolume = false;
    int8_t numEngines = 1;
    int8_t numTanks = 1;
    int8_t type = 0; // 0: jet, 1: prop, 2: turboprop
};

QByteArray AircraftDefinition::toNetworkData() const
{
    ActiveAirplaneSettings temp;
    temp.hasFlaps = hasFlaps;
    temp.hasSpoilers = hasSpoilers;
    temp.hasElevTrim = hasElevatorTrim;
    temp.hasRudderTrim = hasRudderTrim;
    temp.hasAileronTrim = hasAileronTrim;
    temp.fuelQtyByVolume = fuelQtyByVolume;
    temp.fuelFlowByVolume = fuelFlowByVolume;
    temp.numEngines = numEngines;
    temp.numTanks = numTanks;

    switch (type)
    {
        case AircraftType::JET:
        {
            JetDefinition def = currentType.value<JetDefinition>();
            temp.secondDivFactor = 1;
            temp.egtReplacesItt = def.egtReplacesItt;
            temp.torqueAsPct = false;
            temp.usePropRpm = false;
            temp.secondIsLoad = false;
            temp.hasApu = def.hasApu;
            temp.hasEgt = false;
            temp.type = 0;
            break;
        }
        case AircraftType::PROP:
        {
            PropDefinition def = currentType.value<PropDefinition>();
            temp.secondDivFactor = def.secondIsLoad ? 5.5 * def.maxHp : 1;
            temp.egtReplacesItt = false;
            temp.torqueAsPct = false;
            temp.usePropRpm = def.usePropRpm;
            temp.secondIsLoad = def.secondIsLoad;
            temp.hasApu = false;
            temp.hasEgt = def.hasEgt;
            temp.type = 1;
            break;
        }
        case AircraftType::TURBOPROP:
        {
            TurbopropDefinition def = currentType.value<TurbopropDefinition>();
            temp.secondDivFactor = 1;
            temp.egtReplacesItt = false;
            temp.torqueAsPct = def.torqueAsPct;
            temp.usePropRpm = def.usePropRpm;
            temp.secondIsLoad = false;
            temp.hasApu = false;
            temp.hasEgt = def.hasEgt;
            temp.type = 2;
            break;
        }
        case AircraftType::INVALID:
            break;
    }

    QByteArray ret(BinaryUtil::toBinary(temp.secondDivFactor));
    ret += BinaryUtil::toBinary(temp.egtReplacesItt);
    ret += BinaryUtil::toBinary(temp.torqueAsPct);
    ret += BinaryUtil::toBinary(temp.usePropRpm);
    ret += BinaryUtil::toBinary(temp.secondIsLoad);
    ret += BinaryUtil::toBinary(temp.hasApu);
    ret += BinaryUtil::toBinary(temp.hasFlaps);
    ret += BinaryUtil::toBinary(temp.hasSpoilers);
    ret += BinaryUtil::toBinary(temp.hasElevTrim);
    ret += BinaryUtil::toBinary(temp.hasRudderTrim);
    ret += BinaryUtil::toBinary(temp.hasAileronTrim);
    ret += BinaryUtil::toBinary(temp.hasEgt);
    ret += BinaryUtil::toBinary(temp.fuelQtyByVolume);
    ret += BinaryUtil::toBinary(temp.fuelFlowByVolume);
    ret += BinaryUtil::toBinary(temp.numEngines);
    ret += BinaryUtil::toBinary(temp.numTanks);
    ret += BinaryUtil::toBinary(temp.type);
    return ret;
}


