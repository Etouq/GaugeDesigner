#ifndef __QML_AIRCRAFT_DEFINITION_HPP__
#define __QML_AIRCRAFT_DEFINITION_HPP__

#include "common/QmlEnums.hpp"
#include "../QmlGaugeDefinition/QmlGaugeDefinition.hpp"
#include "common/UnitModel/UnitModel.hpp"
#include "common/definitions/AircraftDefinition/AircraftDefinition.hpp"

#include <QApplication>
#include <QObject>


class QmlAircraftDefinition : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QmlAircraftTypeClass::Value type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    Q_PROPERTY(QmlSwitchingGaugeTypeClass::Value gauge1Type READ gauge1Type WRITE setGauge1Type NOTIFY gauge1TypeChanged)
    Q_PROPERTY(QmlSwitchingGaugeTypeClass::Value gauge2Type READ gauge2Type WRITE setGauge2Type NOTIFY gauge2TypeChanged)
    Q_PROPERTY(QmlSwitchingGaugeTypeClass::Value gauge3Type READ gauge3Type WRITE setGauge3Type NOTIFY gauge3TypeChanged)
    Q_PROPERTY(QmlSwitchingGaugeTypeClass::Value gauge4Type READ gauge4Type WRITE setGauge4Type NOTIFY gauge4TypeChanged)

    Q_PROPERTY(QmlTemperatureGaugeTypeClass::Value engineTempType READ engineTempType WRITE setEngineTempType NOTIFY engineTempTypeChanged)

    Q_PROPERTY(double maxPower READ maxPower WRITE setMaxPower NOTIFY maxPowerChanged)
    Q_PROPERTY(double maxTorque READ maxTorque WRITE setMaxTorque NOTIFY maxTorqueChanged)

    Q_PROPERTY(bool hasApu READ hasApu WRITE setHasApu NOTIFY hasApuChanged)

    Q_PROPERTY(bool hasFlaps READ hasFlaps WRITE setHasFlaps NOTIFY hasFlapsChanged)
    Q_PROPERTY(bool hasSpoilers READ hasSpoilers WRITE setHasSpoilers NOTIFY hasSpoilersChanged)

    Q_PROPERTY(bool hasElevatorTrim READ hasElevatorTrim WRITE setHasElevatorTrim NOTIFY hasElevatorTrimChanged)
    Q_PROPERTY(bool hasRudderTrim READ hasRudderTrim WRITE setHasRudderTrim NOTIFY hasRudderTrimChanged)
    Q_PROPERTY(bool hasAileronTrim READ hasAileronTrim WRITE setHasAileronTrim NOTIFY hasAileronTrimChanged)

    Q_PROPERTY(bool hasSecondaryTempGauge READ hasSecondaryTempGauge WRITE setHasSecondaryTempGauge NOTIFY hasSecondaryTempGaugeChanged)
    Q_PROPERTY(QmlTemperatureGaugeTypeClass::Value secondaryTempType READ secondaryTempType WRITE setSecondaryTempType NOTIFY secondaryTempTypeChanged)


    Q_PROPERTY(int numEngines READ numEngines WRITE setNumEngines NOTIFY numEnginesChanged)
    Q_PROPERTY(bool singleTank READ singleTank WRITE setSingleTank NOTIFY singleTankChanged)

    Q_PROPERTY(float lowLimit READ lowLimit WRITE setLowLimit NOTIFY lowLimitChanged)
    Q_PROPERTY(float flapsBegin READ flapsBegin WRITE setFlapsBegin NOTIFY flapsBeginChanged)
    Q_PROPERTY(float flapsEnd READ flapsEnd WRITE setFlapsEnd NOTIFY flapsEndChanged)
    Q_PROPERTY(float greenBegin READ greenBegin WRITE setGreenBegin NOTIFY greenBeginChanged)
    Q_PROPERTY(float greenEnd READ greenEnd WRITE setGreenEnd NOTIFY greenEndChanged)
    Q_PROPERTY(float yellowBegin READ yellowBegin WRITE setYellowBegin NOTIFY yellowBeginChanged)
    Q_PROPERTY(float yellowEnd READ yellowEnd WRITE setYellowEnd NOTIFY yellowEndChanged)
    Q_PROPERTY(float redBegin READ redBegin WRITE setRedBegin NOTIFY redBeginChanged)
    Q_PROPERTY(float redEnd READ redEnd WRITE setRedEnd NOTIFY redEndChanged)
    Q_PROPERTY(float highLimit READ highLimit WRITE setHighLimit NOTIFY highLimitChanged)

    Q_PROPERTY(bool noColors READ noColors WRITE setNoColors NOTIFY noColorsChanged)
    Q_PROPERTY(bool dynamicBarberpole READ dynamicBarberpole WRITE setDynamicBarberpole NOTIFY dynamicBarberpoleChanged)

    Q_PROPERTY(bool hasLowLimit READ hasLowLimit WRITE setHasLowLimit NOTIFY hasLowLimitChanged)
    Q_PROPERTY(bool hasFlapsSpeed READ hasFlapsSpeed WRITE setHasFlapsSpeed NOTIFY hasFlapsSpeedChanged)
    Q_PROPERTY(bool hasGreenSpeed READ hasGreenSpeed WRITE setHasGreenSpeed NOTIFY hasGreenSpeedChanged)
    Q_PROPERTY(bool hasYellowSpeed READ hasYellowSpeed WRITE setHasYellowSpeed NOTIFY hasYellowSpeedChanged)
    Q_PROPERTY(bool hasRedSpeed READ hasRedSpeed WRITE setHasRedSpeed NOTIFY hasRedSpeedChanged)
    Q_PROPERTY(bool hasHighLimit READ hasHighLimit WRITE setHasHighLimit NOTIFY hasHighLimitChanged)

    Q_PROPERTY(bool unsavedChanges READ unsavedChanges NOTIFY unsavedChangesChanged)

