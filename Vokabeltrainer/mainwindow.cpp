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


    QStringList qStringList;
    for(int i = 1; i<=5; i++) {
        QString boxnumber = QString::number(i);
        qStringList.push_back(boxnumber);
    }

    Databasequery dbq;
    DatabaseConnection dbc;
    dbc.openConnection();
    ui->comboBoxBox->addItems(qStringList);
    ui->comboBoxCategory->addItems(dbq.getAllCategories(dbc));
    ui->comboBoxWordtype->addItems(dbq.getAllWordtypes(dbc));
    ui->comboBoxSourceLanguage->addItems(dbq.getAllLanguages(dbc));
    sourceLanguage = ui->comboBoxSourceLanguage->currentText();
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
    word1="";
    word2="";
    box=0;
    counter=-1;
    categoryid=0;
    used=-1;
    usedright=-1;
    wordVocableId1=0;
    wordVocableId2=0;

    ui->labelQuiz->setText("");
    ui->labelResult->setText("");
    ui->editAnswer->clear();


    DatabaseConnection conn;

    if(conn.openConnection()){

        QString comboBox = ui->comboBoxBox->currentText();
        QString comboCategory = ui->comboBoxCategory->currentText();
        QString comboWordtype = ui->comboBoxWordtype->currentText();
        QString comboSourceLanguage = ui->comboBoxSourceLanguage->currentText();
        QString comboDestinationLanguage = ui->comboBoxDestinationLanguage->currentText();

        // categoryid für query raussuchen
        QSqlQuery queryCategory;
        queryCategory.exec("select categoryid from category where category = '" + comboCategory + "'");
        queryCategory.next();
        QString categoryid = queryCategory.value(0).toString();

        // wordtypeid für query raussuchen
        QSqlQuery queryWordtpye;
        queryWordtpye.exec("select wordtypeid from wordtype where wordtype = '" + comboWordtype + "'");
        queryWordtpye.next();
        QString wordtypeid = queryWordtpye.value(0).toString();

        // languagesid sourceLanguage für query raussuchen
        QSqlQuery querySourceLanguageId;
        querySourceLanguageId.exec("select languagesid from languages where language = '" + comboSourceLanguage + "'");
        querySourceLanguageId.next();
        QString sourceLanguageId = querySourceLanguageId.value(0).toString();

        // languagesid destinationLanguage für query raussuchen
        QSqlQuery queryDestinationLanguageId;
        queryDestinationLanguageId.exec("select languagesid from languages where language = '" + comboDestinationLanguage + "'");
        queryDestinationLanguageId.next();
        QString destinationLanguageId = queryDestinationLanguageId.value(0).toString();



        QSqlQuery query;
        if(comboSourceLanguage == "Deutsch"){
            query.exec("select w1.word as wordid1, w2.word as wordid2, box, counter, categoryid, used, usedright, wordid1, wordid2 from vocable as v left join word as w1 on v.wordid1=w1.wordid left join word as w2 on v.wordid2=w2.wordid where box = '" + comboBox + "' and categoryid = '" + categoryid + "' and w1.wordtypeid = '" + wordtypeid + "' and w1.languageid = '" + sourceLanguageId + "' and w2.languageid = '" + destinationLanguageId + "' order by random()");
        }else{
            query.exec("select w1.word as wordid1, w2.word as wordid2, box, counter, categoryid, used, usedright, wordid1, wordid2 from vocable as v left join word as w1 on v.wordid1=w1.wordid left join word as w2 on v.wordid2=w2.wordid where box = '" + comboBox + "' and categoryid = '" + categoryid + "' and w1.wordtypeid = '" + wordtypeid + "' and w2.languageid = '" + sourceLanguageId + "' and w1.languageid = '" + destinationLanguageId + "' order by random()");

        }

        while(query.next()){
            // für qstring word1 und word2 muss noch von der tabelle word der QString geholt werden
            word1 = query.value(0).toString();
            word2 = query.value(1).toString();

            //box wird erhöht, wenn richtig beantwortet (und counter auf einen bestimmten Wert kommt?) -> muss noch hinzugefügt werden
            box = query.value(2).toInt();

            // counter wird in jedem fall erhöht -> muss noch hinzugefügt werden (bis zu einem bestimmten Wert erhöhen?)
            counter = query.value(3).toInt();

            // wird (wahrscheinlich) nicht geändert -> wahrscheinlich sinnvoll für herauspicken der Vokabeln
            //int categoryid = query.value(4).toInt();

            // used wird in jedem fall erhöht -> muss noch hinzugefügt werden (used kann endlos groß werden, oder?)
            used = query.value(5).toInt();

            // usedright wird erhöht, wenn richtig beantwortet -> muss noch hinzugefügt werden
            usedright = query.value(6).toInt();

            // wordid1
            wordVocableId1 = query.value(7).toInt();

            // wordid2
            wordVocableId2 = query.value(8).toInt();


        }

        conn.closeConnection();

        if(word1 == "" && word2 == ""){
            QMessageBox msgbox;
            msgbox.setText("Es gibt keine Vokabel mit der Kombination an Parametern. Bitte probiere etwas anderes oder füge neue Vokabeln mit den entprechenden Parametern hinzu.");
            msgbox.exec();
        }

        word1.remove(char('{'));
        word1.remove(char('}'));
        word1.remove(char('"'));

        word2.remove(char('{'));
        word2.remove(char('}'));
        word2.remove(char('"'));


        // wenn ausgangssprache nicht deutsch, dann word2 setText
        // QString vocableQuiz;
        if(comboSourceLanguage != "Deutsch"){
            ui->labelQuiz->setText(word2);
            vocableQuiz = word1;
        }else{
            ui->labelQuiz->setText(word1);
            vocableQuiz = word2;
        }

        ui->labelQuiz->resize(this->width(), ui->labelQuiz->height());

        ui->labelResult->resize(this->width(), ui->labelResult->height());


    }

    else if (!conn.openConnection()){

        QMessageBox msgbox;
        msgbox.setText("Verbindung zur Datenbank konnte nicht hergestellt werden");
        msgbox.exec();

    }

}



