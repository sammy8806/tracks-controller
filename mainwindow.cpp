#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(DspController* dspController, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dspController(dspController)
{
    ui->setupUi(this);
    m_dspController->initDevice();
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

void MainWindow::updateLineData(DspProtocol::LineInfo data)
{
    qDebug() << "MainWindow::updateLineData";

    // Select | -20 | -10 | 0 | +3 | +9 | +15 | Clip | Limit

    ui->limitA->setVisible(false);
    ui->clipA->setVisible(data.inA & (1<<1));
    ui->inA->setValue(!!(data.inA & (1<<1)) + !!(data.inA & (1<<2)) + !!(data.inA & (1<<3)) + !!(data.inA & (1<<4)) + !!(data.inA & (1<<5)) + !!(data.inA & (1<<6)));
    ui->lblA->setFrameShape(!!(data.inA & (1<<7)) ? QFrame::Box : QFrame::NoFrame);

    ui->limitB->setVisible(false);
    ui->clipB->setVisible(data.inB & (1<<0));
    ui->inB->setValue(!!(data.inB & (1<<1)) + !!(data.inB & (1<<2)) + !!(data.inB & (1<<3)) + !!(data.inB & (1<<4)) + !!(data.inB & (1<<5)) + !!(data.inB & (1<<6)));
    ui->lblB->setFrameShape(!!(data.inB & (1<<7)) ? QFrame::Box : QFrame::NoFrame);

    ui->limit1->setVisible(data.out1 & (1<<0));
    ui->clip1->setVisible(data.out1 & (1<<1));
    ui->out1->setValue(!!(data.out1 & (1<<2)) + !!(data.out1 & (1<<3)) + !!(data.out1 & (1<<4)) + !!(data.out1 & (1<<5)) + !!(data.out1 & (1<<6)));
    ui->lbl1->setFrameShape(!!(data.out1 & (1<<7)) ? QFrame::Box : QFrame::NoFrame);

    ui->limit2->setVisible(data.out2 & (1<<0));
    ui->clip2->setVisible(data.out2 & (1<<1));
    ui->out2->setValue(!!(data.out2 & (1<<2)) + !!(data.out2 & (1<<3)) + !!(data.out2 & (1<<4)) + !!(data.out2 & (1<<5)) + !!(data.out2 & (1<<6)));
    ui->lbl2->setFrameShape(!!(data.out2 & (1<<7)) ? QFrame::Box : QFrame::NoFrame);

    ui->limit3->setVisible(data.out3 & (1<<0));
    ui->clip3->setVisible(data.out3 & (1<<1));
    ui->out3->setValue(!!(data.out3 & (1<<2)) + !!(data.out3 & (1<<3)) + !!(data.out3 & (1<<4)) + !!(data.out3 & (1<<5)) + !!(data.out3 & (1<<6)));
    ui->lbl3->setFrameShape(!!(data.out3 & (1<<7)) ? QFrame::Box : QFrame::NoFrame);

    ui->limit4->setVisible(data.out4 & (1<<0));
    ui->clip4->setVisible(data.out4 & (1<<1));
    ui->out4->setValue(!!(data.out4 & (1<<2)) + !!(data.out4 & (1<<3)) + !!(data.out4 & (1<<4)) + !!(data.out4 & (1<<5)) + !!(data.out4 & (1<<6)));
    ui->lbl4->setFrameShape(!!(data.out4 & (1<<7)) ? QFrame::Box : QFrame::NoFrame);
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
