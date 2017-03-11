#include "serialworker.h"

SerialWorker::SerialWorker(QSerialPort *serialPort, QObject *parent)
    : QObject(parent)
    , m_serialPort(serialPort)
    , m_standardOutput(stdout)
{
    connect(m_serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &SerialWorker::handleError);

    m_serialPort->open(QIODevice::ReadWrite);
}

void SerialWorker::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::WriteError) {
        m_standardOutput << QObject::tr("An I/O error occurred while writing the data to port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
        QCoreApplication::exit(1);
    }
}

QByteArray SerialWorker::read() {
    QByteArray buf = m_serialPort->readAll();
    return buf;
}

void SerialWorker::write(QByteArray writeData)
{
    m_serialPort->write(writeData);
    m_serialPort->waitForBytesWritten(1000);
}
