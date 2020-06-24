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

    int getIDCategory(DatabaseConnection &dbc,QString category);
    int getIDWordtype(DatabaseConnection &dbc,QString wordtype);
    int getIDLanguage(DatabaseConnection &dbc,QString language);

    bool checkCategory(QString category);
    bool checkWordtype(QString wordtype);
    bool checkLanguage(QString language);

    void addCategory(QString category);
    void addWordtype(QString wordtype);
    void addLanguage(QString language);

    int addWord(QString statement,QString wordtype,QString language);
    void addVocable(int wordid1,int wordid2, QString category);

};

#endif // DATABASEQUERY_H
