#ifndef LOGWINDOW2P_H
#define LOGWINDOW2P_H

#include "../logwindow2.h"
#include "listviewmodel.h"

namespace CustomWidgetsQt
{

class LogWindow2;
class LogWindow2P : public QObject
{
    Q_OBJECT
    LogWindow2 *q;
public:
    LogWindow2P(LogWindow2 *_parent);

    ListViewModel *m_model;
    QTimer *m_timer;

    bool m_isLastSelected = true;

public slots:
    void selectedItemChangedSlot(const QModelIndex &current, const QModelIndex &previous);
    void timeoutSlot();
    void currentChangedSlot(const QModelIndex &current, const QModelIndex &previous);

    void showConfigStyleDialog();

    void fontSizeChanged(const QString &_text);
};

}

#endif // LOGWINDOW2P_H
