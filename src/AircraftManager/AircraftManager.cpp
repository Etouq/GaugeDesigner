#include "AircraftManager.hpp"

#include <QDir>
#include <QStandardPaths>
#include <QQmlEngine>


AircraftManager::AircraftManager()
  : d_currentQmlDefinition(definitions::AircraftDefinition())
{
    d_dataRoot = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/AppData/Roaming/Flight Display Companion";

    QDir dataDirs(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    dataDirs.mkpath("AppData/Roaming/Flight Display Companion/Definitions");
    dataDirs.mkpath("AppData/Roaming/Flight Display Companion/Thumbnails");
    QSettings settings;

    if (settings.contains("lastChosenDefinition"))
    {
        d_currentDefinitionKey = settings.value("lastChosenDefinition").toString();
    }

    loadDefinitions();

    if (d_currentDefinitionKey.isEmpty()) // no aircraft found at all
    {
        newAircraft();
    }
    else
    {
        d_currentQmlDefinition.changeDefinition(d_definitions.at(d_currentDefinitionKey), true);
        if (QDir().exists(d_dataRoot + "/Thumbnails/" + d_currentDefinitionKey + ".png"))
        {
            d_lastSavedThumbnail = QImage(d_dataRoot + "/Thumbnails/" + d_currentDefinitionKey + ".png");
        }
        else
        {
            d_lastSavedThumbnail = QImage(":/DefaultImage.png");
        }
        d_unsavedThumbnail = false;
        emit unsavedThumbnailChanged();
    }

    d_currentDefinitionImagePath = d_dataRoot + "/Thumbnails/" + d_currentDefinitionKey + ".png";
    emit currentThumbnailPathChanged();

    qmlRegisterSingletonInstance("Definition", 1, 0, "AircraftDefinition", &d_currentQmlDefinition);
    qmlRegisterSingletonInstance("Definition", 1, 0, "AircraftManager", this);
}
