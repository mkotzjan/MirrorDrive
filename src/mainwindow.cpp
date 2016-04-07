#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    fileHelper = new FileHelper();
    ui->setupUi(this);
    ui->editOriginPath->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: orange;}");
    ui->editDestinationPath->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: orange;}");
}

MainWindow::~MainWindow()
{
    delete fileHelper;
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    fileHelper->setDir(ui->editOriginPath->text(), ui->editDestinationPath->text());
    //fileHelper->startMirror(ui->progressBar, ui->statusBar);
    fileHelper->checkPreferences(this);
}

void MainWindow::on_setOriginPath_clicked()
{
    QString dir = fileHelper->openDirDialog(this, "Choose Origin Directory");
    ui->editOriginPath->setText(dir);
}

void MainWindow::on_setDestinationPath_clicked()
{
    QString dir = fileHelper->openDirDialog(this, "Choose Destination Directory");
    ui->editDestinationPath->setText(dir);
}

void MainWindow::on_editOriginPath_textChanged(const QString &arg1)
{
    ui->editOriginPath->setStyleSheet(fileHelper->checkDir(arg1, 1));
    ui->startButton->setEnabled(fileHelper->isStartPossible());
}

void MainWindow::on_editDestinationPath_textChanged(const QString &arg1)
{
    ui->editDestinationPath->setStyleSheet(fileHelper->checkDir(arg1, 2));
    ui->startButton->setEnabled(fileHelper->isStartPossible());
}
