#ifndef DSPCONTROLLER_H
#define DSPCONTROLLER_H

#include "dspprotocol.h"
#include "handlerdspprotocol.h"
#include "handlerchinfoprotocol.h"

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>

class DspController : public QObject
{
    Q_OBJECT
public:
    explicit DspController(QObject *parent = 0);

    void updateDisplayName();
    void updateConnectionStatus();

    void initDevice();
    void disconnectDevice();
    void updateLineData();
    void muteChannel(unsigned char channel, bool status);

protected:
    void request(unsigned char cmd);
    void request(unsigned char cmd, unsigned char *data);

private:
    //DspProtocolHandler* m_protoHandler;
    HandlerDspProtocol* m_protoHandler;
    HandlerDspProtocol* m_handlerDspProtocol;
    HandlerChInfoProtocol* m_handlerChannelInfo;

    unsigned char m_lastCmd;

    QTimer  m_timer;

signals:
    void serialWrite(QByteArray writeData);

    void displayName(QString name);
    void connectionStatus(QString status);
    void lineData(DspProtocol::LineInfo);
    void mute(unsigned char channel, bool status);

public slots:
    void serialReceive(QByteArray recvData);

private slots:
    void timerTimeout();
};

#endif // DSPCONTROLLER_H
