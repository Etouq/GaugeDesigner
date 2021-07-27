#include "aircraftinterface.h"

void AircraftInterface::updateN1Gauge(const GaugeDefinition &gauge)
{
    if (def.type == AircraftDefinition::AircraftType::JET)
    {
        JetDefinition jetDef = def.currentType.value<JetDefinition>();
        jetDef.n1Gauge = gauge;
        def.currentType.setValue(jetDef);
    }
    else if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
    {
        TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
        turbopropDef.n1Gauge = gauge;
        def.currentType.setValue(turbopropDef);
    }
}

void AircraftInterface::updateN2Gauge(const GaugeDefinition &gauge)
{
    if (def.type == AircraftDefinition::AircraftType::JET)
    {
        JetDefinition jetDef = def.currentType.value<JetDefinition>();
        jetDef.n2Gauge = gauge;
        def.currentType.setValue(jetDef);
    }
}

void AircraftInterface::updateIttGauge(const GaugeDefinition &gauge)
{
    if (def.type == AircraftDefinition::AircraftType::JET)
    {
        JetDefinition jetDef = def.currentType.value<JetDefinition>();
        jetDef.ittGauge = gauge;
        def.currentType.setValue(jetDef);
    }
    else if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
    {
        TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
        turbopropDef.ittGauge = gauge;
        def.currentType.setValue(turbopropDef);
    }
}

void AircraftInterface::updateRpmGauge(const GaugeDefinition &gauge)
{
    if (def.type == AircraftDefinition::AircraftType::PROP)
    {
        PropDefinition propDef = def.currentType.value<PropDefinition>();
        propDef.rpmGauge = gauge;
        def.currentType.setValue(propDef);
    }
    else if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
    {
        TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
        turbopropDef.rpmGauge = gauge;
        def.currentType.setValue(turbopropDef);
    }
}

void AircraftInterface::updateSecondGauge(const GaugeDefinition &gauge)
{
    if (def.type == AircraftDefinition::AircraftType::PROP)
    {
        PropDefinition propDef = def.currentType.value<PropDefinition>();
        propDef.secondGauge = gauge;
        def.currentType.setValue(propDef);
    }
}

void AircraftInterface::updateTrqGauge(const GaugeDefinition &gauge)
{
    if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
    {
        TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
        turbopropDef.trqGauge = gauge;
        turbopropDef.torqueAsPct = gauge.unit == Units::PERCENT;
        def.currentType.setValue(turbopropDef);
    }
}

void AircraftInterface::updateFuelQtyGauge(const GaugeDefinition &gauge)
{
    def.fuelQtyGauge = gauge;
    switch (def.fuelQtyGauge.unit)
    {
        case Units::LITRES:
        case Units::CUBICCM:
        case Units::ML:
        case Units::CUBICM:
        case Units::CUBICIN:
        case Units::CUBICDM:
        case Units::OZUS:
        case Units::OZUK:
        case Units::QUARTUS:
        case Units::QUARTUK:
        case Units::CUBICFT:
        case Units::CUBICYD:
        case Units::USGAL:
        case Units::UKGAL:
            def.fuelQtyByVolume = true;
            break;
        default:
            def.fuelQtyByVolume = false;
            break;
    }
}

void AircraftInterface::updateFuelFlowGauge(const GaugeDefinition &gauge)
{
    def.fuelFlowGauge = gauge;
    switch (def.fuelFlowGauge.unit)
    {
        case Units::LITRES_PER_HOUR:
        case Units::CUBICCM_PER_HOUR:
        case Units::ML_PER_HOUR:
        case Units::CUBICM_PER_HOUR:
        case Units::CUBICIN_PER_HOUR:
        case Units::CUBICDM_PER_HOUR:
        case Units::OZUS_PER_HOUR:
        case Units::OZUK_PER_HOUR:
        case Units::QUARTUS_PER_HOUR:
        case Units::QUARTUK_PER_HOUR:
        case Units::CUBICFT_PER_HOUR:
        case Units::CUBICYD_PER_HOUR:
        case Units::USGAL_PER_HOUR:
        case Units::UKGAL_PER_HOUR:
        case Units::LITRES_PER_MINUTE:
        case Units::CUBICCM_PER_MINUTE:
        case Units::ML_PER_MINUTE:
        case Units::CUBICM_PER_MINUTE:
        case Units::CUBICIN_PER_MINUTE:
        case Units::CUBICDM_PER_MINUTE:
        case Units::OZUS_PER_MINUTE:
        case Units::OZUK_PER_MINUTE:
        case Units::QUARTUS_PER_MINUTE:
        case Units::QUARTUK_PER_MINUTE:
        case Units::CUBICFT_PER_MINUTE:
        case Units::CUBICYD_PER_MINUTE:
        case Units::USGAL_PER_MINUTE:
        case Units::UKGAL_PER_MINUTE:
        case Units::LITRES_PER_SECOND:
        case Units::CUBICCM_PER_SECOND:
        case Units::ML_PER_SECOND:
        case Units::CUBICM_PER_SECOND:
        case Units::CUBICIN_PER_SECOND:
        case Units::CUBICDM_PER_SECOND:
        case Units::OZUS_PER_SECOND:
        case Units::OZUK_PER_SECOND:
        case Units::QUARTUS_PER_SECOND:
        case Units::QUARTUK_PER_SECOND:
        case Units::CUBICFT_PER_SECOND:
        case Units::CUBICYD_PER_SECOND:
        case Units::USGAL_PER_SECOND:
        case Units::UKGAL_PER_SECOND:
            def.fuelFlowByVolume = true;
            break;
        default:
            def.fuelFlowByVolume = false;
            break;
    }
}

void AircraftInterface::updateOilTempGauge(const GaugeDefinition &gauge)
{
    def.oilTempGauge = gauge;
}

void AircraftInterface::updateOilPressGauge(const GaugeDefinition &gauge)
{
    def.oilPressGauge = gauge;
}

void AircraftInterface::updateEgtGauge(const GaugeDefinition &gauge)
{
    if (def.type == AircraftDefinition::AircraftType::PROP)
    {
        PropDefinition propDef = def.currentType.value<PropDefinition>();
        propDef.egtGauge = gauge;
        def.currentType.setValue(propDef);
    }
    else if (def.type == AircraftDefinition::AircraftType::TURBOPROP)
    {
        TurbopropDefinition turbopropDef = def.currentType.value<TurbopropDefinition>();
        turbopropDef.egtGauge = gauge;
        def.currentType.setValue(turbopropDef);
    }
}
