#ifndef HANDLERDSPPROTOCOL_H
#define HANDLERDSPPROTOCOL_H

#include "dspprotocolhandler.h"
#include "dspprotocol.h"

#include <QDebug>

class HandlerDspProtocol : public DspProtocolHandler
{
public:
    HandlerDspProtocol();

    void        parsePacket(QByteArray data, DspProtocol::IPacket &packet);
    QByteArray  buildPacket(unsigned char cmd, unsigned char* data);

};

#endif // HANDLERDSPPROTOCOL_H
