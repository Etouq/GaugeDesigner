#include "AircraftManager/definitions/aircraftDefinition.h"
#include "networkmanager.ih"

#include <QImage>

void NetworkManager::receivedDataFromClient()
{
    bool reading = true;

    while (reading && !tcpSocket->atEnd())
    {
        tcpSocket->startTransaction();
        ClientToDesignerIds id = ClientToDesignerIds::LOAD_AIRCRAFT;
        tcpSocket->read(reinterpret_cast<char *>(&id), sizeof(id));
        switch (id)
        {
            case ClientToDesignerIds::CLIENT_NETWORK_VERSION:
            {
                if (tcpSocket->bytesAvailable() < sizeof(latestGaugeNetworkVersion))
                {
                    tcpSocket->rollbackTransaction();
                    reading = false;
                    break;
                }
                uint8_t clientVersion = 0;
                tcpSocket->read(reinterpret_cast<char *>(&clientVersion), sizeof(clientVersion));
                tcpSocket->commitTransaction();
                if (latestGaugeNetworkVersion < clientVersion)
                {
                    tcpSocket->disconnectFromHost();
                    emit versionError("The network data transfer version of the Flight Display "
                                      "Companion is newer than the one used by this application. "
                                      "Please update this application.");
                    return;
                }
                if (latestGaugeNetworkVersion > clientVersion)
                {
                    tcpSocket->disconnectFromHost();
                    emit versionError("The network data transfer version of the Flight Display "
                                      "Companion is older than the one used by this application. "
                                      "Please update the Flight Display Companion.");
                    return;
                }
                break;
            }
            case ClientToDesignerIds::LOAD_AIRCRAFT:
            {
                int64_t byteSize = 0;
                if (tcpSocket->bytesAvailable() < sizeof(byteSize))
                {
                    tcpSocket->rollbackTransaction();
                    reading = false;
                    break;
                }
                tcpSocket->read(reinterpret_cast<char *>(&byteSize), sizeof(byteSize));
                if (tcpSocket->bytesAvailable() < byteSize)
                {
                    tcpSocket->rollbackTransaction();
                    reading = false;
                    break;
                }
                QImage img;
                AircraftDefinition aircraft;

                AircraftFile::readAircraftFromStream(*tcpSocket, aircraft, img);
                tcpSocket->commitTransaction();

                AircraftFile::saveAircraftWithImage(aircraft, img);
                emit receivedAircraft(aircraft);
                break;
            }
            case ClientToDesignerIds::AIRCRAFT_FILE_LIST:
            {
                int64_t byteSize = 0;
                if (tcpSocket->bytesAvailable() < sizeof(byteSize))
                {
                    tcpSocket->rollbackTransaction();
                    reading = false;
                    break;
                }
                tcpSocket->read(reinterpret_cast<char *>(&byteSize), sizeof(byteSize));
                if (tcpSocket->bytesAvailable() < byteSize)
                {
                    tcpSocket->rollbackTransaction();
                    reading = false;
                    break;
                }
                uint16_t size = 0;
                tcpSocket->read(reinterpret_cast<char *>(&size), sizeof(size));
                QStringList names;
                for (int i = 0; i < size; i++)
                {
                    QString name = "";
                    uint8_t stringSize = 0;
                    tcpSocket->read(reinterpret_cast<char *>(&stringSize), sizeof(stringSize));
                    if (stringSize != 0)
                        name = tcpSocket->read(stringSize);

                    names.append(name);
                }

                tcpSocket->commitTransaction();

                emit receivedFileList(names);
                break;
            }
            case ClientToDesignerIds::QUIT:
            {
                tcpSocket->commitTransaction();
                break;
            }
            default:
                qDebug() << "received unknown data:" << static_cast<int>(id);
                tcpSocket->commitTransaction();
                break;
        }
    }
}
