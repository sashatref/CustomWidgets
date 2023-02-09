#ifndef CUSTOM_LIST_WIDGET_ITEM_H
#define CUSTOM_LIST_WIDGET_ITEM_H

#include <QListWidgetItem>
#include "project_pch.h"

class CustomListWidgetItem : public QListWidgetItem
{
public:
    CustomListWidgetItem(const QString &_text, const QString &_sortProperty = "") :
        QListWidgetItem(_text),
        m_sortProperty(_sortProperty)
    {

    }
    void setSortProperty(const QString &_sortProperty)
    {
        m_sortProperty = _sortProperty;
    }

    const QString &getSortProperty() const
    {
        return m_sortProperty;
    }

    virtual QListWidgetItem *clone() const
    {
        CustomListWidgetItem *item = new CustomListWidgetItem(*this);
        item->setSortProperty(m_sortProperty);
        return item;
    }

protected:
    bool operator <(const QListWidgetItem &other) const
    {
        QVariant var1 = VariantHelper::getProperty(data(Qt::UserRole), m_sortProperty);
        QVariant var2 = VariantHelper::getProperty(other.data(Qt::UserRole), m_sortProperty);

        if(var1.isValid() && var2.isValid())
        {
            return var1 < var2;
        }

        return QListWidgetItem::operator <(other);
    }

    QString m_sortProperty;
};

#endif //CUSTOM_LIST_WIDGET_ITEM_H
