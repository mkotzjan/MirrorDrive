#include <QTreeWidgetItem>

#ifndef TREEHELPER_H
#define TREEHELPER_H

class TreeHelper
{
public:
    TreeHelper();
    void addChildren(QTreeWidgetItem *item, QString filePath);

    // Checks if file exists and compare. Returns 0 if equal, 1 if differs and
    // -1 if files don't exist.
    int compareFiles(QString originPath);

    QString originRoot;
    QString destinationRoot;

private:
    QByteArray getHash(QString path);
};

#endif // TREEHELPER_H
