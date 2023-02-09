#include "dropdown.h"
#include "ui_dropdown.h"
#include "priv/dropdownp.h"

namespace CustomWidgetsQt
{

Dropdown::Dropdown(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dropdown),
    p(new DropdownP(this))
{
    ui->setupUi(this);
}

Dropdown::~Dropdown()
{
    delete ui;
}

void Dropdown::setVariantList(const QVariantList &_items)
{
    p->data = _items;
}

}
