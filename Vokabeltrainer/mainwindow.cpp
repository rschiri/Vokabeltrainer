#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addvocable.h"
#include "woerterbuch.h"
#include "databasequery.h"
#include "databaseconnection.h"
#include <QApplication>
#include <QToolBar>
#include <QInputDialog>
#include <QLabel>
#include <QCheckBox>
#include <time.h>
#include <QMessageBox>
#include <QDebug>



//Konstruktor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    //UI Objekt erzeugen mit einem neuen Objekt der Klasse MainWindow
    ui(new Ui::MainWindow)
{
    //Open Main Window
    ui->setupUi(this);
    QObject::connect(ui->quit_Button, &QPushButton::clicked,this, &MainWindow::close);

    Databasequery dbq;
    DatabaseConnection dbc;
    dbc.openConnection();
    //ui->comboBoxBox->addItems(dbq.getAllBoxes);
    ui->comboBoxCategory->addItems(dbq.getAllCategories(dbc));
    ui->comboBoxWordtype->addItems(dbq.getAllWordtypes(dbc));
    ui->comboBoxSourceLanguage->addItems(dbq.getAllLanguages(dbc));
    ui->comboBoxDestinationLanguage->addItems(dbq.getAllLanguagesExcept(dbc,"Deutsch"));
    dbc.closeConnection();

}

MainWindow::~MainWindow()
{
    //ui-Objekt löschen
    delete ui;
}

void MainWindow::close(){
    QApplication::quit();
}



void MainWindow::on_Neu_Button_clicked()
{
    AddVocable addVoc;
    addVoc.setModal(true);
    addVoc.exec();
}
/**
 * @brief MainWindow::on_actionKategorie_triggered Adds a category to the database if not existing
 */
void MainWindow::on_actionKategorie_triggered()
{
    DatabaseConnection dbc;
    Databasequery dbq;
    bool ok = false;
    QString text = QInputDialog::getText(this, "Neue Kategorie", "Name:", QLineEdit::Normal, "", &ok);

    dbc.openConnection();
    if(ok && !text.isEmpty() && !dbq.checkCategory(dbc,text)){
        dbq.addCategory(dbc,text);
        QMessageBox::information(this,"Information", "Kategorie wurde hinzugefügt.");
    }else{
        QMessageBox::information(this,"Information", "Kategorie existiert bereits.");
    }
    dbc.closeConnection();
}
/**
 * @brief MainWindow::on_actionSprache_triggered Adds a language to the database if not existing
 */
void MainWindow::on_actionSprache_triggered()
{
    DatabaseConnection dbc;
    Databasequery dbq;
    bool ok = false;
    QString text = QInputDialog::getText(this, "Neue Sprache", "Name:", QLineEdit::Normal, "", &ok);

    dbc.openConnection();
    if(ok && !text.isEmpty() && !dbq.checkLanguage(dbc,text)){
        dbq.addLanguage(dbc,text);
        QMessageBox::information(this,"Information", "Sprache wurde hinzugefügt.");
    }else{
        QMessageBox::information(this,"Information", "Sprache existiert bereits.");
    }
    dbc.closeConnection();
}
/**
 * @brief MainWindow::on_actionWortart_triggered Adds a wordtype to the database if not existing
 */
void MainWindow::on_actionWortart_triggered()
{
    DatabaseConnection dbc;
    Databasequery dbq;
    bool ok = false;
    QString text = QInputDialog::getText(this, "Neue Wortart", "Name:", QLineEdit::Normal, "", &ok);

    dbc.openConnection();
    if(ok && !text.isEmpty() && !dbq.checkWordtype(dbc,text)){
        dbq.addWordtype(dbc,text);
        QMessageBox::information(this,"Information", "Wortart wurde hinzugefügt.");
    }else{
        QMessageBox::information(this,"Information", "Wortart existiert bereits.");
    }
    dbc.closeConnection();
}

void MainWindow::on_actionOpen_triggered()
{
    Woerterbuch wobuch;
    wobuch.setModal(true);
    wobuch.exec();
}



