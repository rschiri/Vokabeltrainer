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


    void on_ButtonAlle_clicked();

    void on_ButtonAuswahl_clicked();

    void on_Neu_Button_clicked();
    
    void on_actionKategorie_triggered();

    void on_actionOpen_triggered();

private:

    //Über das Objekt ui kann man dann später auf die ganzen Widgets in dem MainWindow zugreifen
    Ui::MainWindow *ui;

    void close();

};

#endif // MAINWINDOW_H
