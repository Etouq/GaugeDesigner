#include "MiscElement.hpp"

#include <cmath>

namespace preview
{

void MiscElement::updateFlaps(double newVal)
{
    d_flapsAngle = newVal;
    emit flapsAngleChanged();

    const int roundedAngle = std::lround(newVal);
    const bool newShowFlapsText = roundedAngle != 0;

    if (d_showFlapsText != newShowFlapsText)
    {
        d_showFlapsText = newShowFlapsText;
        emit showFlapsTextChanged();
    }
    if (d_showFlapsText)
    {
        if (const QString newFlapsValue = QString::number(roundedAngle) + "º"; d_flapsValue != newFlapsValue)
        {
            d_flapsValue = newFlapsValue;
            emit flapsValueChanged();
        }
    }
}

}  // namespace preview