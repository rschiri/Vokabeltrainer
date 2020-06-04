#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QAbstractTableModel>

class MyTableModel : public QAbstractTableModel
{
public:
    enum class ColumnNames { ersteDeutsch, zweiteDeutsch, dritteDeutsch, ersteEnglisch, zweiteEnglisch, dritteEnglisch, Count };

    MyTableModel(const QVector<QVector<QString>>& modelData);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QVector<QVector<QString>> m_modelData;
};

#endif // MYTABLEMODEL_H
