#include "dspcontroller.h"

// Verwaltet die Verbindung mit dem Controller

DspController::DspController(QObject *parent) :
    QObject(parent)
    ,m_handlerDspProtocol(new HandlerDspProtocol())
    ,m_handlerChannelInfo(new HandlerChInfoProtocol())
{

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

void DspController::request(unsigned char cmd) {
    unsigned char data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    this->request(cmd, data);
}

void DspController::request(unsigned char cmd, unsigned char* data)
{
    qDebug() << "DspController::request";

    switch(cmd) {
        case DspProtocol::CH_INFO:
            qDebug() << "- Handler: Channel Info";
            m_protoHandler = m_handlerChannelInfo;

        default:
            qDebug() << "- Handler: DspProtocol";
            m_protoHandler = m_handlerDspProtocol;
    }

    QByteArray serialPacket;
    serialPacket = m_handlerDspProtocol->buildPacket(cmd, data);

    emit serialWrite(serialPacket);
}

void DspController::serialReceive(QByteArray recvData)
{
    qDebug() << "DspController::serialReceive";
    qDebug() << "- Packet-Size: " << recvData.length();

    DspProtocol::IPacket packet;
    m_protoHandler->parsePacket(recvData, packet);
}
