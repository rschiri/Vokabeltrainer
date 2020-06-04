#include "databaseconnection.h"
#include <QtSql/QSqlDatabase>
#include <QMessageBox>

DatabaseConnection::DatabaseConnection()
{

}


bool DatabaseConnection::connOpen(){
    mydb = QSqlDatabase::addDatabase("QString:: .......");
    mydb.setDatabaseName("QString::....");
    

    if(!mydb.open()){
        QMessageBox::critical(this,"Warnung", "Fehler bei Verbindung zur Datenbank!");
    }else{
        QMessageBox::information(this, "Verbindung", "Verbunden!");
    }
}
