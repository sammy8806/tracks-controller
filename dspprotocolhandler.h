#ifndef DSPPROTOCOLHANDLER_H
#define DSPPROTOCOLHANDLER_H

#include "dspprotocol.h"

class DspProtocolHandler
{
public:
    // virtual DspProtocolHandler() = 0;

    template<typename T>
    void parsePacket(QByteArray data, T &packet);
};

#endif // DSPPROTOCOLHANDLER_H
