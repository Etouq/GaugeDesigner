#include "jet-definition.hpp"

JetDefinition::JetDefinition(const RawJetDefinition &rhs)
{
    n1Gauge = rhs.n1Gauge;
    n2Gauge = rhs.n2Gauge;
    ittGauge = rhs.ittGauge;
    hasApu = rhs.hasApu;
    egtReplacesItt = rhs.egtReplacesItt;
}

QByteArray JetDefinition::toBinary() const
{
    QByteArray ret = n1Gauge.toBinary();
    ret += n2Gauge.toBinary();
    ret += ittGauge.toBinary();
    ret += BinaryConverter::toBinary(hasApu);
    ret += BinaryConverter::toBinary(egtReplacesItt);
    return ret;
}

JetDefinition JetDefinition::fromBinary(QIODevice &data, FileVersion version)
{
    switch (version)
    {
        case FileVersion::V1:
        case FileVersion::V2:
            return fromBinaryV1(data, version);
            break;
    }
    return JetDefinition();
}


JetDefinition JetDefinition::fromBinaryV1(QIODevice &data, FileVersion version)
{
    JetDefinition ret;
    ret.n1Gauge = GaugeDefinition::fromBinary(data, version);
    ret.n2Gauge = GaugeDefinition::fromBinary(data, version);
    ret.ittGauge = GaugeDefinition::fromBinary(data, version);
    ret.hasApu = BinaryConverter::readBool(data);
    ret.egtReplacesItt = BinaryConverter::readBool(data);
    return ret;
}
