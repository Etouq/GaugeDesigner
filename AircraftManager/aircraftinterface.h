#ifndef AIRCRAFTINTERFACE_H
#define AIRCRAFTINTERFACE_H

#include <QObject>
#include <QFile>
#include "definitions/aircraftDefinition.h"
#include "FileManager/aircraftfile.h"

class AircraftInterface : public QObject
{
    Q_OBJECT

    AircraftDefinition def;
    QString imagePath = ":/DefaultImage.png";




public:
    explicit AircraftInterface(QObject *parent = nullptr);

    Q_INVOKABLE void newAircraft();

    Q_INVOKABLE int getType() const { return static_cast<int>(def.type); }

    Q_INVOKABLE QString getName() const { return def.name; }

    Q_INVOKABLE QString getImagePath() const { return imagePath; }

    Q_INVOKABLE bool getHasFlaps() const { return def.hasFlaps; }
    Q_INVOKABLE bool getHasSpoilers() const { return def.hasSpoilers; }

    Q_INVOKABLE bool getHasElevTrim() const { return def.hasElevatorTrim; }
    Q_INVOKABLE bool getHasRudderTrim() const { return def.hasRudderTrim; }
    Q_INVOKABLE bool getHasAileronTrim() const { return def.hasAileronTrim; }

    Q_INVOKABLE int getNumEngines() const { return def.numEngines; }
    Q_INVOKABLE int getNumTanks() const { return def.numTanks; }

    Q_INVOKABLE float getLowLimit() const { return def.lowLimit; }
    Q_INVOKABLE float getFlapsBegin() const { return def.flapsBegin; }
    Q_INVOKABLE float getFlapsEnd() const { return def.flapsEnd; }
    Q_INVOKABLE float getGreenBegin() const { return def.greenBegin; }
    Q_INVOKABLE float getGreenEnd() const { return def.greenEnd; }
    Q_INVOKABLE float getYellowBegin() const { return def.yellowBegin; }
    Q_INVOKABLE float getYellowEnd() const { return def.yellowEnd; }
    Q_INVOKABLE float getRedBegin() const { return def.redBegin; }
    Q_INVOKABLE float getRedEnd() const { return def.redEnd; }
    Q_INVOKABLE float getHighLimit() const { return def.highLimit; }

    Q_INVOKABLE bool getNoColors() const { return def.noColors; }
    Q_INVOKABLE bool getDynamicBarberpole() const { return def.dynamicBarberpole; }

    //jet specific
    Q_INVOKABLE bool getHasApu() const {
        if (def.type != AircraftDefinition::AircraftType::JET)
            return false;

        JetDefinition jetDef = def.currentType.value<JetDefinition>();
        return jetDef.hasApu;
    }
    Q_INVOKABLE bool getEgtReplacesItt() const {
        if (def.type != AircraftDefinition::AircraftType::JET)
            return false;

        JetDefinition jetDef = def.currentType.value<JetDefinition>();
        return jetDef.egtReplacesItt;
    }

    //prop + turboprop specific
    Q_INVOKABLE bool getHasEgt() const {
        if (def.type == AircraftDefinition::AircraftType::PROP)
        {
            PropDefinition propDef = def.currentType.value<PropDefinition>();
            return propDef.hasEgt;
        }
        if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
        {
            TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
            return turbopropDef.hasEgt;
        }
        return false;
    }
    Q_INVOKABLE bool getUsePropRpm() const {
        if (def.type == AircraftDefinition::AircraftType::PROP)
        {
            PropDefinition propDef = def.currentType.value<PropDefinition>();
            return propDef.usePropRpm;
        }
        if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
        {
            TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
            return turbopropDef.usePropRpm;
        }
        return false;
    }

