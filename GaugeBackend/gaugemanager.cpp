#include "gaugemanager.h"

GaugeManager::GaugeManager(QObject *parent) : QObject(parent)
{

}


void GaugeManager::changeAircraft(const AircraftDefinition &aircraft)
{
    if (aircraft.type == AircraftDefinition::AircraftType::JET)//jet
    {
        JetDefinition jet = aircraft.currentType.value<JetDefinition>();
        n1Gauge.setDefinition(jet.n1Gauge);
        n2Gauge.setDefinition(jet.n2Gauge);
        ittGauge.setDefinition(jet.ittGauge);
    }
    else if(aircraft.type == AircraftDefinition::AircraftType::PROP)
    {
        PropDefinition prop = aircraft.currentType.value<PropDefinition>();
        rpmGauge.setDefinition(prop.rpmGauge);
        secondGauge.setDefinition(prop.secondGauge);
        egtGauge.setDefinition(prop.egtGauge);
    }
    else if(aircraft.type == AircraftDefinition::AircraftType::TURBOPROP)
    {
        TurbopropDefinition turboprop = aircraft.currentType.value<TurbopropDefinition>();
        n1Gauge.setDefinition(turboprop.n1Gauge);
        trqGauge.setDefinition(turboprop.trqGauge);
        ittGauge.setDefinition(turboprop.ittGauge);
        rpmGauge.setDefinition(turboprop.rpmGauge);
        egtGauge.setDefinition(turboprop.egtGauge);
    }
    else
        return;

    fuelQtyGauge.setDefinition(aircraft.fuelQtyGauge);
    fuelFlowGauge.setDefinition(aircraft.fuelFlowGauge);
    oilTempGauge.setDefinition(aircraft.oilTempGauge);
    oilPressGauge.setDefinition(aircraft.oilPressGauge);
}


void GaugeManager::addGaugesToContext(QQmlContext *context)
{
    context->setContextProperty("n1Interface", &n1Gauge);
    context->setContextProperty("n2Interface", &n2Gauge);
    context->setContextProperty("ittInterface", &ittGauge);
    context->setContextProperty("rpmInterface", &rpmGauge);
    context->setContextProperty("secondInterface", &secondGauge);
    context->setContextProperty("trqInterface", &trqGauge);
    context->setContextProperty("fuelQtyInterface", &fuelQtyGauge);
    context->setContextProperty("fuelFlowInterface", &fuelFlowGauge);
    context->setContextProperty("oilTempInterface", &oilTempGauge);
    context->setContextProperty("oilPressInterface", &oilPressGauge);
    context->setContextProperty("egtInterface", &egtGauge);
}

void GaugeManager::connectGaugeSignals(const AircraftInterface &aircraft)
{
    connect(&n1Gauge, &GaugeInterface::gaugeUpdated, &aircraft, &AircraftInterface::updateN1Gauge);
    connect(&n2Gauge, &GaugeInterface::gaugeUpdated, &aircraft, &AircraftInterface::updateN2Gauge);
    connect(&ittGauge, &GaugeInterface::gaugeUpdated, &aircraft, &AircraftInterface::updateIttGauge);
    connect(&rpmGauge, &GaugeInterface::gaugeUpdated, &aircraft, &AircraftInterface::updateRpmGauge);
    connect(&secondGauge, &GaugeInterface::gaugeUpdated, &aircraft, &AircraftInterface::updateSecondGauge);
    connect(&trqGauge, &GaugeInterface::gaugeUpdated, &aircraft, &AircraftInterface::updateTrqGauge);
    connect(&fuelQtyGauge, &GaugeInterface::gaugeUpdated, &aircraft, &AircraftInterface::updateFuelQtyGauge);
    connect(&fuelFlowGauge, &GaugeInterface::gaugeUpdated, &aircraft, &AircraftInterface::updateFuelFlowGauge);
    connect(&oilTempGauge, &GaugeInterface::gaugeUpdated, &aircraft, &AircraftInterface::updateOilTempGauge);
    connect(&oilPressGauge, &GaugeInterface::gaugeUpdated, &aircraft, &AircraftInterface::updateOilPressGauge);
    connect(&egtGauge, &GaugeInterface::gaugeUpdated, &aircraft, &AircraftInterface::updateEgtGauge);
}

