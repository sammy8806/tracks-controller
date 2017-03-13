#include "handlerdspprotocol.h"

HandlerDspProtocol::HandlerDspProtocol()
{

}


QByteArray HandlerDspProtocol::buildPacket(unsigned char cmd, unsigned char *data)
{
    qDebug() << "HandlerDspProtocol::buildPacket";
    qDebug() << "- Building for cmd: " << QByteArray(1, cmd).toHex();

    unsigned char packetData[] = {0xf0, 0xc2, 0x00, cmd,
                                  0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00,
                                  0xf7};

    /*for(int i=0; i<8; i++)
        packetData[i+4] = data[i];*/

    memcpy(packetData+4, data, 8);

    QByteArray packet(reinterpret_cast<const char*>(packetData), sizeof(packetData));
    return packet;
}
