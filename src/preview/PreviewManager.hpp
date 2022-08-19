#ifndef __PREVIEW_MANAGER_HPP__
#define __PREVIEW_MANAGER_HPP__

#include "GaugeElement/GaugeElement.hpp"
#include "MiscElement/MiscElement.hpp"

#include <QObject>

namespace definitions
{
struct AircraftDefinition;
}

namespace preview
{

class PreviewManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString layoutPath READ layoutPath NOTIFY layoutPathChanged)

public:

    PreviewManager(QObject *parent = nullptr);

    Q_INVOKABLE void resetAnimation()
    {
        d_animationPct = 0;
        d_animationStep = std::abs(d_animationStep);

        d_gauge1.update(d_animationPct);
        d_gauge2.update(d_animationPct);
        d_gauge3.update(d_animationPct);
        d_gauge4.update(d_animationPct);

        d_fuelQtyGauge.update(d_animationPct);
        d_fuelFlowGauge.update(d_animationPct);
        d_oilTempGauge.update(d_animationPct);
        d_secondaryTempGauge.update(d_animationPct);
        d_oilPressGauge.update(d_animationPct);

        d_miscElement.update(d_animationPct);
    }

    const QString &layoutPath() const
    {
        return d_layoutPath;
    }

signals:

    void layoutPathChanged();

public slots:

    void loadAircraft(const definitions::AircraftDefinition &aircraft);

    void update()
    {
        d_gauge1.update(d_animationPct);
        d_gauge2.update(d_animationPct);
        d_gauge3.update(d_animationPct);
        d_gauge4.update(d_animationPct);

        d_fuelQtyGauge.update(d_animationPct);
        d_fuelFlowGauge.update(d_animationPct);
        d_oilTempGauge.update(d_animationPct);
        d_secondaryTempGauge.update(d_animationPct);
        d_oilPressGauge.update(d_animationPct);

        d_miscElement.update(d_animationPct);

        d_animationPct += d_animationStep;

        if (d_animationPct < 0.0 || d_animationPct > 1.0) {
            d_animationStep = -d_animationStep;
            d_animationPct += 2 * d_animationStep;
        }
    }

    GaugeElement *gauge1()
    {
        return &d_gauge1;
    }

    GaugeElement *gauge2()
    {
        return &d_gauge2;
    }

    GaugeElement *gauge3()
    {
        return &d_gauge3;
    }

    GaugeElement *gauge4()
    {
        return &d_gauge4;
    }

    GaugeElement *fuelQtyGauge()
    {
        return &d_fuelQtyGauge;
    }

    GaugeElement *fuelFlowGauge()
    {
        return &d_fuelFlowGauge;
    }

    GaugeElement *oilTempGauge()
    {
        return &d_oilTempGauge;
    }

    GaugeElement *oilPressGauge()
    {
        return &d_oilPressGauge;
    }

    GaugeElement *secondaryTempGauge()
    {
        return &d_secondaryTempGauge;
    }

private:

    // changing gauges
    GaugeElement d_gauge1;
    GaugeElement d_gauge2;
    GaugeElement d_gauge3;
    GaugeElement d_gauge4;


    // regular, mostly present gauges
    GaugeElement d_fuelQtyGauge;
    GaugeElement d_fuelFlowGauge;

    GaugeElement d_oilTempGauge;
    GaugeElement d_secondaryTempGauge;
    GaugeElement d_oilPressGauge;

    MiscElement d_miscElement;

    double d_animationPct = 0;
    double d_animationStep = 0.001;

    QString d_layoutPath;
};

}  // namespace preview

#endif  // __PREVIEW_MANAGER_HPP__