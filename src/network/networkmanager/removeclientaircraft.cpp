#include "networkmanager.ih"

void NetworkManager::removeClientAircraft(const QStringList &list)
{
    uint16_t size = list.size();
    QByteArray dataToSend = BinaryConverter::toBinary(size);

    for (int idx = 0; idx < size; idx++)
        dataToSend += BinaryConverter::toBinary(list[idx]);

    int64_t totalSize = dataToSend.size();   // size in bytes
    dataToSend.prepend(BinaryConverter::toBinary(totalSize));

    DesignerIds id = DesignerIds::REMOVE_AIRCRAFT_LIST;
    dataToSend.prepend(reinterpret_cast<char *>(&id), sizeof(id));

    tcpSocket->write(dataToSend);
}
