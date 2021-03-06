#ifndef GAUGEDEFINITION_H
#define GAUGEDEFINITION_H

#include "util/unitconverter/units.hpp"
#include "../basetypes.hpp"
#include "util/binaryconverter.hpp"

#include <QByteArray>
#include <QColor>
#include <QIODevice>
#include <QMetaType>
#include <QString>
#include <QVector>
#include <cstdint>

// used to allow for designated initialization
struct RawGaugeDefinition
{
    QString title = "";
    QString unitString = "";
    double minValue = 0;
    double maxValue = 0;
    QVector<ColorZone> colorZones;
    QVector<GradDef> grads;
    QVector<TextGradDef> textGrads;
    double textIncrement = 1;
    int textNumDigits = 0;
    bool forceTextColor = false;
    QColor textForcedColor = QColor();
    bool hasMinRedBlink = false;
    double minRedBlinkThreshold = 0;
    bool hasMaxRedBlink = false;
    double maxRedBlinkThreshold = 0;
    bool noText = false;
    Units unit = Units::NONE;
};

struct GaugeDefinition
{
    QString title = "";
    QString unitString = "";
    double minValue = 0;
    double maxValue = 0;
    QVector<ColorZone> colorZones;
    QVector<GradDef> grads;
    QVector<TextGradDef> textGrads;
    double textIncrement = 1;
    int8_t textNumDigits = 0;
    bool forceTextColor = false;
    QColor textForcedColor = QColor();
    bool hasMinRedBlink = false;
    double minRedBlinkThreshold = 0;
    bool hasMaxRedBlink = false;
    double maxRedBlinkThreshold = 0;
    bool noText = false;
    Units unit = Units::NONE;

    GaugeDefinition() = default;
    ~GaugeDefinition() = default;
    GaugeDefinition(const GaugeDefinition &) = default;
    GaugeDefinition(const RawGaugeDefinition &rhs);
    GaugeDefinition &operator=(const GaugeDefinition &) = default;
    GaugeDefinition &operator=(const RawGaugeDefinition &rhs);

    QByteArray toBinary() const;

    static GaugeDefinition fromBinary(QIODevice &data, FileVersion version);

private:
    static GaugeDefinition fromBinaryV1(QIODevice &data);
};

Q_DECLARE_METATYPE(GaugeDefinition)

#endif   // GAUGEDEFINITION_H
