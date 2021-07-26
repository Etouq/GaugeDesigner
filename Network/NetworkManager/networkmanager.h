#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

struct AircraftDefinition;

class NetworkManager : public QObject
{
    Q_OBJECT

    QTcpServer tcpServer;
    QTcpSocket *tcpSocket;

    const uint8_t latestGaugeNetworkVersion = 1;

public:
    explicit NetworkManager(QObject *parent = nullptr);

    void init();

signals:
    void connectedChanged(bool connected);
    void receivedFileList(const QStringList &list);
    void receivedAircraft(const AircraftDefinition &aircraft);
    void serverInitFinished(const QString &address, int port);

    void versionError(const QString &msg);

public slots:
    void connectionStateChanged(QAbstractSocket::SocketState socketState);
    void removeClientAircraft(const QStringList &list);
    void loadClientAircraft(const QStringList &list);
    void sendAircraftToClient(const QVector<AircraftDefinition> &list);

private slots:
    void newIncomingConnection();
    void receivedDataFromClient();



};

#endif // NETWORKMANAGER_H
