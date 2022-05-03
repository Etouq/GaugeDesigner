#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <QObject>

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
    explicit NetworkInterface(QObject *parent = nullptr);

    bool connected() const;
    QString address() const;
    int port() const;

    Q_INVOKABLE void removeAircraft(const QStringList &list);
    Q_INVOKABLE void loadAircraft(const QStringList &list);

signals:
    void connectedChanged();
    void addressChanged();
    void portChanged();
    void removeClientAircraft(const QStringList &list);
    void loadClientAircraft(const QStringList &list);

    void showPopupError(const QString &msg);

public slots:
    void setAddressAndPort(const QString &addr, int prt);
    void setConnectedState(bool connect);

    void showErrorPopup(const QString &msg);

};

#endif // NETWORKINTERFACE_H