public:

    explicit QmlAircraftDefinition(const definitions::AircraftDefinition &definition, QObject *parent = nullptr);

    const definitions::AircraftDefinition &getDefinition() const
    {
        return d_definition;
    }

    void changeDefinition(const definitions::AircraftDefinition &newDefinition, bool fromSavedAircraft = false);

    Q_INVOKABLE QmlGaugeDefinition *gauge1()
    {
        return &d_gauge1;
    }

    Q_INVOKABLE QmlGaugeDefinition *gauge2()
    {
        return &d_gauge2;
    }

    Q_INVOKABLE QmlGaugeDefinition *gauge3()
    {
        return &d_gauge3;
    }

    Q_INVOKABLE QmlGaugeDefinition *gauge4()
    {
        return &d_gauge4;
    }

    Q_INVOKABLE QmlGaugeDefinition *fuelQtyGauge()
    {
        return &d_fuelQtyGauge;
    }

    Q_INVOKABLE QmlGaugeDefinition *fuelFlowGauge()
    {
        return &d_fuelFlowGauge;
    }

    Q_INVOKABLE QmlGaugeDefinition *oilTempGauge()
    {
        return &d_oilTempGauge;
    }

    Q_INVOKABLE QmlGaugeDefinition *secondaryTempGauge()
    {
        return &d_secondaryTempGauge;
    }

    Q_INVOKABLE QmlGaugeDefinition *oilPressGauge()
    {
        return &d_oilPressGauge;
    }

    QmlAircraftType type() const;

    const QString &name() const;

    QmlSwitchingGaugeType gauge1Type() const;
    QmlSwitchingGaugeType gauge2Type() const;
    QmlSwitchingGaugeType gauge3Type() const;
    QmlSwitchingGaugeType gauge4Type() const;

    QmlTemperatureGaugeType engineTempType() const;

    double maxPower() const;
    double maxTorque() const;

    bool hasApu() const;

    bool hasFlaps() const;
    bool hasSpoilers() const;

    bool hasElevatorTrim() const;
    bool hasRudderTrim() const;
    bool hasAileronTrim() const;

    bool hasSecondaryTempGauge() const;
    QmlTemperatureGaugeType secondaryTempType() const;

    int numEngines() const;
    bool singleTank() const;

    float lowLimit() const;
    float flapsBegin() const;
    float flapsEnd() const;
    float greenBegin() const;
    float greenEnd() const;
    float yellowBegin() const;
    float yellowEnd() const;
    float redBegin() const;
    float redEnd() const;
    float highLimit() const;

    bool noColors() const;
    bool dynamicBarberpole() const;

    bool hasLowLimit() const;
    bool hasFlapsSpeed() const;
    bool hasGreenSpeed() const;
    bool hasYellowSpeed() const;
    bool hasRedSpeed() const;
    bool hasHighLimit() const;

    bool unsavedChanges() const;


    void setType(QmlAircraftType type);

    void setName(const QString &name);

    void setGauge1Type(QmlSwitchingGaugeType gauge1Type);
    void setGauge2Type(QmlSwitchingGaugeType gauge2Type);
    void setGauge3Type(QmlSwitchingGaugeType gauge3Type);
    void setGauge4Type(QmlSwitchingGaugeType gauge4Type);

    void setEngineTempType(QmlTemperatureGaugeType engineTempType);

    void setMaxPower(double maxPower);
    void setMaxTorque(double maxTorque);

    void setHasApu(bool hasApu);

    void setHasFlaps(bool hasFlaps);
    void setHasSpoilers(bool hasSpoilers);

    void setHasElevatorTrim(bool hasElevatorTrim);
    void setHasRudderTrim(bool hasRudderTrim);
    void setHasAileronTrim(bool hasAileronTrim);

    void setHasSecondaryTempGauge(bool hasSecondaryTempGauge);

    void setSecondaryTempType(QmlTemperatureGaugeType secondaryTempType)
    {
        TemperatureGaugeType type = static_cast<TemperatureGaugeType>(secondaryTempType);
        if (d_definition.secondaryTempType == type)
            return;

        d_definition.secondaryTempType = type;

        d_secondaryTempGauge.changeType(d_definition.secondaryTempType);
        emit secondaryTempTypeChanged();
    }

    void setNumEngines(int numEngines);
    void setSingleTank(bool singleTank);

    void setLowLimit(float lowLimit);
    void setFlapsBegin(float flapsBegin);
    void setFlapsEnd(float flapsEnd);
    void setGreenBegin(float greenBegin);
    void setGreenEnd(float greenEnd);
    void setYellowBegin(float yellowBegin);
    void setYellowEnd(float yellowEnd);
    void setRedBegin(float redBegin);
    void setRedEnd(float redEnd);
    void setHighLimit(float highLimit);

    void setNoColors(bool noColors);
    void setDynamicBarberpole(bool dynamicBarberpole);

    void setHasLowLimit(bool hasLowLimit);
    void setHasFlapsSpeed(bool hasFlapsSpeed);
    void setHasGreenSpeed(bool hasGreenSpeed);
    void setHasYellowSpeed(bool hasYellowSpeed);
    void setHasRedSpeed(bool hasRedSpeed);
    void setHasHighLimit(bool hasHighLimit);

    void aircraftSaved()
    {
        d_lastSavedDefinition = d_definition;
        d_unsavedChanges = false;

        d_gauge1.aircraftSaved();
        d_gauge2.aircraftSaved();
        d_gauge3.aircraftSaved();
        d_gauge4.aircraftSaved();
        d_fuelQtyGauge.aircraftSaved();
        d_fuelFlowGauge.aircraftSaved();
        d_oilTempGauge.aircraftSaved();
        d_secondaryTempGauge.aircraftSaved();
        d_oilPressGauge.aircraftSaved();

        emit unsavedChangesChanged();
    }

