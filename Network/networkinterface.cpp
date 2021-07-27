#include "networkinterface.h"

NetworkInterface::NetworkInterface(QObject *parent) : QObject(parent)
{
}

bool NetworkInterface::connected() const
{
    return d_connected;
}

QString NetworkInterface::address() const
{
    return d_address;
}

int NetworkInterface::port() const
{
    return d_port;
}

void NetworkInterface::removeAircraft(const QStringList &list)
{
    emit removeClientAircraft(list);
}

void NetworkInterface::loadAircraft(const QStringList &list)
{
    emit loadClientAircraft(list);
}

void NetworkInterface::setAddressAndPort(const QString &addr, int prt)
{
    d_address = addr;
    d_port = prt;
    emit addressChanged();
    emit portChanged();
}

void NetworkInterface::setConnectedState(bool connect)
{
    d_connected = connect;
    emit connectedChanged();
}

void NetworkInterface::showErrorPopup(const QString &msg)
{
    emit showPopupError(msg);
}
