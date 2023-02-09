#ifndef MY_LINE_EDIT_H
#define MY_LINE_EDIT_H

#include <QLineEdit>
#include "../export.h"


class WIDGET_EXPORT MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MyLineEdit(QWidget *parent = 0);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif //MY_LINE_EDIT_H
