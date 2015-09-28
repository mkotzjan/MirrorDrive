#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_chooseOriginFolder_clicked();

    void on_chooseDestinationFolder_clicked();

    void on_originPathButton_clicked();

    void on_destinationPathButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
