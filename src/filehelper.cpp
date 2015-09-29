#include "filehelper.h"

FileHelper::FileHelper()
{
    originDirStatus = 0;
    destinationDirStatus = 0;
}

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

bool FileHelper::isStartPossible()
{
    return originDirStatus == 1 && destinationDirStatus == 1;
}
