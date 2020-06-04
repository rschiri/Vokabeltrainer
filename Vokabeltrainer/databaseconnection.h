#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class DatabaseConnection
{
public:
    DatabaseConnection();
    QSqlDatabase db;
    void openConnection();
    void createTableFromData();
    void queryDataAndPrintData();
    void queryFalseUsedDataAndPrintData();
    void queryInsertDataAndPrintData();
    void closeConnection();


};

#endif // DATABASECONNECTION_H
