#include "unitconverter.hpp"


QString UnitConverter::getSectionHeader(int type)
{
    switch (type)
    {
        case 3:   // temperature
            return "Temperature";
        case 4:   // pressure
            return "Pressure";
        case 5:   // torque
            return "Torque";
        case 6:   // weight
            return "Weight";
        case 7:   // volume
            return "Volume";
        case 8:   // weight per hour
            return "Weight Per Hr";
        case 9:   // volume per hour
            return "Volume Per Hr";
        case 10:   // weight per minute
            return "Weight Per Min";
        case 11:   // volume per minute
            return "Volume Per Min";
        case 12:   // weight per second
            return "Weight Per Sec";
        case 13:   // volume per second
            return "Volume Per Sec";
        case 0:   // none
        case 1:   // percent
        case 2:   // rpm
        default:
            return "";
    }
}


