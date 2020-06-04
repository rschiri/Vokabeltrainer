#include "addvoc.h"
#include "ui_addvoc.h"

AddVoc::AddVoc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddVoc)
{
    ui->setupUi(this);


    layout = new QVBoxLayout();
    layout->addWidget(ui->label_6);
    layout->addWidget(ui->groupBox);
    layout->addWidget(ui->groupBox_2);
    layout->addWidget(ui->groupBox_3);



    setLayout(layout);



}

AddVoc::~AddVoc()
{
    delete ui;
}
