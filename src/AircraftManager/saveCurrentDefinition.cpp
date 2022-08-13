#include "AircraftManager.hpp"

#include <QFile>
#include <QImage>

void AircraftManager::saveCurrentDefinition()
{
    if (d_currentDefinitionKey.isEmpty())
        return;

    static constexpr definitions::FileVersion version = definitions::FileVersion::V3;

    QFile file(d_dataRoot + "/Definitions" + d_currentDefinitionKey + ".fdc");
    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        file.write(reinterpret_cast<const char *>(&version), sizeof(version));
        file.write(d_definitions.at(d_currentDefinitionKey).toBinary());

        file.close();
    }
    else
        return;

    if (d_currentDefinitionImagePath != (d_dataRoot + "/Thumbnails" + d_currentDefinitionKey + ".png") && QFile::exists(d_currentDefinitionImagePath))
    {
        QImage definitionImage(d_currentDefinitionImagePath);
        definitionImage.save(d_dataRoot + "/Thumbnails" + d_currentDefinitionKey + ".png");
    }
}
