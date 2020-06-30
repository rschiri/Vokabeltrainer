#include "addvocable.h"
#include "ui_addvocable.h"

#include <QTextStream>
#include <QMessageBox>
#include <QSqlError>

#include <databasequery.h>
#include <QDebug>

AddVocable::AddVocable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addVocable)
{
    ui->setupUi(this);
    Databasequery dbq;
    DatabaseConnection dbc;
    dbc.openConnection();
    ui->deutschWortartComboBox->addItems(dbq.getAllWordtypes(dbc));
    ui->deutschWortartComboBox->adjustSize();
    ui->deutschWortartComboBox->setStyleSheet("combobox-popup:0;");
    ui->spracheWortartComboBox->addItems(dbq.getAllWordtypes(dbc));
    ui->spracheWortartComboBox->adjustSize();
    ui->spracheWortartComboBox->setStyleSheet("combobox-popup:0;");
    ui->spracheComboBox->addItems(dbq.getAllLanguagesExcept(dbc,"Deutsch"));
    ui->spracheComboBox->adjustSize();
    ui->spracheComboBox->setStyleSheet("combobox-popup:0;");
    ui->kategorieComboBox->addItems(dbq.getAllCategories(dbc));
    ui->kategorieComboBox->adjustSize();
    ui->kategorieComboBox->setStyleSheet("combobox-popup:0;");
    dbc.closeConnection();

}

AddVocable::~AddVocable()
{
    delete ui;
}

void AddVocable::on_hinzufuegenButton_clicked()
{
    DatabaseConnection dbc;
    dbc.openConnection();
    QString stringGermanWords = ui->deutschBedeutung1LineEdit->text();
    if(!stringGermanWords.isEmpty() && !ui->deutschBedeutung2LineEdit->text().isEmpty())
        stringGermanWords =+ "," + ui->deutschBedeutung2LineEdit->text();
    if(!stringGermanWords.isEmpty() && !ui->deutschBedeutung3LineEdit->text().isEmpty())
        stringGermanWords =+ "," + ui->deutschBedeutung3LineEdit->text();
     Databasequery dbq;
     int wordid1= 0;
     int wordid2= 0;
    if(!stringGermanWords.isEmpty()){
        wordid1 = dbq.addWord(dbc,stringGermanWords,ui->deutschWortartComboBox->currentText(),"Deutsch");
    }
    QString stringLanguageWords = ui->spracheBedeutung1LineEdit->text();
    if(!stringLanguageWords.isEmpty() && !ui->spracheBedeutung2LineEdit->text().isEmpty())
        stringLanguageWords =+ "," + ui->spracheBedeutung2LineEdit->text();
    if(!stringLanguageWords.isEmpty() && !ui->spracheBedeutung3LineEdit->text().isEmpty())
        stringLanguageWords =+ "," + ui->spracheBedeutung3LineEdit->text();

    if(!stringLanguageWords.isEmpty()){
        wordid2 = dbq.addWord(dbc,stringLanguageWords,ui->spracheWortartComboBox->currentText(),ui->spracheComboBox->currentText());
    }
    qDebug() << wordid1 << " ist id 1";
    qDebug() << wordid2 << " ist id 2";
    QMessageBox msgbox;
    if(wordid1 > 0 && wordid2 > 0){
        dbq.addVocable(dbc,wordid1,wordid2,ui->kategorieComboBox->currentText());
        msgbox.setText("Vokabel wurde hinzugefügt");
        msgbox.exec();
    }else{
        msgbox.setText("Es muss ein Wort in die erste Bedeutung von Deutsch und der Fremdsprache geschrieben werden");
        msgbox.exec();
    }
    dbc.closeConnection();
    on_resetButton_clicked();

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
