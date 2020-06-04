#include "mytablemodel.h"

MyTableModel::MyTableModel(const QVector<QVector<QString> > &modelData) : m_modelData(modelData)
{

}

// Be sure to enable C++17 for Attribute [[maybe_unused]] to work
int MyTableModel::rowCount([[maybe_unused]]const QModelIndex &parent) const
{
    return m_modelData.size();
}

int MyTableModel::columnCount([[maybe_unused]]const QModelIndex &parent) const
{
    return static_cast<int>(ColumnNames::Count);
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    return m_modelData[index.row()][index.column()];
}


QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation != Qt::Horizontal)
        return QVariant();

    switch (static_cast<ColumnNames>(section)) {
    case ColumnNames::ersteDeutsch:
        return "1. deutsche Bedeutung";
    case ColumnNames::zweiteDeutsch:
        return "2. deutsche Bedeutung";
    case ColumnNames::dritteDeutsch:
        return "3. deutsche Bedeutung";
    case ColumnNames::ersteEnglisch:
        return "1. englische Bedeutung";
    case ColumnNames::zweiteEnglisch:
        return "2. englische Bedeutung";
    case ColumnNames::dritteEnglisch:
        return "3. englische Bedeutung";
    default: break;
    }

    return QVariant();
}
