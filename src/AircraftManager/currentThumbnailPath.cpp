#include "AircraftManager.hpp"

QString AircraftManager::currentThumbnailPath() const
{
    if (QDir().exists(d_currentDefinitionImagePath))
        return "file:///" + d_currentDefinitionImagePath;
    else
        return "qrc:/DefaultImage.png";
}