    //prop specific
    Q_INVOKABLE bool getSecondIsLoad() const {
        if (def.type != AircraftDefinition::AircraftType::PROP)
            return false;
        PropDefinition propDef = def.currentType.value<PropDefinition>();
        return propDef.secondIsLoad;
    }
    Q_INVOKABLE double getMaxHp() const {
        if (def.type != AircraftDefinition::AircraftType::PROP)
            return 1.0;
        PropDefinition propDef = def.currentType.value<PropDefinition>();
        return propDef.maxHp;
    }

    Q_INVOKABLE void setType(int value) 
    {
        def.type = static_cast<AircraftDefinition::AircraftType>(value);
        switch (def.type)
        {
            case AircraftDefinition::AircraftType::JET:
            {
                JetDefinition jetDef;
                def.currentType.setValue(jetDef);
                break;
            }
            case AircraftDefinition::AircraftType::PROP:
            {
                PropDefinition propDef;
                def.currentType.setValue(propDef);
                break;
            }
            case AircraftDefinition::AircraftType::TURBOPROP:
            {
                TurbopropDefinition turbopropDef;
                def.currentType.setValue(turbopropDef);
                break;
            }
            default:
                break;
        }
    }

    Q_INVOKABLE void setName(const QString &name) { def.name = name; }

    Q_INVOKABLE void setHasFlaps(bool value) { def.hasFlaps = value; }
    Q_INVOKABLE void setHasSpoilers(bool value) { def.hasSpoilers = value; }

    Q_INVOKABLE void setHasElevTrim(bool value) { def.hasElevatorTrim = value; }
    Q_INVOKABLE void setHasRudderTrim(bool value) { def.hasRudderTrim = value; }
    Q_INVOKABLE void setHasAileronTrim(bool value) { def.hasAileronTrim = value; }

    Q_INVOKABLE void setNumEngines(int value) { def.numEngines = value; }
    Q_INVOKABLE void setNumTanks(int value) { def.numTanks = value; }

    Q_INVOKABLE void setLowLimit(float value) { def.lowLimit = value; }
    Q_INVOKABLE void setFlapsBegin(float value) { def.flapsBegin = value; }
    Q_INVOKABLE void setFlapsEnd(float value) { def.flapsEnd = value; }
    Q_INVOKABLE void setGreenBegin(float value) { def.greenBegin = value; }
    Q_INVOKABLE void setGreenEnd(float value) { def.greenEnd = value; }
    Q_INVOKABLE void setYellowBegin(float value) { def.yellowBegin = value; }
    Q_INVOKABLE void setYellowEnd(float value) { def.yellowEnd = value; }
    Q_INVOKABLE void setRedBegin(float value) { def.redBegin = value; }
    Q_INVOKABLE void setRedEnd(float value) { def.redEnd = value; }
    Q_INVOKABLE void setHighLimit(float value) { def.highLimit = value; }

    Q_INVOKABLE void setNoColors(bool value) { def.noColors = value; }
    Q_INVOKABLE void setDynamicBarberpole(bool value) { def.dynamicBarberpole = value; }

    //jet specific
    Q_INVOKABLE void setHasApu(bool value) {
        if (def.type != AircraftDefinition::AircraftType::JET)
            return;

        JetDefinition jetDef = def.currentType.value<JetDefinition>();
        jetDef.hasApu = value;
        def.currentType.setValue(jetDef);
    }
    Q_INVOKABLE void setEgtReplacesItt(bool value) {
        if (def.type != AircraftDefinition::AircraftType::JET)
            return;

        JetDefinition jetDef = def.currentType.value<JetDefinition>();
        jetDef.egtReplacesItt = value;
        def.currentType.setValue(jetDef);
    }

    //prop + turboprop specific
    Q_INVOKABLE void setHasEgt(bool value) {
        if (def.type == AircraftDefinition::AircraftType::PROP)
        {
            PropDefinition propDef = def.currentType.value<PropDefinition>();
            propDef.hasEgt = value;
            def.currentType.setValue(propDef);
        }
        if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
        {
            TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
            turbopropDef.hasEgt = value;
            def.currentType.setValue(turbopropDef);
        }
    }
    Q_INVOKABLE void setUsePropRpm(bool value) {
        if (def.type == AircraftDefinition::AircraftType::PROP)
        {
            PropDefinition propDef = def.currentType.value<PropDefinition>();
            propDef.usePropRpm = value;
            def.currentType.setValue(propDef);
        }
        if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
        {
            TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
            turbopropDef.usePropRpm = value;
            def.currentType.setValue(turbopropDef);
        }
    }

