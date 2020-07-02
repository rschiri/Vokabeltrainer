#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <databaseconnection.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_Neu_Button_clicked();
    
    void on_actionKategorie_triggered();

    void on_actionOpen_triggered();

    void on_buttonTestVocabulary_clicked();

    void on_actionSprache_triggered();

    void on_actionWortart_triggered();

    void on_comboBoxSourceLanguage_currentTextChanged(const QString &arg1);

    void on_buttonCompare_clicked();

    void on_buttonTestNewVocabulary_clicked();

    QString clearUpString(QString word);

    int clearUpInt(int number);

    QString clearStringFromCharacters(QString word);
    
    
private:

    Ui::MainWindow *ui;
    QString word1;
    QString word2;
    int box;
    int counter;
    int categoryid;
    int used;
    int usedright;
    QString sourceLanguage;
    QString destinationLanguage;
    QString vocableQuiz;
    int wordVocableId1;
    int wordVocableId2;
    void close();

};

#endif // MAINWINDOW_H
