#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTreeWidgetItem* headerItem = new QTreeWidgetItem();
        headerItem->setText(0,QString("File Name"));
        headerItem->setText(1,QString("Size"));
    ui->originTree->setHeaderItem(headerItem);
    ui->destinationTree->setHeaderItem(headerItem);

    treeHelper = new TreeHelper();
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
    //Check if path exists
    if(ui->originPathEdit->text() == "" || ui->destinationPathEdit->text() == "")
        return;

    QDir* originDir = new QDir(ui->originPathEdit->text());
    QDir* destinationDir = new QDir(ui->destinationPathEdit->text());

    // Check if folder exist
    if(!originDir->exists() || !destinationDir->exists())
        return;

    QFileInfoList originFilesList = originDir->entryInfoList();
    QFileInfoList destinationFilesList = destinationDir->entryInfoList();

    int size = originFilesList.size();

    for(int i = 0; i < size; ++i)
    {
        QFileInfo* fileInfo = new QFileInfo(originDir->entryInfoList()[i]);
        if(fileInfo->isDir() && (fileInfo->fileName() == "." || fileInfo->fileName() == ".."))
        {
            continue;
        }
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, fileInfo->fileName());

        if(fileInfo->isFile())
        {
            item->setText(1,QString::number(fileInfo->size()));
            item->setIcon(0,*(new QIcon(":/icons/file.png")));
        }

        if(fileInfo->isDir())
        {
            item->setIcon(0,*(new QIcon(":/icons/folder.png")));
            treeHelper->addChildren(item, fileInfo->filePath());
        }
        ui->originTree->addTopLevelItem(item);
    }

//    foreach(QFileInfo fileInfo, filesList)
//        {
//          QTreeWidgetItem* item = new QTreeWidgetItem();
//          item->setText(0,fileInfo.fileName());

//          if(fileInfo.isFile())
//          {
//            item->setText(1,QString::number(fileInfo.size()));
//            item->setIcon(0,*(new QIcon("file.jpg")));
//          }

//          if(fileInfo.isDir())
//          {
//            item->setIcon(0,*(new QIcon("folder.jpg")));
//            addChildren(item,fileInfo.filePath());
//          }

//          item->setText(2,fileInfo.filePath());
//          tree->addTopLevelItem(item);
//        }

//        window->setCentralWidget(centralWidget);
//        window->show();
//        return app.exec();
}
