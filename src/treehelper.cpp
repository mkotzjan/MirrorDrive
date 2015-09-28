#include "treehelper.h"
#include <QDir>

TreeHelper::TreeHelper()
{
}

void TreeHelper::addChildren(QTreeWidgetItem *item, QString filePath)
{
    QDir* rootDir = new QDir(filePath);
        QFileInfoList filesList = rootDir->entryInfoList();

        foreach(QFileInfo fileInfo, filesList)
        {
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
            }
            item->addChild(child);
        }
}
