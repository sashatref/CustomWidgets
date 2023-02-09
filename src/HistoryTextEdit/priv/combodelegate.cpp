#include "combodelegate.h"
#include "listitem.h"


ComboDelegate::ComboDelegate(QObject *_parent):
    QItemDelegate(_parent)
{

}

QSize ComboDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index) + QSize(5, 5);
}

QWidget *ComboDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
    QToolButton *btn = new QToolButton(parent);
    btn->setText(tr("Удалить"));
    btn->setToolTip(tr("Удалить"));
    btn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Trash2));
    btn->setAutoRaise(true);

    connect(btn, &QToolButton::clicked, this, [=]
    {
        emit removeRow(index.row());
    });

    m_lastWidget = btn;

    return btn;
}

void ComboDelegate::setEditorData(QWidget * /*editor*/, const QModelIndex &/*index*/) const
{

}

void ComboDelegate::setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const
{
    m_lastWidget = 0;
}

void ComboDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    const int width = option.rect.height();
    const int height = option.rect.height();
    const int x = option.rect.x() + option.rect.width() - width;
    const int y = option.rect.y();

    editor->setGeometry(x, y, width, height);
}

void ComboDelegate::closeEditorIfOpened()
{
    if(m_lastWidget)
    {
        closeEditor(m_lastWidget);
    }
}
