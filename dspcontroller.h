#ifndef DSPCONTROLLER_H
#define DSPCONTROLLER_H

#include <QObject>
#include <QThread>

#include "handlerdspprotocol.h"
#include "handlerchinfoprotocol.h"
#include "dspprotocol.h"

class DspController : public QObject
{
    Q_OBJECT
public:
    explicit DspController(QObject *parent = 0);

    void updateDisplayName();
    void updateConnectionStatus();

protected:
    void request(unsigned char cmd, unsigned char *data);

private:
    DspProtocolHandler* m_protoHandler;
    HandlerDspProtocol* m_handlerDspProtocol;
    HandlerChInfoProtocol* m_handlerChannelInfo;

    unsigned char m_lastCmd;

signals:
    void serialWrite(QByteArray writeData);

    void displayName(QString name);
    void connectionStatus(QString status);

public slots:
    void serialReceive(QByteArray recvData);
};

#endif // DSPCONTROLLER_H
