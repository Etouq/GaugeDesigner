#ifndef GAUGELOADER_H
#define GAUGELOADER_H

#include "AircraftManager/definitions/gaugeDefinition.h"

#include <QObject>

class GaugeInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double engineAngle READ engineAngle NOTIFY engineAngleChanged)
    Q_PROPERTY(
      double engineTransformValue READ engineTransformValue NOTIFY engineTransformValueChanged)
    Q_PROPERTY(QString engineValue READ engineValue NOTIFY engineValueChanged)
    Q_PROPERTY(QColor engineColor READ engineColor NOTIFY engineColorChanged)
    Q_PROPERTY(bool engineRedBlink READ engineRedBlink NOTIFY engineRedBlinkChanged)

    bool d_isCircular = false;

    GaugeDefinition def;

    double d_startAngle = 0;
    double d_endAngle;
    double d_length;

    double d_cursorPosOffset;
    double d_cursorPosFactor;

    bool d_engineRedBlink;
    double d_engineAngle;
    double d_engineTransformValue;
    QString d_engineValue;
    QColor d_engineColor;

    double d_currValue = 0;
    double d_stepSize = 1;
    bool d_incrementing = true;

public:
    explicit GaugeInterface(QObject *parent = nullptr);

    void setGaugeParameters(const GaugeDefinition &gaugeDef, double startAngle, double endAngle);
    void setGaugeParameters(const GaugeDefinition &gaugeDef, double length);

    void setDefinition(const GaugeDefinition &newDef);

    Q_INVOKABLE QString getTitle() const;
    Q_INVOKABLE int getUnit() const;
    Q_INVOKABLE QString getUnitString() const;
    Q_INVOKABLE double getMinValue() const;
    Q_INVOKABLE double getMaxValue() const;

    Q_INVOKABLE double getStartAngle() const;
    Q_INVOKABLE double getEndAngle() const;

    // colorzones
    Q_INVOKABLE int numColorZones() const;

    Q_INVOKABLE double colorZoneStartAt(int idx) const;

    Q_INVOKABLE double colorZoneEndAt(int idx) const;

    Q_INVOKABLE QColor colorZoneColorAt(int idx) const;


    // grads
    Q_INVOKABLE int numGrads() const;

    Q_INVOKABLE double gradValAt(int idx) const;

    Q_INVOKABLE bool gradIsBigAt(int idx) const;

    Q_INVOKABLE QColor gradColorAt(int idx) const;


    // textgrads
    Q_INVOKABLE int numTextGrads() const;

    Q_INVOKABLE double textGradValAt(int idx) const;

    Q_INVOKABLE QString gradTextAt(int idx) const;

    Q_INVOKABLE bool needsExtraWide() const;


    Q_INVOKABLE double getTextIncrement() const;
    Q_INVOKABLE int getTextNumDigits() const;

    Q_INVOKABLE bool getForceTextColor() const;
    Q_INVOKABLE QColor getTextForcedColor() const;

    Q_INVOKABLE bool getHasMinRedBlink() const;
    Q_INVOKABLE double getMinRedBlinkThreshold() const;
    Q_INVOKABLE bool getHasMaxRedBlink() const;
    Q_INVOKABLE double getMaxRedBlinkThreshold() const;

    Q_INVOKABLE bool getNoText() const;


    double engineAngle() const;
    double engineTransformValue() const;
    const QString &engineValue() const;
    const QColor &engineColor() const;
    bool engineRedBlink() const;


    // setters
    Q_INVOKABLE void setTitleAndUnit(const QString &title, int unit, const QString &unitString);
    Q_INVOKABLE void setRange(double minValue, double maxValue);

    Q_INVOKABLE void setNumColorZones(int count);
    Q_INVOKABLE void setColorZoneAt(int idx, double start, double end, const QString &color);

    Q_INVOKABLE void setNumGrads(int count);
    Q_INVOKABLE void setGradAt(int idx, double pos, bool isBig, const QString &color);

    Q_INVOKABLE void setNumTextGrads(int count);
    Q_INVOKABLE void setTextGradAt(int idx, double pos, const QString &text);

    Q_INVOKABLE void setTextIncrement(double textIncrement, int numDecimals);

    Q_INVOKABLE void setForceTextColor(bool forceColor, const QString &color);

    Q_INVOKABLE void setMinBlink(bool hasMinBlink, double minBlinkThreshold);

    Q_INVOKABLE void setMaxBlink(bool hasMaxBlink, double maxBlinkThreshold);

    Q_INVOKABLE void setNoText(bool noText);

    Q_INVOKABLE void updateComplete();

    Q_INVOKABLE void updateEngineAnimation();

    Q_INVOKABLE void updateEngine(double newVal);


signals:
    void updateGauge();
    void gaugeUpdated(const GaugeDefinition &gauge);

    void engineAngleChanged();
    void engineTransformValueChanged();
    void engineValueChanged();
    void engineColorChanged();
    void engineRedBlinkChanged();
};

#endif   // GAUGELOADER_H
