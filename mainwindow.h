#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
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
    bool m_muteStatus[8];
    QMap<unsigned int, QPushButton*> m_muteButtons;

public slots:
    void updateDisplayName(QString name);
    void updateDeviceStatus(QString status);
    void updateLineData(DspProtocol::LineInfo data);
    void updateMute(unsigned char channel, bool status);

private slots:
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
    void on_btnLineUpdate_clicked();
    void on_muteA_clicked();
    void on_mute3_clicked();
    void on_muteB_clicked();
    void on_mute1_clicked();
    void on_mute2_clicked();
    void on_mute4_clicked();
};

#endif // MAINWINDOW_H
