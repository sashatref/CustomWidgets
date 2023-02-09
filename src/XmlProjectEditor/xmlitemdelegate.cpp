#include "../project_pch.h"
#include "xmlitemdelegate.h"

#include "varianmapeditor.h"


QWidget *XmlItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        return new QLineEdit(parent);
    } else if(index.column() == 1)
    {
        return new VarianMapEditor(parent);
    } else if(index.column() == 2)
    {
        QTextEdit *editor = new QTextEdit();
        editor->setWindowTitle(tr("Редактор текста"));
        editor->setReadOnly(false);
        editor->setWordWrapMode(QTextOption::NoWrap);
        editor->setFrameShape(QFrame::Box);
        editor->setFrameShadow(QFrame::Plain);
        QFont tempFont = editor->font();
        tempFont.setBold(true);
        editor->setFont(tempFont);
        return editor;
    }

    return 0;
}

void XmlItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(index.data(Qt::DisplayRole).toString());
    } else if(index.column() == 1)
    {
        VarianMapEditor *varianEditor = static_cast<VarianMapEditor*>(editor);
        varianEditor->setVariantMap(index.data(Qt::UserRole).toMap());
    } else if(index.column() == 2)
    {
        QTextEdit *textEdit = static_cast<QTextEdit*>(editor);
        textEdit->setPlainText(index.data(Qt::DisplayRole).toString());
    }
}

void XmlItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        model->setData(index, lineEdit->text());
    } else if(index.column() == 1)
    {
        VarianMapEditor *mapEditor = static_cast<VarianMapEditor*>(editor);
        QVariantMap map = mapEditor->getVariantMap();
        model->setData(index, map, Qt::UserRole);
        model->setData(index, variantMapToString(map), Qt::DisplayRole);

    } else if(index.column() == 2)
    {
        QTextEdit *textEdit = static_cast<QTextEdit*>(editor);
        model->setData(index, textEdit->toPlainText(), Qt::DisplayRole);
    }
}

void XmlItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);

    if(index.column() == 0)
    {

    } else if(index.column() == 1)
    {
        WidgetHelper::setWidgetOnScreenCenter(editor, editor->parentWidget(), 600,600);
    } else if(index.column() == 2)
    {
        WidgetHelper::setWidgetOnScreenCenter(editor, editor->parentWidget(), 500, 500);
    }
}

QString XmlItemDelegate::variantMapToString(const QVariantMap &_map)
{
    QStringList items;

    for(int i = 0 ; i < _map.keys().size(); i++)
    {
        QString key = _map.keys().at(i);
        QString value = _map[key].toString();

        items.append(QString("%1 = %2").arg(key).arg(value));
    }

    return items.join(" | ");
}

QSize XmlItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index) + QSize(5, 5);
}
