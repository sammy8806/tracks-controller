#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QByteArray>
#include <QTimer>
#include <QTextStream>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QCoreApplication>

class SerialWorker : public QObject
{
    Q_OBJECT

public:
    SerialWorker(QSerialPort *serialPort, QObject *parent = 0);

    QByteArray read();
    void write(QByteArray writeData);

private slots:
    void handleError(QSerialPort::SerialPortError error);

Q_SIGNALS:
    void dataReceived(QByteArray data);

private:
    QSerialPort     *m_serialPort;
    QByteArray      m_readData;
    QTimer          m_timerRead;
    QTextStream     m_standardOutput;
};

#endif // SERIALWORKER_H
