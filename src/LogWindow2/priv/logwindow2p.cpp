#include "logwindow2p.h"
#include "ui_logwindow2.h"
#include "itemsettingsmapeditor.h"
#include "imagelistview.h"

namespace CustomWidgetsQt
{

LogWindow2P::LogWindow2P(LogWindow2 *_parent):
    QObject(_parent),
    q(_parent),
    m_model(new ListViewModel(this))
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &LogWindow2P::timeoutSlot);
    m_timer->setInterval(300);
    m_timer->start();
}


void LogWindow2P::selectedItemChangedSlot(const QModelIndex &current, const QModelIndex &/*previous*/)
{
    m_isLastSelected = current == m_model->getLastRow();
}

void LogWindow2P::timeoutSlot()
{
    QModelIndexList selected = q->ui->listView->selectionModel()->selectedIndexes(); //сохраняем список выделенных элементов

    if(m_model->updateModel())
    {
        //если был выбран последний элемент, то сбрасываем выделение и добавляем новый последний элемент списка
        if(m_isLastSelected)
        {
            selected.clear();
            q->ui->listView->setCurrentIndex(m_model->getLastRow());
        }

        //активируем выделение строк
        for(auto &item : selected)
        {
            q->ui->listView->selectionModel()->select(item, QItemSelectionModel::Select);
        }
    }
}

void LogWindow2P::currentChangedSlot(const QModelIndex &current, const QModelIndex &/*previous*/)
{
    q->ui->textEdit->setText(current.data(Qt::DisplayRole).toString());
}

void LogWindow2P::showConfigStyleDialog()
{
    ItemSettingsMapEditor dialog(q);
    dialog.setSettingsMap(m_model->m_configMap);

    if(dialog.exec() == QDialog::Accepted)
    {
        m_model->m_configMap = dialog.getSettingsMap();
        q->ui->listView->update();
    }
}

void LogWindow2P::fontSizeChanged(const QString &_text)
{
    bool isOk = false;
    const int size = _text.toInt(&isOk);
    if(isOk)
    {
        QFont f = q->ui->textEdit->font();
        f.setPointSize(size);
        q->ui->textEdit->setFont(f);
    }
}



}



