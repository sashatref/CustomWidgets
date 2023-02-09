#pragma once

#include <QWidget>

namespace Ui {
class ListItem;
}

namespace CustomWidgetsQt
{

class ListItem : public QWidget
{
    Q_OBJECT
public:
    explicit ListItem(QWidget *parent = 0);
    ~ListItem();

    void setText(const QString &_text);

signals:
    void removeButtonClicked();

private:
    Ui::ListItem *ui;
};

}
