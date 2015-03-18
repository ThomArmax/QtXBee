#ifndef XBEEPARAMSTABLEMODEL_H
#define XBEEPARAMSTABLEMODEL_H

#include <QObject>
#include <QtArmax-1.0/datamodels/listmodel.h>

class XBeeParamsTableModel : public Armax::Datamodels::ListModel
{
    Q_OBJECT
public:
    explicit XBeeParamsTableModel(QObject *parent = 0);
    XBeeParamsTableModel(Armax::Datamodels::AbstractListItem * proto, QObject * parent = 0);

    QVariant data(const QModelIndex &index, int role) const;

signals:

public slots:

};

#endif // XBEEPARAMSTABLEMODEL_H
