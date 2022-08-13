#include "QmlGaugeDefinition.hpp"

void QmlGaugeDefinition::setTitle(const QString &title)
{
    if (d_definition->title != title)
    {
        d_definition->title = title;
        emit titleChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setUnitString(const QString &unitString)
{
    if (d_definition->unitString != unitString)
    {
        d_definition->unitString = unitString;
        emit unitStringChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setMinValue(double minValue)
{
    if (std::abs(d_definition->minValue - minValue) > 1e-5)
    {
        d_definition->minValue = minValue;
        emit minValueChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setmaxValue(double maxValue)
{
    if (std::abs(d_definition->maxValue - maxValue) > 1e-5)
    {
        d_definition->maxValue = maxValue;
        emit maxValueChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setTextIncrement(double textIncrement)
{
    if (std::abs(d_definition->textIncrement - textIncrement) > 1e-5)
    {
        d_definition->textIncrement = textIncrement;
        emit textIncrementChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setTextNumDigits(int textNumDigits)
{
    if (d_definition->textNumDigits != textNumDigits)
    {
        d_definition->textNumDigits = textNumDigits;
        emit textNumDigitsChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setForceTextColor(bool forceTextColor)
{
    if (d_definition->forceTextColor != forceTextColor)
    {
        d_definition->forceTextColor = forceTextColor;
        emit forceTextColorChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setTextForcedColor(QColor textForcedColor)
{
    if (d_definition->textForcedColor != textForcedColor)
    {
        d_definition->textForcedColor = textForcedColor;
        emit textForcedColorChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setHasMinRedBlink(bool hasMinRedBlink)
{
    if (d_definition->hasMinRedBlink != hasMinRedBlink)
    {
        d_definition->hasMinRedBlink = hasMinRedBlink;
        emit hasMinRedBlinkChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setMinRedBlinkThreshold(double minRedBlinkThreshold)
{
    if (std::abs(d_definition->minRedBlinkThreshold - minRedBlinkThreshold) > 1e-5)
    {
        d_definition->minRedBlinkThreshold = minRedBlinkThreshold;
        emit minRedBlinkThresholdChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setHasMaxRedBlink(bool hasMaxRedBlink)
{
    if (d_definition->hasMaxRedBlink != hasMaxRedBlink)
    {
        d_definition->hasMaxRedBlink = hasMaxRedBlink;
        emit hasMaxRedBlinkChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setMaxRedBlinkThreshold(double maxRedBlinkThreshold)
{
    if (std::abs(d_definition->maxRedBlinkThreshold - maxRedBlinkThreshold) > 1e-5)
    {
        d_definition->maxRedBlinkThreshold = maxRedBlinkThreshold;
        emit maxRedBlinkThresholdChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setNoText(bool noText)
{
    if (d_definition->noText != noText)
    {
        d_definition->noText = noText;
        emit noTextChanged();

        checkForUnsavedChanges();
    }
}

void QmlGaugeDefinition::setUnit(int unit)
{
    if (Units newUnit = static_cast<Units>(unit); d_definition->unit != newUnit)
    {
        d_definition->unit = newUnit;
        emit unitChanged();

        checkForUnsavedChanges();
    }
}