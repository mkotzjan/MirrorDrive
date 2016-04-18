#include "databasehelper.h"
#include "QDebug"
#include "QFile"

// ____________________________________________________________________________
ErrorHelper DatabaseHelper::openDatabase(QString name)
{
    ErrorHelper result;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "Database");
    bool exist = QFile::exists(name);

    db.setDatabaseName(name);
    db.open();

    if(!db.isOpen())
    {
        result.setState(2);
        result.setMessage("Could not open database on path '" + name + "'.");
        return result;
    }

    // TODO: Create Tables
    if(!exist)
    {
        qDebug() << "Hat nicht existiert";
        QSqlQuery query(db);
        query.exec("create table test(name text, alter int)");
    }
    return result;
}

// ____________________________________________________________________________
void DatabaseHelper::closeDatabase()
{
    {
        QSqlDatabase db = QSqlDatabase::database("Database");
        db.close();
    }
    QSqlDatabase::removeDatabase("Database");
}
