#include "gaugeinterface.hpp"

void GaugeInterface::setTitleAndUnit(const QString &title, int unit, const QString &unitString)
{
    def.title = title;
    def.unit = static_cast<Units>(unit);
    def.unitString = unitString;
}

void GaugeInterface::setRange(double minValue, double maxValue)
{
    def.minValue = minValue;
    def.maxValue = maxValue;
}

void GaugeInterface::setNumColorZones(int count)
{
    def.colorZones.resize(count);
}

void GaugeInterface::setColorZoneAt(int idx, double start, double end, const QString &color)
{
    def.colorZones[idx] = ColorZone{ .start = start, .end = end, .color = color };
}

void GaugeInterface::setNumGrads(int count)
{
    def.grads.resize(count);
}

void GaugeInterface::setGradAt(int idx, double pos, bool isBig, const QString &color)
{
    def.grads[idx] = GradDef{ .gradPos = pos, .isBig = isBig, .gradColor = color };
}

void GaugeInterface::setNumTextGrads(int count)
{
    def.textGrads.resize(count);
}

void GaugeInterface::setTextGradAt(int idx, double pos, const QString &text)
{
    def.textGrads[idx] = TextGradDef{ .textGradPos = pos, .gradText = text };
}

void GaugeInterface::setTextIncrement(double textIncrement, int numDecimals)
{
    def.textIncrement = textIncrement;
    def.textNumDigits = numDecimals;
}

void GaugeInterface::setForceTextColor(bool forceColor, const QString &color)
{
    def.forceTextColor = forceColor;
    def.textForcedColor = color;
}

void GaugeInterface::setMinBlink(bool hasMinBlink, double minBlinkThreshold)
{
    def.hasMinRedBlink = hasMinBlink;
    def.minRedBlinkThreshold = minBlinkThreshold;
}

void GaugeInterface::setMaxBlink(bool hasMaxBlink, double maxBlinkThreshold)
{
    def.hasMaxRedBlink = hasMaxBlink;
    def.maxRedBlinkThreshold = maxBlinkThreshold;
}

void GaugeInterface::setNoText(bool noText)
{
    def.noText = noText;
}
