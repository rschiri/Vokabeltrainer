#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql/QSqlDatabase>

class DatabaseConnection
{
public:
    DatabaseConnection();

    void connClose();

    bool connOpen();

    QSqlDatabase mydb;


};

#endif // DATABASECONNECTION_H
