#ifndef AIRCRAFTINTERFACE_H
#define AIRCRAFTINTERFACE_H

#include "definitions/aircraftDefinition.h"

#include <QObject>

class AircraftInterface : public QObject
{
    Q_OBJECT

    AircraftDefinition def;
    QString imagePath = ":/DefaultImage.png";


public:
    explicit AircraftInterface(QObject *parent = nullptr);

    Q_INVOKABLE void newAircraft();

    // getters
    Q_INVOKABLE int getType() const;

    Q_INVOKABLE QString getName() const;

    Q_INVOKABLE QString getImagePath() const;

    Q_INVOKABLE bool getHasFlaps() const;
    Q_INVOKABLE bool getHasSpoilers() const;

    Q_INVOKABLE bool getHasElevTrim() const;
    Q_INVOKABLE bool getHasRudderTrim() const;
    Q_INVOKABLE bool getHasAileronTrim() const;

    Q_INVOKABLE int getNumEngines() const;
    Q_INVOKABLE int getNumTanks() const;

    Q_INVOKABLE float getLowLimit() const;
    Q_INVOKABLE float getFlapsBegin() const;
    Q_INVOKABLE float getFlapsEnd() const;
    Q_INVOKABLE float getGreenBegin() const;
    Q_INVOKABLE float getGreenEnd() const;
    Q_INVOKABLE float getYellowBegin() const;
    Q_INVOKABLE float getYellowEnd() const;
    Q_INVOKABLE float getRedBegin() const;
    Q_INVOKABLE float getRedEnd() const;
    Q_INVOKABLE float getHighLimit() const;

    Q_INVOKABLE bool getNoColors() const;
    Q_INVOKABLE bool getDynamicBarberpole() const;

    // jet specific
    Q_INVOKABLE bool getHasApu() const;
    Q_INVOKABLE bool getEgtReplacesItt() const;

    // prop + turboprop specific
    Q_INVOKABLE bool getHasEgt() const;
    Q_INVOKABLE bool getUsePropRpm() const;

    // prop specific
    Q_INVOKABLE bool getSecondIsLoad() const;
    Q_INVOKABLE double getMaxHp() const;

    // setters
    Q_INVOKABLE void setType(int value);

    Q_INVOKABLE void setName(const QString &name) { def.name = name; }

    Q_INVOKABLE void setHasFlaps(bool value);
    Q_INVOKABLE void setHasSpoilers(bool value);

    Q_INVOKABLE void setHasElevTrim(bool value);
    Q_INVOKABLE void setHasRudderTrim(bool value);
    Q_INVOKABLE void setHasAileronTrim(bool value);

    Q_INVOKABLE void setNumEngines(int value);
    Q_INVOKABLE void setNumTanks(int value);

    Q_INVOKABLE void setLowLimit(float value);
    Q_INVOKABLE void setFlapsBegin(float value);
    Q_INVOKABLE void setFlapsEnd(float value);
    Q_INVOKABLE void setGreenBegin(float value);
    Q_INVOKABLE void setGreenEnd(float value);
    Q_INVOKABLE void setYellowBegin(float value);
    Q_INVOKABLE void setYellowEnd(float value);
    Q_INVOKABLE void setRedBegin(float value);
    Q_INVOKABLE void setRedEnd(float value);
    Q_INVOKABLE void setHighLimit(float value);

    Q_INVOKABLE void setNoColors(bool value);
    Q_INVOKABLE void setDynamicBarberpole(bool value);

    // jet specific
    Q_INVOKABLE void setHasApu(bool value);
    Q_INVOKABLE void setEgtReplacesItt(bool value);

    // prop + turboprop specific
    Q_INVOKABLE void setHasEgt(bool value);
    Q_INVOKABLE void setUsePropRpm(bool value);

    // prop specific
    Q_INVOKABLE void setSecondIsLoad(bool value);
    Q_INVOKABLE void setMaxHp(double value);


    Q_INVOKABLE void selectImage();   // open image selection

    void setAircraft(const AircraftDefinition &aircraft);

    Q_INVOKABLE void saveAircraft();

    Q_INVOKABLE void createPreview();

signals:
    void updateQml();
    void updateImage();
    void imageChanged();
    void updateComplete();
    void createDefaultGauges();
    void updateAircraft(const AircraftDefinition &aircraft);
    void aircraftSaved(const AircraftDefinition &aircraft);
    void loadAircraftPreview(const AircraftDefinition &aircraft);

public slots:
    void updateN1Gauge(const GaugeDefinition &gauge);

    void updateN2Gauge(const GaugeDefinition &gauge);

    void updateIttGauge(const GaugeDefinition &gauge);

    void updateRpmGauge(const GaugeDefinition &gauge);

    void updateSecondGauge(const GaugeDefinition &gauge);

    void updateTrqGauge(const GaugeDefinition &gauge);

    void updateFuelQtyGauge(const GaugeDefinition &gauge);

    void updateFuelFlowGauge(const GaugeDefinition &gauge);

    void updateOilTempGauge(const GaugeDefinition &gauge);

    void updateOilPressGauge(const GaugeDefinition &gauge);

    void updateEgtGauge(const GaugeDefinition &gauge);
};

#endif   // AIRCRAFTINTERFACE_H
