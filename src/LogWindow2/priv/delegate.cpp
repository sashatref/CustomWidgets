#include "delegate.h"




Delegate::Delegate(QObject *_parent):
    QStyledItemDelegate(_parent)
{

}

QSize Delegate::sizeHint(const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    return QSize(18, 18);
}
