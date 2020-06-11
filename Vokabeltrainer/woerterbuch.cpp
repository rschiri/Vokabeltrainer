#include "woerterbuch.h"
#include "ui_woerterbuch.h"
#include "databaseconnection.h"

#include <QTableView>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QtSql/QSqlQueryModel>
#include <QDebug>


Woerterbuch::Woerterbuch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Woerterbuch)
{
    ui->setupUi(this);




}

Woerterbuch::~Woerterbuch()
{
    delete ui;
}





void Woerterbuch::on_Button_LoadDatabase_clicked()
{
    DatabaseConnection conn;
    QSqlQueryModel *model = new QSqlQueryModel();

    conn.openConnection();
    QSqlQuery* qry = new QSqlQuery(conn.db);

    qry->prepare("select * from category");

    qry->exec();

    model->setQuery(*qry);
    ui->tableView->setModel(model);

    //conn.connClose();
    qDebug() << (model->rowCount());





}
