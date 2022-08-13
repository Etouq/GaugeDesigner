#ifndef __BASETYPES_HPP__
#define __BASETYPES_HPP__

#include <QColor>
#include <QString>
#include <cmath>

namespace definitions
{

static constexpr double EPSILON = 1e-5;

// fileversion for aircraft definition files
enum class FileVersion : uint16_t
{
    V1,
    V2,
    V3
};

struct ColorZone
{
    double start;
    double end;
    QColor color;

    bool operator==(const ColorZone &rhs) const
    {
        return std::abs(start - rhs.start) <= EPSILON && std::abs(end - rhs.end) <= EPSILON && color == rhs.color;
    }

    bool operator!=(const ColorZone &rhs) const
    {
        return std::abs(start - rhs.start) > EPSILON || std::abs(end - rhs.end) > EPSILON || color != rhs.color;
    }
};

struct GradDef
{
    double gradPos = 0;
    bool isBig = false;
    QColor gradColor = "white";  // to allow for colorlines

    bool operator==(const GradDef &rhs) const
    {
        return std::abs(gradPos - rhs.gradPos) <= EPSILON && isBig == rhs.isBig && gradColor == rhs.gradColor;
    }

    bool operator!=(const GradDef &rhs) const
    {
        return std::abs(gradPos - rhs.gradPos) > EPSILON || isBig != rhs.isBig || gradColor != rhs.gradColor;
    }
};

struct TextGradDef
{
    double textGradPos = 0;
    QString gradText;

    bool operator==(const TextGradDef &rhs) const
    {
        return std::abs(textGradPos - rhs.textGradPos) <= EPSILON && gradText == rhs.gradText;
    }

    bool operator!=(const TextGradDef &rhs) const
    {
        return std::abs(textGradPos - rhs.textGradPos) > EPSILON || gradText != rhs.gradText;
    }
};

struct ReferenceSpeed
{
    uint16_t speed;
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
