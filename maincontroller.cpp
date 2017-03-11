#include "maincontroller.h"

MainController::MainController()
{

}

MainController::~MainController()
{

}

void MainController::startup()
{
    // Creating Subthreads

    // Creating Serial-Worker
    QSerialPort serialPort;
    QString serialPortName = "COM5";
    serialPort.setPortName(serialPortName);

    int serialPortBaudRate = QSerialPort::Baud9600;
    serialPort.setBaudRate(serialPortBaudRate);

    m_serialWorker = new SerialWorker(&serialPort);
    m_serialWorker->moveToThread(&m_serialThread);

    connect(&m_serialThread, &QThread::finished, m_serialWorker, &QObject::deleteLater);

    // Creating Main-Window
    m_mainWindow = new MainWindow();

    // QT needs the Interface in the main-thread
    // mainWindow.moveToThread(&m_windowThread);
    // connect(&m_windowThread, &QThread::finished, &mainWindow, &QObject::deleteLater);

    m_mainWindow->show();

    // DSP-Controller
    m_dspController = new DspController();
    m_dspController->updateConnectionStatus();

    connect(m_dspController, &DspController::serialWrite, m_serialWorker, &SerialWorker::write);

}
