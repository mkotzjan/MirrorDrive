#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QString>
#include <QFileDialog>

class FileHelper
{
public:
    FileHelper();

    // Open directory dialog
    QString openDirDialog(QWidget* widget, QString header);

    // Check if path is correct and return QLineEdit style
    QString checkDir(QString dir, int lineEditNumber);

    // Check if both directorys are correct and returns a bool
    bool isStartPossible();

private:
    int originDirStatus;
    int destinationDirStatus;
};

#endif // FILEHELPER_H
