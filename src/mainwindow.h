#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <databasehelper.h>
#include <filehelper.h>
#include <QCompleter>
#include <QDirModel>
#include <QMainWindow>
#include <QString>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QCompleter *originCompleter;
    QCompleter *destinationCompleter;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void on_setOriginPath_clicked();

    void on_setDestinationPath_clicked();

    void on_editOriginPath_textChanged(const QString &arg1);

    void on_editDestinationPath_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    FileHelper *fileHelper;
    DatabaseHelper *databaseHelper;
    QString database;
};

#endif // MAINWINDOW_H
