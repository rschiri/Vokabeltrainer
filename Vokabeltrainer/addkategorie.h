#ifndef ADDKATEGORIE_H
#define ADDKATEGORIE_H

#include <QDialog>

namespace Ui {
class AddKategorie;
}

class AddKategorie : public QDialog
{
    Q_OBJECT

public:
    explicit AddKategorie(QWidget *parent = nullptr);
    ~AddKategorie();

private:
    Ui::AddKategorie *ui;
};

#endif // ADDKATEGORIE_H
