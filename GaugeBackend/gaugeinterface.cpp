#include "gaugeinterface.h"

GaugeInterface::GaugeInterface(QObject *parent) : QObject(parent)
{
}

void GaugeInterface::setGaugeParameters(const GaugeDefinition &gaugeDef, double startAngle, double endAngle)
{
    d_isCircular = true;

    def = gaugeDef;

    d_currValue = def.minValue;
    d_stepSize = (def.maxValue - def.minValue) / 1000;
    d_incrementing = true;


    if (def.forceTextColor)
    {
        d_engineColor = def.textForcedColor;

        emit engineColorChanged();
    }

    if (def.noText)
    {
        d_engineValue = "";

        emit engineValueChanged();
    }

    d_startAngle = startAngle;
    d_endAngle = endAngle;

    double sweepAngle = fmod(360.0 + fmod(d_startAngle - d_endAngle, 360.0), 360.0);
    d_cursorPosOffset = (sweepAngle * def.minValue) / (def.maxValue - def.minValue) + d_startAngle;
    d_cursorPosFactor = sweepAngle / (def.maxValue - def.minValue);

    updateEngine(def.minValue);

    d_engineRedBlink = false;

    emit engineRedBlinkChanged();
}


void GaugeInterface::setGaugeParameters(const GaugeDefinition &gaugeDef, double length)
{
    d_isCircular = false;

    def = gaugeDef;

    d_currValue = def.minValue;
    d_stepSize = (def.maxValue - def.minValue) / 1000;
    d_incrementing = true;

    if (def.forceTextColor)
    {
        d_engineColor = def.textForcedColor;

        emit engineColorChanged();
    }

    if (def.noText)
    {
        d_engineValue = "";

        emit engineValueChanged();
    }

    d_length = length;

    d_cursorPosOffset = (def.minValue * d_length) / (def.maxValue - def.minValue);
    d_cursorPosFactor = d_length / (def.maxValue - def.minValue);

    updateEngine(def.minValue);

    d_engineRedBlink = false;

    emit engineRedBlinkChanged();
}

void GaugeInterface::setDefinition(const GaugeDefinition &newDef)
{
    def = newDef;
    emit updateGauge();
    emit gaugeUpdated(def);
}

void GaugeInterface::updateEngine(double newVal)
{

    if (!def.noText)
    {
        QString newValue = QString::number(round(newVal / def.textIncrement) * def.textIncrement, 'f', def.textNumDigits);

        if (newValue != d_engineValue)
        {
            d_engineValue = newValue;
            emit engineValueChanged();
        }

        if (!def.forceTextColor)
        {
            bool colorFound = false;
            for (auto it = def.colorZones.rbegin(); it != def.colorZones.rend(); ++it)
                if (newVal >= it->start && newVal <= it->end)
                {
                    if (it->color != d_engineColor)
                    {
                        d_engineColor = it->color;
                        emit engineColorChanged();
                    }
                    colorFound = true;
                    break;
                }

            if (!colorFound)
            {
                if (d_engineColor != "white")
                {
                    d_engineColor = "white";
                    emit engineColorChanged();
                }
            }
        }
    }


    bool newBlink = (def.hasMinRedBlink && def.minRedBlinkThreshold >= newVal) || (def.hasMaxRedBlink && def.maxRedBlinkThreshold <= newVal);
    if (newBlink != d_engineRedBlink)
    {
        d_engineRedBlink = newBlink;
        emit engineRedBlinkChanged();
    }

    newVal = newVal <= def.minValue ? def.minValue : newVal > def.maxValue ? def.maxValue : newVal;

    if (d_isCircular)
    {
        d_engineAngle = newVal * d_cursorPosFactor - d_cursorPosOffset;
        emit engineAngleChanged();
    }
    else
    {
        d_engineTransformValue = d_cursorPosOffset - newVal * d_cursorPosFactor;
        emit engineTransformValueChanged();
    }
}

double GaugeInterface::engineAngle() const
{
    return d_engineAngle;
}
double GaugeInterface::engineTransformValue() const
{
    return d_engineTransformValue;
}
const QString &GaugeInterface::engineValue() const
{
    return d_engineValue;
}
const QColor &GaugeInterface::engineColor() const
{
    return d_engineColor;
}
bool GaugeInterface::engineRedBlink() const
{
    return d_engineRedBlink;
}

void GaugeInterface::updateComplete()
{
    emit gaugeUpdated(def);
}

void GaugeInterface::updateEngineAnimation()
{
    if (d_incrementing)
    {
        if (d_currValue < def.maxValue)
        {
            d_currValue += d_stepSize;
        }
        else
        {
            d_incrementing = false;
            d_currValue -= d_stepSize;
        }
    }
    else
    {
        if (d_currValue > def.minValue)
        {
            d_currValue -= d_stepSize;
        }
        else
        {
            d_incrementing = true;
            d_currValue += d_stepSize;
        }
    }
    updateEngine(d_currValue);

}


