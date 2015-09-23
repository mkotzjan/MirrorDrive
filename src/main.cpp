#include "filemanager.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    FileManager f;
    f.chooseDirectory();
    w.show();

    return a.exec();
}
