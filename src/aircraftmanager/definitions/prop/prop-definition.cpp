#include "prop-definition.hpp"

PropDefinition::PropDefinition(const RawPropDefinition &rhs)
{
    rpmGauge = rhs.rpmGauge;
    secondGauge = rhs.secondGauge;
    egtGauge = rhs.egtGauge;
    hasEgt = rhs.hasEgt;
    usePropRpm = rhs.usePropRpm;
    secondIsLoad = rhs.secondIsLoad;
    maxHp = rhs.maxHp;
}

QByteArray PropDefinition::toBinary() const
{
    QByteArray ret = rpmGauge.toBinary();
    ret += secondGauge.toBinary();
    ret += egtGauge.toBinary();
    ret += BinaryConverter::toBinary(hasEgt);
    ret += BinaryConverter::toBinary(usePropRpm);
    ret += BinaryConverter::toBinary(secondIsLoad);
    ret += BinaryConverter::toBinary(maxHp);
    return ret;
}

PropDefinition PropDefinition::fromBinary(QIODevice &data, FileVersion version)
{
    switch (version)
    {
        case FileVersion::V1:
        case FileVersion::V2:
            return fromBinaryV1(data, version);
            break;
    }
    return PropDefinition();
}

PropDefinition PropDefinition::fromBinaryV1(QIODevice &data, FileVersion version)
{
    PropDefinition ret;
    ret.rpmGauge = GaugeDefinition::fromBinary(data, version);
    ret.secondGauge = GaugeDefinition::fromBinary(data, version);
    ret.egtGauge = GaugeDefinition::fromBinary(data, version);
    ret.hasEgt = BinaryConverter::readBool(data);
    ret.usePropRpm = BinaryConverter::readBool(data);
    ret.secondIsLoad = BinaryConverter::readBool(data);
    ret.maxHp = BinaryConverter::readDouble(data);
    return ret;
}
