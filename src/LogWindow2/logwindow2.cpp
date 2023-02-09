#include "../project_pch.h"
#include "logwindow2.h"
#include "ui_logwindow2.h"
#include "priv/logwindow2p.h"
#include "priv/imagelistview.h"
#include "priv/delegate.h"

namespace CustomWidgetsQt
{

LogWindow2::LogWindow2(QWidget *parent) :
    ExtendedWidget          (parent),
    ui                      (new Ui::LogWindow2()),
    p                       (new LogWindow2P(this))
{
    ui->setupUi(this);

    ui->listView->setModel(p->m_model);
    ui->listView->setItemDelegate(new Delegate(this));

    initAll();
}

LogWindow2::~LogWindow2()
{
    delete ui;
}

QAction *LogWindow2::getClearAllAction()
{
    return ui->actionClearAll;
}


void LogWindow2::setTextWindowVisible(bool _isVisible)
{
    ui->textEdit->setVisible(_isVisible);
}

bool LogWindow2::getTextWindowVisible() const
{
    return ui->textEdit->isVisible();
}


void LogWindow2::addMessage(const QString &_text, QtMsgType _logLevel)
{
    p->m_model->addMessage(_text, _logLevel, QVariant());
}

void LogWindow2::addMessage(const QString &_text, QtMsgType _logLevel, const QVariant &_userData)
{
    p->m_model->addMessage(_text, _logLevel, _userData);
}

void LogWindow2::scrollToBottom()
{
    ui->listView->scrollToBottom();
}


void LogWindow2::setUpdateInterval(int _ms)
{
    p->m_timer->setInterval(_ms);
}

int LogWindow2::getUpdateInterval() const
{
    return p->m_timer->interval();
}

void LogWindow2::resetUpdateInterval()
{
    setUpdateInterval(300);
}


void LogWindow2::clear()
{
    p->m_model->clearAll();
    ui->textEdit->clear();
    p->m_isLastSelected = true;
}

void LogWindow2::setBackgroundPixmap(const QPixmap &_pixmap)
{
    ui->listView->setBackgroundPixmap(_pixmap);
}

QPixmap LogWindow2::getBackgroundPixmap() const
{
    return ui->listView->getBackgorundPixmap();
}

void LogWindow2::setImageOpacity(double _opacity)
{
    ui->listView->setImageOpacity(_opacity);
}

double LogWindow2::getImageOpacity() const
{
    return ui->listView->getImageOpacity();
}

void LogWindow2::setImagePadding(const QSize &_size)
{
    ui->listView->setImagePadding(_size);
}

QSize LogWindow2::getImagePadding() const
{
    return ui->listView->getImagePadding();
}

void LogWindow2::setMaximumMsgCount(int _count)
{
    p->m_model->maximumMsgCount = _count;
}

int LogWindow2::getMaximumMsgCount() const
{
    return p->m_model->maximumMsgCount;
}

void LogWindow2::resetMaximumMsgCount()
{
    setMaximumMsgCount(1000000);
}

void LogWindow2::setMsgOverhead(int _count)
{
    p->m_model->msgCheckOverhead = _count;
}

int LogWindow2::getMsgOverhead() const
{
    return p->m_model->msgCheckOverhead;
}

void LogWindow2::resetMsgOverhead()
{
    setMsgOverhead(getMaximumMsgCount() / 10);
}

QString LogWindow2::getAllText() const
{
    return p->m_model->makeAllText();
}

void LogWindow2::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    {
        QModelIndexList selected = ui->listView->selectionModel()->selectedRows();
        if(selected.size() == 1)
        {
            QVariant data = p->m_model->data(selected.first(), Qt::UserRole);
            emit addSingleRowContextMenu(&menu, data);
        }
    }

    menu.addAction(ui->actionCopySelected);
    menu.addAction(ui->actionCopyAll);
    menu.addSeparator();
    menu.addAction(ui->actionScrolToStart);
    menu.addAction(ui->actionScrollToEnd);
    menu.addSeparator();
    menu.addAction(ui->actionSelectAll);
    menu.addAction(ui->actionUnselectAll);
    menu.addSeparator();
    menu.addAction(ui->actionClearAll);
    menu.addSeparator();
    menu.addAction(ui->actionShowTextDetail);
    menu.addAction(ui->actionWordWrap);
    menu.addSeparator();
    menu.addAction(ui->actionConfigStyle);

    menu.exec(event->globalPos());
}


void LogWindow2::onSelectAllSlot()
{
    ui->listView->selectAll();
}

void LogWindow2::onUnselectAllSlot()
{
    ui->listView->clearSelection();
}

void LogWindow2::onClearAllSlot()
{
    clear();
}

