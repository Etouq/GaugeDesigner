#include "QmlAircraftDefinition.hpp"

void QmlAircraftDefinition::changeDefinition(const definitions::AircraftDefinition &newDefinition)
{
    d_definition = newDefinition;
    d_lastSavedDefinition = newDefinition;
    d_unsavedChanges = false;
    emit unsavedChangesChanged();

    d_gauge1.changeDefinition(&d_definition.firstGauge, gaugeTypeToModel(d_definition.gauge1Type), true);
    d_gauge2.changeDefinition(&d_definition.secondGauge, gaugeTypeToModel(d_definition.gauge2Type), true);
    d_gauge3.changeDefinition(&d_definition.thirdGauge, gaugeTypeToModel(d_definition.gauge3Type), true);
    d_gauge4.changeDefinition(&d_definition.fourthGauge, gaugeTypeToModel(d_definition.gauge4Type), true);
    d_fuelQtyGauge.changeDefinition(&d_definition.fuelQtyGauge, &d_volOrWghtModel, true);
    d_fuelFlowGauge.changeDefinition(&d_definition.fuelFlowGauge, &d_volOrWghtRateModel, true);
    d_oilTempGauge.changeDefinition(&d_definition.oilTempGauge, &d_temperatureModel, true);
    d_secondaryTempGauge.changeDefinition(&d_definition.secondaryTempGauge, &d_temperatureModel, true);
    d_oilPressGauge.changeDefinition(&d_definition.oilPressGauge, &d_pressureModel, true);

    emit typeChanged();

    emit nameChanged();

    emit gauge1TypeChanged();
    emit gauge2TypeChanged();
    emit gauge3TypeChanged();
    emit gauge4TypeChanged();

    emit engineTempTypeChanged();

    emit maxPowerChanged();

    emit hasApuChanged();

    emit hasFlapsChanged();
    emit hasSpoilersChanged();

    emit hasElevatorTrimChanged();
    emit hasRudderTrimChanged();
    emit hasAileronTrimChanged();

    emit hasSecondaryTempGaugeChanged();
    emit secondaryTempTypeChanged();

    emit numEnginesChanged();
    emit singleTankChanged();

    emit lowLimitChanged();
    emit flapsBeginChanged();
    emit flapsEndChanged();
    emit greenBeginChanged();
    emit greenEndChanged();
    emit yellowBeginChanged();
    emit yellowEndChanged();
    emit redBeginChanged();
    emit redEndChanged();
    emit highLimitChanged();
    emit noColorsChanged();
    emit dynamicBarberpoleChanged();
}