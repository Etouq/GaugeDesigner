#ifndef __AIRCRAFT_MANAGER_HPP__
#define __AIRCRAFT_MANAGER_HPP__

#include <QObject>
#include <QSettings>
#include <QDir>
#include <QDebug>
#include <QUuid>
#include <QImage>

#include <unordered_map>

#include "common/definitions/AircraftDefinition/AircraftDefinition.hpp"
#include "QmlDefinitions/QmlAircraftDefinition/QmlAircraftDefinition.hpp"

class FdcSocket;

class AircraftManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentThumbnailPath READ currentThumbnailPath NOTIFY currentThumbnailPathChanged)
    Q_PROPERTY(bool unsavedThumbnail READ unsavedThumbnail NOTIFY unsavedThumbnailChanged)

public:

    AircraftManager();

    bool unsavedThumbnail() const
    {
        return d_unsavedThumbnail;
    }

    Q_INVOKABLE int getNumJets() const
    {
        return d_jetKeys.size();
    }

    Q_INVOKABLE int getNumProp() const
    {
        return d_propKeys.size();
    }

    Q_INVOKABLE int getNumTurboprop() const
    {
        return d_turbopropKeys.size();
    }

    Q_INVOKABLE QString getJetKey(int idx) const
    {
        return d_jetKeys.at(idx);
    }

    Q_INVOKABLE QString getPropKey(int idx) const
    {
        return d_propKeys.at(idx);
    }

    Q_INVOKABLE QString getTurbopropKey(int idx) const
    {
        return d_turbopropKeys.at(idx);
    }

    Q_INVOKABLE QString getName(const QString &key) const
    {
        return d_definitions.at(key).name;
    }

    Q_INVOKABLE QString getImagePath(const QString &key) const
    {
        if (QDir().exists(d_dataRoot + "/Thumbnails/" + key + ".png"))
            return "file:///" + d_dataRoot + "/Thumbnails/" + key + ".png";

        return "qrc:/DefaultImage.png";
    }

    Q_INVOKABLE void selectAircraft(const QString &key);
    Q_INVOKABLE void copyAircraft(const QString &key);
    Q_INVOKABLE void newAircraft();
    Q_INVOKABLE void deleteAircraft(const QString &key)
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

        d_jetKeys.clear();
        d_propKeys.clear();
        d_turbopropKeys.clear();

        for (const auto &entry : d_definitions)
        {
            if (entry.first == key)
                continue;

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

    Q_INVOKABLE void selectImage(const QString &path)
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

    Q_INVOKABLE bool isCurrentAircraft(const QString &key) const
    {
        return key == d_currentDefinitionKey;
    }

    const definitions::AircraftDefinition &getCurrentDefinition() const
    {
        return d_definitions.at(d_currentDefinitionKey);
    }

    Q_INVOKABLE void saveCurrentDefinition();

    Q_INVOKABLE void previewCurrentDefinition()
    {
        emit previewAircraft(d_currentQmlDefinition.getDefinition());
    }

    QString currentThumbnailPath() const;

signals:

    void previewAircraft(const definitions::AircraftDefinition &definition);
    void currentThumbnailPathChanged();

    void unsavedThumbnailChanged();

private:

    void loadDefinitions();

    QString d_dataRoot;

    QString d_currentDefinitionKey;
    QString d_currentDefinitionImagePath;

    QmlAircraftDefinition d_currentQmlDefinition;

    std::unordered_map<QString, definitions::AircraftDefinition> d_definitions;

    QStringList d_jetKeys;
    QStringList d_propKeys;
    QStringList d_turbopropKeys;

    QImage d_lastSavedThumbnail;

    bool d_unsavedThumbnail = false;

};

#endif // __AIRCRAFT_MANAGER_HPP__