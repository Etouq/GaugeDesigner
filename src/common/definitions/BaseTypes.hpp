#ifndef __BASETYPES_HPP__
#define __BASETYPES_HPP__

#include <QColor>
#include <QString>
#include <cmath>

namespace definitions
{

static constexpr double DEF_EPS = 1e-5;

// fileversion for aircraft definition files
enum class FileVersion : uint16_t
{
    V1,
    V2,
    V3
};

struct ColorZone
{
    double start = 0;
    double end = 100;
    QColor color = Qt::darkGreen;

    bool operator==(const ColorZone &rhs) const
    {
        return std::abs(start - rhs.start) <= DEF_EPS && std::abs(end - rhs.end) <= DEF_EPS && color == rhs.color;
    }

    bool operator!=(const ColorZone &rhs) const
    {
        return std::abs(start - rhs.start) > DEF_EPS || std::abs(end - rhs.end) > DEF_EPS || color != rhs.color;
    }
};

struct GradDef
{
    double gradPos = 0;
    bool isBig = false;
    QColor gradColor = Qt::white;  // to allow for colorlines

    bool operator==(const GradDef &rhs) const
    {
        return std::abs(gradPos - rhs.gradPos) <= DEF_EPS && isBig == rhs.isBig && gradColor == rhs.gradColor;
    }

    bool operator!=(const GradDef &rhs) const
    {
        return std::abs(gradPos - rhs.gradPos) > DEF_EPS || isBig != rhs.isBig || gradColor != rhs.gradColor;
    }
};

struct TextGradDef
{
    double textGradPos = 0;
    QString gradText;

    bool operator==(const TextGradDef &rhs) const
    {
        return std::abs(textGradPos - rhs.textGradPos) <= DEF_EPS && gradText == rhs.gradText;
    }

    bool operator!=(const TextGradDef &rhs) const
    {
        return std::abs(textGradPos - rhs.textGradPos) > DEF_EPS || gradText != rhs.gradText;
    }
};

struct ReferenceSpeed
{
    uint16_t speed = 85;
    QString designator;

    bool operator==(const ReferenceSpeed &rhs) const
    {
        return speed == rhs.speed && designator == rhs.designator;
    }

    bool operator!=(const ReferenceSpeed &rhs) const
    {
        return speed != rhs.speed || designator != rhs.designator;
    }
};

}  // namespace definitions


#endif  // __BASETYPES_HPP__
