#include "QmlAircraftDefinition.hpp"
#include "common/GaugeModels/ColorZoneModel/ColorZoneModel.hpp"
#include "common/GaugeModels/GradModel/GradModel.hpp"
#include "common/GaugeModels/TextGradModel/TextGradModel.hpp"
#include <QQmlEngine>

QmlAircraftDefinition::QmlAircraftDefinition(const definitions::AircraftDefinition &definition, QObject *parent)
  : QObject(parent),
    d_definition(definition),
    d_lastSavedDefinition(definition),
    d_gauge1(&d_definition.firstGauge, gaugeTypeToModel(d_definition.gauge1Type)),
    d_gauge2(&d_definition.secondGauge, gaugeTypeToModel(d_definition.gauge2Type)),
    d_gauge3(&d_definition.thirdGauge, gaugeTypeToModel(d_definition.gauge3Type)),
    d_gauge4(&d_definition.fourthGauge, gaugeTypeToModel(d_definition.gauge4Type)),
    d_fuelQtyGauge(&d_definition.fuelQtyGauge, &d_volOrWghtModel),
    d_fuelFlowGauge(&d_definition.fuelFlowGauge, &d_volOrWghtRateModel),
    d_oilTempGauge(&d_definition.oilTempGauge, &d_temperatureModel),
    d_secondaryTempGauge(&d_definition.secondaryTempGauge, &d_temperatureModel),
    d_oilPressGauge(&d_definition.oilPressGauge, &d_pressureModel)
{
    connect(&d_gauge1, &QmlGaugeDefinition::unsavedChangesChanged, this, &QmlAircraftDefinition::checkForUnsavedChanges);
    connect(&d_gauge2, &QmlGaugeDefinition::unsavedChangesChanged, this, &QmlAircraftDefinition::checkForUnsavedChanges);
    connect(&d_gauge3, &QmlGaugeDefinition::unsavedChangesChanged, this, &QmlAircraftDefinition::checkForUnsavedChanges);
    connect(&d_gauge4, &QmlGaugeDefinition::unsavedChangesChanged, this, &QmlAircraftDefinition::checkForUnsavedChanges);
    connect(&d_fuelQtyGauge, &QmlGaugeDefinition::unsavedChangesChanged, this, &QmlAircraftDefinition::checkForUnsavedChanges);
    connect(&d_fuelFlowGauge, &QmlGaugeDefinition::unsavedChangesChanged, this, &QmlAircraftDefinition::checkForUnsavedChanges);
    connect(&d_oilTempGauge, &QmlGaugeDefinition::unsavedChangesChanged, this, &QmlAircraftDefinition::checkForUnsavedChanges);
    connect(&d_secondaryTempGauge, &QmlGaugeDefinition::unsavedChangesChanged, this, &QmlAircraftDefinition::checkForUnsavedChanges);
    connect(&d_oilPressGauge, &QmlGaugeDefinition::unsavedChangesChanged, this, &QmlAircraftDefinition::checkForUnsavedChanges);


    qRegisterMetaType<QmlGaugeDefinition*>("QmlGaugeDefinition*");
    qRegisterMetaType<UnitModel*>("UnitModel*");
    qRegisterMetaType<ColorZoneModel*>("ColorZoneModel*");
    qRegisterMetaType<GradModel*>("GradModel*");
    qRegisterMetaType<TextGradModel*>("TextGradModel*");

    qmlRegisterUncreatableType<QmlGaugeDefinition>("Definition", 1, 0, "GaugeDefinition", "Bad Boy");
    qmlRegisterUncreatableType<UnitModel>("Definition", 1, 0, "UnitModel", "Bad Boy");
    qmlRegisterUncreatableType<ColorZoneModel>("Definition", 1, 0, "ColorZoneModel", "Bad Boy");
    qmlRegisterUncreatableType<GradModel>("Definition", 1, 0, "GradModel", "Bad Boy");
    qmlRegisterUncreatableType<TextGradModel>("Definition", 1, 0, "TextGradModel", "Bad Boy");

    QQmlEngine::setObjectOwnership(&d_gauge1, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_gauge2, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_gauge3, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_gauge4, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_fuelQtyGauge, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_fuelFlowGauge, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_oilTempGauge, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_secondaryTempGauge, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_oilPressGauge, QQmlEngine::CppOwnership);
}