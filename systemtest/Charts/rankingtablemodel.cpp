
#include "rankingtablemodel.h"
#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtCore/QRandomGenerator>
#include <QtGui/QColor>

RankingTableModel::RankingTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 3;
    m_rowCount = 11;

    // m_data
    for (int i = 0; i < m_rowCount; i++) {
        QVector<QString>* dataVec = new QVector<QString>(m_columnCount);
        dataVec->replace(0, "99");
        dataVec->replace(1, "进程");
        dataVec->replace(2, QString("%1").arg(100-i*6));

        m_data.append(dataVec);
    }

}

RankingTableModel::~RankingTableModel()
{
    qDeleteAll(m_data);
}

int RankingTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

int RankingTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant RankingTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return "进程ID";
        case 1:
            return "进程名称";
        case 2:
            return "占比%";
        default:
            return "";
        }
    }
    else
        return QString("%1").arg(section + 1);
}

QVariant RankingTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::EditRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::BackgroundRole) {
        for (const QRect &rect : m_mapping) {
            if (rect.contains(index.column(), index.row()))
                return QColor(m_mapping.key(rect));
        }

        // cell not mapped return white color
        return QColor(Qt::white);
    }
    return QVariant();
}

QVariant RankingTableModel::cellData(int row, int column) {
    return m_data[row]->at(column);
}

bool RankingTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_data[index.row()]->replace(index.column(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags RankingTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void RankingTableModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}

void RankingTableModel::setRowData(int row, QStringList dataList) {
    for (int i=0; i<m_columnCount; i++) {
        m_data[row]->replace(i, dataList[i]);
    }
}

void RankingTableModel::refresh() {
    QModelIndex start = index(0, 0);
    QModelIndex end = index(m_rowCount - 1, m_columnCount - 1);

    emit dataChanged(start, end);
}
