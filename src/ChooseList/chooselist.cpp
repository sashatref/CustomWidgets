#include "../project_pch.h"
#include "chooselist.h"
#include "ui_chooselist.h"

#include "priv/customlistwidgetitem.h"

ChooseList::ChooseList(QWidget *parent) :
    QDialog                 (parent),
    ui                      (new Ui::ChooseList),
    m_allElementsList       (),
    m_selectedElementsList  (),
    m_rowSize               (QSize(24,24)),
    m_buttonSize            (),
    m_listFont              (),
    m_labelFont             (),
    m_propertyToShow        (),
    m_propertyToSort        (),
    m_isTest                (false)
{
    ui->setupUi(this);
    m_buttonSize = ui->addItemButton->iconSize();
    m_listFont = ui->allElementsList->font();
    m_labelFont = ui->allElementsLabel->font();

    updateStyle();

    connect(ui->allElementsList, &QListWidget::itemSelectionChanged, this, &ChooseList::onListItemSelected);
    connect(ui->selectedElementList, &QListWidget::itemSelectionChanged, this, &ChooseList::onListItemSelected);
}

ChooseList::~ChooseList()
{
    delete ui;
}

void ChooseList::setCloseApplyButtonVisible(bool _isVisible)
{
    ui->applyButton->setVisible(_isVisible);
    ui->closeButton->setVisible(_isVisible);
}

bool ChooseList::getCloseApplyButtonVisible() const
{
    return ui->applyButton->isVisible();
}

void ChooseList::setAllElementsList(const QVector<QVariant> &_valuesList,
                                    const QString &_propertyToShow,
                                    const QString &_sortProperty)
{
    m_allElementsList = _valuesList;
    m_propertyToShow = _propertyToShow;
    m_propertyToSort = _sortProperty;

    ui->allElementsList->clear();

    foreach (const auto &item, _valuesList)
    {
        QString text;
        if(m_propertyToShow == "")
        {
            text = item.toString();
        } else
        {
            text = VariantHelper::getProperty(item, m_propertyToShow).toString();
        }

        if(text.isEmpty())
        {
            qCritical() << QString("Item must be not empty! Set Show Property or add toString converter"\
                                  " for property: %1\n").arg(item.typeName());
        }

        CustomListWidgetItem *listItem = new CustomListWidgetItem(text, m_propertyToSort);
        listItem->setData(Qt::UserRole, item);
        listItem->setData(Qt::SizeHintRole, m_rowSize);
        ui->allElementsList->addItem(listItem);
    }

    //проверяем, вдруг в selected есть значения которых уже нет в all, тогда это значение надо удалить
    for(int i = 0 ; i < ui->selectedElementList->count(); i++)
    {
        bool isPresent = false;
        for(int j = 0 ; j < ui->allElementsList->count(); j++)
        {
            if(ui->allElementsList->item(j)->text() == ui->selectedElementList->item(i)->text())
            {
                isPresent = true;
            }
        }

        if(!isPresent)
        {
            delete ui->selectedElementList->item(i);
            i--;
        }
    }

    ui->allElementsList->sortItems();
}

const QVector<QVariant> &ChooseList::getAllElementsList()
{
    return m_allElementsList;
}

void ChooseList::setSelectedElementsList(const QVector<QVariant> &_valuesList)
{
    m_selectedElementsList = _valuesList;
    filterSelectedList();

    ui->selectedElementList->clear();

    foreach (const auto &item, _valuesList)
    {
        QString text;
        if(m_propertyToShow == "")
        {
            text = item.toString();
        } else
        {
            text = VariantHelper::getProperty(item, m_propertyToShow).toString();
        }

        for(int i = ui->allElementsList->count() - 1 ; i > -1; i--)
        {
            QListWidgetItem *listItem = ui->allElementsList->item(i);
            if(listItem->text() == text)
            {
                ui->selectedElementList->addItem(listItem->clone());
                delete listItem;
            }
        }
    }

    ui->selectedElementList->sortItems();

    emit selectedElementsListChanged(m_selectedElementsList);
}

const QVector<QVariant> &ChooseList::getSelectedElementsList()
{
    return m_selectedElementsList;
}

const QFont &ChooseList::getLabelsFont()
{
    return m_labelFont;
}

void ChooseList::setLabelsFont(const QFont &_font)
{
    m_labelFont = _font;
    ui->allElementsLabel->setFont(m_labelFont);
    ui->selectedElementsLabel->setFont(m_labelFont);
}

void ChooseList::setListFont(const QFont &_font)
{
    m_listFont = _font;
    ui->allElementsList->setFont(m_listFont);
    ui->selectedElementList->setFont(m_listFont);
}

