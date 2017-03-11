#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dspcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DspController *dspController, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DspController* m_dspController;

public slots:
    void updateDisplayName(QString name);
    void updateDeviceStatus(QString status);
    void updateLineData(DspProtocol::LineInfo data);

private slots:
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
    void on_btnLineUpdate_clicked();
};

#endif // MAINWINDOW_H
