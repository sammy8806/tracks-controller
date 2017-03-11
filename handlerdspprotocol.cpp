#include "handlerdspprotocol.h"

HandlerDspProtocol::HandlerDspProtocol()
{

}

void HandlerDspProtocol::parsePacket(QByteArray data, DspProtocol::IPacket &packet)
{
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

    packet = static_cast<DspProtocol::IPacket>(packetTmp);
}
