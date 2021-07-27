#ifndef GAUGEMANAGER_H
#define GAUGEMANAGER_H

#include <QObject>

#include "gaugeinterface.h"

class QQmlContext;
class AircraftInterface;
struct AircraftDefinition;

class GaugeManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double spoilersAngle READ spoilersAngle NOTIFY spoilersAngleChanged)
    Q_PROPERTY(QString spoilersValue READ spoilersValue NOTIFY spoilersValueChanged)
    Q_PROPERTY(bool showSpoilersText READ showSpoilersText NOTIFY showSpoilersTextChanged)

    Q_PROPERTY(double flapsAngle READ flapsAngle NOTIFY flapsAngleChanged)
    Q_PROPERTY(QString flapsValue READ flapsValue NOTIFY flapsValueChanged)
    Q_PROPERTY(bool showFlapsText READ showFlapsText NOTIFY showFlapsTextChanged)

    Q_PROPERTY(double trimTransformValue READ trimTransformValue NOTIFY trimTransformValueChanged)

    double d_currPct = 0;

    double d_spoilersAngle = 0;
    QString d_spoilersValue = "0%";
    bool d_showSpoilersText = false;

    double d_currFlapsAngle = -10;
    QString d_flapsValue = "-10º";
    bool d_showFlapsText = true;

    double d_currTrimPct = -1;
    double d_trimTransformValue = -60;

    bool d_Incrementing = true;

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

    double spoilersAngle() const;
    const QString &spoilersValue() const;
    bool showSpoilersText() const;
    double flapsAngle() const;
    const QString &flapsValue() const;
    bool showFlapsText() const;

    double trimTransformValue() const;

    Q_INVOKABLE void updateMiscAnimations();

signals:
    void gaugesLoaded();

    void spoilersAngleChanged();
    void spoilersValueChanged();
    void showSpoilersTextChanged();

    void flapsAngleChanged();
    void flapsValueChanged();
    void showFlapsTextChanged();

    void trimTransformValueChanged();

public slots:
    void changeAircraft(const AircraftDefinition &aircraft);
    void createDefaults();
    void loadAircraftPreview(const AircraftDefinition &aircraft);

    void updateSpoilersAnim();
    void updateFlapsAnim();

    void updateTrimAnim();
};

#endif   // GAUGEMANAGER_H
