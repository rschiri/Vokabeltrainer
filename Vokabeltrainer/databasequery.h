/**
*@author: Christin
*/

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

    QStringList getAllCategories(DatabaseConnection &dbc);
    QStringList getAllWordtypes(DatabaseConnection &dbc);
    QStringList getAllLanguages(DatabaseConnection &dbc);
    QStringList getAllLanguagesExcept(DatabaseConnection &dbc,QString language);

    int getIDCategory(DatabaseConnection &dbc,QString &category);
    int getIDWordtype(DatabaseConnection &dbc,QString &wordtype);
    int getIDLanguage(DatabaseConnection &dbc,QString &language);

    bool checkCategory(DatabaseConnection &dbc, QString &category);
    bool checkWordtype(DatabaseConnection &dbc, QString &wordtype);
    bool checkLanguage(DatabaseConnection &dbc, QString &language);

    void addCategory(DatabaseConnection &dbc, QString &category);
    void addWordtype(DatabaseConnection &dbc, QString &wordtype);
    void addLanguage(DatabaseConnection &dbc, QString &language);

    int addWord(DatabaseConnection &dbc, const QString &statement,QString wordtype,QString language);
    void addVocable(DatabaseConnection &dbc, int wordid1,int wordid2, QString category);
    
    void updateQuizVocable(DatabaseConnection &dbc, QString box, QString counter, QString used, QString usedright, QString wordId1, QString wordId2);

};

#endif // DATABASEQUERY_H
