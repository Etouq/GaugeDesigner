#include "AircraftManager.hpp"

#include <QSettings>


void AircraftManager::selectAircraft(const QString &key)
{
    QSettings settings;
    settings.setValue("lastChosenDefinition", key);

    d_currentDefinitionKey = key;

    d_currentQmlDefinition.changeDefinition(d_definitions.at(key), true);
    d_currentDefinitionImagePath = d_dataRoot + "/Thumbnails/" + d_currentDefinitionKey + ".png";
    if (QDir().exists(d_currentDefinitionImagePath))
    {
        d_lastSavedThumbnail = QImage(d_currentDefinitionImagePath);
    }
    else
    {
        d_lastSavedThumbnail = QImage(":/DefaultImage.png");
    }
    d_unsavedThumbnail = false;
    emit unsavedThumbnailChanged();

    emit currentThumbnailPathChanged();
}