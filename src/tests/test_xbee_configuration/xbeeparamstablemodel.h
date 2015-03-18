#ifndef XBEEPARAMSTABLEMODEL_H
#define XBEEPARAMSTABLEMODEL_H

#include <QObject>
#include <QtArmax-1.0/datamodels/listmodel.h>
#include "xbee.h"

class XBeeParamsTableModel : public Armax::Datamodels::ListModel
{
    Q_OBJECT
public:
//    explicit XBeeParamsTableModel(QObject *parent = 0);
//    XBeeParamsTableModel(Armax::Datamodels::AbstractListItem * proto, QObject * parent = 0);
    XBeeParamsTableModel(XBee * bee, QObject * parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int,QByteArray> roleNames() const;

signals:

public slots:

private slots:
    void onDHChanged(const quint32 dh);
    void onDLChanged(const quint32 dl);
    void onMYChanged(const quint16 my);
    void onMPChanged(const quint16 mp);
    void onNCChanged(const quint32 nc);
    void onSHChanged(const quint32 sh);
    void onSLChanged(const quint32 sl);
    void onNIChanged(const QString & ni);
    void onSEChanged(const quint8 se);
    void onDEChanged(const quint8 de);
    void onCIChanged(const quint8 ci);
    void onTOChanged(const quint8 to);
    void onNPChanged(const quint8 np);
    void onDDChanged(const quint16 dd);
    void onCRChanged(const quint8 cr);

private:
    XBee * m_xbee;

};

#endif // XBEEPARAMSTABLEMODEL_H
