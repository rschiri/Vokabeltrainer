#ifndef ADDVOCABLE_H
#define ADDVOCABLE_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class addVocable;
}

class AddVocable : public QDialog
{
    Q_OBJECT

public:
    explicit AddVocable(QWidget *parent = 0);
    ~AddVocable();

private slots:
    void on_hinzufuegenButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::addVocable *ui;
};

#endif // ADDVOCABLE_H
