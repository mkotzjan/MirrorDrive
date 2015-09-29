#include "filehelper.h"
#include <QCryptographicHash>
#include <QDebug>

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

    copyFiles(originDir, progressBar, statusBar);
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

// ____________________________________________________________________________
void FileHelper::copyFiles(QDir* dir, QProgressBar* progressBar, QStatusBar* statusBar)
{
    QFileInfoList fileList = dir->entryInfoList();
    foreach(QFileInfo fileInfo, fileList)
    {
        if(fileInfo.isDir() && (fileInfo.fileName() == "." || fileInfo.fileName() == ".."))
        {
            continue;
        }
        else if(fileInfo.isFile())
        {
            // Display filepath and name in statusbar
            statusBar->showMessage(fileInfo.absoluteFilePath());

            // Check file and copy if needed
            int result = compareFiles(fileInfo.filePath());
            if(result == -1)
            {
                qDebug() << fileInfo.filePath() + " -> " + (new QString(fileInfo.filePath()))->replace(originRoot, destinationRoot) << endl;
                // File doesn't exist. Copy.
                bool test = QFile::copy(fileInfo.filePath(), (new QString(fileInfo.filePath()))->replace(originRoot, destinationRoot));
                qDebug() << test << endl;
            }
            else if (result == 0)
            {
                // File exist but differs. Override.
                QFile::remove((new QString(fileInfo.filePath()))->replace(originRoot, destinationRoot));
                QFile::copy(fileInfo.filePath(), (new QString(fileInfo.filePath()))->replace(originRoot, destinationRoot));
            }

            // Progress bar
            int value = progressBar->value();
            progressBar->setValue(++value);
        }
        else if(fileInfo.isDir())
        {
            qDebug() << "Dir:" << endl;
            qDebug() << fileInfo.filePath() + " -> " + (new QString(fileInfo.filePath()))->replace(originRoot, destinationRoot) << endl;
            QDir dir;
            bool test = dir.mkpath((new QString(fileInfo.filePath()))->replace(originRoot, destinationRoot));
            qDebug() << test << endl;

            copyFiles(new QDir(fileInfo.filePath()), progressBar, statusBar);
        }
    }
}

// ____________________________________________________________________________
QByteArray FileHelper::getHash(QString path)
{
    QCryptographicHash hash1(QCryptographicHash::Sha1);
    QFile file(path);

    if (file.open( QIODevice::ReadOnly)) {
        hash1.addData(file.readAll());
    } else {
        // Handle "cannot open file" error
        throw "File could not be opened";
    }

    // Retrieve the SHA1 signature of the file
    return hash1.result();
}

// ____________________________________________________________________________
int FileHelper::compareFiles(QString path)
{
    QString origin = QString(path);
    QString destination = path.replace(originRoot, destinationRoot);

    if(QFile::exists(destination))
    {
        if(getHash(origin) == getHash(destination))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }
}
