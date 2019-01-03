

#ifndef RANKINGTABLEMODEL_H
#define RANKINGTABLEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>

class RankingTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RankingTableModel(QObject *parent = 0);
    virtual ~RankingTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void addMapping(QString color, QRect area);
    void clearMapping() { m_mapping.clear(); }

    void setRowData(int row, QStringList dataList);
    void refresh();

    QVariant cellData(int row, int column);

private:
    QList<QVector<QString> * > m_data;
    QHash<QString, QRect> m_mapping;
    int m_columnCount;
    int m_rowCount;
};

#endif // RANKINGTABLEMODEL_H
