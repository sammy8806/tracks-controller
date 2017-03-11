#include <QApplication>

#include "maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    MainController* controller = new MainController();
    controller->startup();

    return a.exec();
}
