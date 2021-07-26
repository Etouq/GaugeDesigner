#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <QObject>
#include "NetworkManager/networkmanager.h"

class NetworkInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(QString address READ address NOTIFY addressChanged)
    Q_PROPERTY(int port READ port NOTIFY portChanged)


    bool d_connected = false;
    QString d_address = "";
    int d_port = -1;

public:
    explicit NetworkInterface(QObject *parent = nullptr) : QObject(parent) {}

    bool connected() const { return d_connected; }
    QString address() const { return d_address; }
    int port() const { return d_port; }

    Q_INVOKABLE void removeAircraft(const QStringList &list) { emit removeClientAircraft(list); }
    Q_INVOKABLE void loadAircraft(const QStringList &list) { emit loadClientAircraft(list); }

signals:
    void connectedChanged();
    void addressChanged();
    void portChanged();
    void removeClientAircraft(const QStringList &list);
    void loadClientAircraft(const QStringList &list);

    void showPopupError(const QString &msg);

public slots:
    void setAddressAndPort(const QString &addr, int prt) { d_address = addr; d_port = prt; emit addressChanged(); emit portChanged(); }
    void setConnectedState(bool connect) { d_connected = connect; emit connectedChanged(); }

    void showErrorPopup(const QString &msg) { emit showPopupError(msg); }

};

#endif // NETWORKINTERFACE_H
