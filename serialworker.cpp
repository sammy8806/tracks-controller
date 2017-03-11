#include "serialworker.h"

QT_USE_NAMESPACE

SerialWorker::SerialWorker(QObject *parent)
    : QObject(parent)
    , m_standardOutput(stdout)
    , m_serialPort(new QSerialPort())
{
    qDebug() << "SerialWorker::SerialWorker";

    QString serialPortName = "COM5";
    m_serialPort->setPortName(serialPortName);

    int serialPortBaudRate = QSerialPort::Baud9600;
    m_serialPort->setBaudRate(serialPortBaudRate);
    m_serialPort->open(QIODevice::ReadWrite);

    connect(m_serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &SerialWorker::handleError);

    qDebug() << "- Opening SerialPort: " << m_serialPort->portName();
    qDebug() << "- Address: " << m_serialPort->handle();
    qDebug() << "- Is port open: " << m_serialPort->isOpen();
    qDebug() << "- is port writeable: " << m_serialPort->isWritable();
}

void SerialWorker::handleError(QSerialPort::SerialPortError serialPortError)
{
    qDebug() << "ERROR!!!!!";

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
    QByteArray writeStr;
    qDebug() << "SerialWorker::write";
    qDebug() << "- is port open: " << m_serialPort->isOpen();
    qDebug() << "- is port writeable: " << m_serialPort->isWritable();
    qDebug() << "- Address: " << m_serialPort->handle();
    writeStr = QByteArray::fromHex(writeData.toHex());
    qDebug() << "- Data: " << writeStr;

    qDebug() << "= ThreadId: " << this->thread()->currentThreadId();

    // QString writeStr(writeData.toHex());

    if(!m_serialPort->isWritable()) {
        qDebug() << "-> Reopening Device for Write";
        m_serialPort->close();
        m_serialPort->open(QIODevice::ReadWrite);
        qDebug() << "-> Selfcall";
        this->write(writeData);
        return;
    }

    qint64 bytesWritten = m_serialPort->write(writeStr);
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
