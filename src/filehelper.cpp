#include "filehelper.h"
#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>

// ____________________________________________________________________________
FileHelper::FileHelper()
{
    originDirStatus = 0;
    destinationDirStatus = 0;
    originRoot = "";
    destinationRoot = "";
    originPreference = "/.source.mirror";
    destinationPreference = "/.destination.mirror";
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
bool FileHelper::checkPreferences(QWidget* widget)
{
    bool sourceExists = QFile::exists(originRoot + originPreference);
    bool destinationExists = QFile::exists(destinationRoot + destinationPreference);
    QDateTime current;
    int timestamp;

    if (sourceExists && destinationExists)
    {
        // Both files exists
        qDebug() << "Both.";
        if(!comparePreferences())
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(widget, "MirrorDrive", "The two folders where never used together to mirror them. Continue?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply != QMessageBox::Yes) {
                return false;
            }
            // Get timestamp, open files and append as id
            current = QDateTime::currentDateTime();
            timestamp = current.toTime_t();

            // Write to origin
            QFile origin(originRoot + originPreference);
            if(!origin.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                QMessageBox::information(0, "error", origin.errorString());
            QTextStream out(&origin);
            out << timestamp << endl;
            origin.close();

            // Write to destination
            QFile destination(destinationRoot + destinationPreference);
            if(!destination.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                QMessageBox::information(0, "error", destination.errorString());
            QTextStream out2(&destination);
            out2 << timestamp << endl;
            destination.close();
        }
        return true;

    } else if (sourceExists)
    {
        // Only source exists
        qDebug() << "Source.";
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(widget, "MirrorDrive", "Destination folder was never used before. Continue?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

        }
    } else if (destinationExists)
    {
        // Only destination exists
        qDebug() << "Destination.";
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(widget, "MirrorDrive", "Source folder was never used before. Continue?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

        }
    } else
    {
        // None exists
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(widget, "MirrorDrive", "Neither the source or destination folder was used before. Continue?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

        }
        qDebug() << "None.";
    }
    return false;
}

// ____________________________________________________________________________
bool FileHelper::comparePreferences()
{
    QVector<QString> originIDs;
    QVector<QString> destinationIDs;
    QFile originFile(originRoot + originPreference);
    QFile destinationFile(destinationRoot + destinationPreference);

    // Read origin
    if(!originFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", originFile.errorString());
    }

    QTextStream in(&originFile);

    while(!in.atEnd())
    {
        originIDs.append(in.readLine());
    }

    originFile.close();
    // Read destination
    if(!destinationFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", destinationFile.errorString());
    }

    QTextStream in2(&destinationFile);

    while(!in2.atEnd())
    {
        destinationIDs.append(in2.readLine());
    }

    destinationFile.close();

    // Check if one of both is empty
    if(originIDs.empty() || destinationIDs.empty())
        return false;
    // Compare Id's
    if(originIDs.size() > destinationIDs.size())
    {
        for(int i = 0; i < originIDs.size(); ++i)
        {
            if(destinationIDs.contains(originIDs.value(i)))
                return true;
        }
    } else
    {
        for(int i = 0; i < destinationIDs.size(); ++i)
        {
            if(originIDs.contains(destinationIDs.value(i)))
                return true;
        }
    }
    return false;
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
                // File doesn't exist. Copy.
                QFile::copy(fileInfo.filePath(), (new QString(fileInfo.filePath()))->replace(originRoot, destinationRoot));
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
            QDir dir;
            dir.mkpath((new QString(fileInfo.filePath()))->replace(originRoot, destinationRoot));

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
