/**
*@author: Lea
*/

#ifndef WOERTERBUCH_H
#define WOERTERBUCH_H

#include <QDialog>
#include <QTableView>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>


#include "databaseconnection.h"

namespace Ui {
class Woerterbuch;
}

class Woerterbuch : public QDialog
{
    Q_OBJECT

public:

    void slotOpenDataFile();

    explicit Woerterbuch(QWidget *parent = nullptr);

    void findVocable();

    void showDEVocables();
    void showDSVocables();
    void showSearchVocable(QString);
    bool inVocableList(QVector<QString>, QString);

    void showNomen();
    void showVerben();
    void showAdjektive();
    void showArtikel();
    void showKonjunktion();
    void showUnregelVerben();

    void showAdverben();
    void showPraepositionen();
    void showPronomen();
    void showSubMas();
    void showSubFem();
    void showSubNeu();
    void showZahlenwoerter();



    ~Woerterbuch();

private slots:


private:

    Ui::Woerterbuch *ui;
    QString findText;
    DatabaseConnection conn;
    QVector<QString> vocableList;
};

#endif // WOERTERBUCH_H
