#include "turboprop-definition.hpp"

TurbopropDefinition::TurbopropDefinition(const RawTurbopropDefinition &rhs)
{
    n1Gauge = rhs.n1Gauge;
    trqGauge = rhs.trqGauge;
    ittGauge = rhs.ittGauge;
    rpmGauge = rhs.rpmGauge;
    egtGauge = rhs.egtGauge;
    hasEgt = rhs.hasEgt;
    usePropRpm = rhs.usePropRpm;
    torqueAsPct = rhs.torqueAsPct;
}

QByteArray TurbopropDefinition::toBinary() const
{
    QByteArray ret = n1Gauge.toBinary();
    ret += trqGauge.toBinary();
    ret += ittGauge.toBinary();
    ret += rpmGauge.toBinary();
    ret += egtGauge.toBinary();
    ret += BinaryConverter::toBinary(hasEgt);
    ret += BinaryConverter::toBinary(usePropRpm);
    ret += BinaryConverter::toBinary(torqueAsPct);
    return ret;
}

TurbopropDefinition TurbopropDefinition::fromBinary(QIODevice &data, FileVersion version)
{
    switch (version)
    {
        case FileVersion::V1:
        case FileVersion::V2:
            return fromBinaryV1(data, version);
            break;
    }
    return TurbopropDefinition();
}

TurbopropDefinition TurbopropDefinition::fromBinaryV1(QIODevice &data, FileVersion version)
{
    TurbopropDefinition ret;
    ret.n1Gauge = GaugeDefinition::fromBinary(data, version);
    ret.trqGauge = GaugeDefinition::fromBinary(data, version);
    ret.ittGauge = GaugeDefinition::fromBinary(data, version);
    ret.rpmGauge = GaugeDefinition::fromBinary(data, version);
    ret.egtGauge = GaugeDefinition::fromBinary(data, version);
    ret.hasEgt = BinaryConverter::readBool(data);
    ret.usePropRpm = BinaryConverter::readBool(data);
    ret.torqueAsPct = BinaryConverter::readBool(data);
    return ret;
}
