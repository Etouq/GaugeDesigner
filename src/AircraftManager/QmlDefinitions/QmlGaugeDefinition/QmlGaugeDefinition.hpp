#ifndef __QML_GAUGE_DEFINITION_HPP__
#define __QML_GAUGE_DEFINITION_HPP__

#include "common/TypeEnums.hpp"
#include "common/UnitModel/UnitModel.hpp"
#include "common/definitions/GaugeDefinition/GaugeDefinition.hpp"
#include "common/GaugeModels/ColorZoneModel/ColorZoneModel.hpp"
#include "common/GaugeModels/GradModel/GradModel.hpp"
#include "common/GaugeModels/TextGradModel/TextGradModel.hpp"

#include <QObject>
#include <QQmlEngine>

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
    Q_PROPERTY(ColorZoneModel *colorZoneModel READ colorZoneModel NOTIFY colorZoneModelChanged)
    Q_PROPERTY(GradModel *gradModel READ gradModel NOTIFY gradModelChanged)
    Q_PROPERTY(TextGradModel *textGradModel READ textGradModel NOTIFY textGradModelChanged)


public:

    QmlGaugeDefinition(definitions::GaugeDefinition *definition,
                       UnitModel *unitModel,
                       QObject *parent = nullptr)
      : QObject(parent),
        d_definition(definition),
        d_lastSavedDefinition(*definition),
        d_unitModel(unitModel)
    {
        d_colorZoneModel.changeData(definition->colorZones);
        d_gradModel.changeData(definition->grads);
        d_textGradModel.changeData(definition->textGrads);

        connect(&d_colorZoneModel, &ColorZoneModel::rowDeleted, this, &QmlGaugeDefinition::colorZoneRowDeleted);
        connect(&d_gradModel, &GradModel::rowDeleted, this, &QmlGaugeDefinition::gradRowDeleted);
        connect(&d_textGradModel, &TextGradModel::rowDeleted, this, &QmlGaugeDefinition::textGradRowDeleted);

        connect(&d_colorZoneModel, &ColorZoneModel::rowModified, this, &QmlGaugeDefinition::colorZoneRowModified);
        connect(&d_gradModel, &GradModel::rowModified, this, &QmlGaugeDefinition::gradRowModified);
        connect(&d_textGradModel, &TextGradModel::rowModified, this, &QmlGaugeDefinition::textGradRowModified);

        connect(&d_colorZoneModel, &ColorZoneModel::rowAppended, this, &QmlGaugeDefinition::colorZoneRowAppended);
        connect(&d_gradModel, &GradModel::rowAppended, this, &QmlGaugeDefinition::gradRowAppended);
        connect(&d_textGradModel, &TextGradModel::rowAppended, this, &QmlGaugeDefinition::textGradRowAppended);

        connect(&d_colorZoneModel, &ColorZoneModel::rowInserted, this, &QmlGaugeDefinition::colorZoneRowInserted);
        connect(&d_gradModel, &GradModel::rowInserted, this, &QmlGaugeDefinition::gradRowInserted);
        connect(&d_textGradModel, &TextGradModel::rowInserted, this, &QmlGaugeDefinition::textGradRowInserted);

        connect(&d_gradModel, &GradModel::dataGenerated, this, &QmlGaugeDefinition::gradsGenerated);
        connect(&d_textGradModel, &TextGradModel::dataGenerated, this, &QmlGaugeDefinition::textGradsGenerated);
    }

    void changeDefinition(definitions::GaugeDefinition *newDefinition, UnitModel *newModel, bool fromNewAircraft = false, bool fromSavedAircraft = false);

    void changeType(SwitchingGaugeType type, TemperatureGaugeType tempType, UnitModel *newModel);
    void changeType(TemperatureGaugeType type);

    void changeModel(UnitModel *newModel)
    {
        d_unitModel = newModel;
        emit unitModelChanged();
    }

    ColorZoneModel *colorZoneModel()
    {
        return &d_colorZoneModel;
    }
    GradModel *gradModel()
    {
        return &d_gradModel;
    }
    TextGradModel *textGradModel()
    {
        return &d_textGradModel;
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

    void aircraftSaved()
    {
        d_lastSavedDefinition = *d_definition;
        d_unsavedChanges = false;
    }

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
    void colorZoneModelChanged();
    void gradModelChanged();
    void textGradModelChanged();

    void unsavedChangesChanged();

private slots:

    void colorZoneRowDeleted(int index);
    void gradRowDeleted(int index);
    void textGradRowDeleted(int index);

    void colorZoneRowModified(int index, const definitions::ColorZone &row);
    void gradRowModified(int index, const definitions::GradDef &row);
    void textGradRowModified(int index, const definitions::TextGradDef &row);

    void colorZoneRowAppended(const definitions::ColorZone &row);
    void gradRowAppended(const definitions::GradDef &row);
    void textGradRowAppended(const definitions::TextGradDef &row);

    void colorZoneRowInserted(int index, const definitions::ColorZone &row);
    void gradRowInserted(int index, const definitions::GradDef &row);
    void textGradRowInserted(int index, const definitions::TextGradDef &row);

    void gradsGenerated(const QList<definitions::GradDef> &newData);
    void textGradsGenerated(const QList<definitions::TextGradDef> &newData);

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

    ColorZoneModel d_colorZoneModel;
    GradModel d_gradModel;
    TextGradModel d_textGradModel;

    bool d_unsavedChanges = false;

};

#endif  // __QML_GAUGE_DEFINITION_HPP__