void MainWindow::on_comboBoxSourceLanguage_currentTextChanged(const QString &arg1){

    DatabaseConnection dbc;
    comboboxChangeDestinationLanguage(dbc, arg1);

}


void MainWindow::comboboxChangeDestinationLanguage(DatabaseConnection &dbc, const QString &arg1){

    Databasequery dbq;
    ui->comboBoxDestinationLanguage->clear();
    dbc.closeConnection();
    dbc.openConnection();
    ui->comboBoxDestinationLanguage->addItems(dbq.getAllLanguagesExcept(dbc, arg1));
    dbc.closeConnection();
}


void MainWindow::on_buttonCompare_clicked()
{
    QString answer = ui->editAnswer->text();

    vocableQuiz.remove(char(' '));
    answer.remove(char(' '));

    QStringList listVocableQuiz = vocableQuiz.split(QLatin1Char(','));

    QStringList listAnswer = answer.split(QLatin1Char(','));

    int matches = 0;
    int givenanswers = 0;


    foreach(answer, listAnswer){
        givenanswers++;
        foreach(vocableQuiz, listVocableQuiz){
            if(answer==vocableQuiz){
                matches++;
            }
        }
    }


    // wenn text von labelquiz == eingabe ist
    //QString answer = ui->editAnswer->text();
    if(matches==givenanswers){
        ui->labelResult->setText("Richtig! :)");
        counter++;
        usedright++;
        if(box < 5 && counter == 3){
            box++;
            counter = 0;
        }
    }else if(matches!=givenanswers){
        ui->labelResult->setText("Falsch");
        counter = 0;
        box = 1;
    }

    used++;

    QString updatebox = updatebox.number(box);
    QString updatecounter = updatecounter.number(counter);
    QString updateused = updateused.number(used);
    QString updateusedright = updateusedright.number(usedright);
    QString updatewordVocableId1 = updatewordVocableId1.number(wordVocableId1);
    QString updatewordVocableId2 = updatewordVocableId2.number(wordVocableId2);


    DatabaseConnection conn;

    if(conn.openConnection()){
        QSqlQuery query;
        query.exec("update vocable set box= '" + updatebox + "', counter = '" + updatecounter + "', used = '" + updateused + "', usedright = '" + updateusedright + "' where wordid1 = '" + updatewordVocableId1 +  "' and wordid2 = '" + updatewordVocableId2 + "'");
        conn.closeConnection();
    }

}
