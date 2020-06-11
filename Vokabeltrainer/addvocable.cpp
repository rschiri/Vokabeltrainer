#include "addvocable.h"
#include "ui_addvocable.h"

addVocable::addVocable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addVocable)
{
    ui->setupUi(this);

    /*ui->deutschWortartComboBox->addItems();
     *
     *
     * */
}

addVocable::~addVocable()
{
    delete ui;
}

void addVocable::on_hinzufuegenButton_clicked()
{

}
