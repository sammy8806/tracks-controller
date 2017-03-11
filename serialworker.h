#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QTimer>
#include <QThread>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QTextStream>
#include <QCoreApplication>
#include <QFile>
#include <QStringList>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

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