signals:

    void typeChanged();

    void nameChanged();

    void gauge1TypeChanged();
    void gauge2TypeChanged();
    void gauge3TypeChanged();
    void gauge4TypeChanged();

    void engineTempTypeChanged();

    void maxPowerChanged();
    void maxTorqueChanged();

    void hasApuChanged();

    void hasFlapsChanged();
    void hasSpoilersChanged();

    void hasElevatorTrimChanged();
    void hasRudderTrimChanged();
    void hasAileronTrimChanged();

    void hasSecondaryTempGaugeChanged();
    void secondaryTempTypeChanged();

    void numEnginesChanged();
    void singleTankChanged();

    void lowLimitChanged();
    void flapsBeginChanged();
    void flapsEndChanged();
    void greenBeginChanged();
    void greenEndChanged();
    void yellowBeginChanged();
    void yellowEndChanged();
    void redBeginChanged();
    void redEndChanged();
    void highLimitChanged();

    void noColorsChanged();
    void dynamicBarberpoleChanged();

    void hasLowLimitChanged();
    void hasFlapsSpeedChanged();
    void hasGreenSpeedChanged();
    void hasYellowSpeedChanged();
    void hasRedSpeedChanged();
    void hasHighLimitChanged();

    void unsavedChangesChanged();

private slots:

    void checkForUnsavedChanges()
    {
        bool unsavedChanges = (d_definition.gauge1Type != SwitchingGaugeType::NONE && d_gauge1.unsavedChanges())
            || (d_definition.gauge2Type != SwitchingGaugeType::NONE && d_gauge2.unsavedChanges())
            || (d_definition.gauge3Type != SwitchingGaugeType::NONE && d_gauge3.unsavedChanges())
            || (d_definition.gauge4Type != SwitchingGaugeType::NONE && d_gauge4.unsavedChanges())
            || d_fuelQtyGauge.unsavedChanges()
            || d_fuelFlowGauge.unsavedChanges()
            || d_oilTempGauge.unsavedChanges()
            || (d_definition.hasSecondaryTempGauge && d_secondaryTempGauge.unsavedChanges())
            || d_oilPressGauge.unsavedChanges()
            || d_definition.localDiffers(d_lastSavedDefinition);

        if (d_unsavedChanges != unsavedChanges)
        {
            d_unsavedChanges = unsavedChanges;
            emit unsavedChangesChanged();
        }
    }

