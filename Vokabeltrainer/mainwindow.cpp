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
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
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
    delete ui;
}

void MainWindow::close(){
    QApplication::quit();
}


/**
 * @brief MainWindow::on_Neu_Button_clicked Opens the addVocable window in order to add a vocable to the database
 */
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
    }else if(ok && (text.isEmpty() || dbq.checkCategory(dbc,text))){
        QMessageBox::information(this,"Information", "Kategorie existiert bereits oder es wurde nichts in das Textfeld geschrieben.");
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
    }else if (ok && (text.isEmpty() || dbq.checkLanguage(dbc,text))){
        QMessageBox::information(this,"Information", "Sprache existiert bereits oder es wurde nichts in das Textfeld geschrieben.");
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
    }else if (ok && (text.isEmpty() || dbq.checkWordtype(dbc,text))){
        QMessageBox::information(this,"Information", "Wortart existiert bereits oder es wurde nichts in das Textfeld geschrieben.");
    }
    dbc.closeConnection();
}


/**
 * @brief MainWindow::on_actionOpen_triggered Opens a new window with the dictionary
 */
void MainWindow::on_actionOpen_triggered()
{
    Woerterbuch wobuch;
    wobuch.setModal(true);
    wobuch.exec();
}


/**
 * @brief MainWindow::clearUpString Changes the value of a QString in order to prevent the usage of old data
 * @param word The QString which has to to be changed
 * @return the changed QString
 */
QString MainWindow::clearUpString(QString word){
    word = "";
    return word;
}

/**
 * @brief MainWindow::clearUpInt Changes the value of an integer in order to prevent the usage of old data
 * @param number The integer which has to to be changed
 * @return the changed integers
 */
int MainWindow::clearUpInt(int number){
    number = -1;
    return number;
}

/**
 * @brief MainWindow::clearStringFromCharacters Removes the characters {, }, and " from a string
 * @param word The word from which the characters have to be removed
 * @return the word without the characters {, }, and "
 */
QString MainWindow::clearStringFromCharacters(QString word){

    word.remove(char('{'));
    word.remove(char('}'));
    word.remove(char('"'));
    return word;
}



/**
 * @brief MainWindow::on_buttonTestVocabulary_clicked Fetches the data of a vocable from the database according to the parameters in the comboboxes and shows one word from the vocable
 * in the mainwindow of which the user has to find the correct translation
 */
