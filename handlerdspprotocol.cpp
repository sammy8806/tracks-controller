#include "handlerdspprotocol.h"

HandlerDspProtocol::HandlerDspProtocol()
{

}

void HandlerDspProtocol::parsePacket(QByteArray data, DspProtocol::IPacket &packet)
{
    qDebug() << "HandlerDspProtocol::parsePacket";

    DspProtocol::Packet packetTmp;
    packetTmp.stx = data[0];
    packetTmp.idm = data[1];
    packetTmp.idn = data[2];
    packetTmp.cmd = data[3];
    packetTmp.d0  = data[4];
    packetTmp.d1  = data[5];
    packetTmp.d2  = data[6];
    packetTmp.d3  = data[7];
    packetTmp.d4  = data[8];
    packetTmp.d5  = data[9];
    packetTmp.d6  = data[10];
    packetTmp.d7  = data[11];
    packetTmp.etx = data[12];

    qDebug() << "- Parsed answer packet type: " << QByteArray(1, packetTmp.cmd).toHex();
    qDebug() << "Data Pack: "
                << "0x" << packetTmp.d0 << " "
                << "0x" << packetTmp.d1 << " "
                << "0x" << packetTmp.d2 << " "
                << "0x" << packetTmp.d3 << " "
                << "0x" << packetTmp.d4 << " "
                << "0x" << packetTmp.d5 << " "
                << "0x" << packetTmp.d6 << " "
                << "0x" << packetTmp.d7 << " ";

    packet = static_cast<DspProtocol::IPacket>(packetTmp);
}

QByteArray HandlerDspProtocol::buildPacket(unsigned char cmd, unsigned char *data)
{
    qDebug() << "HandlerDspProtocol::buildPacket";
    qDebug() << "- Building for cmd: " << QByteArray(1, cmd).toHex();

    unsigned char packetData[] = {0xf0, 0xc2, 0x00, cmd,
                                  0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00,
                                  0xf7};

    for(int i=0; i<7; i++)
        packetData[i+4] = data[i];

    QByteArray packet(reinterpret_cast<const char*>(packetData), sizeof(packetData));
    return packet;
}

