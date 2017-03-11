#ifndef DSPPROTOCOLHANDLER_H
#define DSPPROTOCOLHANDLER_H

#include "dspprotocol.h"

class DspProtocolHandler
{
public:
    // virtual DspProtocolHandler() = 0;

    virtual void parsePacket(QByteArray data, DspProtocol::IPacket &packet) = 0;
};

#endif // DSPPROTOCOLHANDLER_H