void MainWindow::on_buttonTestVocabulary_clicked()
{

    // change values in order to prevent the usage of old data
    word1 = clearUpString(word1);
    word2 = clearUpString(word2);
    box = clearUpInt(box);
    counter = clearUpInt(counter);
    categoryid = clearUpInt(categoryid);
    used = clearUpInt(used);
    usedright = clearUpInt(usedright);
    wordVocableId1 = clearUpInt(wordVocableId1);
    wordVocableId2 = clearUpInt(wordVocableId2);

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

        // get categoryid for query 
        QSqlQuery queryCategory;
        queryCategory.exec("select categoryid from category where category = '" + comboCategory + "'");
        queryCategory.next();
        QString categoryid = queryCategory.value(0).toString();

        // get wordtypeid for query
        QSqlQuery queryWordtpye;
        queryWordtpye.exec("select wordtypeid from wordtype where wordtype = '" + comboWordtype + "'");
        queryWordtpye.next();
        QString wordtypeid = queryWordtpye.value(0).toString();

        // get languagesid of sourceLanguage for query 
        QSqlQuery querySourceLanguageId;
        querySourceLanguageId.exec("select languagesid from languages where language = '" + comboSourceLanguage + "'");
        querySourceLanguageId.next();
        QString sourceLanguageId = querySourceLanguageId.value(0).toString();

        // get languagesid of destinationLanguage for query 
        QSqlQuery queryDestinationLanguageId;
        queryDestinationLanguageId.exec("select languagesid from languages where language = '" + comboDestinationLanguage + "'");
        queryDestinationLanguageId.next();
        QString destinationLanguageId = queryDestinationLanguageId.value(0).toString();



        QSqlQuery query;
        if(comboSourceLanguage == "Deutsch"){
            query.exec("select w1.word as wordid1, w2.word as wordid2, box, counter, used, usedright, wordid1, wordid2 from vocable as v left join word as w1 on v.wordid1=w1.wordid left join word as w2 on v.wordid2=w2.wordid where box = '" + comboBox + "' and categoryid = '" + categoryid + "' and w1.wordtypeid = '" + wordtypeid + "' and w1.languageid = '" + sourceLanguageId + "' and w2.languageid = '" + destinationLanguageId + "' order by random()");
        }else{
            query.exec("select w1.word as wordid1, w2.word as wordid2, box, counter, used, usedright, wordid1, wordid2 from vocable as v left join word as w1 on v.wordid1=w1.wordid left join word as w2 on v.wordid2=w2.wordid where box = '" + comboBox + "' and categoryid = '" + categoryid + "' and w1.wordtypeid = '" + wordtypeid + "' and w2.languageid = '" + sourceLanguageId + "' and w1.languageid = '" + destinationLanguageId + "' order by random()");

        }

        while(query.next()){
            // get text for both words of the vocable
            word1 = query.value(0).toString();
            word2 = query.value(1).toString();

            // get box in which the vocable is
            box = query.value(2).toInt();

            // get the counter for the vocable in order to check later, whether to change the box
            counter = query.value(3).toInt();

            // get the number of times this vocable has been used in order to increase it later
            used = query.value(4).toInt();

            // get the number of times this vocable has been used correctly in order to increase it later
            usedright = query.value(5).toInt();

            // get wordid for both words of the vocable
            wordVocableId1 = query.value(6).toInt();
            wordVocableId2 = query.value(7).toInt();

        }

        conn.closeConnection();

        // check whether the query has been successful in assigning a value to word1 and word2
        if(word1 == "" && word2 == ""){
            QMessageBox msgbox;
            msgbox.setText("Es gibt keine Vokabel mit der Kombination an Parametern. Bitte probiere etwas anderes oder füge neue Vokabeln mit den entprechenden Parametern hinzu.");
            msgbox.exec();
        }

        word1 = clearStringFromCharacters(word1);
        word2 = clearStringFromCharacters(word2);

        // put one word of the vocable in the label
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



/**
 * @brief MainWindow::on_comboBoxSourceLanguage_currentTextChanged If the text of comboBoxSourceLanguage changes fill comboBoxDestinationLanguage will all languages except the language
 * selected in comboBoxSourceLanguage
 * @param arg1 The language selected in comboBoxSourceLanguage
 */
void MainWindow::on_comboBoxSourceLanguage_currentTextChanged(const QString &arg1){

    DatabaseConnection dbc;
    Databasequery dbq;
    ui->comboBoxDestinationLanguage->clear();
    dbc.closeConnection();
    dbc.openConnection();
    ui->comboBoxDestinationLanguage->addItems(dbq.getAllLanguagesExcept(dbc, arg1));
    dbc.closeConnection();

}



/**
 * @brief MainWindow::on_buttonCompare_clicked Compares the answer given by the user in the lineEdit called editAnswer with the correct answer which has been set in
 * on_buttonTestVocabulary_clicked() or on_buttonTestNewVocabulary_clicked()
 * Depending on the given answer the vocable is updated in the database
 */
void MainWindow::on_buttonCompare_clicked(){

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

/**
 * @brief MainWindow::on_buttonTestNewVocabulary_clicked Fetches the data of a vocable from the database which has not been used yet and shows one word from the vocable
 * in the mainwindow of which the user has to find the correct translation
 */
void MainWindow::on_buttonTestNewVocabulary_clicked()
{
    // change values in order to prevent the usage of old data
    word1 = clearUpString(word1);
    word2 = clearUpString(word2);
    box = clearUpInt(box);
    counter = clearUpInt(counter);
    categoryid = clearUpInt(categoryid);
    used = clearUpInt(used);
    usedright = clearUpInt(usedright);
    wordVocableId1 = clearUpInt(wordVocableId1);
    wordVocableId2 = clearUpInt(wordVocableId2);

    ui->labelQuiz->setText("");
    ui->labelResult->setText("");
    ui->editAnswer->clear();


    DatabaseConnection conn;

    if(conn.openConnection()){

        QSqlQuery query;
        query.exec("select w1.word as wordid1, w2.word as wordid2, box, counter, used, usedright, wordid1, wordid2 from vocable as v left join word as w1 on v.wordid1=w1.wordid left join word as w2 on v.wordid2=w2.wordid where used = 0 order by random()");

        while(query.next()){
            // get text for both words of the vocable
            word1 = query.value(0).toString();
            word2 = query.value(1).toString();

            // get box in which the vocable is
            box = query.value(2).toInt();

            // get the counter for the vocable in order to check later, whether to change the box
            counter = query.value(3).toInt();

            // get the number of times this vocable has been used in order to increase it later
            used = query.value(4).toInt();

            // get the number of times this vocable has been used correctly in order to increase it later
            usedright = query.value(5).toInt();

            // get wordid for both words of the vocable
            wordVocableId1 = query.value(6).toInt();
            wordVocableId2 = query.value(7).toInt();

        }

        conn.closeConnection();

        if(word1 == "" && word2 == ""){
            QMessageBox msgbox;
            msgbox.setText("Es gibt keine Vokabeln, die noch nicht abgefragt wurden. Lege neue Vokabeln an, um diese zu üben.");
            msgbox.exec();
        }

        word1 = clearStringFromCharacters(word1);
        word2 = clearStringFromCharacters(word2);

        ui->labelQuiz->setText(word2);
        vocableQuiz = word1;

        ui->labelQuiz->resize(this->width(), ui->labelQuiz->height());
        ui->labelResult->resize(this->width(), ui->labelResult->height());

    }

    else if (!conn.openConnection()){

        QMessageBox msgbox;
        msgbox.setText("Verbindung zur Datenbank konnte nicht hergestellt werden");
        msgbox.exec();

    }
}