void LogWindow2::onScrollToEndSlot()
{
    ui->listView->scrollToBottom();
    ui->listView->setCurrentIndex(p->m_model->getLastRow());
}

void LogWindow2::onScrollToStartSlot()
{
    ui->listView->scrollToTop();
    ui->listView->setCurrentIndex(p->m_model->getFirstRow());
}

void LogWindow2::onCopySelectedSlot()
{
    QModelIndexList selected = ui->listView->selectionModel()->selectedRows();

    QList<int> rows;

    for(int i = 0; i < selected.size(); i++)
    {
        rows << selected[i].row();
    }

    qApp->clipboard()->setText(p->m_model->makeText(rows));
}

void LogWindow2::onCopyAllSlot()
{
    qApp->clipboard()->setText(p->m_model->makeAllText());
}

void LogWindow2::on_actionShowTextDetail_triggered(bool checked)
{
    ui->editorWidget->setVisible(checked);
}

void LogWindow2::on_actionWordWrap_triggered(bool checked)
{
    ui->textEdit->setWordWrapMode(checked ? QTextOption::WordWrap : QTextOption::NoWrap);
}

void LogWindow2::updateLanguage()
{
    ui->retranslateUi(this);
}

void LogWindow2::updateStyle()
{
    ui->actionClearAll->setIcon(IconsEnum::getIcon(IconsEnum::SP_Erase1));
    ui->actionCopyAll->setIcon(IconsEnum::getIcon(IconsEnum::SP_Copy1));
    ui->actionCopySelected->setIcon(IconsEnum::getIcon(IconsEnum::SP_Copy1));
    ui->actionScrolToStart->setIcon(IconsEnum::getIcon(IconsEnum::SP_ArrowUp1));
    ui->actionScrollToEnd->setIcon(IconsEnum::getIcon(IconsEnum::SP_ArrowDown1));
    ui->actionConfigStyle->setIcon(IconsEnum::getIcon(IconsEnum::SP_Services1));
}

void LogWindow2::initUiComponets()
{
    ui->editorWidget->setVisible(false);

    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->actionShowTextDetail->setChecked(false);
    ui->actionWordWrap->setChecked(true);

    ui->fontSizeCombo->addItems({ "8", "10", "12", "14", "18", "24", "36"});
}

void LogWindow2::initConnections()
{
    connect(ui->actionSelectAll, &QAction::triggered, this, &LogWindow2::onSelectAllSlot);
    connect(ui->actionUnselectAll, &QAction::triggered, this, &LogWindow2::onUnselectAllSlot);
    connect(ui->actionClearAll, &QAction::triggered, this, &LogWindow2::onClearAllSlot);
    connect(ui->actionCopyAll, &QAction::triggered, this, &LogWindow2::onCopyAllSlot);
    connect(ui->actionCopySelected, &QAction::triggered, this, &LogWindow2::onCopySelectedSlot);
    connect(ui->actionScrollToEnd, &QAction::triggered, this, &LogWindow2::onScrollToEndSlot);
    connect(ui->actionScrolToStart, &QAction::triggered, this, &LogWindow2::onScrollToStartSlot);
    connect(ui->actionConfigStyle, &QAction::triggered, p, &LogWindow2P::showConfigStyleDialog);

    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged, p, &LogWindow2P::currentChangedSlot);

    connect(ui->fontSizeCombo, &QComboBox::currentTextChanged, p, &LogWindow2P::fontSizeChanged);

    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged,
            p, &LogWindow2P::selectedItemChangedSlot);

    connect(ui->listView, &ImageListView::endKeyPressed, this, &LogWindow2::onScrollToEndSlot);
    connect(ui->listView, &ImageListView::homeKeyPressed, this, &LogWindow2::onScrollToStartSlot);
    connect(ui->listView, &ImageListView::copyAllPressed, this, &LogWindow2::onCopyAllSlot);
    connect(ui->listView, &ImageListView::copySelectedPressed, this, &LogWindow2::onCopySelectedSlot);
    connect(ui->listView, &ImageListView::deleteAllPressed, this, &LogWindow2::clear);
    connect(ui->listView, &ImageListView::selectAllPressed, this, &LogWindow2::onSelectAllSlot);
}

void LogWindow2::loadState(const LayoutSaver &_saver)
{
    if(_saver.contains("styleConfig"))
    {
        p->m_model->m_configMap = _saver["styleConfig"].value<ItemSettingsMap>();
    }

    ui->fontSizeCombo->setCurrentText(_saver["fontSize"].toString());

}

void LogWindow2::saveState(LayoutSaver &_saver) const
{
    _saver["styleConfig"] = QVariant::fromValue(p->m_model->m_configMap);
    _saver["fontSize"] = ui->fontSizeCombo->currentText();
}

}


