#include "MiscElement.hpp"

#include <cmath>

namespace preview
{

void MiscElement::updateTrim(double newPct)
{
    d_trimTransformValue = newPct * 60.0;
    emit trimTransformValueChanged();

    const int trimPct = std::lround(newPct * 100.0);

    if (const QString newValue = (trimPct < 0 ? "" : " ") + QString::number(trimPct) + "%"; d_trimValue != newValue)
    {
        d_trimValue = newValue;
        emit trimValueChanged();
    }
}

}  // namespace preview