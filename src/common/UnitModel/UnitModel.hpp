#ifndef __UNIT_MODEL_HPP__
#define __UNIT_MODEL_HPP__

#include "common/Units.hpp"

#include <QAbstractListModel>
#include <string>
#include <vector>
#include <bitset>

class UnitModel : public QAbstractListModel
{
    Q_OBJECT

    struct UnitEntry
    {
        int unitId;
        QString longText;
        QString shortText;
        QString unitSection;
    };

public:

    enum UnitRoles
    {
        UnitIdRole = Qt::UserRole + 1,
        LongTextRole,
        ShortTextRole,
        SectionRole
    };

    enum UnitType
    {
        NONE = 0,
        PERCENT = 0x1,
        RPM = 0x2,
        TEMPERATURE = 0x4,
        PRESSURE = 0x8,
        TORQUE = 0x10,
        POWER = 0x20,
        VOL_OR_WGHT = 0x40,
        VOL_OR_WGHT_RATE = 0x80
    };
    Q_DECLARE_FLAGS(UnitTypes, UnitType)

    explicit UnitModel(UnitType type, QObject *parent = nullptr)
      : QAbstractListModel(parent),
        d_data(getTypeValues(type))
    {}

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QString getShortText(int index) const
    {
        if (index < 0 || index >= d_data.size())
            return "";

        return d_data[index].shortText;
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        Q_UNUSED(parent);
        return d_data.size();
    }

protected:

    QHash<int, QByteArray> roleNames() const
    {
        return { { UnitIdRole, "unitId" },
                 { LongTextRole, "longText" },
                 { ShortTextRole, "shortText" },
                 { SectionRole, "unitSection" } };
    }

private:

    static const std::vector<UnitEntry> &getTypeValues(UnitType type)
    {
        switch (type)
        {
            default:
            case UnitType::NONE:
                return d_unitless;
            case UnitType::PERCENT:
                return d_percent;
            case UnitType::RPM:
                return d_rpm;
            case UnitType::TEMPERATURE:
                return d_temperature;
            case UnitType::PRESSURE:
                return d_pressure;
            case UnitType::TORQUE:
                return d_torque;
            case UnitType::POWER:
                return d_power;
            case UnitType::VOL_OR_WGHT:
                return d_volOrWght;
            case UnitType::VOL_OR_WGHT_RATE:
                return d_volOrWghtRate;
        }
    }


    const std::vector<UnitEntry> &d_data;

    // inline static const std::vector<UnitEntry> d_ = ;
    inline static const std::vector<UnitEntry> d_unitless = { { static_cast<int>(Units::NONE), "", "", "" } };

    inline static const std::vector<UnitEntry> d_percent = { { static_cast<int>(Units::PERCENT), "Percent", "%", "" } };
    inline static const std::vector<UnitEntry> d_rpm = {
        { static_cast<int>(Units::PERCENT), "Percent", "%", "Percent" },
        { static_cast<int>(Units::RPM), "Rpm", "", "Rpm" } };

    inline static const std::vector<UnitEntry> d_temperature = {
        { static_cast<int>(Units::CELSIUS), "Celcius", "ºC", "" },
        { static_cast<int>(Units::FAHRENHEIT), "Fahrenheit", "ºF", "" },
        { static_cast<int>(Units::KELVIN), "Kelvin", "K", "" },
        { static_cast<int>(Units::RANKINE), "Rankine", "ºR", "" }
    };

    inline static const std::vector<UnitEntry> d_pressure = {
        { static_cast<int>(Units::KILOPASCAL), "Kilopascal", "kPa", "" },
        { static_cast<int>(Units::INHG), "Inch of Mercury", "InHg", "" },
        { static_cast<int>(Units::PSI), "Pound per Square Inch", "PSI", "" },
        { static_cast<int>(Units::BAR), "Bar", "Bar", "" },
        { static_cast<int>(Units::PASCAL_UNIT), "Pascal", "P", "" },
        { static_cast<int>(Units::MMHG), "Millimetre of Mercury", "mmHg", "" },
        { static_cast<int>(Units::CMHG), "Centimetre of Mercury", "cmHg", "" },
        { static_cast<int>(Units::ATM), "Standard Atmosphere", "Atm", "" },
        { static_cast<int>(Units::PSF), "Pound per Square Foot", "PSF", "" },
        { static_cast<int>(Units::MBAR), "Millibar", "mBar", "" },
        { static_cast<int>(Units::HECTOPASCAL), "Hectopascal", "hPa", "" },
        { static_cast<int>(Units::MMH2O), "Millimetre of Water", "mmH₂O", "" },
        { static_cast<int>(Units::CMH2O), "Centimetre of Water", "cmH₂O", "" },
        { static_cast<int>(Units::INH2O), "Inch of Water", "InH₂O", "" }
    };

