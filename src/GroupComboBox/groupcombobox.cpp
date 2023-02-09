#include "project_pch.h"
#include "groupcombobox.h"

class ComboBoxDelegate : public QItemDelegate
{
public:
    ComboBoxDelegate(QObject *_parent = 0):
        QItemDelegate(_parent)
    { }

public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if(index.data(Qt::AccessibleDescriptionRole).toString() == QLatin1String("separator"))
        {
            painter->setPen(Qt::gray);
            painter->drawLine(option.rect.left(), option.rect.center().y(), option.rect.right(), option.rect.center().y());
        }
        else if(index.data(Qt::AccessibleDescriptionRole).toString() == QLatin1String("parent"))
        {
            QStyleOptionViewItem parentOption = option;
            parentOption.state |= QStyle::State_Enabled;
            QItemDelegate::paint( painter, parentOption, index );
        }
        else if ( index.data(Qt::AccessibleDescriptionRole).toString() == QLatin1String( "child" ) ) {
            QStyleOptionViewItem childOption = option;
            int indent = option.fontMetrics.width( QString( 4, QChar( ' ' ) ) );
            childOption.rect.adjust( indent, 0, 0, 0 );
            childOption.textElideMode = Qt::ElideNone;
            QItemDelegate::paint( painter, childOption, index );
        }
        else
        {
            QItemDelegate::paint(painter, option, index);
        }
    }

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QString type = index.data(Qt::AccessibleDescriptionRole).toString();
            if(type == QLatin1String("separator"))
                return QSize(0, 10);
            return QItemDelegate::sizeHint( option, index );
    }
};

GroupComboBox::GroupComboBox(QWidget *_parent):
    QComboBox(_parent)
{
    setItemDelegate(new ComboBoxDelegate(this));
}

void GroupComboBox::addParentItem(const QString &text)
{
    QStandardItem* item = new QStandardItem( text );
    item->setFlags( item->flags() & ~( Qt::ItemIsEnabled | Qt::ItemIsSelectable ) );
    item->setData( "parent", Qt::AccessibleDescriptionRole );

    QFont font = item->font();
    font.setBold( true );
    item->setFont( font );

    QStandardItemModel* itemModel = (QStandardItemModel*)model();
    itemModel->appendRow( item );
}

void GroupComboBox::addChildItem(const QString &text, const QVariant &data)
{
    QStandardItem* item = new QStandardItem( text + QString( 4, QChar( ' ' ) ) );
    item->setData( data, Qt::UserRole );
    item->setData( "child", Qt::AccessibleDescriptionRole );

    QStandardItemModel* itemModel = (QStandardItemModel*)model();
    itemModel->appendRow( item );
}
