#ifndef AIRCRAFTMANAGER_H
#define AIRCRAFTMANAGER_H

#include <QList>
#include <QMap>
#include <QObject>
#include <QStringList>

struct AircraftDefinition;


class AircraftManager : public QObject
{
    Q_OBJECT

    QMap<QString, AircraftDefinition> allAircraft;

    QStringList clientKeys;

public:
    explicit AircraftManager(QObject *parent = nullptr);

    Q_INVOKABLE QList<QString> getKeys() const;
    Q_INVOKABLE QStringList getClientKeys() const;

    AircraftDefinition &getAircraft(const QString &key);
    AircraftDefinition getAircraft(const QString &key) const;

    Q_INVOKABLE void removeAircraft(
      const QString &key);   // remove aircraft with name 'key' from our list and also remove the
                             // associated files

    Q_INVOKABLE void loadAircraft(
      const QString &name);   // load aircraft with name 'name' into the gauge inputs

    Q_INVOKABLE void copyAircraft(
      const QString &name);   // create a copy of the aircraft with name 'name', add an index to the
                              // end, save it and load it into the gauge inputs

    Q_INVOKABLE void sendAircraft(const QStringList &list);   // send the aircraft whose names are
                                                              // in list to the client to store


signals:
    void changeAircraft(
      const AircraftDefinition &def);   // tell gauge and aircraft interfaces to change the current
                                        // data to the data from 'def'
    void sendAircraftToClient(
      const QVector<AircraftDefinition>
        &list);   // tell network manager to send the aircraft from list to the client to store

public slots:
    void setAircraft(
      const AircraftDefinition
        &newDef);   // add (or update if it already exists) the data from newDef to allAircraft list
    void setClientKeys(const QStringList &keys);   // update the names of the client stored aircraft
};

#endif   // AIRCRAFTMANAGER_H
