#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(DspController* dspController, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dspController(dspController)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDisplayName(QString name)
{
    ui->deviceDisplayName->setText(name);
}

void MainWindow::updateDeviceStatus(QString status)
{
    ui->deviceStatus->setText(status);
}

void MainWindow::on_btnConnect_clicked()
{
    m_dspController->initDevice();
}

void MainWindow::on_btnDisconnect_clicked()
{
    m_dspController->disconnectDevice();
}

void MainWindow::on_btnLineUpdate_clicked()
{
    m_dspController->updateLineData();
}
