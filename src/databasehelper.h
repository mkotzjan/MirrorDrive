#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <errorhelper.h>
#include <QtSql>
#include <QString>

class DatabaseHelper
{
public:
    // Opens a Database with given Name or creates a new one
    static ErrorHelper openDatabase(QString name);

    // Closes a Database
    static void closeDatabase();
};

#endif // DATABASEHELPER_H
