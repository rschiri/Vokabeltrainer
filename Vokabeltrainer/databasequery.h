#ifndef DATABASEQUERY_H
#define DATABASEQUERY_H

#include <databaseconnection.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>


class Databasequery
{
public:
    Databasequery();
    ~Databasequery();

    QStringList getAllCategories();
    QStringList getAllWordtypes();
    QStringList getAllLanguages();
    QStringList getAllLanguagesExcept(QString language);

    //QSqlQuery query("select w1.word as wordid1, w2.word as wordid2, box from vocable as v left join word as w1 on v.wordid1=w1.wordid left join word as w2 on v.wordid2=w2.wordid", conn.db);

    int getIDCategory(DatabaseConnection &dbc,QString category);
    int getIDWordtype(DatabaseConnection &dbc,QString wordtype);
    int getIDLanguage(DatabaseConnection &dbc,QString language);

    int addWord(QString statement,QString wordtype,QString language);
    void addVocable(int wordid1,int wordid2, QString category);

};

#endif // DATABASEQUERY_H
