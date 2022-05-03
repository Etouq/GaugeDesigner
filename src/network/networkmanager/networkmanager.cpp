#include "networkmanager.ih"

#include <QMessageBox>
#include <QNetworkInterface>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent), tcpSocket(new QTcpSocket)
{
    connect(&tcpServer, &QTcpServer::newConnection, this, &NetworkManager::newIncomingConnection);
}


void NetworkManager::init()
{
    if (!tcpServer.listen(QHostAddress::Any, 58008))
        if (!tcpServer.listen())
        {
            QMessageBox::critical(
              nullptr,
              "Gauge Designer Server",
              QString("Unable to start the server: %1.").arg(tcpServer.errorString()));
            return;
        }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost ipv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost
            && ipAddressesList.at(i).protocol() == QAbstractSocket::IPv4Protocol)
        {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    // if we did not find one, use first non-localhost
    if (ipAddress.isEmpty())
        for (int i = 0; i < ipAddressesList.size(); ++i)
        {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost)
            {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }

    // else use localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    emit serverInitFinished(ipAddress, tcpServer.serverPort());
}

void NetworkManager::newIncomingConnection()
{
    tcpSocket->abort();
    tcpSocket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    tcpSocket = tcpServer.nextPendingConnection();
    tcpSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    tcpServer.pauseAccepting();

    connect(tcpSocket, &QTcpSocket::stateChanged, this, &NetworkManager::connectionStateChanged);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &NetworkManager::receivedDataFromClient);

    connectionStateChanged(tcpSocket->state());

    SharedServerIds id = SharedServerIds::GAUGE_DESIGNER_SERVER;

    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&latestGaugeNetworkVersion),
                      sizeof(latestGaugeNetworkVersion));
    tcpSocket->write(dataToSend);
}

void NetworkManager::connectionStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        disconnect(tcpSocket,
                   &QTcpSocket::stateChanged,
                   this,
                   &NetworkManager::connectionStateChanged);
        disconnect(tcpSocket,
                   &QTcpSocket::readyRead,
                   this,
                   &NetworkManager::receivedDataFromClient);
        tcpServer.resumeAccepting();
    }
    emit connectedChanged(socketState == QAbstractSocket::ConnectedState);
}
