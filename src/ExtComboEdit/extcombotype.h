#ifndef EXT_COMBO_TYPE_H
#define EXT_COMBO_TYPE_H

#include <QDataStream>
#include <QStringList>
#include <QVariantMap>

class ExtComboType
{
public:
    ExtComboType(const QMap<int, QString> &_valuesList = QMap<int, QString>(), int _type = -1) :
        m_valuesList(_valuesList),
        m_type(_type)
    {}

    ExtComboType(const ExtComboType &other)
    {
        m_valuesList    = other.m_valuesList;
        m_type          = other.m_type;
    }

    ExtComboType & operator = (const ExtComboType & other)
    {
        m_valuesList    = other.m_valuesList;
        m_type          = other.m_type;
        return *this;
    }

    void init(const QVector<QVariant> &_values, const QString &_nameProp, const QString &_idProp)
    {
        m_valuesList.clear();

        for(int i = 0; i < _values.size(); i++)
        {
            QObject *obj = _values[i].value<QObject*>();
            if(obj)
            {
                QString name = obj->property(_nameProp.toStdString().c_str()).toString();
                int id = obj->property(_idProp.toStdString().c_str()).toInt();
                m_valuesList[id] = name;
            }
        }
    }

    QMap<int, QString> m_valuesList;
    int m_type;
};

Q_DECLARE_METATYPE(ExtComboType)

#endif //EXT_COMBO_TYPE_H
