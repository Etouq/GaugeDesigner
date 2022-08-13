#ifndef __GAUGE_ELEMENT_HPP__
#define __GAUGE_ELEMENT_HPP__

#include "common/definitions/GaugeDefinition/GaugeDefinition.hpp"

#include <QFont>
#include <QFontMetrics>
#include <QObject>

namespace preview
{

class GaugeElement : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double angle READ angle NOTIFY angleChanged)
    Q_PROPERTY(double transformValue READ transformValue NOTIFY transformValueChanged)
    Q_PROPERTY(QString value READ value NOTIFY valueChanged)
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
    Q_PROPERTY(bool redBlink READ redBlink NOTIFY redBlinkChanged)


public:

    explicit GaugeElement(QObject *parent = nullptr)
      : QObject(parent)
    {}

    void setGaugeParameters(const definitions::GaugeDefinition &gaugeDef, double startAngle, double endAngle);

    void setGaugeParameters(const definitions::GaugeDefinition &gaugeDef, double length);

    double angle() const
    {
        return d_angle;
    }

    double transformValue() const
    {
        return d_transformValue;
    }

    const QString &value() const
    {
        return d_value;
    }

    const QColor &color() const
    {
        return d_color;
    }

    bool redBlink() const
    {
        return d_redBlink;
    }

    // basic gauge info
    Q_INVOKABLE QString getTitle() const
    {
        return d_def.title;
    }

    Q_INVOKABLE int getUnit() const
    {
        return static_cast<int>(d_def.unit);
    }

    Q_INVOKABLE QString getUnitString() const
    {
        return d_def.unitString;
    }

    Q_INVOKABLE double getMinValue() const
    {
        return d_def.minValue;
    }

    Q_INVOKABLE double getMaxValue() const
    {
        return d_def.maxValue;
    }

    Q_INVOKABLE double getRange() const
    {
        return d_def.maxValue - d_def.minValue;
    }

    Q_INVOKABLE double getStartAngle() const
    {
        return d_startAngle;
    }

    Q_INVOKABLE double getEndAngle() const
    {
        return d_endAngle;
    }

    Q_INVOKABLE double getLength() const
    {
        return d_length;
    }

    Q_INVOKABLE double valueToAngle(double value) const
    {
        return d_cursorPosOffset + value * d_cursorPosFactor;
    }

    Q_INVOKABLE int valueMaxSize() const
    {
        if (d_def.noText)
            return 0;

        QString text =
          QString::number(round(d_def.minValue / d_def.textIncrement) * d_def.textIncrement, 'f', d_def.textNumDigits);
        QFont robotoFont("Roboto Mono", -1, QFont::Bold);
        robotoFont.setPixelSize(18);
        QFontMetrics metrics(robotoFont);

        int minValueWidth = metrics.horizontalAdvance(text);
        text =
          QString::number(round(d_def.maxValue / d_def.textIncrement) * d_def.textIncrement, 'f', d_def.textNumDigits);
        int maxValueWidth = metrics.horizontalAdvance(text);

        return std::max(minValueWidth, maxValueWidth);
    }

    Q_INVOKABLE int unitWidth() const
    {

        QFont robotoFont("Roboto Mono", -1, QFont::Bold);
        robotoFont.setPixelSize(18);
        QFontMetrics metrics(robotoFont);

        return metrics.horizontalAdvance(d_def.unitString);
    }

    // colorzones
    Q_INVOKABLE int numColorZones() const
    {
        return d_def.colorZones.size();
    }

    Q_INVOKABLE double colorZoneStartAt(int idx) const
    {
        return d_def.colorZones.at(idx).start;
    }

    Q_INVOKABLE double colorZoneEndAt(int idx) const
    {
        return d_def.colorZones.at(idx).end;
    }

    Q_INVOKABLE double colorZoneRangeAt(int idx) const
    {
        return d_def.colorZones.at(idx).end - d_def.colorZones.at(idx).start;
    }

    Q_INVOKABLE QColor colorZoneColorAt(int idx) const
    {
        return d_def.colorZones.at(idx).color;
    }

    // grads
    Q_INVOKABLE int numGrads() const
    {
        return d_def.grads.size();
    }

    Q_INVOKABLE double gradValAt(int idx) const
    {
        return d_def.grads.at(idx).gradPos;
    }

    Q_INVOKABLE bool gradIsBigAt(int idx) const
    {
        return d_def.grads.at(idx).isBig;
    }

    Q_INVOKABLE QColor gradColorAt(int idx) const
    {
        return d_def.grads.at(idx).gradColor;
    }

    // textgrads
    Q_INVOKABLE int numTextGrads() const
    {
        return d_def.textGrads.size();
    }

    Q_INVOKABLE double textGradValAt(int idx) const
    {
        return d_def.textGrads.at(idx).textGradPos;
    }

    Q_INVOKABLE QString gradTextAt(int idx) const
    {
        return d_def.textGrads.at(idx).gradText;
    }

    Q_INVOKABLE bool needsExtraWide() const
    {
        for (int i = 0; i < d_def.textGrads.size(); i++)
            if (d_def.textGrads[i].gradText.size() > 4)
                return true;
        return false;
    }

    Q_INVOKABLE int maxTextGradWidth() const
    {
        int ret = 0;

        QFont robotoFont("Roboto Mono", -1, QFont::Bold);
        robotoFont.setPixelSize(15);
        QFontMetrics metrics(robotoFont);

        for (const definitions::TextGradDef &textGrad : d_def.textGrads)
        {
            int width = metrics.horizontalAdvance(textGrad.gradText);
            if (width > ret)
                ret = width;
        }

        return ret;
    }

signals:

    void angleChanged();
    void transformValueChanged();
    void valueChanged();
    void colorChanged();
    void redBlinkChanged();

public slots:

    void update(double newValue);

private:

    definitions::GaugeDefinition d_def;

    double d_startAngle = 0;
    double d_endAngle = 0;
    double d_length = 0;

    bool d_isCircular = false;

    double d_cursorPosOffset;
    double d_cursorPosFactor;


    double d_angle;
    double d_transformValue;
    QString d_value;
    QColor d_color;
    bool d_redBlink;

};

}  // namespace preview


#endif  // __GAUGE_ELEMENT_HPP__