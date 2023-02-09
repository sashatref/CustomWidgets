#include "../project_pch.h"
#include "varianmapeditor.h"
#include "ui_varianmapeditor.h"

VarianMapEditor::VarianMapEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VarianMapEditor)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableWidget->horizontalHeader()->setVisible(true);
}

VarianMapEditor::~VarianMapEditor()
{
    delete ui;
}

void VarianMapEditor::setVariantMap(const QVariantMap &_map)
{
    for(int i = 0; i < _map.keys().size();i++)
    {
        QString key = _map.keys().at(i);
        QVariant value = _map[key];

        addItem(key, value.toString());
    }
}

QVariantMap VarianMapEditor::getVariantMap() const
{
    QVariantMap map;
    for(int i = 0 ; i < ui->tableWidget->rowCount(); i++)
    {
        if(!ui->tableWidget->item(i, 0) || !ui->tableWidget->item(i, 1)) continue;
        QString key = ui->tableWidget->item(i, 0)->text();
        if(key.isEmpty()) continue;

        QVariant value = ui->tableWidget->item(i, 1)->text();
        map[key] = value;
    }

    return map;
}

void VarianMapEditor::addItem(const QString &key, const QVariant &_value)
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

    QTableWidgetItem *keyItem = new QTableWidgetItem(key);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, keyItem);

    QTableWidgetItem *valueItem = new QTableWidgetItem(_value.toString());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, valueItem);
}

void VarianMapEditor::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Delete)
    {
        on_removeButton_clicked();
    }
}

void VarianMapEditor::showEvent(QShowEvent *)
{
    Buttons btns = getButtonsHint();
    ui->saveToFileButton->setEnabled(btns.testFlag(SaveButton));
    ui->loadFromFileButton->setEnabled(btns.testFlag(LoadButton));

    ui->tableWidget->horizontalHeader()->resizeSections(QHeaderView::Stretch);
}

void VarianMapEditor::saveData(const QString &/*_filePath*/)
{
    qWarning() << Q_FUNC_INFO;
    qWarning() << "not implemented!";
}

void VarianMapEditor::loadData(const QString &/*_filePath*/)
{
    qWarning() << Q_FUNC_INFO;
    qWarning() << "not implemented!";
}

QString VarianMapEditor::openDialogFilter() const
{
    return "XML(*.xml)";
}

VarianMapEditor::Buttons VarianMapEditor::getButtonsHint() const
{
    return 0;
}

void VarianMapEditor::on_applyButton_clicked()
{
    accept();
}

void VarianMapEditor::on_closeButton_clicked()
{
    reject();
}

void VarianMapEditor::on_removeButton_clicked()
{
    QModelIndexList selected = ui->tableWidget->selectionModel()->selectedRows();
    for(int i = selected.size() - 1; i > -1; i--)
    {
        ui->tableWidget->removeRow(selected.at(i).row());
    }
}

void VarianMapEditor::on_addButton_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
}



void VarianMapEditor::on_loadFromFileButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Выберите файл для загрузки..."), "", "XML(*.xml)");
    if(path.isEmpty()) return;

    loadData(path);
}

void VarianMapEditor::on_saveToFileButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Выберите файл для сохранения..."), "", openDialogFilter());
    if(path.isEmpty()) return;

    saveData(path);
}

void VarianMapEditor::on_tableWidget_itemSelectionChanged()
{
    QList<QTableWidgetItem*> selected = ui->tableWidget->selectedItems();
    ui->removeButton->setEnabled(selected.size() ? true :  false);
}
