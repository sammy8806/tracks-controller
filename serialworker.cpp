#include "serialworker.h"

SerialWorker::SerialWorker(QSerialPort *serialPort, QObject *parent)
    : QObject(parent)
    , m_serialPort(serialPort)
    , m_standardOutput(stdout)
{
    qDebug() << "SerialWorker::SerialWorker";

    connect(m_serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &SerialWorker::handleError);

    qDebug() << "- Opening SerialPort: " << m_serialPort->portName();
    qDebug() << "- Address: " << m_serialPort->handle();
    m_serialPort->open(QIODevice::ReadWrite);
    qDebug() << "- Is port open: " << m_serialPort->isOpen();
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
    qDebug() << "SerialWorker::write";
    qDebug() << "- is port open: " << m_serialPort->isOpen();
    qDebug() << "- Address: " << m_serialPort->handle();

    qint64 bytesWritten = m_serialPort->write(writeData);
    qDebug() << "- Written: " << bytesWritten;

    if (bytesWritten == -1) {
        m_standardOutput << QObject::tr("Failed to write the data to port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
        QCoreApplication::exit(1);
    } else if (bytesWritten != writeData.size()) {
        m_standardOutput << QObject::tr("Failed to write all the data to port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
        QCoreApplication::exit(1);
    }

    m_serialPort->waitForBytesWritten(1000);

    m_serialPort->waitForReadyRead(1000);
    QByteArray answerData = this->read();
    emit dataReceived(answerData);
}
