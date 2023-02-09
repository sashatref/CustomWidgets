#include "../project_pch.h"
#include "manageprojects.h"
#include "ui_manageprojects.h"

ManageProjects::ManageProjects(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageProjects),
    m_rowHeight(24)
{
    ui->setupUi(this);

    connect(ui->projectsListWidget, &QListWidget::itemSelectionChanged, this, &ManageProjects::onListWidgetItemChanged);
    connect(ui->projectsListWidget, &QListWidget::itemDoubleClicked, this, &ManageProjects::on_loadButton_clicked);

    setAlternatingRowColors(true);

    ui->removeButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
    ui->loadButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogOpenButton));
    ui->applyButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
}

ManageProjects::~ManageProjects()
{
    delete ui;
}

void ManageProjects::setProjectMap(const QVariantMap &_projectList)
{
    ui->projectsListWidget->clear();

    for(int i = 0; i < _projectList.keys().size(); i++)
    {
        if(_projectList.keys().at(i).isEmpty()) continue;

        QListWidgetItem *listItem = new QListWidgetItem();
        listItem->setSizeHint(QSize(m_rowHeight, m_rowHeight));
        listItem->setText(_projectList.keys().at(i));
        listItem->setData(Qt::UserRole, _projectList[_projectList.keys().at(i)]);
        ui->projectsListWidget->addItem(listItem);
    }
}

QVariantMap ManageProjects::getProjectMap() const
{
    QMap<QString, QVariant> projectMap;

    for(int i = 0 ; i < ui->projectsListWidget->count(); i++)
    {
        projectMap[ui->projectsListWidget->item(i)->text()] = ui->projectsListWidget->item(i)->data(Qt::UserRole);
    }

    return projectMap;
}

void ManageProjects::setRowHeight(int _height)
{
    m_rowHeight = _height;
    for(int i = 0; i < ui->projectsListWidget->count(); i++)
    {
        ui->projectsListWidget->item(i)->setSizeHint(QSize(m_rowHeight, m_rowHeight));
    }
}

int ManageProjects::getRowHeight() const
{
    return m_rowHeight;
}

void ManageProjects::resetRowHeight()
{
    setRowHeight(24);
}

void ManageProjects::setAlternatingRowColors(bool _isTrue)
{
    ui->projectsListWidget->setAlternatingRowColors(_isTrue);
}

bool ManageProjects::getAlternatingRowColors() const
{
    return ui->projectsListWidget->alternatingRowColors();
}

void ManageProjects::setListWidgetFont(const QFont &_font)
{
    ui->projectsListWidget->setFont(_font);
}

QFont ManageProjects::getListWidgetFont() const
{
    return ui->projectsListWidget->font();
}

void ManageProjects::resetListWidgetFont()
{
    setListWidgetFont(QFont());
}

void ManageProjects::on_loadButton_clicked()
{
    emit projectMapChanged(getProjectMap());

    if(ui->projectsListWidget->currentItem())
    {
        emit loadProject2(ui->projectsListWidget->currentItem()->text(), ui->projectsListWidget->currentItem()->data(Qt::UserRole));
        emit loadProject(ui->projectsListWidget->currentItem()->data(Qt::UserRole));
        accept();
    }
}

void ManageProjects::on_removeButton_clicked()
{
    for(int i =  ui->projectsListWidget->selectedItems().count() - 1; i > -1; i--)
    {
        delete ui->projectsListWidget->selectedItems().at(i);
    }
}

void ManageProjects::on_applyButton_clicked()
{
    emit projectMapChanged(getProjectMap());
    accept();
}

void ManageProjects::onListWidgetItemChanged()
{
    if(ui->projectsListWidget->selectedItems().size() > 0)
    {
        ui->loadButton->setEnabled(true);
        ui->removeButton->setEnabled(true);
    } else
    {
        ui->loadButton->setEnabled(false);
        ui->removeButton->setEnabled(false);
    }
}


