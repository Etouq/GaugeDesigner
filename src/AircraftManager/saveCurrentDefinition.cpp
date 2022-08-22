#include "AircraftManager.hpp"

#include <QFile>
#include <QImage>

void AircraftManager::saveCurrentDefinition()
{
    if (d_currentDefinitionKey.isEmpty() || !d_definitions.contains(d_currentDefinitionKey))
        return;

    static constexpr definitions::FileVersion version = definitions::FileVersion::V3;

    QFile file(d_dataRoot + "/Definitions/" + d_currentDefinitionKey + ".fdc");
    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        file.write(reinterpret_cast<const char *>(&version), sizeof(version));
        file.write(d_currentQmlDefinition.getDefinition().toBinary());
        d_currentQmlDefinition.aircraftSaved();
        d_definitions[d_currentDefinitionKey] = d_currentQmlDefinition.getDefinition();

        file.close();
    }
    else
        return;

    if (d_currentDefinitionImagePath != (d_dataRoot + "/Thumbnails/" + d_currentDefinitionKey + ".png")
        && QFile::exists(d_currentDefinitionImagePath))
    {
        QImage definitionImage(d_currentDefinitionImagePath);
        definitionImage.save(d_dataRoot + "/Thumbnails/" + d_currentDefinitionKey + ".png");

        d_currentDefinitionImagePath = d_dataRoot + "/Thumbnails/" + d_currentDefinitionKey + ".png";
        emit currentThumbnailPathChanged();
    }

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

    updateKeys();
}
