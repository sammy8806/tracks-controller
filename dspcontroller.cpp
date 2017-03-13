#include "dspcontroller.h"

// Verwaltet die Verbindung mit dem Controller

DspController::DspController(QObject *parent) :
    QObject(parent)
    ,m_handlerDspProtocol(new HandlerDspProtocol())
    ,m_handlerChannelInfo(new HandlerChInfoProtocol())
{
    connect(&m_timer, &QTimer::timeout, this, &DspController::timerTimeout);
    m_timer.setSingleShot(false);
    // m_timer.start(2000);
}

void DspController::timerTimeout() {
    qDebug() << "DspController::timerTimeout";
    this->updateLineData();
}

void DspController::updateDisplayName()
{
    qDebug() << "DspController::updateDisplayName";
    emit displayName("Test123");
}

void DspController::updateConnectionStatus()
{
    qDebug() << "DspController::updateConnectionStatus";
    emit connectionStatus("Foooo!");
}

void DspController::initDevice()
{
    qDebug() << "DspController::initDevice";
    this->request(DspProtocol::INIT);
}

void DspController::disconnectDevice()
{
    qDebug() << "DspController::disconnectDevice";
    this->request(DspProtocol::QUIT);
}

void DspController::updateLineData()
{
    qDebug() << "DspController::updateLineData";
    this->request(DspProtocol::LINE_DATA);
}

void DspController::muteChannel(unsigned char channel, bool status)
{
    qDebug() << "DspController::mute(" << QString::number(channel) << "-" << status << ")";
    unsigned char data[] = {channel, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, status};
    this->request(DspProtocol::MUTE, data);
}

void DspController::request(unsigned char cmd) {
    unsigned char data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    this->request(cmd, data);
}

void DspController::request(unsigned char cmd, unsigned char* data)
{
    qDebug() << "DspController::request";

    switch(cmd) {
/*        case DspProtocol::CH_INFO:
            qDebug() << "- Handler: Channel Info";
            m_protoHandler = m_handlerChannelInfo;
*/
        default:
            qDebug() << "- Handler: DspProtocol";
            m_protoHandler = m_handlerDspProtocol;
    }

    QByteArray serialPacket;
    serialPacket = m_handlerDspProtocol->buildPacket(cmd, data);
    qDebug() << "~~ " << serialPacket.toHex();

    emit serialWrite(serialPacket);
}

void DspController::serialReceive(QByteArray recvData)
{
    qDebug() << "DspController::serialReceive";
    qDebug() << "- Packet-Size: " << recvData.length();

    DspProtocol::Packet packet;
    m_protoHandler->parsePacket<DspProtocol::Packet>(recvData, packet);

    switch (packet.cmd) {
    case DspProtocol::LINE_DATA:
        qDebug() << "# Line Data";

        DspProtocol::LineInfo data;
        data.inA = packet.d0;
        data.inB = packet.d1;
        data.out1 = packet.d2;
        data.out2 = packet.d3;
        data.out3 = packet.d4;
        data.out4 = packet.d5;

        emit lineData(data);
        break;

    case DspProtocol::MUTE:
        qDebug() << "# Mute";
        emit mute(packet.d0, packet.d7);
        break;

    default:
        qDebug() << "# Some Data";
        break;
    }

}
