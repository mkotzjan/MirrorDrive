#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_originPathButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(
                this,
                tr("Choose Origin Directory"),
                "/home",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );
    ui->originPathEdit->setText(dir);
}

void MainWindow::on_destinationPathButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(
                this,
                tr("Choose Destination Directory"),
                "/home",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );
    ui->destinationPathEdit->setText(dir);
}

void MainWindow::on_startButton_clicked()
{
    // do stuff
}
