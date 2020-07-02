/**
*@author: Rebecca : updateQuizVocable()
*@author: Christin : Rest
*/

#include "databasequery.h"
#include "databaseconnection.h"
#include <QTextStream>

Databasequery::Databasequery()
{

}
/**
 * @brief Databasequery::getAllCategories Executes a query to get all categories on a given databaseconnection.
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @return all categories from the table category as QStringList
 */
QStringList Databasequery::getAllCategories(DatabaseConnection &dbc){
    QStringList qStringList;
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select category from category;");

    while (qry->next()) {
        QString mystring = qry->value(0).toString();
        qStringList.push_back(mystring);
    }
    return qStringList;
}
/**
 * @brief Databasequery::getAllWordtypes Executes a query to get all wordtypes.
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @return all wordtypes from the table category as QStringList
 */
QStringList Databasequery::getAllWordtypes(DatabaseConnection &dbc){
    QStringList qStringList;
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select wordtype from wordtype;");

    while (qry->next()) {
        QString mystring = qry->value(0).toString();
        qStringList.push_back(mystring);
    }
    return qStringList;
}
/**
 * @brief Databasequery::getAllLanguages Executes a query to get all laguages.
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @return
 */
QStringList Databasequery::getAllLanguages(DatabaseConnection &dbc){
    QStringList qStringList;
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select language from languages order by language ASC;");

    while (qry->next()) {
        QString mystring = qry->value(0).toString();
        qStringList.push_back(mystring);
    }

    return qStringList;
}
/**
 * @brief Databasequery::getAllLanguagesExcept Executes a query to get all laguages except one.
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param qstring the exempted language
 * @return
 */
QStringList Databasequery::getAllLanguagesExcept(DatabaseConnection &dbc,QString qstring){
    QStringList qStringList;

    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->exec("select language from languages except select language from languages where language = '"+ qstring +"';");

    while (qry->next()) {
        QString mystring = qry->value(0).toString();
        qStringList.push_back(mystring);
    }

    return qStringList;
}
/**
 * @brief Databasequery::getIDCategory Executes a query to get the id of a category.
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param category the searched category
 * @return the id of the category
 */
int Databasequery::getIDCategory(DatabaseConnection &dbc,QString &category){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select categoryid from category where category = '"+ category +"';");
    qry->next();
    return qry->value(0).toInt();
}
/**
 * @brief Databasequery::getIDWordtype Executes a query to get the id of a wordtype.
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param wordtype the searched wordtype
 * @return the id of the wordtype
 */
int Databasequery::getIDWordtype(DatabaseConnection &dbc,QString &wordtype){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select wordtypeid from wordtype where wordtype = '"+ wordtype +"';");
    qry->next();
    return qry->value(0).toInt();
}
/**
 * @brief Databasequery::getIDLanguage Executes a query to get the id of a language.
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param language the searched language
 * @return the id of the laguage
 */
int Databasequery::getIDLanguage(DatabaseConnection &dbc,QString &language){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("select languagesid from languages where language = '"+ language +"';");
    qry->next();
    return qry->value(0).toInt();
}
/**
 * @brief Databasequery::checkCategory Checks whether the category already exists in the database.
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param category the category to be checked
 * @return true if exists
 */
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
/**
 * @brief Databasequery::checkWordtype Checks whether the wordtype already exists in the database.
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param wordtype the wordtype to be checked
 * @return true if exists
 */
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
/**
 * @brief Databasequery::checkLanguage Checks whether the language already exists in the database
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param language the language to be checked
 * @return true if exists
 */
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
/**
 * @brief Databasequery::addCategory
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param category the new category to be added
 */
void Databasequery::addCategory(DatabaseConnection &dbc,QString &category){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("INSERT INTO category (category) VALUES ('"+category+"');");
}
/**
 * @brief Databasequery::addWordtype
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param wordtype the new wordtype to be added
 */
void Databasequery::addWordtype(DatabaseConnection &dbc, QString &wordtype){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("INSERT INTO wordtype (wordtype) VALUES ('"+wordtype+"');");
}
/**
 * @brief Databasequery::addLanguage
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param language the new language to be added
 */
void Databasequery::addLanguage(DatabaseConnection &dbc, QString &language){
    QSqlQuery *qry = new QSqlQuery(dbc.db);
    qry->exec("INSERT INTO languages (language) VALUES ('"+ language +"');");
}
/**
 * @brief Databasequery::addWord Adds a word in the database
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param statement the words separated by a "," which are added to the database
 * @param wordtype the wordtype of the word
 * @param language the language of the word
 * @return the id of the added word
 */
int Databasequery::addWord(DatabaseConnection &dbc, const QString &statement,QString wordtype,QString language){
    int wordid;
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->prepare("INSERT INTO word (wordtypeid, languageid, word)"
                 "VALUES (:wordtypeid, :languageid, '{ "+ statement + " }') returning wordid;");
    qry->bindValue(":wordtypeid", getIDWordtype(dbc,wordtype));
    qry->bindValue(":languageid", getIDLanguage(dbc,language));
    qry->exec();
    qry->next();
    wordid = qry->value(0).toInt();
    return wordid;
}
/**
 * @brief Databasequery::addVocable Adds a vocable as a combination of two word ids and a category in the database.
 * The database must first be opened and then closed.
 * @param dbc the databaseconnection for the query
 * @param wordid1 the id of existing word in the database for the vocable
 * @param wordid2 the id of existing word in the database for the vocable
 * @param category the category of the vocable
 */
void Databasequery::addVocable(DatabaseConnection &dbc, int wordid1, int wordid2, QString category){
    QSqlQuery *qry = new QSqlQuery(dbc.db);

    qry->prepare("INSERT INTO vocable (wordid1,wordid2,categoryid)"
                 "VALUES (:word1,:word2,:category);");
    qry->bindValue(":word1",wordid1);
    qry->bindValue(":word2",wordid2);
    qry->bindValue(":category",getIDCategory(dbc,category));
    qry->exec();
}

/**
 * @brief Databasequery::updateQuizVocable Updates a vocable after the solution has been compared to the users answer
 * @param dbc the databaseconnection for the query
 * @param box the box in which the vocable be in
 * @param counter the counter to keep track whether to change the box the vocable is in
 * @param used the number of times the vocable has been used in the quiz
 * @param usedright the number of times the user has given the right answer
 * @param wordId1 the wordId of the first word of the vocable
 * @param wordId2 the wordId of the second word of the vocable
 */
void Databasequery::updateQuizVocable(DatabaseConnection &dbc, QString box, QString counter, QString used, QString usedright, QString wordId1, QString wordId2){
    QSqlQuery *query = new QSqlQuery(dbc.db);
    query->exec("update vocable set box= '" + box + "', counter = '" + counter + "', used = '" + used + "', usedright = '" + usedright + "' where wordid1 = '" + wordId1 +  "' and wordid2 = '" + wordId2 + "'");
}


Databasequery::~Databasequery()
{

}


