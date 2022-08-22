#include "AircraftManager.hpp"

void AircraftManager::selectImage(const QString &path)
{
    d_currentDefinitionImagePath = path;

    const QImage newImage(d_currentDefinitionImagePath);

    if (bool unsavedThumbnail = newImage != d_lastSavedThumbnail; d_unsavedThumbnail != unsavedThumbnail)
    {
        d_unsavedThumbnail = unsavedThumbnail;
        emit unsavedThumbnailChanged();
    }

    emit currentThumbnailPathChanged();
}