#include "networkmanager.ih"
#include <QBuffer>
#include <QImage>
#include "AircraftManager/definitions/aircraftDefinition.h"

void NetworkManager::sendAircraftToClient(const QVector<AircraftDefinition> &list)
{
        for (int i = 0; i < list.size(); i++)
        {
            QString imagePath = AircraftFile::getImagePath(list[i].name);
            if (!QFile(imagePath).exists())
                imagePath = ":/DefaultImage.png";

            QImage img(imagePath);

            DesignerIds id = DesignerIds::SAVE_AIRCRAFT;

            QByteArray buff(reinterpret_cast<char *>(&id), sizeof(id));
            QBuffer bufferStream(&buff);
            bufferStream.open(QIODevice::WriteOnly | QIODevice::Append);
            AircraftFile::writeAircraftToStream(bufferStream, list[i], img);

            tcpSocket->write(buff);
        }
}
