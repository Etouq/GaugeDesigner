#ifndef __MISC_ELEMENT_HPP__
#define __MISC_ELEMENT_HPP__

#include <QObject>

namespace preview
{

class MiscElement : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double spoilersAngle READ spoilersAngle NOTIFY spoilersAngleChanged)
    Q_PROPERTY(QString spoilersValue READ spoilersValue NOTIFY spoilersValueChanged)
    Q_PROPERTY(bool showSpoilersText READ showSpoilersText NOTIFY showSpoilersTextChanged)

    Q_PROPERTY(double flapsAngle READ flapsAngle NOTIFY flapsAngleChanged)
    Q_PROPERTY(QString flapsValue READ flapsValue NOTIFY flapsValueChanged)
    Q_PROPERTY(bool showFlapsText READ showFlapsText NOTIFY showFlapsTextChanged)

    Q_PROPERTY(double trimTransformValue READ trimTransformValue NOTIFY trimTransformValueChanged)
    Q_PROPERTY(QString trimValue READ trimValue NOTIFY trimValueChanged)

public:

    MiscElement(QObject *parent = nullptr)
      : QObject(parent)
    {}

    void setParameters(bool hasApu,
                       bool hasSecondaryTempGauge,
                       bool hasFlaps,
                       bool hasSpoilers,
                       bool hasElevatorTrim,
                       bool hasRudderTrim,
                       bool hasAileronTrim)
    {
        d_hasApu = hasApu;
        d_hasSecondaryTempGauge = hasSecondaryTempGauge;

        d_hasFlaps = hasFlaps;
        d_hasSpoilers = hasSpoilers;

        d_hasElevatorTrim = hasElevatorTrim;
        d_hasRudderTrim = hasRudderTrim;
        d_hasAileronTrim = hasAileronTrim;
    }

    // basic info
    Q_INVOKABLE bool hasApu() const
    {
        return d_hasApu;
    }

    Q_INVOKABLE bool hasSecondaryTempGauge() const
    {
        return d_hasSecondaryTempGauge;
    }

    Q_INVOKABLE bool hasSingleTank() const
    {
        return d_hasSingleTank;
    }

    Q_INVOKABLE bool hasSpoilers() const
    {
        return d_hasSpoilers;
    }

    Q_INVOKABLE bool hasFlaps() const
    {
        return d_hasFlaps;
    }

    Q_INVOKABLE bool hasElevatorTrim() const
    {
        return d_hasElevatorTrim;
    }

    Q_INVOKABLE bool hasRudderTrim() const
    {
        return d_hasRudderTrim;
    }

    Q_INVOKABLE bool hasAileronTrim() const
    {
        return d_hasAileronTrim;
    }

    // flaps\spoilers
    double spoilersAngle() const
    {
        return d_spoilersAngle;
    }

    const QString &spoilersValue() const
    {
        return d_spoilersValue;
    }

    bool showSpoilersText() const
    {
        return d_showSpoilersText;
    }

    double flapsAngle() const
    {
        return d_flapsAngle;
    }

    const QString &flapsValue() const
    {
        return d_flapsValue;
    }

    bool showFlapsText() const
    {
        return d_showFlapsText;
    }

    // trims
    double trimTransformValue() const
    {
        return d_trimTransformValue;
    }

    const QString &trimValue() const
    {
        return d_trimValue;
    }

signals:

    void spoilersAngleChanged();
    void spoilersValueChanged();
    void showSpoilersTextChanged();

    void flapsAngleChanged();
    void flapsValueChanged();
    void showFlapsTextChanged();

    void trimTransformValueChanged();
    void trimValueChanged();

public slots:

    void update(double newPct)
    {
        static constexpr double flapsMinAngle = -10;
        static constexpr double flapsMaxAngle =  45;

        updateFlaps(newPct * (flapsMaxAngle - flapsMinAngle) + flapsMinAngle);
        updateSpoilers(newPct);
        updateTrim(newPct);
    }

private:

    void updateFlaps(double newVal);
    void updateSpoilers(double newVal);
    void updateTrim(double newPct);

    bool d_hasApu = false;
    bool d_hasSecondaryTempGauge = false;
    bool d_hasSingleTank = false;

    // flaps\spoilers
    static constexpr double d_spoilersMaxAngle = -60;
    double d_spoilersAngle = 0;
    QString d_spoilersValue = "0%";
    bool d_showSpoilersText = false;
    bool d_hasSpoilers = false;
    double d_flapsAngle = 0;
    QString d_flapsValue = "0º";
    bool d_showFlapsText = false;
    bool d_hasFlaps = false;

    // trims
    bool d_hasElevatorTrim = false;
    bool d_hasRudderTrim = false;
    bool d_hasAileronTrim = false;
    double d_trimTransformValue = 0;
    QString d_trimValue = "0%";
};

}  // namespace preview

#endif  // __MISC_ELEMENT_HPP__