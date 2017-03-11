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
    emit displayName("Test123");
}

void DspController::updateConnectionStatus()
{
    emit connectionStatus("Foooo!");
}

void DspController::request(unsigned char cmd, unsigned char* data)
{
    switch(cmd) {
        case DspProtocol::CH_INFO:
            m_protoHandler = m_handlerChannelInfo;

        default:
            m_protoHandler = m_handlerDspProtocol;
    }

    QByteArray serialPacket;
    serialPacket = m_handlerDspProtocol->buildPacket(cmd, data);

    emit serialWrite(serialPacket);
}

void DspController::serialReceive(QByteArray recvData)
{
    DspProtocol::IPacket packet;
    m_protoHandler->parsePacket(recvData, packet);
}