private:

    static UnitModel *gaugeTypeToModel(SwitchingGaugeType type)
    {
        switch (type)
        {
            case SwitchingGaugeType::N1:
            case SwitchingGaugeType::N2:
                return &d_percentModel;
            case SwitchingGaugeType::ENGINE_TEMP:
                return &d_temperatureModel;
            case SwitchingGaugeType::RPM:
            case SwitchingGaugeType::PROP_RPM:
                return &d_rpmModel;
            case SwitchingGaugeType::POWER:
                return &d_powerModel;
            case SwitchingGaugeType::MANIFOLD_PRESSURE:
                return &d_pressureModel;
            case SwitchingGaugeType::TORQUE:
                return &d_torqueModel;
            case SwitchingGaugeType::NONE:
            default:
                return &d_unitlessModel;
        }
    }

    definitions::AircraftDefinition d_definition;
    definitions::AircraftDefinition d_lastSavedDefinition;

    QmlGaugeDefinition d_gauge1;
    QmlGaugeDefinition d_gauge2;
    QmlGaugeDefinition d_gauge3;
    QmlGaugeDefinition d_gauge4;

    QmlGaugeDefinition d_fuelQtyGauge;
    QmlGaugeDefinition d_fuelFlowGauge;
    QmlGaugeDefinition d_oilTempGauge;
    QmlGaugeDefinition d_secondaryTempGauge;
    QmlGaugeDefinition d_oilPressGauge;

    bool d_unsavedChanges = false;

    bool d_hasLowLimit = true;
    bool d_hasFlapsSpeed = true;
    bool d_hasGreenSpeed = true;
    bool d_hasYellowSpeed = true;
    bool d_hasRedSpeed = true;
    bool d_hasHighLimit = true;

    inline static UnitModel d_unitlessModel = UnitModel(UnitModel::NONE, QApplication::instance());
    inline static UnitModel d_percentModel = UnitModel(UnitModel::PERCENT, QApplication::instance());
    inline static UnitModel d_rpmModel = UnitModel(UnitModel::RPM, QApplication::instance());
    inline static UnitModel d_temperatureModel = UnitModel(UnitModel::TEMPERATURE, QApplication::instance());
    inline static UnitModel d_pressureModel = UnitModel(UnitModel::PRESSURE, QApplication::instance());
    inline static UnitModel d_torqueModel = UnitModel(UnitModel::TORQUE, QApplication::instance());
    inline static UnitModel d_powerModel = UnitModel(UnitModel::POWER, QApplication::instance());
    inline static UnitModel d_volOrWghtModel = UnitModel(UnitModel::VOL_OR_WGHT, QApplication::instance());
    inline static UnitModel d_volOrWghtRateModel = UnitModel(UnitModel::VOL_OR_WGHT_RATE, QApplication::instance());
};

#endif  // __QML_AIRCRAFT_DEFINITION_HPP__