const QFont &ChooseList::getListFont()
{
    return m_listFont;
}

void ChooseList::setButtonsSize(const QSize &_buttonSize)
{
    m_buttonSize = _buttonSize;
    ui->addItemButton->setIconSize(m_buttonSize);
    ui->removeItemButton->setIconSize(m_buttonSize);
}

const QSize &ChooseList::getButtonsSize() const
{
    return m_buttonSize;
}

void ChooseList::setRowSize(const QSize &_rowSize)
{
    m_rowSize = _rowSize;

    for(int i = 0 ; i < ui->allElementsList->count(); i++)
    {
        ui->allElementsList->item(i)->setData(Qt::SizeHintRole, m_rowSize);
    }

    for(int i = 0 ; i < ui->selectedElementList->count(); i++)
    {
        ui->selectedElementList->item(i)->setData(Qt::SizeHintRole, m_rowSize);
    }
}

const QSize &ChooseList::getRowSize() const
{
    return m_rowSize;
}

void ChooseList::setTest(bool _test)
{
    m_isTest = _test;
    if(m_isTest)
    {
        setAllElementsList(QVector<QVariant>()
                           << "value1"
                           << "value2"
                           << "value3"
                           << "value4"
                           << "value5");
        setSelectedElementsList(QVector<QVariant>()
                                << "value2"
                                << "value4");
    } else
    {
        clearTest();
    }
}

void ChooseList::clearTest()
{
    setAllElementsList(QVector<QVariant>());
    setSelectedElementsList(QVector<QVariant>());
}

bool ChooseList::getTest()
{
    return m_isTest;
}

void ChooseList::translate()
{
    ui->retranslateUi(this);
}

const QString &ChooseList::getShowProperty() const
{
    return m_propertyToShow;
}

const QString &ChooseList::getSortProperty() const
{
    return m_propertyToSort;
}

void ChooseList::on_addItemButton_clicked()
{
    int selectedItemsSize = ui->allElementsList->selectedItems().size();
    if(selectedItemsSize == 0)
    {
        return;
    }

    for(int i = selectedItemsSize - 1 ; i > - 1; i--)
    {
        CustomListWidgetItem *item = static_cast<CustomListWidgetItem*>(ui->allElementsList->selectedItems()[i]);
        ui->selectedElementList->addItem(item->clone());
        emit itemAdded(item->data(Qt::UserRole));
        delete item;
    }

    ui->selectedElementList->sortItems();

    recountSelectedItems();
}

void ChooseList::on_removeItemButton_clicked()
{
    int selectedItemsSize = ui->selectedElementList->selectedItems().size();
    if(selectedItemsSize == 0)
    {
        return;
    }

    for(int i = selectedItemsSize - 1 ; i > - 1; i--)
    {
        CustomListWidgetItem *item = static_cast<CustomListWidgetItem*>(ui->selectedElementList->selectedItems()[i]);
        ui->allElementsList->addItem(item->clone());
        emit itemRemoved(item->data(Qt::UserRole));
        delete item;
    }

    ui->allElementsList->sortItems();

    recountSelectedItems();
}


void ChooseList::onListItemSelected()
{
    if(sender() == ui->allElementsList)
    {
        ui->addItemButton->setEnabled(ui->allElementsList->selectedItems().size());
    } else if(sender() == ui->selectedElementList)
    {
        ui->removeItemButton->setEnabled(ui->selectedElementList->selectedItems().size());
    }
}

void ChooseList::recountSelectedItems()
{
    m_selectedElementsList.clear();
    for(int i = 0 ; i < ui->selectedElementList->count(); i++)
    {
        m_selectedElementsList.push_back(ui->selectedElementList->item(i)->data(Qt::UserRole));
    }

    emit selectedElementsListChanged(m_selectedElementsList);
}

void ChooseList::filterSelectedList()
{
    for(int i = m_selectedElementsList.size() - 1; i > -1; i--)
    {
        if(!m_allElementsList.contains(m_selectedElementsList[i]))
        {
            m_selectedElementsList.removeAt(i);
        }
    }
}

void ChooseList::on_closeButton_clicked()
{
    reject();
}

void ChooseList::on_applyButton_clicked()
{
    accept();
}

void ChooseList::updateStyle()
{
    ui->closeButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
    ui->applyButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
}

void ChooseList::updateLanguage()
{

}


void ChooseList::changeEvent(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::LanguageChange:
        updateLanguage();
        break;
    case QEvent::StyleChange:
        updateStyle();
        break;
    default:
        break;
    }
}
