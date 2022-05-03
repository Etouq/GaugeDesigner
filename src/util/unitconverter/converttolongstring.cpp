#include "unitconverter.hpp"
#include "units.hpp"


QString UnitConverter::convertToLongString(int unitInt)
{
    Units unit = Units(unitInt);
    switch (unit)
    {
        case Units::NONE:
            return "";
        case Units::PERCENT:
            return "Percent";
        case Units::RPM:
            return "Rpm";
        case Units::CELSIUS:
            return "Celcius";
        case Units::KILOPASCAL:
            return "Kilopascal";
        case Units::NEWTONMETER:
            return "Newton Metre";
        case Units::LITRES:
            return "Litre";
        case Units::CUBICDM:
            return "Cubic dm";
        case Units::KG:
            return "Kilogram";
        case Units::LITRES_PER_HOUR:
            return "Litres Per Hour";
        case Units::CUBICDM_PER_HOUR:
            return "Cubic dm Per Hour";
        case Units::KG_PER_HOUR:
            return "Kg Per Hour";
        // temperature
        case Units::FAHRENHEIT:
            return "Fahrenheit";
        case Units::KELVIN:
            return "Kelvin";
        case Units::RANKINE:
            return "Rankine";
        // pressure
        case Units::INHG:
            return "Inch of Mercury";
        case Units::BAR:
            return "Bar";
        case Units::PSI:
            return "Pound per Square Inch";
        case Units::PASCAL_UNIT:
            return "Pascal";
        case Units::MMHG:
            return "Millimetre of Mercury";
        case Units::CMHG:
            return "Centimetre of Mercury";
        case Units::ATM:
            return "Standard Atmosphere";
        case Units::PSF:
            return "Pound per Square Foot";
        case Units::MBAR:
            return "Millibar";
        case Units::HECTOPASCAL:
            return "Hectopascal";
        case Units::MMH2O:
            return "Millimetre of Water";
        case Units::CMH2O:
            return "Centimetre of H2O";
        case Units::INH2O:
            return "Inch of H2O";
        // torque
        case Units::FOOTPOUND:
            return "Footpound";
        case Units::INCHPOUND:
            return "Inchpound";
        // volume
        case Units::CUBICCM:
            return "Cubic cm";
        case Units::CUBICCM_PER_HOUR:
            return "Cubic cm Per Hour";
        case Units::ML:
            return "Millilitre";
        case Units::ML_PER_HOUR:
            return "Millilitre Per Hour";
        case Units::CUBICM:
            return "Cubic Metre";
        case Units::CUBICM_PER_HOUR:
            return "Cubic Metre Per Hour";
        case Units::CUBICIN:
            return "Cubic Inch";
        case Units::CUBICIN_PER_HOUR:
            return "Cubic Inch Per Hour";
        case Units::OZUS:
            return "Ounce (US)";
        case Units::OZUS_PER_HOUR:
            return "Ounce (US) Per Hour";
        case Units::OZUK:
            return "Ounce (UK)";
        case Units::OZUK_PER_HOUR:
            return "Ounce (UK) Per Hour";
        case Units::QUARTUS:
            return "Quart (US)";
        case Units::QUARTUS_PER_HOUR:
            return "Quart (US) Per Hour";
        case Units::QUARTUK:
            return "Quart (UK)";
        case Units::QUARTUK_PER_HOUR:
            return "Quart (UK) Per Hour";
        case Units::CUBICFT:
            return "Cubic Feet";
        case Units::CUBICFT_PER_HOUR:
            return "Cubic Feet Per Hour";
        case Units::CUBICYD:
            return "Cubic Yard";
        case Units::CUBICYD_PER_HOUR:
            return "Cubic Yard Per Hour";
        case Units::USGAL:
            return "Gallon (US)";
        case Units::USGAL_PER_HOUR:
            return "Gallon (US) Per Hour";
        case Units::UKGAL:
            return "Gallon (UK)";
        case Units::UKGAL_PER_HOUR:
            return "Gallon (UK) Per Hour";
        // weight
        case Units::TONNE:
            return "Tonne";
        case Units::TONNE_PER_HOUR:
            return "Tonnes Per Hour";
        case Units::SLUG:
            return "Slug";
        case Units::SLUG_PER_HOUR:
            return "Slugs Per Hour";
        case Units::GRAM:
            return "Gram";
        case Units::GRAM_PER_HOUR:
            return "Gram Per Hour";
        case Units::LBS:
            return "Pound";
        case Units::LBS_PER_HOUR:
            return "Pounds Per Hour";
        case Units::USTONNE:
            return "Tonne (US)";
        case Units::USTONNE_PER_HOUR:
            return "Tonnes (US) Per Hour";
        case Units::UKTONNE:
            return "Tonne (UK)";
        case Units::UKTONNE_PER_HOUR:
            return "Tonnes (UK) Per Hour";
        // volume rate
        case Units::LITRES_PER_MINUTE:
            return "Litres Per Minute";
        case Units::CUBICDM_PER_MINUTE:
            return "Cubic dm Per Minute";
        case Units::CUBICCM_PER_MINUTE:
            return "Cubic cm Per Minute";
        case Units::ML_PER_MINUTE:
            return "Millilitres Per Minute";
        case Units::CUBICM_PER_MINUTE:
            return "Cubic Metres Per Minute";
        case Units::CUBICIN_PER_MINUTE:
            return "Cubic Inch Per Minute";
        case Units::OZUS_PER_MINUTE:
            return "Ounce (US) Per Minute";
        case Units::OZUK_PER_MINUTE:
            return "Ounce (UK) Per Minute";
        case Units::QUARTUS_PER_MINUTE:
            return "Quart (US) Per Minute";
        case Units::QUARTUK_PER_MINUTE:
            return "Quart (UK) Per Minute";
        case Units::CUBICFT_PER_MINUTE:
            return "Cubic Feet Per Minute";
        case Units::CUBICYD_PER_MINUTE:
            return "Cubic Yard Per Minute";
        case Units::USGAL_PER_MINUTE:
            return "Gallon (US) Per Minute";
        case Units::UKGAL_PER_MINUTE:
            return "Gallon (UK) Per Minute";
        case Units::LITRES_PER_SECOND:
            return "Litres Per Second";
        case Units::CUBICDM_PER_SECOND:
            return "Cubic dm Per Second";
        case Units::CUBICCM_PER_SECOND:
            return "Cubic cm Per Second";
        case Units::ML_PER_SECOND:
            return "Millilitres Per Second";
        case Units::CUBICM_PER_SECOND:
            return "Cubic Metres Per Second";
        case Units::CUBICIN_PER_SECOND:
            return "Cubic Inch Per Second";
        case Units::OZUS_PER_SECOND:
            return "Ounce (US) Per Second";
        case Units::OZUK_PER_SECOND:
            return "Ounce (UK) Per Second";
        case Units::QUARTUS_PER_SECOND:
            return "Quart (US) Per Second";
        case Units::QUARTUK_PER_SECOND:
            return "Quart (UK) Per Second";
        case Units::CUBICFT_PER_SECOND:
            return "Cubic Feet Per Second";
        case Units::CUBICYD_PER_SECOND:
            return "Cubic Yard Per Second";
        case Units::USGAL_PER_SECOND:
            return "Gallon (US) Per Second";
        case Units::UKGAL_PER_SECOND:
            return "Gallon (UK) Per Second";
        // weight rate
        case Units::KG_PER_MINUTE:
            return "Kilogram Per Minute";
        case Units::TONNE_PER_MINUTE:
            return "Tonne Per Minute";
        case Units::SLUG_PER_MINUTE:
            return "Slug Per Minute";
        case Units::GRAM_PER_MINUTE:
            return "Gram Per Minute";
        case Units::LBS_PER_MINUTE:
            return "Pound Per Minute";
        case Units::USTONNE_PER_MINUTE:
            return "Tonne (US) Per Minute";
        case Units::UKTONNE_PER_MINUTE:
            return "Tonne (UK) Per Minute";
        case Units::KG_PER_SECOND:
            return "Kilogram Per Second";
        case Units::TONNE_PER_SECOND:
            return "Tonne Per Second";
        case Units::SLUG_PER_SECOND:
            return "Slug Per Second";
        case Units::GRAM_PER_SECOND:
            return "Gram Per Second";
        case Units::LBS_PER_SECOND:
            return "Pound Per Second";
        case Units::USTONNE_PER_SECOND:
            return "Tonne (US) Per Second";
        case Units::UKTONNE_PER_SECOND:
            return "Tonne (UK) Per Second";
        default:
            return "Unknown Unit: " + QString::number(unitInt);
    }
}
