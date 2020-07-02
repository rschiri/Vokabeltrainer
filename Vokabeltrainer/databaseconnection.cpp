#include "databaseconnection.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QSqlError>

DatabaseConnection::DatabaseConnection()
{

}


bool DatabaseConnection::openConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("192.168.180.1");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("Postgres123.");
    bool success = db.open();
    qDebug()<<"Database connection established: "<<success;
    return success;


}

void DatabaseConnection::closeConnection(){
    {
            QSqlDatabase db = QSqlDatabase::database();
            db.close();
    }
    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );

}

