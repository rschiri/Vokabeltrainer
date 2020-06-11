#ifndef ADDVOCABLE_H
#define ADDVOCABLE_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class addVocable;
}

class addVocable : public QDialog
{
    Q_OBJECT

public:
    explicit addVocable(QWidget *parent = 0);
    ~addVocable();

private slots:
    void on_hinzufuegenButton_clicked();

private:
    Ui::addVocable *ui;
};

#endif // ADDVOCABLE_H
