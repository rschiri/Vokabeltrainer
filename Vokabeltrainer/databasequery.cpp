#include "databasequery.h"
#include "databaseconnection.h"

#include <QTextStream>

Databasequery::Databasequery()
{

}

QStringList Databasequery::getAllCategories(){
    QStringList qStringList;

    DatabaseConnection dbc;
    dbc.openConnection();
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select category from category");

    while (qry->next()) {
       QString mystring = qry->value(0).toString();
       qStringList.push_back(mystring);
        }

    dbc.closeConnection();
    return qStringList;
}

QStringList Databasequery::getAllWordtypes(){
    QStringList qStringList;

    DatabaseConnection dbc;
    dbc.openConnection();
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select wordtype from wordtype");

    while (qry->next()) {
       QString mystring = qry->value(0).toString();
       qStringList.push_back(mystring);
        }

    dbc.closeConnection();
    return qStringList;
}

QStringList Databasequery::getAllLanguages(){
    QStringList qStringList;

    DatabaseConnection dbc;
    dbc.openConnection();
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select language from languages");

    while (qry->next()) {
       QString mystring = qry->value(0).toString();
       qStringList.push_back(mystring);
        }

    dbc.closeConnection();
    return qStringList;
}

QStringList Databasequery::getAllLanguagesExcept(QString qstring){
    QStringList qStringList;

    DatabaseConnection dbc;
    dbc.openConnection();
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select language from languages except select language from languages where language = '"+ qstring +"'");

    while (qry->next()) {
       QString mystring = qry->value(0).toString();
       qStringList.push_back(mystring);
        }

    dbc.closeConnection();
    return qStringList;
}

int Databasequery::getIDCategory(DatabaseConnection &dbc,QString category){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select categoryid from category where category = '"+ category +"' ");
    qry->next();
    return qry->value(0).toInt();
}

int Databasequery::getIDWordtype(DatabaseConnection &dbc,QString wordtype){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select wordtypeid from wordtype where wordtype = '"+ wordtype +"' ");
    qry->next();
    return qry->value(0).toInt();
}

int Databasequery::getIDLanguage(DatabaseConnection &dbc,QString language){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select languagesid from languages where language = '"+ language +"' ");
    qry->next();
    return qry->value(0).toInt();
}

int Databasequery::addWord(QString statement,QString wordtype,QString language){
    DatabaseConnection dbc;
    int wordid = 0;
    dbc.openConnection();
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->prepare("INSERT INTO word (wordtypeid, languageid, word)"
                 "VALUES (:wordtypeid, :languageid, '{ "+ statement + " }') returning wordid");
    qry->bindValue(":wordtypeid", getIDWordtype(dbc,wordtype));
    qry->bindValue(":languageid", getIDLanguage(dbc,language));
    wordid = qry->exec();

    dbc.closeConnection();
    return wordid;
}

void Databasequery::addVocable(int wordid1, int wordid2, QString category){
    DatabaseConnection dbc;
    dbc.openConnection();
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->prepare("INSERT INTO vocable (wordid1,wordid2,categoryid)"
              "VALUES (:word1,:word2,:category)");
    qry->bindValue(":word1",wordid1);
    qry->bindValue(":word2",wordid2);
    qry->bindValue(":category",getIDCategory(dbc,category));
    qry->exec();
    dbc.closeConnection();

}

Databasequery::~Databasequery()
{

}


