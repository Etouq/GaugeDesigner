#include "GaugeElement.hpp"

namespace preview
{

void GaugeElement::setGaugeParameters(const definitions::GaugeDefinition &gaugeDef, double length)
{
    d_isCircular = false;

    d_def = gaugeDef;

    d_length = length;

    if (d_def.forceTextColor)
    {
        d_color = d_def.textForcedColor;

        emit colorChanged();
    }

    if (d_def.noText)
    {
        d_value = "";
    }

    d_cursorPosOffset = (d_def.minValue * length) / (d_def.maxValue - d_def.minValue);
    d_cursorPosFactor = length / (d_def.maxValue - d_def.minValue);

    update(d_def.minValue);

    d_redBlink = false;

    emit redBlinkChanged();
}

}  // namespace pages::mfd
