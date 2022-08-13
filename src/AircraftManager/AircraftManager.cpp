#include "AircraftManager.hpp"

#include <QDir>
#include <QStandardPaths>
#include <QQmlEngine>


AircraftManager::AircraftManager()
  : d_currentQmlDefinition(definitions::AircraftDefinition())
{
    // d_dataRoot = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
    //   + "/AppData/Roaming/MKootstra/Flight Display Companion";

    // QDir dataDirs(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    // dataDirs.mkpath("/AppData/Roaming/MKootstra/Flight Display Companion/Definitions");
    // dataDirs.mkpath("/AppData/Roaming/MKootstra/Flight Display Companion/Thumbnails");

    d_dataRoot = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/AppData/Roaming/MKootstra/Simconnect Server";

    QDir dataDirs(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    dataDirs.mkpath("/AppData/Roaming/MKootstra/Simconnect Server/Definitions");
    dataDirs.mkpath("/AppData/Roaming/MKootstra/Simconnect Server/Thumbnails");
    QSettings settings;

    if (settings.contains("lastChosenDefinition"))
    {
        d_currentDefinitionKey = settings.value("lastChosenDefinition").toString();
    }

    loadDefinitions();

    d_currentQmlDefinition.changeDefinition(d_definitions.at(d_currentDefinitionKey));

    qmlRegisterSingletonInstance("Definition", 1, 0, "AircraftDefinition", &d_currentQmlDefinition);
    qmlRegisterSingletonInstance("Definition", 1, 0, "AircraftManager", this);
}
