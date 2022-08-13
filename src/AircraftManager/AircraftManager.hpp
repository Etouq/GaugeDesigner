#ifndef __AIRCRAFT_MANAGER_HPP__
#define __AIRCRAFT_MANAGER_HPP__

#include <QObject>
#include <QSettings>

#include <unordered_map>

#include "common/definitions/AircraftDefinition/AircraftDefinition.hpp"
#include "QmlDefinitions/QmlAircraftDefinition/QmlAircraftDefinition.hpp"

class FdcSocket;

class AircraftManager : public QObject
{
    Q_OBJECT

public:

    AircraftManager();

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
        return "file:///" + d_dataRoot + "/Thumbnails/" + key + ".png";
    }
    Q_INVOKABLE void selectAircraft(const QString &key)
    {
        QSettings settings;
        settings.setValue("lastChosenDefinition", key);

        d_currentDefinitionKey = key;

        emit aircraftSelected(d_definitions.at(key));
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


signals:

    void aircraftSelected(const definitions::AircraftDefinition &definition);

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

};

#endif // __AIRCRAFT_MANAGER_HPP__