    inline static const std::vector<UnitEntry> d_torque = {
        { static_cast<int>(Units::PERCENT), "Percent", "%", "Percent" },
        { static_cast<int>(Units::NEWTONMETER), "Newton Metre", "N·M", "Torque" },
        { static_cast<int>(Units::FOOTPOUND), "Footpound", "Ft-lbs", "Torque" },
        { static_cast<int>(Units::INCHPOUND), "Inchpound", "In-lbs", "Torque" }
    };

    inline static const std::vector<UnitEntry> d_power = {
        { static_cast<int>(Units::PERCENT), "Percent", "%", "Percent" },
        { static_cast<int>(Units::HP_IMPERIAL), "Horsepower (l)", "hp", "Power" },
        { static_cast<int>(Units::HP_METRIC), "Horsepower (M)", "hp", "Power" },
        { static_cast<int>(Units::WATT), "watt", "W", "Power" },
        { static_cast<int>(Units::KILOWATT), "Kilowatt", "KW", "Power" },
        { static_cast<int>(Units::FT_LBF_HOUR), "foot-pounds p/h", "Ft·lbf/h", "Power" },
        { static_cast<int>(Units::FT_LBF_MIN), "foot-pounds p/m", "Ft·lbf/m", "Power" },
        { static_cast<int>(Units::FT_LBF_SEC), "foot-pounds p/s", "Ft·lbf/s", "Power" }
    };

    inline static const std::vector<UnitEntry> d_volOrWght = {
        // volume
        { static_cast<int>(Units::LITRES), "Litre", "L", "Volume" },
        { static_cast<int>(Units::USGAL), "Gallon (US)", "GAL", "Volume" },
        { static_cast<int>(Units::UKGAL), "Gallon (UK)", "GAL", "Volume" },
        { static_cast<int>(Units::CUBICDM), "Cubic dm", "dm³", "Volume" },
        { static_cast<int>(Units::CUBICCM), "Cubic cm", "cm³", "Volume" },
        { static_cast<int>(Units::ML), "Millilitre", "ml", "Volume" },
        { static_cast<int>(Units::CUBICM), "Cubic Metre", "m³", "Volume" },
        { static_cast<int>(Units::CUBICIN), "Cubic Inch", "In³", "Volume" },
        { static_cast<int>(Units::OZUS), "Ounce (US)", "Oz", "Volume" },
        { static_cast<int>(Units::OZUK), "Ounce (UK)", "Oz", "Volume" },
        { static_cast<int>(Units::QUARTUS), "Quart (US)", "qt", "Volume" },
        { static_cast<int>(Units::QUARTUK), "Quart (UK)", "qt", "Volume" },
        { static_cast<int>(Units::CUBICFT), "Cubic Feet", "Ft³", "Volume" },
        { static_cast<int>(Units::CUBICYD), "Cubic Yard", "Yd³", "Volume" },
        // weight
        { static_cast<int>(Units::KG), "Kilogram", "KG", "Weight" },
        { static_cast<int>(Units::LBS), "Pound", "lbs", "Weight" },
        { static_cast<int>(Units::GRAM), "Gram", "gr", "Weight" },
        { static_cast<int>(Units::TONNE), "Tonne", "TONNE", "Weight" },
        { static_cast<int>(Units::USTONNE), "Tonne (US)", "TONNE", "Weight" },
        { static_cast<int>(Units::UKTONNE), "Tonne (UK)", "TONNE", "Weight" },
        { static_cast<int>(Units::SLUG), "Slug", "Slug", "Weight" }
    };

