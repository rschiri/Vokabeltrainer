#include "woerterbuch.h"
#include "ui_woerterbuch.h"
#include "databaseconnection.h"

#include <QTableView>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QtSql/QSqlQueryModel>
#include <QDebug>


void Woerterbuch::showVocables(){
    DatabaseConnection conn;

    if(conn.openConnection()){

            QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1=w1.wordid left join word as w2 on v.wordid2=w2.wordid", conn.db);

            model->setQuery(query);
            ui->tableView->setModel(model);
            ui->tableView->resizeColumnsToContents();

        } else if (!conn.openConnection()){

            QMessageBox msgbox;
            msgbox.setText("Verbindung zur Datenbank konnte nicht hergestellt werden");
            msgbox.exec();

        }

        conn.closeConnection();
}


Woerterbuch::Woerterbuch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Woerterbuch)
{
    ui->setupUi(this);
    showVocables();

}


Woerterbuch::~Woerterbuch()
{
    delete ui;
}





void Woerterbuch::on_Button_LoadDatabase_clicked()
{
    DatabaseConnection conn;

        conn.openConnection();

        if(conn.openConnection()){

            QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery query("select * from word");

            model->setQuery(query);
            ui->tableView->setModel(model);
            ui->tableView->resizeColumnsToContents();
            
        }else{

            QMessageBox msgbox;
            msgbox.setText("Verbindung zur Datenbank konnte nicht hergestellt werden");
            msgbox.exec();
        }

        conn.closeConnection();
}
