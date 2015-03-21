#include "xbeeparamitem.h"

XBeeParamItem::XBeeParamItem(QObject *parent) :
    Armax::Datamodels::AbstractListItem(parent),
    m_name(QString()),
    m_value(QVariant()),
    m_at(ATCommand::Command_Undefined)
{
}

XBeeParamItem::XBeeParamItem(const QString &name, const QVariant &value, QObject *parent) :
    Armax::Datamodels::AbstractListItem(parent),
    m_name(name),
    m_value(value),
    m_at(ATCommand::Command_Undefined)
{
}

QHash<int,QByteArray> XBeeParamItem::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ValueRole] = "value";
    roles[AtCommandRole] = "at";
    return roles;
}

bool XBeeParamItem::setData(const QVariant &value, int role)
{
    switch(role) {
    case NameRole: return setName(value.toString());
    case ValueRole: return setValue(value);
    case AtCommandRole: return setAtCommand((ATCommand::ATCommandType)value.toInt());
    }
    return false;
}

QVariant XBeeParamItem::data(int role) const
{
    switch(role) {
    case NameRole: return name();
    case ValueRole: return value();
    case AtCommandRole: return QString::number(atCommand(), 16).prepend("0x");
    }
    return QVariant();
}

bool XBeeParamItem::setName(const QString &name)
{
    if(m_name != name) {
        m_name = name;
        emit nameChanged(m_name);
        emit dataChanged(NameRole);
        return true;
    }
    return false;
}

bool XBeeParamItem::setValue(const QVariant &value) {
    if(m_value != value) {
        m_value = value;
        emit valueChanged(m_value);
        emit dataChanged(ValueRole);
        return true;
    }
    return false;
}

bool XBeeParamItem::setAtCommand(const ATCommand::ATCommandType at) {
    if(m_at != at) {
        m_at = at;
        emit valueChanged(m_at);
        emit dataChanged(AtCommandRole);
        return true;
    }
    return false;
}
