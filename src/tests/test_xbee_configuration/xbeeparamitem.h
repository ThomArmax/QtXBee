#ifndef XBEEPARAMITEM_H
#define XBEEPARAMITEM_H

#include <QObject>
#include <QtArmax-1.0/datamodels/listmodel.h>

class XBeeParamItem : public Armax::Datamodels::AbstractListItem
{
    Q_OBJECT
public:
    enum Roles {
        NameRole,
        ValueRole
    };

    explicit XBeeParamItem(QObject *parent = 0);
    XBeeParamItem(const QString & name, const QVariant & value, QObject * parent = 0);

    QString name() const { return m_name; }
    QVariant value() const { return m_value; }

    bool setName(const QString & name);
    bool setValue(const QVariant & value);

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
};

#endif // XBEEPARAMITEM_H
