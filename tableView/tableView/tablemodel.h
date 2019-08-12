#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = Q_NULLPTR);
    ~TableModel();

public: // overrider 重写父类
    /** 获取数据 */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    /** 获取标志, 是否可编辑，拖拽等 */
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    /** 头标题 */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    /** rowCount */
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    /** columnCount */
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    /** 设置数据 */
    bool setData(const QModelIndex &index, const QVariant &value,
        int role = Qt::EditRole) Q_DECL_OVERRIDE;

    /** 设置头 */
    bool setHeaderData(int section, Qt::Orientation orientation,
        const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    /** 插入列 */
    bool insertColumns(int position, int columns,
        const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    /** 移除列 */
    bool removeColumns(int position, int columns,
        const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    /** 插入行 */
    bool insertRows(int position, int rows,
        const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    /** 移除行 */
    bool removeRows(int position, int rows,
        const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    /** 获取索引 */
    QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;

private:
//    QAbstractTableModel *m_tableModel = nullptr;
};

#endif // TABLEMODEL_H
