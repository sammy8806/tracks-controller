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

    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialWorker::handleReadyRead, Qt::DirectConnection);
    connect(m_serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &SerialWorker::handleError);
    connect(&m_timerRead, &QTimer::timeout, this, &SerialWorker::handleReadTimeout, Qt::DirectConnection);

    m_timerRead.setSingleShot(false);
    m_timerRead.start(300);

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

void SerialWorker::handleReadyRead()
{
    qDebug() << "SerialWorker::handleReadyRead";
    QByteArray readData = m_serialPort->readAll();
    m_readData.append(readData);

    if(0 < readData.size()){
        qDebug() << "Received bytes: " << readData.size() << " Timestamp: " << QDateTime::currentMSecsSinceEpoch();
    }else{
        qDebug() << "No data." << " Timestamp: " << QDateTime::currentMSecsSinceEpoch();
    }

    if (!m_timerRead.isActive())
        m_timerRead.start(500);
}

void SerialWorker::handleReadTimeout()
{
    // qDebug() << "SerialWorker::handleReadTimeout";

    if (m_readData.isEmpty()) {
        // m_standardOutput << QObject::tr("No data was currently available for reading from port %1").arg(m_serialPort->portName()) << endl;
    } else {
        qDebug() << QObject::tr("Data successfully received from port %1").arg(m_serialPort->portName()) << endl;
        QByteArray buf;
        bool inPacket = false;
        for(int i=0; i<m_readData.length(); i++) {
            qDebug() << "-> " << QByteArray(1, m_readData.at(i)).toHex();

            unsigned char activeChar = m_readData.at(i);
            if((activeChar == PACKET_BEGIN) && (!inPacket)) {
                qDebug() << "- Starting Packet";
                inPacket = true;
            }

            if(inPacket) {
                qDebug() << "- Packet Data";
                buf.append(activeChar);
            }

            if(activeChar == PACKET_END && inPacket) {
                qDebug() << "- Ending Packet";

                inPacket = false;
                emit dataReceived(buf);
                // emit incomingPacket(buf);
                buf.clear();
            }

            qDebug() << "~ Packet processed";
        }

        m_readData.clear();
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
}
