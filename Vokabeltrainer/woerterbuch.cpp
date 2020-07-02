#include "woerterbuch.h"
#include "ui_woerterbuch.h"
#include "databaseconnection.h"

#include <QTableView>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QtSql/QSqlQueryModel>
#include <QDebug>
#include <iostream>
#include <QSqlRecord>



Woerterbuch::Woerterbuch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Woerterbuch)
{
    ui->setupUi(this);

    conn.openConnection();

    if (!conn.openConnection()){
        QMessageBox msgbox;
        msgbox.setText("Verbindung zur Datenbank konnte nicht hergestellt werden");
        msgbox.exec();

    }

    ui->radioButton_DE->setChecked(true);
    showDEVocables();

    ui->radioButton_Deutsch->setChecked(true);

    connect(ui->pushButton_Suche, &QPushButton::clicked, this, &Woerterbuch::findVocable);
    connect(ui->radioButton_DE, &QRadioButton::clicked, this, &Woerterbuch::showDEVocables);
    connect(ui->radioButton_DS, &QRadioButton::clicked, this, &Woerterbuch::showDSVocables);
    connect(ui->pushbutton_Nomen, &QPushButton::clicked, this, &Woerterbuch::showNomen);
    connect(ui->pushbutton_Verben, &QPushButton::clicked, this, &Woerterbuch::showVerben);
    connect(ui->pushbutton_Adjektive, &QPushButton::clicked, this, &Woerterbuch::showAdjektive);
    connect(ui->pushButton_Artikel, &QPushButton::clicked, this, &Woerterbuch::showArtikel);
    connect(ui->pushButton_Konjunktionen, &QPushButton::clicked, this, &Woerterbuch::showKonjunktion);
    connect(ui->pushButton_unregelVerben, &QPushButton::clicked, this, &Woerterbuch::showUnregelVerben);
    connect(ui->pushButton_Adverben, &QPushButton::clicked, this, &Woerterbuch::showAdverben);
    connect(ui->pushButton_Praeposition, &QPushButton::clicked, this, &Woerterbuch::showPraepositionen);
    connect(ui->pushButton_Pronomen, &QPushButton::clicked, this, &Woerterbuch::showPronomen);
    connect(ui->pushButton_Zahlenwoerter, &QPushButton::clicked, this, &Woerterbuch::showZahlenwoerter);
    connect(ui->pushButton_NomenFEM, &QPushButton::clicked, this, &Woerterbuch::showSubFem);
    connect(ui->pushButton_NomenMAS, &QPushButton::clicked, this, &Woerterbuch::showSubMas);
    connect(ui->pushButton_NomenNEU, &QPushButton::clicked, this, &Woerterbuch::showSubNeu);

}


Woerterbuch::~Woerterbuch()
{
    conn.closeConnection();
    delete ui;
}


/*
Methode prüft, ob eine Vokabel in das Suchfeld eingegeben wurde und ruft eine Methode auf, die die gesuchte Vokabel erscheinen lässt.
Gibt Meldungen aus, wenn entweder nichts in das Suchfeld eingegeben wurde oder wenn die eingegebene Vokabel nicht im Wörterbuch enthalten ist.
*/

/**
 * @brief method checks whether a word has been entered in the search field and calls a method that makes the searched word appear.
Returns messages if either nothing has been entered in the search field or if the entered word is not in the dictionary
 */
void Woerterbuch::findVocable(){

    QString vocable = ui->lineEdit_Suche->text();

    if(vocable.isEmpty()){
        QMessageBox::information(this, tr("Leeres Feld"),
                                 tr("Bitte gebe eine Vokabel ein!"));
        return;

    }else{

        QSqlQuery qry("select word from word where languageid = 1", conn.db);


        while (qry.next()) {

           QSqlRecord record = qry.record();
           QString mystring;
           for(int i=0; i < record.count(); i++){
               mystring = record.value(i).toString();
           }

           vocableList.append(mystring);

        }

        for (int i = 0; i<vocableList.size(); ++i){
            if (vocableList[i] == vocable){
                showSearchVocable(vocable);
            }
        }

        if(!inVocableList(vocableList, vocable)){
            QMessageBox::information(this, tr("Leeres Feld"),
                                     tr("Vokabel existiert nicht!"));
        }
    }
}


/**
 * @brief method checks if the passed QString is contained in the passed QVector<String>
 * @param QVector<QString> vocableList
 * @param QString vocable
 * @return true if the QString is contained, false if not
 *
 */
bool Woerterbuch::inVocableList(QVector<QString> vocableList, QString vocable){
    for (int i = 0; i<vocableList.size(); ++i){
        if (vocableList[i] == vocable){
            return true;
        }
    }
    return false;
}



/**
 * @brief shows only the vocabulary the user searched for
 * @param QString string
 */
void Woerterbuch::showSearchVocable(QString string){

    QString i = "2";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND w1.word = '"+ string+"' ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();


}

/**
 * @brief shows just the german-english vocabulary
 */
void Woerterbuch::showDEVocables(){

            QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = 2", conn.db);

            model->setQuery(query);
            ui->tableView->setModel(model);
            ui->tableView->resizeColumnsToContents();
}

/**
 * @brief shows just the german-spanish vocabulary
 */
void Woerterbuch::showDSVocables(){

            QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = 3", conn.db);

            model->setQuery(query);
            ui->tableView->setModel(model);
            ui->tableView->resizeColumnsToContents();
}

/**
 * @brief shows all nouns. either all German nouns or all nouns of the foreign language
 */
void Woerterbuch::showNomen(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND ("+word+".wordtypeid = 12 OR "+word+".wordtypeid = 13 OR "+word+".wordtypeid = 14)", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}

void Woerterbuch::showVerben(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }


    QSqlQueryModel *model = new QSqlQueryModel();


    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND "+word+".wordtypeid = 10 ", conn.db);
    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}


void Woerterbuch::showAdjektive(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND "+word+".wordtypeid = 2 ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();


}

void Woerterbuch::showArtikel(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND "+word+".wordtypeid = 4 ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}


void Woerterbuch::showKonjunktion(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND "+word+".wordtypeid = 6 ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}

void Woerterbuch::showUnregelVerben(){
    QString i = "2";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = 2 AND w2.wordtypeid = 11 ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}

void Woerterbuch::showAdverben(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND "+word+".wordtypeid = 3 ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}
void Woerterbuch::showPraepositionen(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND "+word+".wordtypeid = 8 ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}
void Woerterbuch::showPronomen(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND "+word+".wordtypeid = 9 ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}
void Woerterbuch::showSubMas(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND "+word+".wordtypeid = 14 ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}
void Woerterbuch::showSubFem(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND "+word+".wordtypeid = 13 ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}
void Woerterbuch::showSubNeu(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND "+word+".wordtypeid = 15 ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}

void Woerterbuch::showZahlenwoerter(){
    QString i = "2";
    QString word = "w1";

    if(ui->radioButton_DE->isChecked()){
        i = "2";
    }
    if(ui->radioButton_DS->isChecked()){
        i = "3";
    }
    if(ui->radioButton_Fremdsprache->isChecked()){
        word = "w2";
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1 = w1.wordid "
                         "left join word as w2 on v.wordid2 = w2.wordid where w1.languageid =1 AND w2.languageid = "+i+" AND "+word+".wordtypeid = 16 ", conn.db);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}
