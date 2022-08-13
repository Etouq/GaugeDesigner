#include "QmlGaugeDefinition.hpp"

void QmlGaugeDefinition::changeType(TemperatureGaugeType type)
{
    switch (type)
    {
        case TemperatureGaugeType::EGT:
        {
            d_definition->title = "EGT";
            break;
        }
        case TemperatureGaugeType::ITT:
        {
            d_definition->title = "ITT";
            break;
        }
        case TemperatureGaugeType::CHT:
        {
            d_definition->title = "CHT";
            break;
        }
        case TemperatureGaugeType::TIT:
        {
            d_definition->title = "TIT";
            break;
        }
    }

    emit titleChanged();

    d_unsavedChanges = *d_definition != d_lastSavedDefinition;
}
