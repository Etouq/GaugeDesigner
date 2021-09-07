#include "aircraftmanager.h"

#include "AircraftManager/definitions/aircraftDefinition.h"
#include "FileManager/aircraftfile.h"

#include <QImage>

AircraftManager::AircraftManager(QObject *parent) : QObject(parent)
{
    AircraftFile::readAllAircraftFiles(allAircraft);
}

QList<QString> AircraftManager::getKeys() const
{
    return allAircraft.keys();
}

QStringList AircraftManager::getClientKeys() const
{
    return clientKeys;
}

AircraftDefinition &AircraftManager::getAircraft(const QString &key)
{
    return allAircraft[key];
}

AircraftDefinition AircraftManager::getAircraft(const QString &key) const
{
    return allAircraft.value(key);
}

void AircraftManager::removeAircraft(const QString &key)
{
    allAircraft.remove(key);
    AircraftFile::removeAircraft(key);
}

void AircraftManager::loadAircraft(const QString &name)
{
    emit changeAircraft(allAircraft[name]);
}

void AircraftManager::copyAircraft(const QString &name)
{
    AircraftDefinition newDef = allAircraft[name];
    int index = 1;
    while (allAircraft.contains(newDef.name + QString("(%1)").arg(index)))
        index++;
    newDef.name += QString("(%1)").arg(index);

    allAircraft.insert(newDef.name, newDef);
    QImage temp(AircraftFile::getImagePath(name));
    AircraftFile::saveAircraftWithImage(newDef, temp);
    emit changeAircraft(newDef);
}

void AircraftManager::sendAircraft(const QStringList &list)
{
    QVector<AircraftDefinition> selection;
    for (int i = 0; i < list.size(); i++)
        selection.push_back(allAircraft[list[i]]);
    emit sendAircraftToClient(selection);
}

void AircraftManager::setAircraft(const AircraftDefinition &newDef)
{
    allAircraft[newDef.name] = newDef;
}

void AircraftManager::setClientKeys(const QStringList &keys)
{
    clientKeys = keys;
}
