#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    :QAbstractTableModel(parent)
{
//    m_tableModel = new TableModel;
}

TableModel::~TableModel()
{
//    delete m_tableModel;
//    m_tableModel = nullptr;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }
    return index.data(role);
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
//    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index);//默认
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return headerData(section, orientation, role);
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
    {
        return 0;
    }
    return rowCount(parent);
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
    {
        return 0;
    }
    return columnCount(parent);
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = setData(index, value, role);
    if(result)
    {
        emit dataChanged(index,index    );
    }
    return result;
}

bool TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    bool result = setHeaderData(section, orientation, value, role);
    if(result)
    {
        emit headerDataChanged(orientation, section, section);
    }
    return result;
}

bool TableModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success = false;

    beginInsertColumns(parent, position, position + columns - 1);
    success = insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TableModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success = false;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = removeColumns(position, columns);
    endRemoveColumns();

    return success;
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    bool success = false;

    beginInsertRows(parent, position, position + rows - 1);
    success = insertRows(position, rows, parent);
    endInsertRows();

    return success;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    bool success = false;

    beginRemoveRows(parent, position, position + rows - 1);
    success = removeRows(position, rows);
    endRemoveRows();

    return success;
}

QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
    {
        return QModelIndex();
    }

    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    return createIndex(row, column, (void*)nullptr);
}
