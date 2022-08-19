#include "QmlGaugeDefinition.hpp"

void QmlGaugeDefinition::changeDefinition(definitions::GaugeDefinition *newDefinition, UnitModel *newModel, bool fromNewAircraft, bool fromSavedAircraft)
{
    d_definition = newDefinition;
    d_unitModel = newModel;

    d_colorZoneModel.changeData(newDefinition->colorZones);
    d_gradModel.changeData(newDefinition->grads);
    d_textGradModel.changeData(newDefinition->textGrads);

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
        if (fromSavedAircraft)
        {
            d_lastSavedDefinition = *newDefinition;
            d_unsavedChanges = false;
        }
        else
        {
            d_lastSavedDefinition = definitions::GaugeDefinition();
            d_unsavedChanges = true;
        }
    }
    else
        d_unsavedChanges = *d_definition != d_lastSavedDefinition;
}