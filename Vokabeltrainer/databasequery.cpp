#include "databasequery.h"
#include "databaseconnection.h"

#include <QTextStream>
#include <QDebug>

Databasequery::Databasequery()
{

}

QStringList Databasequery::getAllCategories(DatabaseConnection &dbc){
    QStringList qStringList;
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select category from category");

    while (qry->next()) {
       QString mystring = qry->value(0).toString();
       qStringList.push_back(mystring);
        }

    return qStringList;
}

QStringList Databasequery::getAllWordtypes(DatabaseConnection &dbc){
    QStringList qStringList;
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select wordtype from wordtype");

    while (qry->next()) {
       QString mystring = qry->value(0).toString();
       qStringList.push_back(mystring);
        }

    return qStringList;
}

QStringList Databasequery::getAllLanguages(DatabaseConnection &dbc){
    QStringList qStringList;
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select language from languages");

    while (qry->next()) {
       QString mystring = qry->value(0).toString();
       qStringList.push_back(mystring);
        }

    return qStringList;
}

QStringList Databasequery::getAllLanguagesExcept(DatabaseConnection &dbc,QString qstring){
    QStringList qStringList;

    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select language from languages except select language from languages where language = '"+ qstring +"'");

    while (qry->next()) {
       QString mystring = qry->value(0).toString();
       qStringList.push_back(mystring);
        }

    return qStringList;
}

int Databasequery::getIDCategory(DatabaseConnection &dbc,QString &category){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select categoryid from category where category = '"+ category +"' ");
    qry->next();
    return qry->value(0).toInt();
}

int Databasequery::getIDWordtype(DatabaseConnection &dbc,QString &wordtype){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select wordtypeid from wordtype where wordtype = '"+ wordtype +"' ");
    qry->next();
    return qry->value(0).toInt();
}

int Databasequery::getIDLanguage(DatabaseConnection &dbc,QString &language){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select languagesid from languages where language = '"+ language +"' ");
    qry->next();
    return qry->value(0).toInt();
}
bool Databasequery::checkCategory(DatabaseConnection &dbc, QString &category){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select count (category) from category where category = '"+ category +"';");
    qry->next();
    if (qry->value(0).toInt() > 0)
        return true;
    else{
        return false;
    }
}
bool Databasequery::checkWordtype(DatabaseConnection &dbc, QString &wordtype){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select count (wordtype) from wordtype where worstype = '"+ wordtype +"';");
    qry->next();
    if (qry->value(0).toInt() > 0)
        return true;
    else{
        return false;
    }
}
bool Databasequery::checkLanguage(DatabaseConnection &dbc, QString &language){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select count (language) from languages where language = '"+ language +"';");
    qry->next();
    if (qry->value(0).toInt() > 0)
        return true;
    else{
        return false;
    }
}

void Databasequery::addCategory(DatabaseConnection &dbc,QString &category){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("INSERT INTO category (category) VALUES ('"+category+"');");
}

void Databasequery::addWordtype(DatabaseConnection &dbc, QString &wordtype){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("INSERT INTO wordtype (wordtype) VALUES ('"+wordtype+"');");
}

void Databasequery::addLanguage(DatabaseConnection &dbc, QString &language){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("INSERT INTO languages (language) VALUES ('"+ language +"');");
}

int Databasequery::addWord(DatabaseConnection &dbc, const QString &statement,QString wordtype,QString language){
    int wordid;
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->prepare("INSERT INTO word (wordtypeid, languageid, word)"
                 "VALUES (:wordtypeid, :languageid, '{ "+ statement + " }') returning wordid");
    qry->bindValue(":wordtypeid", getIDWordtype(dbc,wordtype));
    qry->bindValue(":languageid", getIDLanguage(dbc,language));
    qry->exec();
    qry->next();
    wordid = qry->value(0).toInt();
    qDebug() << wordid << " aus Databasequery";
    return wordid;
}

void Databasequery::addVocable(DatabaseConnection &dbc, int wordid1, int wordid2, QString category){
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->prepare("INSERT INTO vocable (wordid1,wordid2,categoryid)"
              "VALUES (:word1,:word2,:category)");
    qry->bindValue(":word1",wordid1);
    qry->bindValue(":word2",wordid2);
    qry->bindValue(":category",getIDCategory(dbc,category));
    qry->exec();

}

Databasequery::~Databasequery()
{

}


