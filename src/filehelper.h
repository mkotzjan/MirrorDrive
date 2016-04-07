#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QString>
#include <QFileDialog>
#include <QProgressBar>
#include <QStatusBar>

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

    // Set dir
    void setDir(QString origin, QString destination);

    // Check if both directorys contains the preferences files and a database
    // exists. Otherwise show information dialog and create files. Return if
    // mirroring is possible
    bool checkPreferences(QWidget* widget);

    // Check if the preferences match
    bool comparePreferences();

    // Start mirror
    void startMirror(QProgressBar* progressBar, QStatusBar* statusBar);

    // Count the files inside a folder
    int countFiles(QDir* dir);

    // Copy the files
    void copyFiles(QDir* dir, QProgressBar* progressBar, QStatusBar* statusBar);

    // Get Hash of file
    QByteArray getHash(QString path);

    // Check if file exists in destination folder and compare
    int compareFiles(QString path);

private:
    int originDirStatus;
    int destinationDirStatus;

    QString originRoot;
    QString destinationRoot;

    QString originPreference;
    QString destinationPreference;
};

#endif // FILEHELPER_H
