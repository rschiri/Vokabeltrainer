#include "addkategorie.h"
#include "ui_addkategorie.h"

AddKategorie::AddKategorie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddKategorie)
{
    ui->setupUi(this);
}

AddKategorie::~AddKategorie()
{
    delete ui;
}
