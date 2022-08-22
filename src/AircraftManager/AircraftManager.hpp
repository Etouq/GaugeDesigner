#ifndef __AIRCRAFT_MANAGER_HPP__
#define __AIRCRAFT_MANAGER_HPP__

#include "QmlDefinitions/QmlAircraftDefinition/QmlAircraftDefinition.hpp"
#include "common/definitions/AircraftDefinition/AircraftDefinition.hpp"

#include <QDir>
#include <QImage>
#include <QObject>

#include <unordered_map>


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
    Q_INVOKABLE void deleteAircraft(const QString &key);

    Q_INVOKABLE void selectImage(const QString &path);

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

    void updateKeys();

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

#endif  // __AIRCRAFT_MANAGER_HPP__