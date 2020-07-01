#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_vocableOption1_clicked();

    void on_vocableOption2_clicked();

    void on_vocableOption3_clicked();

    int getChosenVocableOption();

    void on_actionSprache_triggered();

    void on_actionWortart_triggered();

private:

    //Über das Objekt ui kann man dann später auf die ganzen Widgets in dem MainWindow zugreifen
    Ui::MainWindow *ui;
    int rightOption;
    void close();

};

#endif // MAINWINDOW_H