void GaugeManager::createDefaults()
{
    QVector<ColorZone> colorVec = { ColorZone{ .start = 0, .end = 100, .color = QColor(0, 128, 0) }, ColorZone{ .start = 100, .end = 110, .color = QColor(255, 0, 0) } };
    QVector<GradDef> gradVec = { };
    QVector<TextGradDef> textGradVec = { };

    n1Gauge.setDefinition(RawGaugeDefinition{ .title = "N1", .unitString = "%", .minValue = 0, .maxValue = 110, .colorZones = colorVec, .grads = gradVec, .textGrads = textGradVec, .textIncrement = 1, .textNumDigits = 0, .forceTextColor = false, .textForcedColor = QColor(), .hasMinRedBlink = false, .minRedBlinkThreshold = 0, .hasMaxRedBlink = true, .maxRedBlinkThreshold = 100, .noText = false, .unit = Units::PERCENT });

    n2Gauge.setDefinition(RawGaugeDefinition{ .title = "N2", .unitString = "%", .minValue = 0, .maxValue = 110, .colorZones = colorVec, .grads = gradVec, .textGrads = textGradVec, .textIncrement = 1, .textNumDigits = 0, .forceTextColor = false, .textForcedColor = QColor(), .hasMinRedBlink = false, .minRedBlinkThreshold = 0, .hasMaxRedBlink = true, .maxRedBlinkThreshold = 100, .noText = false, .unit = Units::PERCENT });

    colorVec = { };

    ittGauge.setDefinition(RawGaugeDefinition{ .title = "ITT", .unitString = "ºC", .minValue = 0, .maxValue = 1000, .colorZones = colorVec, .grads = gradVec, .textGrads = textGradVec, .textIncrement = 1, .textNumDigits = 0, .forceTextColor = false, .textForcedColor = QColor(), .hasMinRedBlink = false, .minRedBlinkThreshold = 0, .hasMaxRedBlink = false, .maxRedBlinkThreshold = 0, .noText = false, .unit = Units::CELSIUS });

    rpmGauge.setDefinition(RawGaugeDefinition{ .title = "RPM", .unitString = "", .minValue = 0, .maxValue = 3000, .colorZones = colorVec, .grads = gradVec, .textGrads = textGradVec, .textIncrement = 10, .textNumDigits = 0, .forceTextColor = false, .textForcedColor = QColor(), .hasMinRedBlink = false, .minRedBlinkThreshold = 0, .hasMaxRedBlink = false, .maxRedBlinkThreshold = 0, .noText = false, .unit = Units::RPM });

    secondGauge.setDefinition(RawGaugeDefinition{ .title = "MAN", .unitString = "kPa", .minValue = 33, .maxValue = 100, .colorZones = colorVec, .grads = gradVec, .textGrads = textGradVec, .textIncrement = 1, .textNumDigits = 0, .forceTextColor = false, .textForcedColor = QColor(), .hasMinRedBlink = false, .minRedBlinkThreshold = 0, .hasMaxRedBlink = false, .maxRedBlinkThreshold = 0, .noText = false, .unit = Units::KILOPASCAL });

    colorVec = { ColorZone{ .start = 0, .end = 92, .color = QColor(0, 128, 0) }, ColorZone{ .start = 92, .end = 100, .color = QColor(255, 255, 0) } };

    trqGauge.setDefinition(RawGaugeDefinition{ .title = "TRQ", .unitString = "%", .minValue = 0, .maxValue = 100, .colorZones = colorVec, .grads = gradVec, .textGrads = textGradVec, .textIncrement = 1, .textNumDigits = 0, .forceTextColor = false, .textForcedColor = QColor(), .hasMinRedBlink = false, .minRedBlinkThreshold = 0, .hasMaxRedBlink = false, .maxRedBlinkThreshold = 0, .noText = false, .unit = Units::PERCENT });

    colorVec = { ColorZone{ .start = 0, .end = 12.5, .color = QColor(255, 0, 0) }, ColorZone{ .start = 12.5, .end = 25, .color = QColor(255, 255, 0) }, ColorZone{ .start = 25, .end = 100, .color = QColor(0, 128, 0) } };
    gradVec = { GradDef{ .gradPos = 10, .isBig = false, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 20, .isBig = true, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 30, .isBig = false, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 40, .isBig = true, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 50, .isBig = false, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 60, .isBig = true, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 70, .isBig = false, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 80, .isBig = true, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 90, .isBig = false, .gradColor = QColor(255, 255, 255) } };
    textGradVec = { TextGradDef{ .textGradPos = 0, .gradText = "0" }, TextGradDef{ .textGradPos = 20, .gradText = "20" }, TextGradDef{ .textGradPos = 40, .gradText = "40" }, TextGradDef{ .textGradPos = 60, .gradText = "60" }, TextGradDef{ .textGradPos = 80, .gradText = "80" }, TextGradDef{ .textGradPos = 100, .gradText = "100" } };

    fuelQtyGauge.setDefinition(RawGaugeDefinition{ .title = "FUEL QTY", .unitString = "KG", .minValue = 0, .maxValue = 100, .colorZones = colorVec, .grads = gradVec, .textGrads = textGradVec, .textIncrement = 1, .textNumDigits = 0, .forceTextColor = false, .textForcedColor = QColor(), .hasMinRedBlink = false, .minRedBlinkThreshold = 0, .hasMaxRedBlink = false, .maxRedBlinkThreshold = 0, .noText = false, .unit = Units::KG });

    colorVec = { };
    gradVec = { GradDef{ .gradPos = 5, .isBig = false, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 10, .isBig = false, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 15, .isBig = false, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 20, .isBig = false, .gradColor = QColor(255, 255, 255) }, GradDef{ .gradPos = 25, .isBig = false, .gradColor = QColor(255, 255, 255) } };
    textGradVec = { TextGradDef{ .textGradPos = 0, .gradText = "0" }, TextGradDef{ .textGradPos = 10, .gradText = "10" }, TextGradDef{ .textGradPos = 20, .gradText = "20" }, TextGradDef{ .textGradPos = 30, .gradText = "30" } };

    fuelFlowGauge.setDefinition(RawGaugeDefinition{ .title = "FUEL FLOW", .unitString = "KGH", .minValue = 0, .maxValue = 30, .colorZones = colorVec, .grads = gradVec, .textGrads = textGradVec, .textIncrement = 1, .textNumDigits = 0, .forceTextColor = false, .textForcedColor = QColor(), .hasMinRedBlink = false, .minRedBlinkThreshold = 0, .hasMaxRedBlink = false, .maxRedBlinkThreshold = 0, .noText = false, .unit = Units::KG_PER_HOUR });

    colorVec = { ColorZone{ .start = 10, .end = 100, .color = QColor(0, 128, 0) }, ColorZone{ .start = -40, .end = 10, .color = QColor(255, 255, 0) }, ColorZone{ .start = 100, .end = 105, .color = QColor(255, 255, 0) } };
    gradVec = { GradDef{ .gradPos = -41, .isBig = true, .gradColor = QColor(255, 0, 0) }, GradDef{ .gradPos = 105, .isBig = true, .gradColor = QColor(255, 0, 0) } };
    textGradVec = { };

    oilTempGauge.setDefinition(RawGaugeDefinition{ .title = "OIL TEMP", .unitString = "ºC", .minValue = -50, .maxValue = 120, .colorZones = colorVec, .grads = gradVec, .textGrads = textGradVec, .textIncrement = 1, .textNumDigits = 0, .forceTextColor = false, .textForcedColor = QColor(), .hasMinRedBlink = true, .minRedBlinkThreshold = -41, .hasMaxRedBlink = true, .maxRedBlinkThreshold = 105, .noText = false, .unit = Units::CELSIUS });

    colorVec = { ColorZone{ .start = 0, .end = 90, .color = QColor(255, 0, 0) }, ColorZone{ .start = 90, .end = 250, .color = QColor(255, 255, 0) }, ColorZone{ .start = 250, .end = 600, .color = QColor(0, 128, 0) }, ColorZone{ .start = 600, .end = 650, .color = QColor(255, 255, 0) }, ColorZone{ .start = 650, .end = 700, .color = QColor(255, 0, 0) } };
    gradVec = { };
    textGradVec = { };

    oilPressGauge.setDefinition(RawGaugeDefinition{ .title = "OIL PRESS", .unitString = "kPa", .minValue = 0, .maxValue = 700, .colorZones = colorVec, .grads = gradVec, .textGrads = textGradVec, .textIncrement = 1, .textNumDigits = 0, .forceTextColor = false, .textForcedColor = QColor(), .hasMinRedBlink = true, .minRedBlinkThreshold = 90, .hasMaxRedBlink = true, .maxRedBlinkThreshold = 650, .noText = false, .unit = Units::KILOPASCAL });

    colorVec = { };
    gradVec = { GradDef{ .gradPos = 700, .isBig = false, .gradColor = "white" }, GradDef{ .gradPos = 725, .isBig = false, .gradColor = "white" }, GradDef{ .gradPos = 750, .isBig = false, .gradColor = "white" }, GradDef{ .gradPos = 775, .isBig = false, .gradColor = "white" }, GradDef{ .gradPos = 800, .isBig = false, .gradColor = "white" }, GradDef{ .gradPos = 825, .isBig = false, .gradColor = "white" }, GradDef{ .gradPos = 850, .isBig = false, .gradColor = "white" }, GradDef{ .gradPos = 875, .isBig = false, .gradColor = "white" } };
    textGradVec = { };

    egtGauge.setDefinition(RawGaugeDefinition{ .title = "EGT", .unitString = "ºC", .minValue = 1218.0 / 1.8, .maxValue = 1618.0 / 1.8, .colorZones = colorVec, .grads = gradVec, .textGrads = textGradVec, .textIncrement = 1, .textNumDigits = 0, .forceTextColor = false, .textForcedColor = QColor(), .hasMinRedBlink = false, .minRedBlinkThreshold = 0, .hasMaxRedBlink = false, .maxRedBlinkThreshold = 0, .noText = false, .unit = Units::CELSIUS });

}
