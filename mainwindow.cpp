#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
