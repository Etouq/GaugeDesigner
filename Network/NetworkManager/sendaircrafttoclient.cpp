#include "networkmanager.ih"

void NetworkManager::sendAircraftToClient(const QVector<AircraftDefinition> &list)
{
        for (int i = 0; i < list.size(); i++)
        {
            QString imagePath = AircraftFile::getImagePath(list[i].name);
            if (!QFile(imagePath).exists())
                imagePath = ":/DefaultImage.png";

            QImage img(imagePath);
            DataIdentifiers id = DataIdentifiers::SAVE_AIRCRAFT;
            tcpSocket->write(reinterpret_cast<char *>(&id), sizeof(id));
            AircraftFile::writeAircraftToStream(*tcpSocket, list[i], img);
        }
}
