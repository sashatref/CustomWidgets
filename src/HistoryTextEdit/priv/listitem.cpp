#include <HelperLibrary/Styles/iconsenum.h>
#include "listitem.h"
#include "ui_listitem.h"

namespace CustomWidgetsQt
{

ListItem::ListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItem)
{
    ui->setupUi(this);

    ui->removeButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Trash2));

    connect(ui->removeButton, &QToolButton::clicked, this, &ListItem::removeButtonClicked);
}

ListItem::~ListItem()
{
    delete ui;
}

void ListItem::setText(const QString &_text)
{
    ui->label->setText(_text);
}

}
