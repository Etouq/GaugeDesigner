#ifndef GAUGEMANAGER_H
#define GAUGEMANAGER_H

#include <QObject>
#include <QQmlContext>
#include "gaugeinterface.h"
#include "AircraftManager/definitions/aircraftDefinition.h"
#include "AircraftManager/aircraftinterface.h"

class GaugeManager : public QObject
{
    Q_OBJECT

    GaugeInterface n1Gauge;
    GaugeInterface n2Gauge;
    GaugeInterface ittGauge;
    GaugeInterface rpmGauge;
    GaugeInterface secondGauge;
    GaugeInterface trqGauge;
    GaugeInterface fuelQtyGauge;
    GaugeInterface fuelFlowGauge;
    GaugeInterface oilTempGauge;
    GaugeInterface oilPressGauge;
    GaugeInterface egtGauge;

public:
    explicit GaugeManager(QObject *parent = nullptr);

    void addGaugesToContext(QQmlContext *context);

    void connectGaugeSignals(const AircraftInterface &aircraft);

public slots:
    void changeAircraft(const AircraftDefinition& aircraft);
    void createDefaults();

};

#endif // GAUGEMANAGER_H
