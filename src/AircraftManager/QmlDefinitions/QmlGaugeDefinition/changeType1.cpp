#include "QmlGaugeDefinition.hpp"

void QmlGaugeDefinition::changeType(SwitchingGaugeType type, TemperatureGaugeType tempType, UnitModel *newModel)
{
    d_unitModel = newModel;
    switch (type)
    {
        case SwitchingGaugeType::N1:
        {
            d_definition->title = "N1";
            d_definition->unitString = "%";
            d_definition->unit = Units::PERCENT;
            break;
        }
        case SwitchingGaugeType::N2:
        {
            d_definition->title = "N2";
            d_definition->unitString = "%";
            d_definition->unit = Units::PERCENT;
            break;
        }
        case SwitchingGaugeType::ENGINE_TEMP:
        {
            switch (tempType)
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
            d_definition->unitString = "ºC";
            d_definition->unit = Units::CELSIUS;
            break;
        }
        case SwitchingGaugeType::RPM:
        case SwitchingGaugeType::PROP_RPM:
        {
            d_definition->title = "RPM";
            d_definition->unitString = "";
            d_definition->unit = Units::RPM;
            break;
        }
        case SwitchingGaugeType::POWER:
        {
            d_definition->title = "PWR";
            d_definition->unitString = "hp";
            d_definition->unit = Units::HP_METRIC;
            break;
        }
        case SwitchingGaugeType::MANIFOLD_PRESSURE:
        {
            d_definition->title = "MAN";
            d_definition->unitString = "kPa";
            d_definition->unit = Units::KILOPASCAL;
            break;
        }
        case SwitchingGaugeType::TORQUE:
        {
            d_definition->title = "TRQ";
            d_definition->unitString = "N·M";
            d_definition->unit = Units::NEWTONMETER;
            break;
        }
        default:
        {
            d_definition->title = "";
            d_definition->unitString = "";
            d_definition->unit = Units::NONE;
            break;
        }
    }

    emit unitModelChanged();
    emit titleChanged();
    emit unitStringChanged();
    emit unitChanged();

    d_unsavedChanges = *d_definition != d_lastSavedDefinition;
}
