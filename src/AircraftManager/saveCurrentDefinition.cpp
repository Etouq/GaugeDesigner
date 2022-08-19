#include "AircraftManager.hpp"

#include <QFile>
#include <QImage>

void AircraftManager::saveCurrentDefinition()
{
    if (d_currentDefinitionKey.isEmpty())
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

    if (d_currentDefinitionImagePath != (d_dataRoot + "/Thumbnails/" + d_currentDefinitionKey + ".png") && QFile::exists(d_currentDefinitionImagePath))
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

    d_jetKeys.clear();
    d_propKeys.clear();
    d_turbopropKeys.clear();

    for (const auto &entry : d_definitions)
    {
        switch(entry.second.type)
        {
            case AircraftType::JET:
                d_jetKeys.append(entry.first);
                break;
            case AircraftType::PROP:
                d_propKeys.append(entry.first);
                break;
            case AircraftType::TURBOPROP:
                d_turbopropKeys.append(entry.first);
                break;
            default:
                break;
        }
    }

    std::sort(d_jetKeys.begin(), d_jetKeys.end(), [this](const QString &lhs, const QString &rhs) {
        return d_definitions.at(lhs).name.toUpper().localeAwareCompare(d_definitions.at(rhs).name.toUpper()) < 0;
    });
    std::sort(d_propKeys.begin(), d_propKeys.end(), [this](const QString &lhs, const QString &rhs) {
        return d_definitions.at(lhs).name.toUpper().localeAwareCompare(d_definitions.at(rhs).name.toUpper()) < 0;
    });
    std::sort(d_turbopropKeys.begin(), d_turbopropKeys.end(), [this](const QString &lhs, const QString &rhs) {
        return d_definitions.at(lhs).name.toUpper().localeAwareCompare(d_definitions.at(rhs).name.toUpper()) < 0;
    });

}
