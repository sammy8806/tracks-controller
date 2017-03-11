#ifndef HANDLERCHINFOPROTOCOL_H
#define HANDLERCHINFOPROTOCOL_H

#include "dspprotocol.h"
#include "dspprotocolhandler.h"

class HandlerChInfoProtocol : public DspProtocolHandler
{
public:
    HandlerChInfoProtocol();

    void parsePacket(QByteArray data, DspProtocol::IPacket &packet);
};

#endif // HANDLERCHINFOPROTOCOL_H
