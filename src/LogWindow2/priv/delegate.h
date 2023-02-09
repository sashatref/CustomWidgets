#ifndef DELEGATE_H
#define DELEGATE_H


class Delegate : public QStyledItemDelegate
{
public:
    Delegate(QObject *_parent);
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DELEGATE_H
