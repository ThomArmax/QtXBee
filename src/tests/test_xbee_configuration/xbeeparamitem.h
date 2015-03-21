#ifndef XBEEPARAMITEM_H
#define XBEEPARAMITEM_H

#include <QObject>
#include <QtArmax-1.0/datamodels/listmodel.h>

#include "atcommand.h"

class XBeeParamItem : public Armax::Datamodels::AbstractListItem
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = /*Qt::UserRole+1*/0,
        AtCommandRole,
        ValueRole
    };

    explicit XBeeParamItem(QObject *parent = 0);
    XBeeParamItem(const QString & name, const QVariant & value, QObject * parent = 0);

    QString name() const { return m_name; }
    QVariant value() const { return m_value; }
    ATCommand::ATCommandType atCommand() const { return m_at; }

    bool setName(const QString & name);
    bool setValue(const QVariant & value);
    bool setAtCommand(const ATCommand::ATCommandType at);

    virtual QHash<int,QByteArray> roleNames() const;
    virtual bool setData(const QVariant &value, int role);
    virtual QVariant data(int role) const;

signals:
    void nameChanged(QString name);
    void valueChanged(QVariant value);

public slots:

protected:
    QString m_name;
    QVariant m_value;
    ATCommand::ATCommandType m_at;
};

#endif // XBEEPARAMITEM_H
