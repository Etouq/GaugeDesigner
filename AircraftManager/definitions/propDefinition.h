#ifndef PROPDEFINITION_H
#define PROPDEFINITION_H

#include "gaugeDefinition.h"

// used to allow for designated initialization
struct RawPropDefinition
{
    GaugeDefinition rpmGauge;
    GaugeDefinition secondGauge;
    GaugeDefinition egtGauge;

    bool hasEgt = false;

    bool usePropRpm = false;

    bool secondIsLoad = false;
    double maxHp = 1.0;
};

struct PropDefinition
{
    GaugeDefinition rpmGauge;
    GaugeDefinition secondGauge;
    GaugeDefinition egtGauge;

    bool hasEgt = false;

    bool usePropRpm = false;

    bool secondIsLoad = false;
    double maxHp = 1.0;

    PropDefinition() = default;
    ~PropDefinition() = default;
    PropDefinition(const PropDefinition &) = default;
    PropDefinition(const RawPropDefinition &rhs);
    PropDefinition &operator=(const PropDefinition &) = default;

    QByteArray toBinary() const;

    static PropDefinition fromBinary(QIODevice &data, FileVersion version)
    {
        switch (version)
        {
            case FileVersion::V1:
            default:
                return fromBinaryV1(data, version);
                break;
        }
    }

private:
    static PropDefinition fromBinaryV1(QIODevice &data, FileVersion version);

};

Q_DECLARE_METATYPE(PropDefinition)

#endif // PROPDEFINITION_H
