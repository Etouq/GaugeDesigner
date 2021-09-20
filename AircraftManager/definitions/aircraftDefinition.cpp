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

    ret += BinaryUtil::toBinary(defaultVr);
    ret += BinaryUtil::toBinary(defaultVx);
    ret += BinaryUtil::toBinary(defaultVy);
    ret += BinaryUtil::toBinary(defaultVapp);

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

AircraftDefinition AircraftDefinition::fromBinaryV2(QIODevice &data, FileVersion version)
{
    AircraftDefinition ret = fromBinaryV1(data, version);

    ret.defaultVr = BinaryUtil::readUint16_t(data);
    ret.defaultVx = BinaryUtil::readUint16_t(data);
    ret.defaultVy = BinaryUtil::readUint16_t(data);
    ret.defaultVapp = BinaryUtil::readUint16_t(data);

    return ret;
}

AircraftDefinition AircraftDefinition::fromBinary(QIODevice &data, FileVersion version)
{
    switch (version)
    {
        case FileVersion::V1:
            return fromBinaryV1(data, version);
            break;
        case FileVersion::V2:
            return fromBinaryV2(data, version);
            break;
    }
    return AircraftDefinition();
}

bool AircraftDefinition::operator==(const AircraftDefinition &rhs) const
{
    return name == rhs.name;
}

bool AircraftDefinition::operator!=(const AircraftDefinition &rhs) const
{
    return name != rhs.name;
}

bool AircraftDefinition::operator<(const AircraftDefinition &rhs) const
{
    return name < rhs.name;
}

bool AircraftDefinition::operator<=(const AircraftDefinition &rhs) const
{
    return name <= rhs.name;
}

bool AircraftDefinition::operator>(const AircraftDefinition &rhs) const
{
    return name > rhs.name;
}

bool AircraftDefinition::operator>=(const AircraftDefinition &rhs) const
{
    return name >= rhs.name;
}