    //prop specific
    Q_INVOKABLE void setSecondIsLoad(bool value) {
        if (def.type != AircraftDefinition::AircraftType::PROP)
            return;
        PropDefinition propDef = def.currentType.value<PropDefinition>();
        propDef.secondIsLoad = value;
        def.currentType.setValue(propDef);
    }
    Q_INVOKABLE void setMaxHp(double value) {
        if (def.type != AircraftDefinition::AircraftType::PROP)
            return;
        PropDefinition propDef = def.currentType.value<PropDefinition>();
        propDef.maxHp = value;
        def.currentType.setValue(propDef);
    }

    Q_INVOKABLE void selectImage();

    void setAircraft(const AircraftDefinition &aircraft)
    {
        def = aircraft;
        imagePath = AircraftFile::getImagePath(def.name);
        if (!QFile(imagePath).exists())
            imagePath = ":/DefaultImage.png";

        emit updateQml();
        emit updateAircraft(aircraft);
        emit updateComplete();
    }

    Q_INVOKABLE void saveAircraft()
    {
        QImage temp(imagePath);
        AircraftFile::saveAircraftWithImage(def, temp);
        emit aircraftSaved(def);
    }

    Q_INVOKABLE void createPreview()
    {
        emit loadAircraftPreview(def);
    }

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
    void updateN1Gauge(const GaugeDefinition &gauge)
    {
        if (def.type == AircraftDefinition::AircraftType::JET)
        {
            JetDefinition jetDef = def.currentType.value<JetDefinition>();
            jetDef.n1Gauge = gauge;
            def.currentType.setValue(jetDef);
        }
        else if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
        {
            TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
            turbopropDef.n1Gauge = gauge;
            def.currentType.setValue(turbopropDef);
        }
    }

    void updateN2Gauge(const GaugeDefinition &gauge)
    {
        if (def.type == AircraftDefinition::AircraftType::JET)
        {
            JetDefinition jetDef = def.currentType.value<JetDefinition>();
            jetDef.n2Gauge = gauge;
            def.currentType.setValue(jetDef);
        }
    }

    void updateIttGauge(const GaugeDefinition &gauge)
    {
        if (def.type == AircraftDefinition::AircraftType::JET)
        {
            JetDefinition jetDef = def.currentType.value<JetDefinition>();
            jetDef.ittGauge = gauge;
            def.currentType.setValue(jetDef);
        }
        else if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
        {
            TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
            turbopropDef.ittGauge = gauge;
            def.currentType.setValue(turbopropDef);
        }
    }

    void updateRpmGauge(const GaugeDefinition &gauge)
    {
        if (def.type == AircraftDefinition::AircraftType::PROP)
        {
            PropDefinition propDef = def.currentType.value<PropDefinition>();
            propDef.rpmGauge = gauge;
            def.currentType.setValue(propDef);
        }
        else if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
        {
            TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
            turbopropDef.rpmGauge = gauge;
            def.currentType.setValue(turbopropDef);
        }
    }

    void updateSecondGauge(const GaugeDefinition &gauge)
    {
        if (def.type == AircraftDefinition::AircraftType::PROP)
        {
            PropDefinition propDef = def.currentType.value<PropDefinition>();
            propDef.secondGauge = gauge;
            def.currentType.setValue(propDef);
        }
    }

    void updateTrqGauge(const GaugeDefinition &gauge)
    {
        if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
        {
            TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
            turbopropDef.trqGauge = gauge;
            turbopropDef.torqueAsPct = gauge.unit == Units::PERCENT;
            def.currentType.setValue(turbopropDef);
        }
    }

