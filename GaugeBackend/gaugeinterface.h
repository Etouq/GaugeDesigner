#ifndef GAUGELOADER_H
#define GAUGELOADER_H

#include <QObject>
#include "AircraftManager/definitions/gaugeDefinition.h"

class GaugeInterface : public QObject
{
    Q_OBJECT

    GaugeDefinition def;
public:
    explicit GaugeInterface(QObject *parent = nullptr);

    void setDefinition(const GaugeDefinition &newDef)
    {
        def = newDef;
        emit updateGauge();
    }

    Q_INVOKABLE QString getTitle() const { return def.title; }
    Q_INVOKABLE int getUnit() const { return static_cast<int>(def.unit); }
    Q_INVOKABLE QString getUnitString() const { return def.unitString; }
    Q_INVOKABLE double getMinValue() const { return def.minValue; }
    Q_INVOKABLE double getMaxValue() const { return def.maxValue; }

    //colorzones
    Q_INVOKABLE int numColorZones() const { return def.colorZones.size(); }

    Q_INVOKABLE double colorZoneStartAt(int idx) const { return def.colorZones.at(idx).start; }

    Q_INVOKABLE double colorZoneEndAt(int idx) const { return def.colorZones.at(idx).end; }

    Q_INVOKABLE QColor colorZoneColorAt(int idx) const { return def.colorZones.at(idx).color; }


    //grads
    Q_INVOKABLE int numGrads() const { return def.grads.size(); }

    Q_INVOKABLE double gradValAt(int idx) const { return def.grads.at(idx).gradPos; }

    Q_INVOKABLE bool gradIsBigAt(int idx) const { return def.grads.at(idx).isBig; }

    Q_INVOKABLE QColor gradColorAt(int idx) const { return def.grads.at(idx).gradColor; }


    //textgrads
    Q_INVOKABLE int numTextGrads() const { return def.textGrads.size(); }

    Q_INVOKABLE double textGradValAt(int idx) const { return def.textGrads.at(idx).textGradPos; }

    Q_INVOKABLE QString gradTextAt(int idx) const { return def.textGrads.at(idx).gradText; }


    Q_INVOKABLE double getTextIncrement() const { return def.textIncrement; }
    Q_INVOKABLE int getTextNumDigits() const { return def.textNumDigits; }

    Q_INVOKABLE bool getForceTextColor() const { return def.forceTextColor; }
    Q_INVOKABLE QColor getTextForcedColor() const { return def.textForcedColor.isValid() ? def.textForcedColor : "white"; }

    Q_INVOKABLE bool getHasMinRedBlink() const { return def.hasMinRedBlink; }
    Q_INVOKABLE double getMinRedBlinkThreshold() const { return def.minRedBlinkThreshold; }
    Q_INVOKABLE bool getHasMaxRedBlink() const { return def.hasMaxRedBlink; }
    Q_INVOKABLE double getMaxRedBlinkThreshold() const { return def.maxRedBlinkThreshold; }

    Q_INVOKABLE bool getNoText() const { return def.noText; }



    //setters
    Q_INVOKABLE void setTitleAndUnit(const QString &title, int unit, const QString &unitString)
    {
        def.title = title;
        def.unit = static_cast<Units>(unit);
        def.unitString = unitString;
    }
    Q_INVOKABLE void setRange(double minValue, double maxValue)
    {
        def.minValue = minValue;
        def.maxValue = maxValue;
    }

    Q_INVOKABLE void setNumColorZones(int count)
    {
        def.colorZones.resize(count);
    }
    Q_INVOKABLE void setColorZoneAt(int idx, double start, double end, const QString &color)
    {
        def.colorZones[idx] = ColorZone{ .start = start, .end = end, .color = color };
    }

    Q_INVOKABLE void setNumGrads(int count)
    {
        def.grads.resize(count);
    }
    Q_INVOKABLE void setGradAt(int idx, double pos, bool isBig, const QString &color)
    {
        def.grads[idx] = GradDef{ .gradPos = pos, .isBig = isBig, .gradColor = color };
    }

    Q_INVOKABLE void setNumTextGrads(int count)
    {
        def.textGrads.resize(count);
    }
    Q_INVOKABLE void setTextGradAt(int idx, double pos, const QString &text)
    {
        def.textGrads[idx] = TextGradDef{ .textGradPos = pos, .gradText = text };
    }

    Q_INVOKABLE void setTextIncrement(double textIncrement, int numDecimals)
    {
        def.textIncrement = textIncrement;
        def.textNumDigits = numDecimals;
    }

    Q_INVOKABLE void setForceTextColor(bool forceColor, const QString &color)
    {
        def.forceTextColor = forceColor;
        def.textForcedColor = color;
    }

    Q_INVOKABLE void setMinBlink(bool hasMinBlink, double minBlinkThreshold)
    {
        def.hasMinRedBlink = hasMinBlink;
        def.minRedBlinkThreshold = minBlinkThreshold;
    }

    Q_INVOKABLE void setMaxBlink(bool hasMaxBlink, double maxBlinkThreshold)
    {
        def.hasMaxRedBlink = hasMaxBlink;
        def.maxRedBlinkThreshold = maxBlinkThreshold;
    }

    Q_INVOKABLE void setNoText(bool noText)
    {
        def.noText = noText;
    }

    Q_INVOKABLE void updateComplete()
    {
        emit gaugeUpdated(def);
    }


signals:
    void updateGauge();
    void gaugeUpdated(const GaugeDefinition &gauge);

};

#endif // GAUGELOADER_H
