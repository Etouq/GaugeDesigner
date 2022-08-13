#include "QmlGaugeDefinition.hpp"

void QmlGaugeDefinition::changeDefinition(definitions::GaugeDefinition *newDefinition, UnitModel *newModel, bool fromNewAircraft)
{
    d_definition = newDefinition;
    d_unitModel = newModel;

    emit unitModelChanged();

    emit titleChanged();
    emit unitStringChanged();

    emit minValueChanged();
    emit maxValueChanged();

    emit textIncrementChanged();
    emit textNumDigitsChanged();

    emit forceTextColorChanged();
    emit textForcedColorChanged();

    emit hasMinRedBlinkChanged();
    emit minRedBlinkThresholdChanged();
    emit hasMaxRedBlinkChanged();
    emit maxRedBlinkThresholdChanged();

    emit noTextChanged();

    emit unitChanged();

    if (fromNewAircraft)
    {
        d_lastSavedDefinition = *newDefinition;
        d_unsavedChanges = false;
    }
    else
        d_unsavedChanges = *d_definition != d_lastSavedDefinition;
}