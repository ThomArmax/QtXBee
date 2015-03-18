#include "xbeeparamstablemodel.h"

XBeeParamsTableModel::XBeeParamsTableModel(QObject *parent) :
    Armax::Datamodels::ListModel(parent)
{
}

XBeeParamsTableModel::XBeeParamsTableModel(Armax::Datamodels::AbstractListItem *proto, QObject *parent) :
    Armax::Datamodels::ListModel(proto, parent)
{
}

QVariant XBeeParamsTableModel::data(const QModelIndex &index, int role) const
Q_DECL_OVERRIDE
{
    if(index.row() < 0 || index.row() >= m_list.size()) {
        return QVariant();
    }
    if(index.column() < 0 || index.column() >= m_prototype->roleNames().size())
        return QVariant();

    if(role == Qt::DisplayRole)
        return m_list.at(index.row())->data(index.column());

    return m_list.at(index.row())->data(role);
}
