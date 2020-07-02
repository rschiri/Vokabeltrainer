/**
*@author: Christin
*/

#include "addvocable.h"
#include "ui_addvocable.h"

#include <QTextStream>
#include <QMessageBox>

#include <databasequery.h>

AddVocable::AddVocable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addVocable)
{
    ui->setupUi(this);
    Databasequery dbq;
    DatabaseConnection dbc;
    dbc.openConnection();
    ui->germanWordtypeComboBox->addItems(dbq.getAllWordtypes(dbc));
    ui->germanWordtypeComboBox->adjustSize();
    ui->germanWordtypeComboBox->setStyleSheet("combobox-popup:0;");
    ui->languageWordtypeComboBox->addItems(dbq.getAllWordtypes(dbc));
    ui->languageWordtypeComboBox->adjustSize();
    ui->languageWordtypeComboBox->setStyleSheet("combobox-popup:0;");
    ui->languageComboBox->addItems(dbq.getAllLanguagesExcept(dbc,"Deutsch"));
    ui->languageComboBox->adjustSize();
    ui->languageComboBox->setStyleSheet("combobox-popup:0;");
    ui->categoryComboBox->addItems(dbq.getAllCategories(dbc));
    ui->categoryComboBox->adjustSize();
    ui->categoryComboBox->setStyleSheet("combobox-popup:0;");
    dbc.closeConnection();

}

AddVocable::~AddVocable()
{
    delete ui;
}
/**
 * @brief AddVocable::on_hinzufuegenButton_clicked adds a new vocabulary to the database with the information entered and resets.
 *  The entries are then reset
 */
void AddVocable::on_hinzufuegenButton_clicked()
{
    int wordid1= 0;
    int wordid2= 0;
    DatabaseConnection dbc;
    Databasequery dbq;

    // put together the statement of the German words
    QString stringGermanWords = ui->germanMeaning1LineEdit->text();
    if(!stringGermanWords.isEmpty() && !ui->germanMeaning2LineEdit->text().isEmpty())
        stringGermanWords =stringGermanWords+ "," + ui->germanMeaning2LineEdit->text();
    if(!stringGermanWords.isEmpty() && !ui->germanMeaning3LineEdit->text().isEmpty())
        stringGermanWords =stringGermanWords+ "," + ui->germanMeaning3LineEdit->text();

    //put together the statement of the foreign language words
    QString stringLanguageWords = ui->languageMeaning1LineEdit->text();
    if(!stringLanguageWords.isEmpty() && !ui->languageMeaning2LineEdit->text().isEmpty())
        stringLanguageWords =stringLanguageWords+ "," + ui->languageMeaning2LineEdit->text();
    if(!stringLanguageWords.isEmpty() && !ui->languageMeaning3LineEdit->text().isEmpty())
        stringLanguageWords =stringLanguageWords+ "," + ui->languageMeaning3LineEdit->text();

    //checking the entries
    if(!stringGermanWords.isEmpty() && !stringLanguageWords.isEmpty()){
        dbc.openConnection();
        //adding the words
        wordid1 = dbq.addWord(dbc,stringGermanWords,ui->germanWordtypeComboBox->currentText(),"Deutsch");
        wordid2 = dbq.addWord(dbc,stringLanguageWords,ui->languageWordtypeComboBox->currentText(),ui->languageComboBox->currentText());
        //adding the vocable
        dbq.addVocable(dbc,wordid1,wordid2,ui->categoryComboBox->currentText());
        dbc.closeConnection();
        on_resetButton_clicked();
        QMessageBox::information(this,"Information", "Vocable wurde hinzugefügt");
    }else{
        QMessageBox::information(this,"Information","Es muss ein Wort in die erste Bedeutung von Deutsch und der Fremdsprache geschrieben werden");
    }
}
/**
 * @brief AddVocable::on_resetButton_clicked Resets the entries
 */
void AddVocable::on_resetButton_clicked()
{
    ui->germanMeaning1LineEdit->clear();
    ui->germanMeaning2LineEdit->clear();
    ui->germanMeaning3LineEdit->clear();
    ui->languageMeaning1LineEdit->clear();
    ui->languageMeaning2LineEdit->clear();
    ui->languageMeaning3LineEdit->clear();
    ui->germanWordtypeComboBox->setCurrentIndex(0);
    ui->languageWordtypeComboBox->setCurrentIndex(0);
    ui->languageComboBox->setCurrentIndex(0);
    ui->categoryComboBox->setCurrentIndex(0);
}
