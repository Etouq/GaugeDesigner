#include "MiscElement.hpp"

#include <cmath>

namespace preview
{

void MiscElement::updateSpoilers(double newVal)
{
    d_spoilersAngle = newVal * d_spoilersMaxAngle;
    emit spoilersAngleChanged();

    const int pctValue = std::lround(newVal * 100.0);
    const bool newShowSpoilersText = pctValue != 0;

    if (d_showSpoilersText != newShowSpoilersText)
    {
        d_showSpoilersText = newShowSpoilersText;
        emit showSpoilersTextChanged();
    }
    if (d_showSpoilersText)
    {
        if (const QString newSpoilersValue = QString::number(pctValue) + "%"; d_spoilersValue != newSpoilersValue)
        {
            d_spoilersValue = newSpoilersValue;
            emit spoilersValueChanged();
        }
    }
}

}  // namespace preview