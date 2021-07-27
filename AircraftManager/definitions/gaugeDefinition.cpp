#include "gaugeDefinition.h"

GaugeDefinition::GaugeDefinition(const RawGaugeDefinition &rhs)
{
    title = rhs.title;
    unitString = rhs.unitString;
    minValue = rhs.minValue;
    maxValue = rhs.maxValue;
    colorZones = rhs.colorZones;
    grads = rhs.grads;
    textGrads = rhs.textGrads;
    textIncrement = rhs.textIncrement;
    textNumDigits = rhs.textNumDigits;
    forceTextColor = rhs.forceTextColor;
    textForcedColor = rhs.textForcedColor;
    hasMinRedBlink = rhs.hasMinRedBlink;
    minRedBlinkThreshold = rhs.minRedBlinkThreshold;
    hasMaxRedBlink = rhs.hasMaxRedBlink;
    maxRedBlinkThreshold = rhs.maxRedBlinkThreshold;
    noText = rhs.noText;
    unit = rhs.unit;
}

GaugeDefinition &GaugeDefinition::operator=(const RawGaugeDefinition &rhs)
{
    title = rhs.title;
    unitString = rhs.unitString;
    minValue = rhs.minValue;
    maxValue = rhs.maxValue;
    colorZones = rhs.colorZones;
    grads = rhs.grads;
    textGrads = rhs.textGrads;
    textIncrement = rhs.textIncrement;
    textNumDigits = rhs.textNumDigits;
    forceTextColor = rhs.forceTextColor;
    textForcedColor = rhs.textForcedColor;
    hasMinRedBlink = rhs.hasMinRedBlink;
    minRedBlinkThreshold = rhs.minRedBlinkThreshold;
    hasMaxRedBlink = rhs.hasMaxRedBlink;
    maxRedBlinkThreshold = rhs.maxRedBlinkThreshold;
    noText = rhs.noText;
    unit = rhs.unit;
    return *this;
}

QByteArray GaugeDefinition::toBinary() const
{
    QByteArray ret = BinaryUtil::toBinary(title);
    ret += BinaryUtil::toBinary(unitString);
    ret += BinaryUtil::toBinary(minValue);
    ret += BinaryUtil::toBinary(maxValue);
    ret += BinaryUtil::toBinary(colorZones);
    ret += BinaryUtil::toBinary(grads);
    ret += BinaryUtil::toBinary(textGrads);
    ret += BinaryUtil::toBinary(textIncrement);
    ret += BinaryUtil::toBinary(textNumDigits);
    ret += BinaryUtil::toBinary(forceTextColor);
    ret += BinaryUtil::toBinary(textForcedColor);
    ret += BinaryUtil::toBinary(hasMinRedBlink);
    ret += BinaryUtil::toBinary(minRedBlinkThreshold);
    ret += BinaryUtil::toBinary(hasMaxRedBlink);
    ret += BinaryUtil::toBinary(maxRedBlinkThreshold);
    ret += BinaryUtil::toBinary(noText);
    ret += BinaryUtil::toBinary(unit);
    return ret;
}

GaugeDefinition GaugeDefinition::fromBinary(QIODevice &data, FileVersion version)
{
    switch (version)
    {
        case FileVersion::V1:
        default:
            return fromBinaryV1(data);
            break;
    }
}


GaugeDefinition GaugeDefinition::fromBinaryV1(QIODevice &data)
{
    GaugeDefinition ret;
    ret.title = BinaryUtil::readString(data);
    ret.unitString = BinaryUtil::readString(data);
    ret.minValue = BinaryUtil::readDouble(data);
    ret.maxValue = BinaryUtil::readDouble(data);
    BinaryUtil::readColorZoneVec(data, ret.colorZones);
    BinaryUtil::readGradVec(data, ret.grads);
    BinaryUtil::readTextGradVec(data, ret.textGrads);
    ret.textIncrement = BinaryUtil::readDouble(data);
    ret.textNumDigits = BinaryUtil::readInt8_t(data);
    ret.forceTextColor = BinaryUtil::readBool(data);
    ret.textForcedColor = BinaryUtil::readColor(data);
    ret.hasMinRedBlink = BinaryUtil::readBool(data);
    ret.minRedBlinkThreshold = BinaryUtil::readDouble(data);
    ret.hasMaxRedBlink = BinaryUtil::readBool(data);
    ret.maxRedBlinkThreshold = BinaryUtil::readDouble(data);
    ret.noText = BinaryUtil::readBool(data);
    ret.unit = BinaryUtil::readUnit(data);
    return ret;
}
