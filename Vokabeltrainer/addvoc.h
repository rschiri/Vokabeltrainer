#ifndef ADDVOC_H
#define ADDVOC_H

#include <QDialog>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class AddVoc;
}

class AddVoc : public QDialog
{
    Q_OBJECT

public:
    explicit AddVoc(QWidget *parent = nullptr);
    ~AddVoc();

private:
    Ui::AddVoc *ui;
    QVBoxLayout *layout;
    QWidget *widget;

};

#endif // ADDVOC_H
