#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QListWidget>
#include "../export.h"

class WIDGET_EXPORT CustomListWidget : public QListWidget
{
    Q_OBJECT
public:
    CustomListWidget(QWidget *_parent = 0);

signals:
    void enterClicked(QListWidgetItem *_selected);

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // CUSTOMLISTWIDGET_H
