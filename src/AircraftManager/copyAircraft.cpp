#include "AircraftManager.hpp"

void AircraftManager::copyAircraft(const QString &key)
{
    QString newKey = QUuid::createUuid().toString(QUuid::WithoutBraces);

    definitions::AircraftDefinition newDefinition = d_definitions.at(key);

    newDefinition.name.truncate(57);  // 64 - 7

    newDefinition.name += " (copy)";

    d_currentDefinitionKey = newKey;

    d_definitions.insert({ newKey, newDefinition });
    d_currentDefinitionImagePath = d_dataRoot + "/Thumbnails/" + key + ".png";
    emit currentThumbnailPathChanged();

    if (QDir().exists(d_currentDefinitionImagePath))
    {
        d_lastSavedThumbnail = QImage(d_currentDefinitionImagePath);
    }
    else
    {
        d_lastSavedThumbnail = QImage(":/DefaultImage.png");
    }
    d_unsavedThumbnail = true;
    emit unsavedThumbnailChanged();

    d_currentQmlDefinition.changeDefinition(d_definitions.at(newKey), false);
}