void MainWindow::on_buttonTestVocabulary_clicked()
{

    ui->labelResult->setText("");
    bool checkable = true;

    /*
    ui->vocableOption1->setVisible(checkable);
    ui->vocableOption2->setVisible(checkable);
    ui->vocableOption3->setVisible(checkable);
    */

    ui->vocableOption1->setEnabled(checkable);
    ui->vocableOption2->setEnabled(checkable);
    ui->vocableOption3->setEnabled(checkable);

    ui->vocableOption1->setCheckable(checkable);
    ui->vocableOption2->setCheckable(checkable);
    ui->vocableOption3->setCheckable(checkable);

    if(ui->vocableOption1->isChecked()){
        ui->vocableOption1->setChecked(checkable);
    }

    if(ui->vocableOption2->isChecked()){
        ui->vocableOption2->setChecked(checkable);
    }

    if(ui->vocableOption3->isChecked()){
        ui->vocableOption3->setChecked(checkable);
    }


    // hol abzufragende Vokabel und speichere die Daten -> Details von comboboxen

    DatabaseConnection conn;

        if(conn.openConnection()){

                // Die Vokabel, die abgefragt werden soll, wird von der DB geholt -> DYNAMISCH machen & RANDOM
                QSqlQuery query;
                query.exec("select w1.word as wordid1, w2.word as wordid2, box, counter, categoryid, used, usedright from vocable as v left join word as w1 on v.wordid1=w1.wordid left join word as w2 on v.wordid2=w2.wordid where wordid1=1 and wordid2=6");
                QString word1;
                QString word2;

                /*
                ui->labelResult->setText("");
                bool checkable = true;

                ui->vocableOption1->setEnabled(checkable);
                ui->vocableOption2->setEnabled(checkable);
                ui->vocableOption3->setEnabled(checkable);

                ui->vocableOption1->setCheckable(checkable);
                ui->vocableOption2->setCheckable(checkable);
                ui->vocableOption3->setCheckable(checkable);
                */



                while(query.next()){
                    // für qstring word1 und word2 muss noch von der tabelle word der QString geholt werden
                    word1 = query.value(0).toString();
                    word2 = query.value(1).toString();

                    //box wird erhöht, wenn richtig beantwortet (und counter auf einen bestimmten Wert kommt?) -> muss noch hinzugefügt werden
                    //int box = query.value(2).toInt();

                    // counter wird in jedem fall erhöht -> muss noch hinzugefügt werden (bis zu einem bestimmten Wert erhöhen?)
                    //int counter = query.value(3).toInt();

                    // wird (wahrscheinlich) nicht geändert -> wahrscheinlich sinnvoll für herauspicken der Vokabeln
                    //int categoryid = query.value(4).toInt();

                    // used wird in jedem fall erhöht -> muss noch hinzugefügt werden (used kann endlos groß werden, oder?)
                    //int used = query.value(5).toInt();

                    // usedright wird erhöht, wenn richtig beantwortet -> muss noch hinzugefügt werden
                    //int usedright = query.value(6).toInt();

                }


                // hol 2 weitere Vokabeln von der gleichen Sprache -> combobox zielsprache

                // eine zufällige, falsche Vokabel wird geholt mit der gleichen Zielsprache -> noch ändern
                QSqlQuery queryFalsch1;
                //queryFalsch1.exec("select word.word from word where wordid = 8");
                //queryFalsch1.exec("select word.word from word where wordid != 1 || 2 and random()");
                queryFalsch1.exec("select word.word from word order by random()");
                QString wordFalsch1;

                while(queryFalsch1.next()){
                    wordFalsch1 = queryFalsch1.value(0).toString();
                }

                // eine weitere zufällige, falsche Vokabel wird geholt mit der gleichen Zielsprache -> noch ändern
                QSqlQuery queryFalsch2;
                //queryFalsch2.exec("select word.word from word where wordid = 7");
                queryFalsch2.exec("select word.word from word order by random()");
                QString wordFalsch2;

                while(queryFalsch2.next()){
                    wordFalsch2 = queryFalsch2.value(0).toString();
                }

                conn.closeConnection();

                // füll labelAbfrage mit richtigerVokabelAbfrageQuiz
                ui->labelQuiz->setText(word1);

                // initialisiere int richtigeOption mit einer random zahl zwischen 1 und 3
                srand((unsigned)time(NULL));
                rightOption = (rand() %3);


                qDebug() << rightOption;
                // option_? an der stelle int richtigeOption mit lösung zur Vokabel Abfrage füllen, den Rest mit den falschen Vokabeloptionen
                if(rightOption == 0){
                    ui->vocableOption1->setText(word2);
                    ui->vocableOption2->setText(wordFalsch1);
                    ui->vocableOption3->setText(wordFalsch2);
                }else if(rightOption == 1){
                    ui->vocableOption1->setText(wordFalsch1);
                    ui->vocableOption2->setText(word2);
                    ui->vocableOption3->setText(wordFalsch2);
                }else if(rightOption == 2){
                    ui->vocableOption1->setText(wordFalsch1);
                    ui->vocableOption2->setText(wordFalsch2);
                    ui->vocableOption3->setText(word2);
                }



                ui->labelQuiz->resize(this->width(), ui->labelQuiz->height());
                ui->labelResult->resize(this->width(), ui->labelResult->height());
                ui->vocableOption1->resize(this->width(), ui->vocableOption1->height());
                ui->vocableOption2->resize(this->width(), ui->vocableOption2->height());
                ui->vocableOption3->resize(this->width(), ui->vocableOption3->height());


            }

        else if (!conn.openConnection()){

                QMessageBox msgbox;
                msgbox.setText("Verbindung zur Datenbank konnte nicht hergestellt werden");
                msgbox.exec();

            }

            //conn.closeConnection();


}


int MainWindow::getChosenVocableOption(){
    return -1;
}


void MainWindow::on_vocableOption1_clicked()
{

    if(rightOption == 0){
        ui->labelResult->setText("Richtig! :)");
    }else if(rightOption != 0){
        ui->labelResult->setText("Falsch! :(");
    }

    qDebug() << rightOption << "sollte 0 sein";

    bool checked = true;
    ui->vocableOption1->setDisabled(checked);
    ui->vocableOption2->setDisabled(checked);
    ui->vocableOption3->setDisabled(checked);
    // vocable updaten
}


void MainWindow::on_vocableOption2_clicked()
{

    if(rightOption == 1){
        ui->labelResult->setText("Richtig! :)");
    }else if(rightOption != 1){
        ui->labelResult->setText("Falsch! :(");
    }

    qDebug() << rightOption << "sollte 1 sein";

    bool checked = true;
    ui->vocableOption1->setDisabled(checked);
    ui->vocableOption2->setDisabled(checked);
    ui->vocableOption3->setDisabled(checked);
    // vocable updaten
}


void MainWindow::on_vocableOption3_clicked()
{

    if(rightOption == 2){
        ui->labelResult->setText("Richtig! :)");
    }else if(rightOption != 2){
        ui->labelResult->setText("Falsch! :(");
    }

    qDebug() << rightOption << "sollte 2 sein";

    bool checked = true;
    ui->vocableOption1->setDisabled(checked);
    ui->vocableOption2->setDisabled(checked);
    ui->vocableOption3->setDisabled(checked);
    // vocable updaten
}



