#include "treehelper.h"
#include <QDir>
#include <QCryptographicHash>

TreeHelper::TreeHelper()
{
}

void TreeHelper::addChildren(QTreeWidgetItem *item, QString filePath)
{
    QDir* rootDir = new QDir(filePath);
        QFileInfoList filesList = rootDir->entryInfoList();

        foreach(QFileInfo fileInfo, filesList)
        {
            if(fileInfo.isDir() && (fileInfo.fileName() == "." || fileInfo.fileName() == ".."))
            {
                continue;
            }
            QTreeWidgetItem* child = new QTreeWidgetItem();
            child->setText(0,fileInfo.fileName());


            if(fileInfo.isFile())
            {
                child->setText(1,QString::number(fileInfo.size()));
                child->setIcon(0,*(new QIcon(":/icons/file.png")));
            }

            if(fileInfo.isDir())
            {
                child->setIcon(0,*(new QIcon(":/icons/folder.png")));
                addChildren(child, fileInfo.filePath());
            }
            item->addChild(child);
        }
}

int TreeHelper::compareFiles(QString originPath)
{
    QString origin = QString(originPath);
    QString destination = originPath.replace(originRoot, destinationRoot);

    try {
        if(getHash(origin) == getHash(destination))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    } catch (...) {
        return -1;
    }
}

QByteArray TreeHelper::getHash(QString path)
{
    QCryptographicHash hash1( QCryptographicHash::Sha1 );
    QFile file( path );

    if ( file.open( QIODevice::ReadOnly ) ) {
        hash1.addData( file.readAll() );
    } else {
        // Handle "cannot open file" error
        throw "File could not be opened";
    }

    // Retrieve the SHA1 signature of the file
    return hash1.result();
}
