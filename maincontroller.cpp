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
    m_serialThread = new QThread();
    m_serialWorker = new SerialWorker();
    m_serialWorker->moveToThread(m_serialThread);

    connect(m_serialThread, &QThread::finished, m_serialWorker, &QObject::deleteLater);

    // DSP-Controller init
    m_dspController = new DspController();

    // Creating Main-Window
    m_mainWindow = new MainWindow(m_dspController);
    m_mainWindow->show();

    // QT needs the Interface in the main-thread
    // mainWindow.moveToThread(&m_windowThread);
    // connect(&m_windowThread, &QThread::finished, &mainWindow, &QObject::deleteLater);

    connect(m_dspController, &DspController::connectionStatus, m_mainWindow, &MainWindow::updateDeviceStatus);
    connect(m_dspController, &DspController::displayName, m_mainWindow, &MainWindow::updateDisplayName);
    connect(m_dspController, &DspController::serialWrite, m_serialWorker, &SerialWorker::write, Qt::DirectConnection);
    connect(m_serialWorker, &SerialWorker::dataReceived, m_dspController, &DspController::serialReceive, Qt::DirectConnection);

    m_dspController->updateConnectionStatus();
    m_dspController->disconnectDevice();

}
