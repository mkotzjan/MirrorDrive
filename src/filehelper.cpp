#include "filehelper.h"
#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>

// ____________________________________________________________________________
FileHelper::FileHelper()
{
    originDirStatus = 0;
    destinationDirStatus = 0;
    originRoot = "";
    destinationRoot = "";
    originPreference = "/.source.mirror";
    destinationPreference = "/.destination.mirror";
    database = "/.mirror.db";
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
ErrorHelper FileHelper::checkPreferences()
{
    bool sourceExists = QFile::exists(originRoot + originPreference);
    bool destinationExists = QFile::exists(destinationRoot + destinationPreference);
    ErrorHelper result;
    result.setState(1);

    if (sourceExists && destinationExists)
    {
        // Both file exists
        result = comparePreferences();

        // If there was an error pass it through. If everything was ok pass it as well
        if (result.getState() != 1)
        {
            return result;
        }
        // Return state 1 with the question
        result.setMessage("The two folders where never used together to mirror them. Continue?");
        return result;
    } else if (sourceExists)
    {
        // Only source exists
        result.setMessage("Destination folder was never used before. Continue?");
        return result;
    } else if (destinationExists)
    {
        // Only destination exists
        result.setState(2);
        result.setMessage("Destination folder was used before and therefore cannot be used again.");
        return result;
    } else
    {
        result.setMessage("Neither the source or destination folder was used before. Continue?");
        return result;
    }
}

// ____________________________________________________________________________
ErrorHelper FileHelper::comparePreferences()
{
    QVector<QString> originIDs;
    QVector<QString> destinationIDs;
    QFile originFile(originRoot + originPreference);
    QFile destinationFile(destinationRoot + destinationPreference);
    ErrorHelper result;

    // Read origin
    if(!originFile.open(QIODevice::ReadOnly))
    {
        result.setState(2);
        result.setMessage(originFile.errorString());
        return result;
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
        result.setState(2);
        result.setMessage(originFile.errorString());
        return result;
    }

    QTextStream in2(&destinationFile);

    while(!in2.atEnd())
    {
        destinationIDs.append(in2.readLine());
    }

    destinationFile.close();

    // Check if one of both is empty
    if(originIDs.empty() || destinationIDs.empty())
    {
        result.setState(1);
        return result;
    }
    // Compare Id's
    if(originIDs.size() > destinationIDs.size())
    {
        for(int i = 0; i < originIDs.size(); ++i)
        {
            if(destinationIDs.contains(originIDs.value(i)))
            {
                result.setState(0);
                return result;
            }
        }
    } else
    {
        for(int i = 0; i < destinationIDs.size(); ++i)
        {
            if(originIDs.contains(destinationIDs.value(i)))
            {
                result.setState(0);
                return result;
            }
        }
    }
    result.setState(1);
    return result;
}

// ____________________________________________________________________________
ErrorHelper FileHelper::setTimestamp()
{
    ErrorHelper result;
    // Get timestamp, open files and append as id
    QDateTime current = QDateTime::currentDateTime();
    int timestamp = current.toTime_t();
    qDebug() << timestamp;

    qDebug() << "Start Source";
    // Write to origin
    QFile origin(originRoot + originPreference);
    qDebug() << "file path created";
    if(!origin.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        result.setState(2);
        result.setMessage(origin.errorString());
        return result;
    }
    QTextStream out(&origin);
    out << timestamp << endl;
    origin.close();

    qDebug() << "Start destination";
    // Write to destination
    QFile destination(destinationRoot + destinationPreference);
    if(!destination.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        result.setState(2);
        result.setMessage(origin.errorString());
        return result;
    }
    QTextStream out2(&destination);
    out2 << timestamp << endl;
    destination.close();

    result.setState(0);
    return result;
}

// ____________________________________________________________________________
void FileHelper::startMirror(QProgressBar* progressBar, QStatusBar* statusBar)
{
    qDebug()<<"Run.";
    QDir* originDir = new QDir(originRoot);
    // QDir* destinationDir = new QDir(destinationRoot);

    int numberOfFiles = countFiles(originDir);
    progressBar->setMaximum(numberOfFiles);
    qDebug() << "Filecount: " << numberOfFiles;
    // copyFiles(originDir, progressBar, statusBar);
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
            qDebug() << "Name: " << getRelativeFile(fileInfo.filePath());
            qDebug() << "Dir: " << getRelativeDir(fileInfo.filePath());
            qDebug() << fileInfo.filePath();
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

// ____________________________________________________________________________
QString FileHelper::getRelativeFile(QString path)
{
    return path.remove(originRoot);
}

// ____________________________________________________________________________
QString FileHelper::getRelativeDir(QString path)
{
    path = getRelativeFile(path);
    path.truncate(path.lastIndexOf("/"));
    return path;
}
