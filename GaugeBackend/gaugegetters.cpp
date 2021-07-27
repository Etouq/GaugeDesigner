#include "gaugeinterface.h"

QString GaugeInterface::getTitle() const
{
    return def.title;
}

int GaugeInterface::getUnit() const
{
    return static_cast<int>(def.unit);
}

QString GaugeInterface::getUnitString() const
{
    return def.unitString;
}

double GaugeInterface::getMinValue() const
{
    return def.minValue;
}

double GaugeInterface::getMaxValue() const
{
    return def.maxValue;
}

double GaugeInterface::getStartAngle() const
{
    return d_startAngle;
}
double GaugeInterface::getEndAngle() const
{
    return d_endAngle;
}

int GaugeInterface::numColorZones() const
{
    return def.colorZones.size();
}

double GaugeInterface::colorZoneStartAt(int idx) const
{
    return def.colorZones.at(idx).start;
}

double GaugeInterface::colorZoneEndAt(int idx) const
{
    return def.colorZones.at(idx).end;
}

QColor GaugeInterface::colorZoneColorAt(int idx) const
{
    return def.colorZones.at(idx).color;
}

int GaugeInterface::numGrads() const
{
    return def.grads.size();
}

double GaugeInterface::gradValAt(int idx) const
{
    return def.grads.at(idx).gradPos;
}

bool GaugeInterface::gradIsBigAt(int idx) const
{
    return def.grads.at(idx).isBig;
}

QColor GaugeInterface::gradColorAt(int idx) const
{
    return def.grads.at(idx).gradColor;
}

int GaugeInterface::numTextGrads() const
{
    return def.textGrads.size();
}

double GaugeInterface::textGradValAt(int idx) const
{
    return def.textGrads.at(idx).textGradPos;
}

QString GaugeInterface::gradTextAt(int idx) const
{
    return def.textGrads.at(idx).gradText;
}

bool GaugeInterface::needsExtraWide() const
{
    for (int i = 0; i < def.textGrads.size(); i++)
        if (def.textGrads[i].gradText.size() > 4)
            return true;
    return false;
}

double GaugeInterface::getTextIncrement() const
{
    return def.textIncrement;
}

int GaugeInterface::getTextNumDigits() const
{
    return def.textNumDigits;
}

bool GaugeInterface::getForceTextColor() const
{
    return def.forceTextColor;
}

QColor GaugeInterface::getTextForcedColor() const
{
    return def.textForcedColor.isValid() ? def.textForcedColor : "white";
}

bool GaugeInterface::getHasMinRedBlink() const
{
    return def.hasMinRedBlink;
}

double GaugeInterface::getMinRedBlinkThreshold() const
{
    return def.minRedBlinkThreshold;
}

bool GaugeInterface::getHasMaxRedBlink() const
{
    return def.hasMaxRedBlink;
}

double GaugeInterface::getMaxRedBlinkThreshold() const
{
    return def.maxRedBlinkThreshold;
}

bool GaugeInterface::getNoText() const
{
    return def.noText;
}
