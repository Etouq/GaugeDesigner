#include "networkmanager.ih"

void NetworkManager::removeClientAircraft(const QStringList &list)
{
    uint16_t size = list.size();
    QByteArray dataToSend = BinaryUtil::toBinary(size);
    for (int idx = 0; idx < size; idx++)
    {
        dataToSend += BinaryUtil::toBinary(list[idx]);
    }
    int64_t totalSize = dataToSend.size();
    dataToSend.prepend(BinaryUtil::toBinary(totalSize));
    DataIdentifiers id = DataIdentifiers::REMOVE_AIRCRAFT_LIST;
    dataToSend.prepend(reinterpret_cast<char *>(&id), sizeof(id));
    tcpSocket->write(dataToSend);
}
