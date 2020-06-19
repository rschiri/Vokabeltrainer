#ifndef WOERTERBUCH_H
#define WOERTERBUCH_H

#include <QDialog>
#include <QTableView>
#include "mytablemodel.h"

namespace Ui {
class Woerterbuch;
}

class Woerterbuch : public QDialog
{
    Q_OBJECT

public:
    void slotOpenDataFile();
    void showVocables();
    explicit Woerterbuch(QWidget *parent = nullptr);
    ~Woerterbuch();

private slots:


    void on_Button_LoadDatabase_clicked();

private:

    Ui::Woerterbuch *ui;
};

#endif // WOERTERBUCH_H
