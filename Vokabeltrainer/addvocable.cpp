#include "addvocable.h"
#include "ui_addvocable.h"

#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

#include <databasequery.h>

AddVocable::AddVocable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addVocable)
{
    ui->setupUi(this);
    Databasequery dbq;
    ui->deutschWortartComboBox->addItems(dbq.getAllWordtypes());
    ui->deutschWortartComboBox->adjustSize();
    ui->deutschWortartComboBox->setStyleSheet("combobox-popup:0;");
    ui->spracheWortartComboBox->addItems(dbq.getAllWordtypes());
    ui->spracheWortartComboBox->adjustSize();
    ui->spracheWortartComboBox->setStyleSheet("combobox-popup:0;");
    ui->spracheComboBox->addItems(dbq.getAllLanguagesExcept("Deutsch"));
    ui->spracheComboBox->adjustSize();
    ui->spracheComboBox->setStyleSheet("combobox-popup:0;");
    ui->kategorieComboBox->addItems(dbq.getAllCategories());
    ui->kategorieComboBox->adjustSize();
    ui->kategorieComboBox->setStyleSheet("combobox-popup:0;");

}

AddVocable::~AddVocable()
{
    delete ui;
}

void AddVocable::on_hinzufuegenButton_clicked()
{
    QString stringGermanWords = ui->deutschBedeutung1LineEdit->text();
    if(!stringGermanWords.isEmpty() && !ui->deutschBedeutung2LineEdit->text().isEmpty())
        stringGermanWords =+ "," + ui->deutschBedeutung2LineEdit->text();
    if(!stringGermanWords.isEmpty() && !ui->deutschBedeutung3LineEdit->text().isEmpty())
        stringGermanWords =+ "," + ui->deutschBedeutung3LineEdit->text();
     Databasequery dbq;
     int wordid1= 0;
     int wordid2= 0;
    if(!stringGermanWords.isEmpty()){
        wordid1 = dbq.addWord(stringGermanWords,ui->deutschWortartComboBox->currentText(),"Deutsch");
    }
    QString stringLanguageWords = ui->spracheBedeutung1LineEdit->text();
    if(!stringLanguageWords.isEmpty() && !ui->spracheBedeutung2LineEdit->text().isEmpty())
        stringLanguageWords =+ "," + ui->spracheBedeutung2LineEdit->text();
    if(!stringLanguageWords.isEmpty() && !ui->spracheBedeutung3LineEdit->text().isEmpty())
        stringLanguageWords =+ "," + ui->spracheBedeutung3LineEdit->text();

    if(!stringLanguageWords.isEmpty()){
        wordid2 = dbq.addWord(stringLanguageWords,ui->spracheWortartComboBox->currentText(),ui->spracheComboBox->currentText());
    }
    QMessageBox msgbox;
    if(wordid1 > 0 && wordid2 > 0){
        dbq.addVocable(wordid1,wordid2,ui->kategorieComboBox->currentText());
        QMessageBox msgbox;
        msgbox.setText("Vocable wurde hinzugefügt");
        msgbox.exec();
    }else{
        msgbox.setText("Es muss ein Wort in die erste Bedeutung von Deutsch und der Fremdsprache geschrieben werden");
        msgbox.exec();
    }

}

void AddVocable::on_resetButton_clicked()
{
    ui->deutschBedeutung1LineEdit->clear();
    ui->deutschBedeutung2LineEdit->clear();
    ui->deutschBedeutung3LineEdit->clear();
    ui->spracheBedeutung1LineEdit->clear();
    ui->spracheBedeutung2LineEdit->clear();
    ui->spracheBedeutung3LineEdit->clear();
    ui->deutschWortartComboBox->setCurrentIndex(0);
    ui->spracheWortartComboBox->setCurrentIndex(0);
    ui->spracheComboBox->setCurrentIndex(0);
    ui->kategorieComboBox->setCurrentIndex(0);
}
