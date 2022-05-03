#include "gauge-definition.hpp"

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
    QByteArray ret = BinaryConverter::toBinary(title);
    ret += BinaryConverter::toBinary(unitString);
    ret += BinaryConverter::toBinary(minValue);
    ret += BinaryConverter::toBinary(maxValue);
    ret += BinaryConverter::toBinary(colorZones);
    ret += BinaryConverter::toBinary(grads);
    ret += BinaryConverter::toBinary(textGrads);
    ret += BinaryConverter::toBinary(textIncrement);
    ret += BinaryConverter::toBinary(textNumDigits);
    ret += BinaryConverter::toBinary(forceTextColor);
    ret += BinaryConverter::toBinary(textForcedColor);
    ret += BinaryConverter::toBinary(hasMinRedBlink);
    ret += BinaryConverter::toBinary(minRedBlinkThreshold);
    ret += BinaryConverter::toBinary(hasMaxRedBlink);
    ret += BinaryConverter::toBinary(maxRedBlinkThreshold);
    ret += BinaryConverter::toBinary(noText);
    ret += BinaryConverter::toBinary(unit);
    return ret;
}

GaugeDefinition GaugeDefinition::fromBinary(QIODevice &data, FileVersion version)
{
    switch (version)
    {
        case FileVersion::V1:
        case FileVersion::V2:
            return fromBinaryV1(data);
            break;
    }
    return GaugeDefinition();
}


GaugeDefinition GaugeDefinition::fromBinaryV1(QIODevice &data)
{
    GaugeDefinition ret;
    ret.title = BinaryConverter::readString(data);
    ret.unitString = BinaryConverter::readString(data);
    ret.minValue = BinaryConverter::readDouble(data);
    ret.maxValue = BinaryConverter::readDouble(data);
    BinaryConverter::readColorZoneVec(data, ret.colorZones);
    BinaryConverter::readGradVec(data, ret.grads);
    BinaryConverter::readTextGradVec(data, ret.textGrads);
    ret.textIncrement = BinaryConverter::readDouble(data);
    ret.textNumDigits = BinaryConverter::readInt8_t(data);
    ret.forceTextColor = BinaryConverter::readBool(data);
    ret.textForcedColor = BinaryConverter::readColor(data);
    ret.hasMinRedBlink = BinaryConverter::readBool(data);
    ret.minRedBlinkThreshold = BinaryConverter::readDouble(data);
    ret.hasMaxRedBlink = BinaryConverter::readBool(data);
    ret.maxRedBlinkThreshold = BinaryConverter::readDouble(data);
    ret.noText = BinaryConverter::readBool(data);
    ret.unit = BinaryConverter::readUnit(data);
    return ret;
}
