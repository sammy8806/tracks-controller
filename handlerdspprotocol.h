#ifndef HANDLERDSPPROTOCOL_H
#define HANDLERDSPPROTOCOL_H

#include "dspprotocolhandler.h"
#include "dspprotocol.h"

#include <QDebug>

class HandlerDspProtocol : public DspProtocolHandler
{
public:
    HandlerDspProtocol();

    template<typename T>
    void parsePacket(QByteArray data, T &packet)
    {
        qDebug() << "HandlerDspProtocol::parsePacket";
        qDebug() << "- Data: " << data.toHex();

        packet.stx = data[0];
        packet.idm = data[1];
        packet.idn = data[2];
        packet.cmd = data[3];
        packet.d0  = data[4];
        packet.d1  = data[5];
        packet.d2  = data[6];
        packet.d3  = data[7];
        packet.d4  = data[8];
        packet.d5  = data[9];
        packet.d6  = data[10];
        packet.d7  = data[11];
        packet.etx = data[12];

        qDebug() << "- Parsed answer packet type: " << QByteArray(1, packet.cmd).toHex();
        qDebug() << "Data Pack: " << endl
                    << QString::number(packet.d0, 2) << " " << QString::number(packet.d0, 16) << " " << QString::number(packet.d0, 10) << endl
                    << QString::number(packet.d1, 2) << " " << QString::number(packet.d1, 16) << " " << QString::number(packet.d1, 10) << endl
                    << QString::number(packet.d2, 2) << " " << QString::number(packet.d2, 16) << " " << QString::number(packet.d2, 10) << endl
                    << QString::number(packet.d3, 2) << " " << QString::number(packet.d3, 16) << " " << QString::number(packet.d3, 10) << endl
                    << QString::number(packet.d4, 2) << " " << QString::number(packet.d4, 16) << " " << QString::number(packet.d4, 10) << endl
                    << QString::number(packet.d5, 2) << " " << QString::number(packet.d5, 16) << " " << QString::number(packet.d5, 10) << endl
                    << QString::number(packet.d6, 2) << " " << QString::number(packet.d6, 16) << " " << QString::number(packet.d6, 10) << endl
                    << QString::number(packet.d7, 2) << " " << QString::number(packet.d7, 16) << " " << QString::number(packet.d7, 10) << endl;
                   /* << packet.d0 << " "
                    << packet.d1 << " "
                    << packet.d2 << " "
                    << packet.d3 << " "
                    << packet.d4 << " "
                    << packet.d5 << " "
                    << packet.d6 << " "
                    << packet.d7 << " ";*/
    }

    QByteArray buildPacket(unsigned char cmd, unsigned char* data);

};

#endif // HANDLERDSPPROTOCOL_H
