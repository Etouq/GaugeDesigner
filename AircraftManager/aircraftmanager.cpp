#include "aircraftmanager.h"
#include "aircraftinitializer.h"

AircraftManager::AircraftManager(QObject *parent) : QObject(parent)
{
    AircraftFile::readAllAircraftFiles(allAircrafts);

    /*AircraftInitializer::initAircraft(allAircrafts);

    for (auto it = allAircrafts.begin(); it != allAircrafts.end(); it++)
        AircraftFile::saveAircraftToFile(it.value());*/
}

void AircraftManager::copyAircraft(const QString &name)
{
    AircraftDefinition newDef = allAircrafts[name];
    newDef.name += " (Copy)";
    allAircrafts.insert(newDef.name, newDef);
    QImage temp(AircraftFile::getImagePath(name));
    AircraftFile::saveAircraftWithImage(newDef, temp);
    emit changeAircraft(newDef);
}

void AircraftManager::sendAircraft(const QStringList &list)
{
    QVector<AircraftDefinition> selection;
    for (int i = 0; i < list.size(); i++)
        selection.push_back(allAircrafts[list[i]]);
    emit sendAircraftToClient(selection);
}
