#include "main.hpp"
#include "common/QmlEnums.hpp"
#include <QQmlEngine>
#include <QtQml>

void setupQml()
{
    qRegisterMetaType<QmlAircraftType>("QmlAircraftType");
    qmlRegisterUncreatableType<QmlAircraftTypeClass>("TypeEnums",
                                                     1,
                                                     0,
                                                     "AircraftType",
                                                     "Not creatable as it is an enum type");

    qRegisterMetaType<QmlTemperatureGaugeType>("QmlTemperatureGaugeType");
    qmlRegisterUncreatableType<QmlTemperatureGaugeTypeClass>("TypeEnums",
                                                     1,
                                                     0,
                                                     "TemperatureGaugeType",
                                                     "Not creatable as it is an enum type");

    qRegisterMetaType<QmlSwitchingGaugeType>("QmlSwitchingGaugeType");
    qmlRegisterUncreatableType<QmlSwitchingGaugeTypeClass>("TypeEnums",
                                                     1,
                                                     0,
                                                     "SwitchingGaugeType",
                                                     "Not creatable as it is an enum type");
}