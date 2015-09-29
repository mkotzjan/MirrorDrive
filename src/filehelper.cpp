#include "filehelper.h"

// ____________________________________________________________________________
FileHelper::FileHelper()
{
    originDirStatus = 0;
    destinationDirStatus = 0;
    originRoot = "";
    destinationRoot = "";
}

// ____________________________________________________________________________
QString FileHelper::openDirDialog(QWidget* widget, QString header)
{
    QString dir = QFileDialog::getExistingDirectory(
                widget,
                header,
                "/home",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );
    return dir;
}

// ____________________________________________________________________________
QString FileHelper::checkDir(QString dir, int lineEditNumber)
{
    int status;
    QString result;
    if(dir.isEmpty())
    {
        status = 0;
        result = "QLineEdit { border-style: outset; border-width: 2px; border-color: orange;}";
    }
    else if((new QDir(dir))->exists())
    {
        status = 1;
        result = "QLineEdit { border-style: outset; border-width: 2px; border-color: green;}";
    }
    else
    {
        status = -1;
        result = "QLineEdit { border-style: outset; border-width: 2px; border-color: red;}";
    }

    if(lineEditNumber == 1)
    {
        originDirStatus = status;
    }
    else
    {
        destinationDirStatus = status;
    }

    return result;
}

// ____________________________________________________________________________
bool FileHelper::isStartPossible()
{
    return originDirStatus == 1 && destinationDirStatus == 1;
}

// ____________________________________________________________________________
void FileHelper::setDir(QString origin, QString destination)
{
    originRoot = origin;
    destinationRoot = destination;
}

// ____________________________________________________________________________
void FileHelper::startMirror(QProgressBar* progressBar, QStatusBar* statusBar)
{
    QDir* originDir = new QDir(originRoot);
    // QDir* destinationDir = new QDir(destinationRoot);

    QFileInfoList originFilesList = originDir->entryInfoList();
    int numberOfFiles = countFiles(originDir);
    progressBar->setMaximum(numberOfFiles);

    // copyFiles();
}

// ____________________________________________________________________________
int FileHelper::countFiles(QDir *dir)
{
    int result = 0;
    QFileInfoList fileList = dir->entryInfoList();
    foreach(QFileInfo fileInfo, fileList)
    {
        if(fileInfo.isDir() && (fileInfo.fileName() == "." || fileInfo.fileName() == ".."))
        {
            continue;
        }
        else if(fileInfo.isFile())
        {
            ++result;
        }
        else if(fileInfo.isDir())
        {
            result += countFiles(new QDir(fileInfo.filePath()));
        }
    }
    return result;
}
