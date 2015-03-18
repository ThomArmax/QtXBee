#include "xbeeparamstablemodel.h"
#include "xbeeparamitem.h"

//XBeeParamsTableModel::XBeeParamsTableModel(QObject *parent) :
//    Armax::Datamodels::ListModel(parent)
//{
//}

//XBeeParamsTableModel::XBeeParamsTableModel(Armax::Datamodels::AbstractListItem *proto, QObject *parent) :
//    Armax::Datamodels::ListModel(proto, parent)
//{
//}

XBeeParamsTableModel::XBeeParamsTableModel(XBee *bee, QObject *parent) :
    Armax::Datamodels::ListModel(parent),
    m_xbee(bee)
{
    m_prototype = new XBeeParamItem(this);

    connect(m_xbee, SIGNAL(DHChanged(const quint32)), this, SLOT(onDHChanged(const quint32)));
    connect(m_xbee, SIGNAL(DLChanged(const quint32)), this, SLOT(onDLChanged(const quint32)));
    connect(m_xbee, SIGNAL(MYChanged(const quint16)), this, SLOT(onMYChanged(const quint16)));
    connect(m_xbee, SIGNAL(MPChanged(const quint16)), this, SLOT(onMPChanged(const quint16)));
    connect(m_xbee, SIGNAL(NCChanged(const quint32)), this, SLOT(onNCChanged(const quint32)));
    connect(m_xbee, SIGNAL(SHChanged(const quint32)), this, SLOT(onSHChanged(const quint32)));
    connect(m_xbee, SIGNAL(SLChanged(const quint32)), this, SLOT(onSLChanged(const quint32)));
    connect(m_xbee, SIGNAL(NIChanged(const QString)), this, SLOT(onNIChanged(const QString)));
    connect(m_xbee, SIGNAL(SEChanged(const quint8)), this, SLOT(onSEChanged(const quint8)));
    connect(m_xbee, SIGNAL(DEChanged(const quint8)), this, SLOT(onDEChanged(const quint8)));
    connect(m_xbee, SIGNAL(CIChanged(const quint8)), this, SLOT(onCIChanged(const quint8)));
    connect(m_xbee, SIGNAL(TOChanged(const quint8)), this, SLOT(onTOChanged(const quint8)));
    connect(m_xbee, SIGNAL(NPChanged(const quint8)), this, SLOT(onNPChanged(const quint8)));
    connect(m_xbee, SIGNAL(DDChanged(const quint16)), this, SLOT(onDDChanged(const quint16)));
    connect(m_xbee, SIGNAL(CRChanged(const quint8)), this, SLOT(onCRChanged(const quint8)));

    appendRow(new XBeeParamItem("DH", QVariant(), this));
    appendRow(new XBeeParamItem("DL", QVariant(), this));
    appendRow(new XBeeParamItem("MY", QVariant(), this));
    appendRow(new XBeeParamItem("MP", QVariant(), this));
    appendRow(new XBeeParamItem("NC", QVariant(), this));
    appendRow(new XBeeParamItem("SH", QVariant(), this));
    appendRow(new XBeeParamItem("SL", QVariant(), this));
    appendRow(new XBeeParamItem("NI", QVariant(), this));
    appendRow(new XBeeParamItem("SE", QVariant(), this));
    appendRow(new XBeeParamItem("DE", QVariant(), this));
    appendRow(new XBeeParamItem("CI", QVariant(), this));
    appendRow(new XBeeParamItem("TO", QVariant(), this));
    appendRow(new XBeeParamItem("NP", QVariant(), this));
    appendRow(new XBeeParamItem("DD", QVariant(), this));
    appendRow(new XBeeParamItem("CR", QVariant(), this));
}

QHash<int,QByteArray> XBeeParamsTableModel::roleNames() const {
    return m_prototype->roleNames();
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

void XBeeParamsTableModel::onDHChanged(const quint32 dh) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("DH", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(dh);
    }
}
void XBeeParamsTableModel::onDLChanged(const quint32 dl) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("DL", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(dl);
    }
}
void XBeeParamsTableModel::onMYChanged(const quint16 my) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("MY", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(my);
    }
}
void XBeeParamsTableModel::onMPChanged(const quint16 mp) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("MP", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(mp);
    }
}
void XBeeParamsTableModel::onNCChanged(const quint32 nc) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("NC", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(nc);
    }
}
void XBeeParamsTableModel::onSHChanged(const quint32 sh) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("SH", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(sh);
    }
}
void XBeeParamsTableModel::onSLChanged(const quint32 sl) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("SL", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(sl);
    }
}
void XBeeParamsTableModel::onNIChanged(const QString & ni) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("NI", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(ni);
    }
}
void XBeeParamsTableModel::onSEChanged(const quint8 se) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("SE", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(se);
    }
}
void XBeeParamsTableModel::onDEChanged(const quint8 de) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("DE", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(de);
    }
}
void XBeeParamsTableModel::onCIChanged(const quint8 ci) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("CI", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(ci);
    }
}
void XBeeParamsTableModel::onTOChanged(const quint8 to) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("TO", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(to);
    }
}
void XBeeParamsTableModel::onNPChanged(const quint8 np) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("NP", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(np);
    }
}
void XBeeParamsTableModel::onDDChanged(const quint16 dd) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("DD", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(dd);
    }
}
void XBeeParamsTableModel::onCRChanged(const quint8 cr) {
    XBeeParamItem * item = NULL;
    item = qobject_cast<XBeeParamItem*>(find("CR", XBeeParamItem::NameRole));
    if(item) {
        item->setValue(cr);
    }
}
