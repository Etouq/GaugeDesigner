#include "AircraftManager.hpp"

void AircraftManager::deleteAircraft(const QString &key)
{
    if (d_definitions.empty())
        return;

    if (d_definitions.size() <= 1)
        newAircraft();
    else if (key == d_currentDefinitionKey && d_definitions.begin()->first != key)
        selectAircraft(d_definitions.begin()->first);
    else if (key == d_currentDefinitionKey)
        selectAircraft(d_definitions.end()->first);

    d_definitions.erase(key);

    if (QDir().exists(d_dataRoot + "/Definitions/" + key + ".fdc"))
    {
        QDir().remove(d_dataRoot + "/Definitions/" + key + ".fdc");
    }

    if (QDir().exists(d_dataRoot + "/Thumbnails/" + key + ".png"))
    {
        QDir().remove(d_dataRoot + "/Thumbnails/" + key + ".png");
    }

    updateKeys();
}