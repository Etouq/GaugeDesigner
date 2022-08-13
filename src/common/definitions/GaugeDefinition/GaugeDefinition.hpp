#ifndef GAUGEDEFINITION_H
#define GAUGEDEFINITION_H

#include "../BaseTypes.hpp"
#include "common/Units.hpp"

#include <cstdint>
#include <QColor>
#include <QList>
#include <QString>
#include <string>


class QIODevice;
class QByteArray;

namespace definitions
{

// definition used to display a gauge
struct GaugeDefinition
{

    QString title = "";
    QString unitString = "";

    double minValue = 0;
    double maxValue = 100;

    QList<ColorZone> colorZones;
    QList<GradDef> grads;
    QList<TextGradDef> textGrads;

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

    std::string toBinary() const;

    static GaugeDefinition fromBinary(QIODevice &data, FileVersion version)
    {
        switch (version)
        {
            case FileVersion::V1:
            case FileVersion::V2:
                return fromBinaryV1(data);
            case FileVersion::V3:
                return fromBinaryV3(data);
            default:
                return GaugeDefinition();
        }
    }

    double getEpsilon(bool isCircular) const;

    bool operator==(const GaugeDefinition &rhs) const
    {
        return title == rhs.title
          && unitString == rhs.unitString
          && std::abs(minValue - rhs.minValue) <= EPSILON
          && std::abs(maxValue - rhs.maxValue) <= EPSILON
          && colorZones == rhs.colorZones
          && grads == rhs.grads
          && textGrads == rhs.textGrads
          && (noText || (std::abs(textIncrement - rhs.textIncrement) <= EPSILON && textNumDigits == rhs.textNumDigits))
          && forceTextColor == rhs.forceTextColor
          && (!forceTextColor || textForcedColor == rhs.textForcedColor)
          && hasMinRedBlink == rhs.hasMinRedBlink
          && (!hasMinRedBlink || std::abs(minRedBlinkThreshold - rhs.minRedBlinkThreshold) <= EPSILON)
          && hasMaxRedBlink == rhs.hasMaxRedBlink
          && (!hasMaxRedBlink || std::abs(maxRedBlinkThreshold - rhs.maxRedBlinkThreshold) <= EPSILON)
          && noText == rhs.noText
          && unit == rhs.unit;
    }

    bool operator!=(const GaugeDefinition &rhs) const
    {
        return title != rhs.title
          || unitString != rhs.unitString
          || std::abs(minValue - rhs.minValue) > EPSILON
          || std::abs(maxValue - rhs.maxValue) > EPSILON
          || colorZones != rhs.colorZones
          || grads != rhs.grads
          || textGrads != rhs.textGrads
          || (!noText && (std::abs(textIncrement - rhs.textIncrement) > EPSILON || textNumDigits != rhs.textNumDigits))
          || forceTextColor != rhs.forceTextColor
          || (forceTextColor && textForcedColor != rhs.textForcedColor)
          || hasMinRedBlink != rhs.hasMinRedBlink
          || (hasMinRedBlink && std::abs(minRedBlinkThreshold - rhs.minRedBlinkThreshold) > EPSILON)
          || hasMaxRedBlink != rhs.hasMaxRedBlink
          || (hasMaxRedBlink && std::abs(maxRedBlinkThreshold - rhs.maxRedBlinkThreshold) > EPSILON)
          || noText != rhs.noText
          || unit != rhs.unit;
    }

private:

    static GaugeDefinition fromBinaryV1(QIODevice &data);
    static GaugeDefinition fromBinaryV3(QIODevice &data);
};

}  // namespace definitions


#endif  // GAUGEDEFINITION_H
