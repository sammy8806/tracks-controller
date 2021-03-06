#ifndef HANDLERCHINFOPROTOCOL_H
#define HANDLERCHINFOPROTOCOL_H

#include "dspprotocol.h"
#include "dspprotocolhandler.h"

class HandlerChInfoProtocol : public DspProtocolHandler
{
public:
    HandlerChInfoProtocol();

    template<typename T>
    void parsePacket(QByteArray data, T &packet)
    {
        DspProtocol::ChInfoPacket packetTmp;

        // memcpy_s(packet.unclear, 40, data, 40);
        for(int i=0; i<40; i++)
            packetTmp.unclear[i] = data[i];

        // memcpy_s(packet.chanName, 8, *(&data + 40), 8);
        for(int i=0; i<8; i++)
            packetTmp.chanName[i] = data[i+40];

        // memcpy_s(packet.presetName, 16, *(&data + 40), 16);
        for(int i=0; i<16; i++)
            packetTmp.presetName[i] = data[i+48];

        packet = static_cast<DspProtocol::IPacket>(packetTmp);
    }

};

#endif // HANDLERCHINFOPROTOCOL_H
