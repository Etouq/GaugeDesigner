#include "QmlGaugeDefinition.hpp"

UnitModel *QmlGaugeDefinition::unitModel()
{
    return d_unitModel;
}

const QString &QmlGaugeDefinition::title() const
{
    return d_definition->title;
}

const QString &QmlGaugeDefinition::unitString() const
{
    return d_definition->unitString;
}

double QmlGaugeDefinition::minValue() const
{
    return std::round(d_definition->minValue * 1e10) * 1e-10;
}

double QmlGaugeDefinition::maxValue() const
{
    return std::round(d_definition->maxValue * 1e10) * 1e-10;
}

double QmlGaugeDefinition::textIncrement() const
{
    return std::round(d_definition->textIncrement * 1e10) * 1e-10;
}

int QmlGaugeDefinition::textNumDigits() const
{
    return d_definition->textNumDigits;
}

bool QmlGaugeDefinition::forceTextColor() const
{
    return d_definition->forceTextColor;
}

QColor QmlGaugeDefinition::textForcedColor() const
{
    return d_definition->textForcedColor;
}

bool QmlGaugeDefinition::hasMinRedBlink() const
{
    return d_definition->hasMinRedBlink;
}

double QmlGaugeDefinition::minRedBlinkThreshold() const
{
    return std::round(d_definition->minRedBlinkThreshold * 1e10) * 1e-10;
}

bool QmlGaugeDefinition::hasMaxRedBlink() const
{
    return d_definition->hasMaxRedBlink;
}

double QmlGaugeDefinition::maxRedBlinkThreshold() const
{
    return std::round(d_definition->maxRedBlinkThreshold * 1e10) * 1e-10;
}

bool QmlGaugeDefinition::noText() const
{
    return d_definition->noText;
}

int QmlGaugeDefinition::unit() const
{
    return static_cast<int>(d_definition->unit);
}

bool QmlGaugeDefinition::unsavedChanges() const
{
    return d_unsavedChanges;
}