    void updateFuelQtyGauge(const GaugeDefinition &gauge)
    {
        def.fuelQtyGauge = gauge;
        switch (def.fuelQtyGauge.unit)
        {
            case Units::LITRES:
            case Units::CUBICCM:
            case Units::ML:
            case Units::CUBICM:
            case Units::CUBICIN:
            case Units::CUBICDM:
            case Units::OZUS:
            case Units::OZUK:
            case Units::QUARTUS:
            case Units::QUARTUK:
            case Units::CUBICFT:
            case Units::CUBICYD:
            case Units::USGAL:
            case Units::UKGAL:
                def.fuelQtyByVolume = true;
                break;
            default:
                def.fuelQtyByVolume = false;
                break;
        }
    }

    void updateFuelFlowGauge(const GaugeDefinition &gauge)
    {
        def.fuelFlowGauge = gauge;
        switch (def.fuelFlowGauge.unit)
        {
            case Units::LITRES_PER_HOUR:
            case Units::CUBICCM_PER_HOUR:
            case Units::ML_PER_HOUR:
            case Units::CUBICM_PER_HOUR:
            case Units::CUBICIN_PER_HOUR:
            case Units::CUBICDM_PER_HOUR:
            case Units::OZUS_PER_HOUR:
            case Units::OZUK_PER_HOUR:
            case Units::QUARTUS_PER_HOUR:
            case Units::QUARTUK_PER_HOUR:
            case Units::CUBICFT_PER_HOUR:
            case Units::CUBICYD_PER_HOUR:
            case Units::USGAL_PER_HOUR:
            case Units::UKGAL_PER_HOUR:
            case Units::LITRES_PER_MINUTE:
            case Units::CUBICCM_PER_MINUTE:
            case Units::ML_PER_MINUTE:
            case Units::CUBICM_PER_MINUTE:
            case Units::CUBICIN_PER_MINUTE:
            case Units::CUBICDM_PER_MINUTE:
            case Units::OZUS_PER_MINUTE:
            case Units::OZUK_PER_MINUTE:
            case Units::QUARTUS_PER_MINUTE:
            case Units::QUARTUK_PER_MINUTE:
            case Units::CUBICFT_PER_MINUTE:
            case Units::CUBICYD_PER_MINUTE:
            case Units::USGAL_PER_MINUTE:
            case Units::UKGAL_PER_MINUTE:
            case Units::LITRES_PER_SECOND:
            case Units::CUBICCM_PER_SECOND:
            case Units::ML_PER_SECOND:
            case Units::CUBICM_PER_SECOND:
            case Units::CUBICIN_PER_SECOND:
            case Units::CUBICDM_PER_SECOND:
            case Units::OZUS_PER_SECOND:
            case Units::OZUK_PER_SECOND:
            case Units::QUARTUS_PER_SECOND:
            case Units::QUARTUK_PER_SECOND:
            case Units::CUBICFT_PER_SECOND:
            case Units::CUBICYD_PER_SECOND:
            case Units::USGAL_PER_SECOND:
            case Units::UKGAL_PER_SECOND:
                def.fuelFlowByVolume = true;
                break;
            default:
                def.fuelFlowByVolume = false;
                break;
        }
    }

    void updateOilTempGauge(const GaugeDefinition &gauge)
    {
        def.oilTempGauge = gauge;
    }

    void updateOilPressGauge(const GaugeDefinition &gauge)
    {
        def.oilPressGauge = gauge;
    }

    void updateEgtGauge(const GaugeDefinition &gauge)
    {
        if (def.type == AircraftDefinition::AircraftType::PROP)
        {
            PropDefinition propDef = def.currentType.value<PropDefinition>();
            propDef.egtGauge = gauge;
            def.currentType.setValue(propDef);
        }
        else if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
        {
            TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
            turbopropDef.egtGauge = gauge;
            def.currentType.setValue(turbopropDef);
        }
    }

};

#endif // AIRCRAFTINTERFACE_H
