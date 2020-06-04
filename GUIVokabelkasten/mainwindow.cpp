#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addvoc.h"
#include "woerterbuch.h"
#include <QApplication>
#include <QToolBar>
#include <QInputDialog>
#include <QLabel>
#include <QCheckBox>



//Konstruktor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    //UI Objekt erzeugen mit einem neuen Objekt der Klasse MainWindow
    ui(new Ui::MainWindow)
{
    //Open Main Window
    ui->setupUi(this);
    QObject::connect(ui->quit_Button, &QPushButton::clicked,this, &MainWindow::close);

    ui->ButtonAlle->setChecked(true);
    ui->ButtonEngDeu->setChecked(true);
    on_ButtonAlle_clicked();
    on_ButtonAuswahl_clicked();


}

MainWindow::~MainWindow()
{
    //ui-Objekt löschen
    delete ui;
}

void MainWindow::close(){
    QApplication::quit();
}


void MainWindow::on_ButtonAlle_clicked()
{
    if (ui->ButtonAlle->isChecked()){
        ui->scrollArea_2->hide();
    }

}

void MainWindow::on_ButtonAuswahl_clicked()
{
    if(ui->ButtonAuswahl->isChecked()){
        ui->scrollArea_2->show();
    }
}

void MainWindow::on_Neu_Button_clicked()
{
    AddVoc addVoc;
    addVoc.setModal(true);
    addVoc.exec();
}

void MainWindow::on_actionKategorie_triggered()
{
    QCheckBox *check = new QCheckBox;
    bool ok = false;
    QString text = QInputDialog::getText(this, "Neue Kategorie", "Name:", QLineEdit::Normal, "", &ok);

    if(ok && !text.isEmpty()){

        check->setText(text);
        ui->verticalLayout_2->addWidget(check);



    }
}



void MainWindow::on_actionOpen_triggered()
{
    Woerterbuch wobuch;
    wobuch.setModal(true);
    wobuch.exec();
}
