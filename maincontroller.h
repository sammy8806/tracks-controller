#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "serialworker.h"
#include "mainwindow.h"
#include "dspcontroller.h"

#include <QObject>
#include <QThread>

class MainController : public QObject
{
    Q_OBJECT

public:
    MainController();
    ~MainController();

    void startup();

Q_SIGNALS:

public slots:

private:

    QThread* m_serialThread;
    QThread* m_windowThread;

    MainWindow* m_mainWindow;
    SerialWorker* m_serialWorker;
    DspController* m_dspController;

};

#endif // MAINCONTROLLER_H
