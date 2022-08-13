#ifndef __QML_GAUGE_DEFINITION_HPP__
#define __QML_GAUGE_DEFINITION_HPP__

#include "common/TypeEnums.hpp"
#include "common/UnitModel/UnitModel.hpp"
#include "common/definitions/GaugeDefinition/GaugeDefinition.hpp"

#include <QObject>

class QmlGaugeDefinition : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString unitString READ unitString WRITE setUnitString NOTIFY unitStringChanged)
    Q_PROPERTY(double minValue READ minValue WRITE setMinValue NOTIFY minValueChanged)
    Q_PROPERTY(double maxValue READ maxValue WRITE setmaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(double textIncrement READ textIncrement WRITE setTextIncrement NOTIFY textIncrementChanged)
    Q_PROPERTY(int textNumDigits READ textNumDigits WRITE setTextNumDigits NOTIFY textNumDigitsChanged)
    Q_PROPERTY(bool forceTextColor READ forceTextColor WRITE setForceTextColor NOTIFY forceTextColorChanged)
    Q_PROPERTY(QColor textForcedColor READ textForcedColor WRITE setTextForcedColor NOTIFY textForcedColorChanged)
    Q_PROPERTY(bool hasMinRedBlink READ hasMinRedBlink WRITE setHasMinRedBlink NOTIFY hasMinRedBlinkChanged)
    Q_PROPERTY(double minRedBlinkThreshold READ minRedBlinkThreshold WRITE setMinRedBlinkThreshold NOTIFY
                 minRedBlinkThresholdChanged)
    Q_PROPERTY(bool hasMaxRedBlink READ hasMaxRedBlink WRITE setHasMaxRedBlink NOTIFY hasMaxRedBlinkChanged)
    Q_PROPERTY(double maxRedBlinkThreshold READ maxRedBlinkThreshold WRITE setMaxRedBlinkThreshold NOTIFY
                 maxRedBlinkThresholdChanged)
    Q_PROPERTY(bool noText READ noText WRITE setNoText NOTIFY noTextChanged)
    Q_PROPERTY(int unit READ unit WRITE setUnit NOTIFY unitChanged)

    Q_PROPERTY(UnitModel *unitModel READ unitModel NOTIFY unitModelChanged)


public:

    QmlGaugeDefinition(definitions::GaugeDefinition *definition,
                       UnitModel *unitModel,
                       QObject *parent = nullptr)
      : QObject(parent),
        d_definition(definition),
        d_lastSavedDefinition(*definition),
        d_unitModel(unitModel)
    {}

    void changeDefinition(definitions::GaugeDefinition *newDefinition, UnitModel *newModel, bool fromNewAircraft = false);

    void changeType(SwitchingGaugeType type, TemperatureGaugeType tempType, UnitModel *newModel);
    void changeType(TemperatureGaugeType type);

    void changeModel(UnitModel *newModel)
    {
        d_unitModel = newModel;
        emit unitModelChanged();
    }

    UnitModel *unitModel();

    const QString &title() const;
    const QString &unitString() const;
    double minValue() const;
    double maxValue() const;
    double textIncrement() const;
    int textNumDigits() const;
    bool forceTextColor() const;
    QColor textForcedColor() const;
    bool hasMinRedBlink() const;
    double minRedBlinkThreshold() const;
    bool hasMaxRedBlink() const;
    double maxRedBlinkThreshold() const;
    bool noText() const;
    int unit() const;

    bool unsavedChanges() const;

    void setTitle(const QString &title);
    void setUnitString(const QString &unitString);
    void setMinValue(double minValue);
    void setmaxValue(double maxValue);
    void setTextIncrement(double textIncrement);
    void setTextNumDigits(int textNumDigits);
    void setForceTextColor(bool forceTextColor);
    void setTextForcedColor(QColor textForcedColor);
    void setHasMinRedBlink(bool hasMinRedBlink);
    void setMinRedBlinkThreshold(double minRedBlinkThreshold);
    void setHasMaxRedBlink(bool hasMaxRedBlink);
    void setMaxRedBlinkThreshold(double maxRedBlinkThreshold);
    void setNoText(bool noText);
    void setUnit(int unit);

signals:

    void titleChanged();
    void unitStringChanged();

    void minValueChanged();
    void maxValueChanged();

    void textIncrementChanged();
    void textNumDigitsChanged();

    void forceTextColorChanged();
    void textForcedColorChanged();

    void hasMinRedBlinkChanged();
    void minRedBlinkThresholdChanged();
    void hasMaxRedBlinkChanged();
    void maxRedBlinkThresholdChanged();

    void noTextChanged();

    void unitChanged();

    void unitModelChanged();

    void unsavedChangesChanged();

private:

    void checkForUnsavedChanges()
    {
        bool unsavedChanges = *d_definition != d_lastSavedDefinition;
        if (unsavedChanges != d_unsavedChanges)
        {
            d_unsavedChanges = unsavedChanges;
            emit unsavedChangesChanged();
        }
    }

    definitions::GaugeDefinition *d_definition;
    definitions::GaugeDefinition d_lastSavedDefinition;

    UnitModel *d_unitModel;

    bool d_unsavedChanges = false;

};

#endif  // __QML_GAUGE_DEFINITION_HPP__