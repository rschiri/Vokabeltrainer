#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class DatabaseConnection
{
public:
    DatabaseConnection();
    QSqlDatabase db;
    bool openConnection();
    void closeConnection();


};

#endif // DATABASECONNECTION_H
