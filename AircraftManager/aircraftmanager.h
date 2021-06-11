#ifndef AIRCRAFTMANAGER_H
#define AIRCRAFTMANAGER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QImage>
#include "FileManager/aircraftfile.h"

class AircraftManager : public QObject
{
    Q_OBJECT

    QMap<QString, AircraftDefinition> allAircrafts;

    QStringList clientKeys;

public:
    explicit AircraftManager(QObject *parent = nullptr);

    Q_INVOKABLE QList<QString> getKeys() const { return allAircrafts.keys(); }
    Q_INVOKABLE QStringList getClientKeys() const { return clientKeys; }

    AircraftDefinition &getAircraft(const QString &key) { return allAircrafts[key]; }
    const AircraftDefinition getAircraft(const QString &key) const { return allAircrafts[key]; }

    Q_INVOKABLE void removeAircraft(const QString &key) { allAircrafts.remove(key); AircraftFile::removeAircraft(key); }

    Q_INVOKABLE void loadAircraft(const QString &name) { emit changeAircraft(allAircrafts[name]); }

    Q_INVOKABLE void copyAircraft(const QString &name);

    Q_INVOKABLE void sendAircraft(const QStringList &list);


signals:
    void changeAircraft(const AircraftDefinition &def);
    void sendAircraftToClient(const QVector<AircraftDefinition> &list);

public slots:
    void setAircraft(const AircraftDefinition &newDef)
    {
        allAircrafts[newDef.name] = newDef;
    }
    void setClientKeys(const QStringList &keys) { clientKeys = keys; }


};

#endif // AIRCRAFTMANAGER_H
