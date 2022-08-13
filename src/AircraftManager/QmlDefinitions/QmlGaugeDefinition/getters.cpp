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
    return d_definition->minValue;
}

double QmlGaugeDefinition::maxValue() const
{
    return d_definition->maxValue;
}

double QmlGaugeDefinition::textIncrement() const
{
    return d_definition->textIncrement;
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
    return d_definition->minRedBlinkThreshold;
}

bool QmlGaugeDefinition::hasMaxRedBlink() const
{
    return d_definition->hasMaxRedBlink;
}

double QmlGaugeDefinition::maxRedBlinkThreshold() const
{
    return d_definition->maxRedBlinkThreshold;
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