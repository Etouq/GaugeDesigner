#ifndef JETDEFINITION_H
#define JETDEFINITION_H

#include "gaugeDefinition.h"

// used to allow for designated initialization
struct RawJetDefinition
{
    GaugeDefinition n1Gauge;
    GaugeDefinition n2Gauge;
    GaugeDefinition ittGauge;

    bool hasApu = false;

    bool egtReplacesItt = false;
};

struct JetDefinition
{
    GaugeDefinition n1Gauge;
    GaugeDefinition n2Gauge;
    GaugeDefinition ittGauge;

    bool hasApu = false;

    bool egtReplacesItt = false;

    JetDefinition() = default;
    ~JetDefinition() = default;
    JetDefinition(const JetDefinition &) = default;
    JetDefinition(const RawJetDefinition &rhs);
    JetDefinition &operator=(const JetDefinition &) = default;

    QByteArray toBinary() const;

    static JetDefinition fromBinary(QIODevice &data, FileVersion version)
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
    static JetDefinition fromBinaryV1(QIODevice &data, FileVersion version);

};

Q_DECLARE_METATYPE(JetDefinition)

#endif // JETDEFINITION_H
