#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    fileHelper = new FileHelper();
    ui->setupUi(this);
    originCompleter = new QCompleter(this);
    destinationCompleter = new QCompleter(this);
    QStringList filter;
    originCompleter->setModel(new QDirModel(filter, QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name, originCompleter));
    destinationCompleter->setModel(new QDirModel(filter, QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name, destinationCompleter));
    ui->editOriginPath->setCompleter(originCompleter);
    ui->editOriginPath->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: orange;}");
    ui->editDestinationPath->setCompleter(destinationCompleter);
    ui->editDestinationPath->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: orange;}");

    database = "/.mirror.db";
}

MainWindow::~MainWindow()
{
    delete fileHelper;
    delete originCompleter;
    delete destinationCompleter;
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    ui->progressBar->setValue(0);
    fileHelper->setDir(ui->editOriginPath->text(), ui->editDestinationPath->text());
    ErrorHelper result = fileHelper->checkPreferences();

    switch(result.getState())
    {
    case 2:
        QMessageBox::information(0, "Error", result.getMessage());
        return;
    case 1:
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "MirrorDrive", result.getMessage(),
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply != QMessageBox::Yes)
        {
            return;
        }
        ErrorHelper setTime = fileHelper->setTimestamp();
        if (setTime.getState() == 2)
            QMessageBox::information(0, "Error", setTime.getMessage());
        break;
    }

    result = DatabaseHelper::openDatabase(ui->editDestinationPath->text() + database);
    if (result.getState() == 2)
    {
        QMessageBox::information(0, "Error", result.getMessage());
        return;
    }

    fileHelper->startMirror(ui->progressBar, ui->statusBar);
    DatabaseHelper::closeDatabase();
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
