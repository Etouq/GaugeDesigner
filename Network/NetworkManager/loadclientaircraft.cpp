#include "networkmanager.ih"

void NetworkManager::loadClientAircraft(const QStringList &list)
{

    uint16_t size = list.size();
    QByteArray dataToSend = BinaryUtil::toBinary(size);

    for (int idx = 0; idx < size; idx++)
        dataToSend += BinaryUtil::toBinary(list[idx]);

    int64_t totalSize = dataToSend.size();   // size in bytes
    dataToSend.prepend(BinaryUtil::toBinary(totalSize));

    DesignerIds id = DesignerIds::LOAD_AIRCRAFT_LIST;
    dataToSend.prepend(reinterpret_cast<char *>(&id), sizeof(id));

    tcpSocket->write(dataToSend);
}
