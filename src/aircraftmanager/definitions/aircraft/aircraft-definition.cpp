#include "aircraft-definition.hpp"

QByteArray AircraftDefinition::toBinary() const
{
    QByteArray ret = BinaryConverter::toBinary(static_cast<int8_t>(type));


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

    ret += BinaryConverter::toBinary(name);
    ret += fuelQtyGauge.toBinary();
    ret += fuelFlowGauge.toBinary();
    ret += oilTempGauge.toBinary();
    ret += oilPressGauge.toBinary();

    ret += BinaryConverter::toBinary(hasFlaps);
    ret += BinaryConverter::toBinary(hasSpoilers);

    ret += BinaryConverter::toBinary(hasElevatorTrim);
    ret += BinaryConverter::toBinary(hasRudderTrim);
    ret += BinaryConverter::toBinary(hasAileronTrim);

    ret += BinaryConverter::toBinary(fuelQtyByVolume);
    ret += BinaryConverter::toBinary(fuelFlowByVolume);

    ret += BinaryConverter::toBinary(numEngines);
    ret += BinaryConverter::toBinary(numTanks);

    ret += BinaryConverter::toBinary(lowLimit);
    ret += BinaryConverter::toBinary(flapsBegin);
    ret += BinaryConverter::toBinary(flapsEnd);
    ret += BinaryConverter::toBinary(greenBegin);
    ret += BinaryConverter::toBinary(greenEnd);
    ret += BinaryConverter::toBinary(yellowBegin);
    ret += BinaryConverter::toBinary(yellowEnd);
    ret += BinaryConverter::toBinary(redBegin);
    ret += BinaryConverter::toBinary(redEnd);
    ret += BinaryConverter::toBinary(highLimit);

    ret += BinaryConverter::toBinary(noColors);
    ret += BinaryConverter::toBinary(dynamicBarberpole);

    ret += BinaryConverter::toBinary(defaultVr);
    ret += BinaryConverter::toBinary(defaultVx);
    ret += BinaryConverter::toBinary(defaultVy);
    ret += BinaryConverter::toBinary(defaultVapp);

    return ret;
}

AircraftDefinition AircraftDefinition::fromBinaryV1(QIODevice &data, FileVersion version)
{
    AircraftDefinition ret;
    ret.type = AircraftType(BinaryConverter::readInt8_t(data));

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

    ret.name = BinaryConverter::readString(data);
    ret.fuelQtyGauge = GaugeDefinition::fromBinary(data, version);
    ret.fuelFlowGauge = GaugeDefinition::fromBinary(data, version);
    ret.oilTempGauge = GaugeDefinition::fromBinary(data, version);
    ret.oilPressGauge = GaugeDefinition::fromBinary(data, version);

    ret.hasFlaps = BinaryConverter::readBool(data);
    ret.hasSpoilers = BinaryConverter::readBool(data);

    ret.hasElevatorTrim = BinaryConverter::readBool(data);
    ret.hasRudderTrim = BinaryConverter::readBool(data);
    ret.hasAileronTrim = BinaryConverter::readBool(data);

    ret.fuelQtyByVolume = BinaryConverter::readBool(data);
    ret.fuelFlowByVolume = BinaryConverter::readBool(data);

    ret.numEngines = BinaryConverter::readInt8_t(data);
    ret.numTanks = BinaryConverter::readInt8_t(data);

    ret.lowLimit = BinaryConverter::readFloat(data);
    ret.flapsBegin = BinaryConverter::readFloat(data);
    ret.flapsEnd = BinaryConverter::readFloat(data);
    ret.greenBegin = BinaryConverter::readFloat(data);
    ret.greenEnd = BinaryConverter::readFloat(data);
    ret.yellowBegin = BinaryConverter::readFloat(data);
    ret.yellowEnd = BinaryConverter::readFloat(data);
    ret.redBegin = BinaryConverter::readFloat(data);
    ret.redEnd = BinaryConverter::readFloat(data);
    ret.highLimit = BinaryConverter::readFloat(data);

    ret.noColors = BinaryConverter::readBool(data);
    ret.dynamicBarberpole = BinaryConverter::readBool(data);

    return ret;
}

AircraftDefinition AircraftDefinition::fromBinaryV2(QIODevice &data, FileVersion version)
{
    AircraftDefinition ret = fromBinaryV1(data, version);

    ret.defaultVr = BinaryConverter::readUint16_t(data);
    ret.defaultVx = BinaryConverter::readUint16_t(data);
    ret.defaultVy = BinaryConverter::readUint16_t(data);
    ret.defaultVapp = BinaryConverter::readUint16_t(data);

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
