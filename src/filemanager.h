#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QFileDialog>

class FileManager
{
public:
    // Constructor
    FileManager();

    QString chooseDirectory();
};

#endif // FILEMANAGER_H