    inline static const std::vector<UnitEntry> d_volOrWghtRate = {
        // volume per hour
        { static_cast<int>(Units::LITRES_PER_HOUR), "Litres Per Hour", "LH", "Volume p/h" },
        { static_cast<int>(Units::USGAL_PER_HOUR), "Gallon (US) Per Hour", "GPH", "Volume p/h" },
        { static_cast<int>(Units::UKGAL_PER_HOUR), "Gallon (UK) Per Hour", "GPH", "Volume p/h" },
        { static_cast<int>(Units::CUBICDM_PER_HOUR), "Cubic dm Per Hour", "dm³H", "Volume p/h" },
        { static_cast<int>(Units::CUBICCM_PER_HOUR), "Cubic cm Per Hour", "cm³H", "Volume p/h" },
        { static_cast<int>(Units::ML_PER_HOUR), "Millilitre Per Hour", "mlH", "Volume p/h" },
        { static_cast<int>(Units::CUBICM_PER_HOUR), "Cubic Metre Per Hour", "m³H", "Volume p/h" },
        { static_cast<int>(Units::CUBICIN_PER_HOUR), "Cubic Inch Per Hour", "In³H", "Volume p/h" },
        { static_cast<int>(Units::OZUS_PER_HOUR), "Ounce (US) Per Hour", "OzH", "Volume p/h" },
        { static_cast<int>(Units::OZUK_PER_HOUR), "Ounce (UK) Per Hour", "OzH", "Volume p/h" },
        { static_cast<int>(Units::QUARTUS_PER_HOUR), "Quart (US) Per Hour", "qtH", "Volume p/h" },
        { static_cast<int>(Units::QUARTUK_PER_HOUR), "Quart (UK) Per Hour", "qtH", "Volume p/h" },
        { static_cast<int>(Units::CUBICFT_PER_HOUR), "Cubic Feet Per Hour", "Ft³H", "Volume p/h" },
        { static_cast<int>(Units::CUBICYD_PER_HOUR), "Cubic Yard Per Hour", "Yd³H", "Volume p/h" },
        // weight per hour
        { static_cast<int>(Units::KG_PER_HOUR), "Kg Per Hour", "KGH", "Weight p/h" },
        { static_cast<int>(Units::LBS_PER_HOUR), "Pounds Per Hour", "PPH", "Weight p/h" },
        { static_cast<int>(Units::GRAM_PER_HOUR), "Gram Per Hour", "grH", "Weight p/h" },
        { static_cast<int>(Units::TONNE_PER_HOUR), "Tonnes Per Hour", "TPH", "Weight p/h" },
        { static_cast<int>(Units::USTONNE_PER_HOUR), "Tonnes (US) Per Hour", "TPH", "Weight p/h" },
        { static_cast<int>(Units::UKTONNE_PER_HOUR), "Tonnes (UK) Per Hour", "TPH", "Weight p/h" },
        { static_cast<int>(Units::SLUG_PER_HOUR), "Slugs Per Hour", "SPH", "Weight p/h" },
        // volume per minute
        { static_cast<int>(Units::LITRES_PER_MINUTE), "Litres Per Minute", "LPM", "Volume p/m" },
        { static_cast<int>(Units::USGAL_PER_MINUTE), "Gallon (US) Per Minute", "GPM", "Volume p/m" },
        { static_cast<int>(Units::UKGAL_PER_MINUTE), "Gallon (UK) Per Minute", "GPM", "Volume p/m" },
        { static_cast<int>(Units::CUBICDM_PER_MINUTE), "Cubic dm Per Minute", "dm³M", "Volume p/m" },
        { static_cast<int>(Units::CUBICCM_PER_MINUTE), "Cubic cm Per Minute", "cm³M", "Volume p/m" },
        { static_cast<int>(Units::ML_PER_MINUTE), "Millilitres Per Minute", "mlM", "Volume p/m" },
        { static_cast<int>(Units::CUBICM_PER_MINUTE), "Cubic Metres Per Minute", "m³M", "Volume p/m" },
        { static_cast<int>(Units::CUBICIN_PER_MINUTE), "Cubic Inch Per Minute", "In³M", "Volume p/m" },
        { static_cast<int>(Units::OZUS_PER_MINUTE), "Ounce (US) Per Minute", "OPM", "Volume p/m" },
        { static_cast<int>(Units::OZUK_PER_MINUTE), "Ounce (UK) Per Minute", "OPM", "Volume p/m" },
        { static_cast<int>(Units::QUARTUS_PER_MINUTE), "Quart (US) Per Minute", "QPM", "Volume p/m" },
        { static_cast<int>(Units::QUARTUK_PER_MINUTE), "Quart (UK) Per Minute", "QPM", "Volume p/m" },
        { static_cast<int>(Units::CUBICFT_PER_MINUTE), "Cubic Feet Per Minute", "Ft³M", "Volume p/m" },
        { static_cast<int>(Units::CUBICYD_PER_MINUTE), "Cubic Yard Per Minute", "Yd³M", "Volume p/m" },
        // weight per minute
        { static_cast<int>(Units::KG_PER_MINUTE), "Kilogram Per Minute", "KGM", "Weight p/m" },
        { static_cast<int>(Units::LBS_PER_MINUTE), "Pound Per Minute", "PPM", "Weight p/m" },
        { static_cast<int>(Units::GRAM_PER_MINUTE), "Gram Per Minute", "grM", "Weight p/m" },
        { static_cast<int>(Units::TONNE_PER_MINUTE), "Tonne Per Minute", "TPM", "Weight p/m" },
        { static_cast<int>(Units::USTONNE_PER_MINUTE), "Tonne (US) Per Minute", "TPM", "Weight p/m" },
        { static_cast<int>(Units::UKTONNE_PER_MINUTE), "Tonne (UK) Per Minute", "TPM", "Weight p/m" },
        { static_cast<int>(Units::SLUG_PER_MINUTE), "Slug Per Minute", "SPM", "Weight p/m" },
        // volume per second
        { static_cast<int>(Units::LITRES_PER_SECOND), "Litres Per Second", "LPS", "Volume p/s" },
        { static_cast<int>(Units::USGAL_PER_SECOND), "Gallon (US) Per Second", "GPS", "Volume p/s" },
        { static_cast<int>(Units::UKGAL_PER_SECOND), "Gallon (UK) Per Second", "GPS", "Volume p/s" },
        { static_cast<int>(Units::CUBICDM_PER_SECOND), "Cubic dm Per Second", "dm³S", "Volume p/s" },
        { static_cast<int>(Units::CUBICCM_PER_SECOND), "Cubic cm Per Second", "cm³S", "Volume p/s" },
        { static_cast<int>(Units::ML_PER_SECOND), "Millilitres Per Second", "mlS", "Volume p/s" },
        { static_cast<int>(Units::CUBICM_PER_SECOND), "Cubic Metres Per Second", "m³S", "Volume p/s" },
        { static_cast<int>(Units::CUBICIN_PER_SECOND), "Cubic Inch Per Second", "In³S", "Volume p/s" },
        { static_cast<int>(Units::OZUS_PER_SECOND), "Ounce (US) Per Second", "OPS", "Volume p/s" },
        { static_cast<int>(Units::OZUK_PER_SECOND), "Ounce (UK) Per Second", "OPS", "Volume p/s" },
        { static_cast<int>(Units::QUARTUS_PER_SECOND), "Quart (US) Per Second", "QPS", "Volume p/s" },
        { static_cast<int>(Units::QUARTUK_PER_SECOND), "Quart (UK) Per Second", "QPS", "Volume p/s" },
        { static_cast<int>(Units::CUBICFT_PER_SECOND), "Cubic Feet Per Second", "Ft³S", "Volume p/s" },
        { static_cast<int>(Units::CUBICYD_PER_SECOND), "Cubic Yard Per Second", "Yd³S", "Volume p/s" },
        // weight per second
        { static_cast<int>(Units::KG_PER_SECOND), "Kilogram Per Second", "KPS", "Weight p/s" },
        { static_cast<int>(Units::LBS_PER_SECOND), "Pound Per Second", "PPS", "Weight p/s" },
        { static_cast<int>(Units::GRAM_PER_SECOND), "Gram Per Second", "grS", "Weight p/s" },
        { static_cast<int>(Units::TONNE_PER_SECOND), "Tonne Per Second", "TPS", "Weight p/s" },
        { static_cast<int>(Units::USTONNE_PER_SECOND), "Tonne (US) Per Second", "TPS", "Weight p/s" },
        { static_cast<int>(Units::UKTONNE_PER_SECOND), "Tonne (UK) Per Second", "TPS", "Weight p/s" },
        { static_cast<int>(Units::SLUG_PER_SECOND), "Slug Per Second", "SPS", "Weight p/s" }
    };
};

Q_DECLARE_OPERATORS_FOR_FLAGS(UnitModel::UnitTypes)

#endif  // __UNIT_MODEL_HPP__