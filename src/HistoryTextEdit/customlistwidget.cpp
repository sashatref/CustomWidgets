#include "customlistwidget.h"

#include <QKeyEvent>

CustomListWidget::CustomListWidget(QWidget *_parent):
    QListWidget(_parent)
{

}


void CustomListWidget::keyPressEvent(QKeyEvent *event)
{
    QList<QListWidgetItem*> selected = selectedItems();

    if(event->key() == Qt::Key_Enter
            || event->key() == Qt::Key_Return
            || event->key() == Qt::Key_Space)
    {
        emit enterClicked(selected.size() ? selected.first() : 0);
        return;
    }

    if(event->key() == Qt::Key_Delete)
    {
        if(selected.size()) delete selected.first();
        return;
    }

    int nextRow = -1;

    if(selected.size())
    {
        int currentRow = row(selected.first());
        switch(event->key())
        {
        case Qt::Key_Up:
            nextRow = currentRow - 1;
            break;
        case Qt::Key_Down:
            nextRow = currentRow + 1;
            break;
        }
    } else
    {
        if(!count()) return;

        switch(event->key())
        {
        case Qt::Key_Up:
            nextRow = count() - 1;
            break;
        case Qt::Key_Down:
            nextRow = 0;
            break;
        }
    }

    if(nextRow > -1 && nextRow < count())
    {
        item(nextRow)->setSelected(true);
    }

    QListWidget::keyPressEvent(event);
}
