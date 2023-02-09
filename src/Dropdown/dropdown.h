#pragma once

#include <QWidget>
#include "../export.h"

namespace Ui {
class Dropdown;
}


namespace CustomWidgetsQt
{

class DropdownP;

class WIDGET_EXPORT Dropdown : public QWidget
{
    Q_OBJECT
    DropdownP *p;
public:
    explicit Dropdown(QWidget *parent = nullptr);
    ~Dropdown();

    void setVariantList(const QVariantList &_items);


private:
    Ui::Dropdown *ui;
};

}
