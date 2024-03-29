#include "AircraftManager.hpp"

#include <QUuid>


using namespace definitions;

void AircraftManager::newAircraft()
{
    QString newKey = QUuid::createUuid().toString(QUuid::WithoutBraces);

    QList<ColorZone> colorVec = { ColorZone{ .start = 1900, .end = 2550, .color = QColor(0, 128, 0) },
                                  ColorZone{ .start = 2550, .end = 3000, .color = QColor(255, 0, 0) } };
    QList<GradDef> gradVec = { GradDef{ .gradPos = 0, .isBig = false, .gradColor = "white" },
                               GradDef{ .gradPos = 500, .isBig = false, .gradColor = "white" },
                               GradDef{ .gradPos = 1000, .isBig = false, .gradColor = "white" },
                               GradDef{ .gradPos = 1500, .isBig = false, .gradColor = "white" },
                               GradDef{ .gradPos = 2000, .isBig = false, .gradColor = "white" },
                               GradDef{ .gradPos = 2500, .isBig = false, .gradColor = "white" } };
    QList<TextGradDef> textGradVec = {};

    GaugeDefinition rpmGauge = { .title = "RPM",
                                 .unitString = "",
                                 .minValue = 0,
                                 .maxValue = 3000,
                                 .colorZones = colorVec,
                                 .grads = gradVec,
                                 .textGrads = textGradVec,
                                 .textIncrement = 1,
                                 .textNumDigits = 0,
                                 .forceTextColor = false,
                                 .textForcedColor = QColor(),
                                 .hasMinRedBlink = false,
                                 .minRedBlinkThreshold = 0,
                                 .hasMaxRedBlink = false,
                                 .maxRedBlinkThreshold = 0,
                                 .noText = false,
                                 .unit = Units::RPM };

    colorVec = { ColorZone{ .start = 0, .end = 92, .color = QColor(0, 128, 0) },
                 ColorZone{ .start = 92, .end = 100, .color = QColor(255, 255, 0) } };
    gradVec = {};
    textGradVec = {};

    GaugeDefinition secondGauge = { .title = "LOAD",
                                    .unitString = "%",
                                    .minValue = 0,
                                    .maxValue = 100,
                                    .colorZones = colorVec,
                                    .grads = gradVec,
                                    .textGrads = textGradVec,
                                    .textIncrement = 1,
                                    .textNumDigits = 0,
                                    .forceTextColor = false,
                                    .textForcedColor = QColor(),
                                    .hasMinRedBlink = false,
                                    .minRedBlinkThreshold = 0,
                                    .hasMaxRedBlink = false,
                                    .maxRedBlinkThreshold = 0,
                                    .noText = false,
                                    .unit = Units::PERCENT };

    colorVec = {};
    gradVec = { GradDef{ .gradPos = 0, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 200, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 400, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 600, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 800, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 1000, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 1200, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 1400, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 1600, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 1800, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 2000, .isBig = false, .gradColor = "white" } };
    textGradVec = {};

    GaugeDefinition egtGauge = { .title = "EGT",
                                 .unitString = "ºC",
                                 .minValue = 0,
                                 .maxValue = 2100.0 / 1.8,
                                 .colorZones = colorVec,
                                 .grads = gradVec,
                                 .textGrads = textGradVec,
                                 .textIncrement = 1,
                                 .textNumDigits = 0,
                                 .forceTextColor = false,
                                 .textForcedColor = QColor(),
                                 .hasMinRedBlink = false,
                                 .minRedBlinkThreshold = 0,
                                 .hasMaxRedBlink = false,
                                 .maxRedBlinkThreshold = 0,
                                 .noText = false,
                                 .unit = Units::CELSIUS };

    colorVec = { ColorZone{ .start = 38.10 * 5.0 / 26.0, .end = 38.1, .color = QColor(0, 128, 0) },
                 ColorZone{ .start = 0, .end = 38.10 * 5.0 / 26.0, .color = QColor(255, 0, 0) } };
    gradVec = { GradDef{ .gradPos = 0, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 6, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 12, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 18, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 24, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 30, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 36, .isBig = false, .gradColor = "white" } };
    textGradVec = {
        TextGradDef{ .textGradPos = 0, .gradText = "0" },   TextGradDef{ .textGradPos = 6, .gradText = "6" },
        TextGradDef{ .textGradPos = 12, .gradText = "12" }, TextGradDef{ .textGradPos = 18, .gradText = "18" },
        TextGradDef{ .textGradPos = 24, .gradText = "24" }, TextGradDef{ .textGradPos = 30, .gradText = "30" },
        TextGradDef{ .textGradPos = 36, .gradText = "36" }
    };

    GaugeDefinition fuelQtyGauge = { .title = "L FUEL QTY R",
                                     .unitString = "KG",
                                     .minValue = 0,
                                     .maxValue = 38.1,
                                     .colorZones = colorVec,
                                     .grads = gradVec,
                                     .textGrads = textGradVec,
                                     .textIncrement = 1,
                                     .textNumDigits = 0,
                                     .forceTextColor = false,
                                     .textForcedColor = QColor(),
                                     .hasMinRedBlink = false,
                                     .minRedBlinkThreshold = 0,
                                     .hasMaxRedBlink = false,
                                     .maxRedBlinkThreshold = 0,
                                     .noText = false,
                                     .unit = Units::KG };

    colorVec = {};
    gradVec = { GradDef{ .gradPos = 0, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 5, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 10, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 15, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 20, .isBig = false, .gradColor = "white" } };
    textGradVec = { TextGradDef{ .textGradPos = 0, .gradText = "0" },
                    TextGradDef{ .textGradPos = 5, .gradText = "5" },
                    TextGradDef{ .textGradPos = 10, .gradText = "10" },
                    TextGradDef{ .textGradPos = 15, .gradText = "15" },
                    TextGradDef{ .textGradPos = 20, .gradText = "20" } };

    GaugeDefinition fuelFlowGauge = { .title = "FUEL FLOW",
                                      .unitString = "KGH",
                                      .minValue = 0,
                                      .maxValue = 50.0 * 0.45359237,
                                      .colorZones = colorVec,
                                      .grads = gradVec,
                                      .textGrads = textGradVec,
                                      .textIncrement = 1,
                                      .textNumDigits = 0,
                                      .forceTextColor = false,
                                      .textForcedColor = QColor(),
                                      .hasMinRedBlink = false,
                                      .minRedBlinkThreshold = 0,
                                      .hasMaxRedBlink = false,
                                      .maxRedBlinkThreshold = 0,
                                      .noText = false,
                                      .unit = Units::KG_PER_HOUR };

    colorVec = { ColorZone{ .start = 78.0 / 1.8, .end = 213.0 / 1.8, .color = QColor(0, 128, 0) } };
    gradVec = { GradDef{ .gradPos = 0, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 20, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 40, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 60, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 80, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 100, .isBig = false, .gradColor = "white" } };
    textGradVec = {};

    GaugeDefinition oilTempGauge = { .title = "OIL TEMP",
                                     .unitString = "ºC",
                                     .minValue = 0,
                                     .maxValue = 213.0 / 1.8,
                                     .colorZones = colorVec,
                                     .grads = gradVec,
                                     .textGrads = textGradVec,
                                     .textIncrement = 1,
                                     .textNumDigits = 0,
                                     .forceTextColor = false,
                                     .textForcedColor = QColor(),
                                     .hasMinRedBlink = false,
                                     .minRedBlinkThreshold = 0,
                                     .hasMaxRedBlink = false,
                                     .maxRedBlinkThreshold = 0,
                                     .noText = false,
                                     .unit = Units::CELSIUS };

    colorVec = { ColorZone{ .start = 60.0 * 6.894757, .end = 90.0 * 6.894757, .color = QColor(0, 128, 0) } };
    gradVec = { GradDef{ .gradPos = 0, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 120, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 240, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 360, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 480, .isBig = false, .gradColor = "white" },
                GradDef{ .gradPos = 600, .isBig = false, .gradColor = "white" } };
    textGradVec = {};

    GaugeDefinition oilPressGauge = { .title = "OIL PRESS",
                                      .unitString = "kPa",
                                      .minValue = 0,
                                      .maxValue = 100.0 * 6.894757,
                                      .colorZones = colorVec,
                                      .grads = gradVec,
                                      .textGrads = textGradVec,
                                      .textIncrement = 1,
                                      .textNumDigits = 0,
                                      .forceTextColor = false,
                                      .textForcedColor = QColor(),
                                      .hasMinRedBlink = false,
                                      .minRedBlinkThreshold = 0,
                                      .hasMaxRedBlink = false,
                                      .maxRedBlinkThreshold = 0,
                                      .noText = false,
                                      .unit = Units::KILOPASCAL };

    AircraftDefinition newDefinition{ .type = AircraftType::PROP,
                                      .name = "",
                                      .firstGauge = rpmGauge,
                                      .secondGauge = secondGauge,
                                      .fuelQtyGauge = fuelQtyGauge,
                                      .fuelFlowGauge = fuelFlowGauge,
                                      .oilTempGauge = oilTempGauge,
                                      .secondaryTempGauge = egtGauge,
                                      .oilPressGauge = oilPressGauge,
                                      .gauge1Type = SwitchingGaugeType::RPM,
                                      .gauge2Type = SwitchingGaugeType::POWER,
                                      .maxPower = 110,
                                      .hasApu = false,
                                      .hasFlaps = true,
                                      .hasSpoilers = false,
                                      .hasElevatorTrim = true,
                                      .hasRudderTrim = true,
                                      .hasAileronTrim = true,
                                      .hasSecondaryTempGauge = true,
                                      .secondaryTempType = TemperatureGaugeType::EGT,
                                      .numEngines = 1,
                                      .singleTank = false,
                                      .lowLimit = 0,
                                      .flapsBegin = 35,
                                      .flapsEnd = 85,
                                      .greenBegin = 40,
                                      .greenEnd = 111,
                                      .yellowBegin = 111,
                                      .yellowEnd = 148,
                                      .redBegin = 149,
                                      .redEnd = 152,
                                      .highLimit = 152,
                                      .noColors = false,
                                      .dynamicBarberpole = false };

    d_currentDefinitionKey = newKey;
    d_currentDefinitionImagePath = d_dataRoot + "/Thumbnails/" + newKey + ".png";
    emit currentThumbnailPathChanged();

    d_lastSavedThumbnail = QImage(":/DefaultImage.png");
    d_unsavedThumbnail = false;
    emit unsavedThumbnailChanged();

    d_definitions.insert({ newKey, newDefinition });

    d_currentQmlDefinition.changeDefinition(d_definitions.at(newKey), false);
}