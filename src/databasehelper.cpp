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

    QSqlQuery query(db);
    query.exec("PRAGMA foreign_keys = ON;");

    // TODO: Create Tables
    if(!exist)
    {
        query.exec("create table folder "
                  "(id integer primary key, "
                  "path text);");
        query.exec("create table file "
                  "(id integer primary key, "
                  "folder int,"
                  "path text,"
                  "FOREIGN KEY(folder) REFERENCES folder(id));");
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
