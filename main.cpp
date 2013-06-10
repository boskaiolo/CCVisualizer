#include <QtGui/QApplication>
#include "mainwindow.h"

#include "parameters.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(W_WIDGET, H_WIDGET);

    w.show();

    return a.exec();
}
