#include "databasehelper.h"
#include "QDebug"
#include "QFile"

DatabaseHelper::DatabaseHelper()
{
    db = QSqlDatabase();
    db.addDatabase("QSQLITE");
    QString dbName = "test.db";
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        if( QFile::exists(dbName))
            {
                qDebug()<<"Data base exist....";
            }
            else {
                qDebug()<<"Data base not exist creating new....";
                db.setDatabaseName(dbName);
                db.open(); // <<< Add this!

                if(!db.isOpen()) {
                    qDebug() << "ERROR: could not open database";
                }
                qDebug() << "DB opened";
            }
}
