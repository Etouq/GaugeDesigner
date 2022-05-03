#include "unitconverter.hpp"
#include "units.hpp"

QVector<int>
  UnitConverter::getAllowedUnits(int type)
{
    switch (type)
    {
        case 1:  // percent
            return { static_cast<int>(Units::PERCENT) };
        case 2:  // rpm
            return { static_cast<int>(Units::RPM) };
        case 3:  // temperature
            return { static_cast<int>(Units::CELSIUS),
                     static_cast<int>(Units::KELVIN),
                     static_cast<int>(Units::FAHRENHEIT),
                     static_cast<int>(Units::RANKINE) };
        case 4:  // pressure
            return { static_cast<int>(Units::KILOPASCAL),  static_cast<int>(Units::INHG),
                     static_cast<int>(Units::BAR),         static_cast<int>(Units::PSI),
                     static_cast<int>(Units::PASCAL_UNIT), static_cast<int>(Units::MMHG),
                     static_cast<int>(Units::CMHG),        static_cast<int>(Units::ATM),
                     static_cast<int>(Units::PSF),         static_cast<int>(Units::MBAR),
                     static_cast<int>(Units::HECTOPASCAL), static_cast<int>(Units::MMH2O),
                     static_cast<int>(Units::CMH2O),       static_cast<int>(Units::INH2O) };
        case 5:  // torque
            return { static_cast<int>(Units::NEWTONMETER),
                     static_cast<int>(Units::FOOTPOUND),
                     static_cast<int>(Units::INCHPOUND) };
        case 6:  // weight
            return { static_cast<int>(Units::KG),     static_cast<int>(Units::TONNE), static_cast<int>(Units::SLUG),
                     static_cast<int>(Units::GRAM),   static_cast<int>(Units::LBS),   static_cast<int>(Units::USTONNE),
                     static_cast<int>(Units::UKTONNE) };
        case 7:  // volume
            return { static_cast<int>(Units::LITRES),  static_cast<int>(Units::CUBICCM),
                     static_cast<int>(Units::ML),      static_cast<int>(Units::CUBICM),
                     static_cast<int>(Units::CUBICIN), static_cast<int>(Units::CUBICDM),
                     static_cast<int>(Units::OZUS),    static_cast<int>(Units::OZUK),
                     static_cast<int>(Units::QUARTUS), static_cast<int>(Units::QUARTUK),
                     static_cast<int>(Units::CUBICFT), static_cast<int>(Units::CUBICYD),
                     static_cast<int>(Units::USGAL),   static_cast<int>(Units::UKGAL) };
        case 8:  // weight per hour
            return { static_cast<int>(Units::KG_PER_HOUR),     static_cast<int>(Units::TONNE_PER_HOUR),
                     static_cast<int>(Units::SLUG_PER_HOUR),   static_cast<int>(Units::GRAM_PER_HOUR),
                     static_cast<int>(Units::LBS_PER_HOUR),    static_cast<int>(Units::USTONNE_PER_HOUR),
                     static_cast<int>(Units::UKTONNE_PER_HOUR) };
        case 9:  // volume per hour
            return { static_cast<int>(Units::LITRES_PER_HOUR),  static_cast<int>(Units::CUBICCM_PER_HOUR),
                     static_cast<int>(Units::ML_PER_HOUR),      static_cast<int>(Units::CUBICM_PER_HOUR),
                     static_cast<int>(Units::CUBICIN_PER_HOUR), static_cast<int>(Units::CUBICDM_PER_HOUR),
                     static_cast<int>(Units::OZUS_PER_HOUR),    static_cast<int>(Units::OZUK_PER_HOUR),
                     static_cast<int>(Units::QUARTUS_PER_HOUR), static_cast<int>(Units::QUARTUK_PER_HOUR),
                     static_cast<int>(Units::CUBICFT_PER_HOUR), static_cast<int>(Units::CUBICYD_PER_HOUR),
                     static_cast<int>(Units::USGAL_PER_HOUR),   static_cast<int>(Units::UKGAL_PER_HOUR) };
        case 10:  // weight per minute
            return { static_cast<int>(Units::KG_PER_MINUTE),     static_cast<int>(Units::TONNE_PER_MINUTE),
                     static_cast<int>(Units::SLUG_PER_MINUTE),   static_cast<int>(Units::GRAM_PER_MINUTE),
                     static_cast<int>(Units::LBS_PER_MINUTE),    static_cast<int>(Units::USTONNE_PER_MINUTE),
                     static_cast<int>(Units::UKTONNE_PER_MINUTE) };
        case 11:  // volume per minute
            return { static_cast<int>(Units::LITRES_PER_MINUTE),  static_cast<int>(Units::CUBICCM_PER_MINUTE),
                     static_cast<int>(Units::ML_PER_MINUTE),      static_cast<int>(Units::CUBICM_PER_MINUTE),
                     static_cast<int>(Units::CUBICIN_PER_MINUTE), static_cast<int>(Units::CUBICDM_PER_MINUTE),
                     static_cast<int>(Units::OZUS_PER_MINUTE),    static_cast<int>(Units::OZUK_PER_MINUTE),
                     static_cast<int>(Units::QUARTUS_PER_MINUTE), static_cast<int>(Units::QUARTUK_PER_MINUTE),
                     static_cast<int>(Units::CUBICFT_PER_MINUTE), static_cast<int>(Units::CUBICYD_PER_MINUTE),
                     static_cast<int>(Units::USGAL_PER_MINUTE),   static_cast<int>(Units::UKGAL_PER_MINUTE) };
        case 12:  // weight per second
            return { static_cast<int>(Units::KG_PER_SECOND),     static_cast<int>(Units::TONNE_PER_SECOND),
                     static_cast<int>(Units::SLUG_PER_SECOND),   static_cast<int>(Units::GRAM_PER_SECOND),
                     static_cast<int>(Units::LBS_PER_SECOND),    static_cast<int>(Units::USTONNE_PER_SECOND),
                     static_cast<int>(Units::UKTONNE_PER_SECOND) };
        case 13:  // volume per second
            return { static_cast<int>(Units::LITRES_PER_SECOND),  static_cast<int>(Units::CUBICCM_PER_SECOND),
                     static_cast<int>(Units::ML_PER_SECOND),      static_cast<int>(Units::CUBICM_PER_SECOND),
                     static_cast<int>(Units::CUBICIN_PER_SECOND), static_cast<int>(Units::CUBICDM_PER_SECOND),
                     static_cast<int>(Units::OZUS_PER_SECOND),    static_cast<int>(Units::OZUK_PER_SECOND),
                     static_cast<int>(Units::QUARTUS_PER_SECOND), static_cast<int>(Units::QUARTUK_PER_SECOND),
                     static_cast<int>(Units::CUBICFT_PER_SECOND), static_cast<int>(Units::CUBICYD_PER_SECOND),
                     static_cast<int>(Units::USGAL_PER_SECOND),   static_cast<int>(Units::UKGAL_PER_SECOND) };
        case 0:  // none
        default:
            return { static_cast<int>(Units::NONE) };
    }
}
