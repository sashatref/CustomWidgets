#include "itemsettingsmapeditor.h"
#include "ui_itemsettingsmapeditor.h"
#include "itemsettingseditor.h"

ItemSettingsMapEditor::ItemSettingsMapEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemSettingsMapEditor)
{
    ui->setupUi(this);

    ui->cancelButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
    ui->applyButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
    ui->resetToDefBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Restart1));

    ui->saveButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Save1));
    ui->loadButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_FileOpen1));

    ui->resetToDefBtn->addActions(
                {
                    ui->actionLoadLayout1,
                    ui->actionLoadLayout2
                });

    QDir appDir(qApp->applicationDirPath());
    QDirIterator it(qApp->applicationDirPath(), QStringList("*.lwbin"), QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QString path = it.next();

        QAction *act = new QAction(this);
        act->setText(appDir.relativeFilePath(path));

        connect(act, &QAction::triggered, this, [=]
        {
            loadLayoutFromFile(path);
        });

        ui->resetToDefBtn->addAction(act);
    }
}

ItemSettingsMapEditor::~ItemSettingsMapEditor()
{
    delete ui;
}

void ItemSettingsMapEditor::setSettingsMap(const CustomWidgetsQt::ItemSettingsMap &_editor)
{
    ui->tabWidget->clear();

    QMap<QtMsgType, QString> map =
    {
        { QtDebugMsg,       "QtDebugMsg" },
        { QtInfoMsg,        "QtInfoMsg" },
        { QtWarningMsg,     "QtWarningMsg" },
        { QtCriticalMsg,    "QtCriticalMsg" },
        { QtFatalMsg,       "QtFatalMsg" }
    };

    for(auto it = map.begin(); it != map.end(); ++it)
    {
        ItemSettingsEditor *editor = new ItemSettingsEditor(this);
        editor->setSettings(_editor[it.key()]);
        editor->setProperty("type", it.key());

        ui->tabWidget->addTab(editor, it.value());
    }
}

CustomWidgetsQt::ItemSettingsMap ItemSettingsMapEditor::getSettingsMap() const
{
    CustomWidgetsQt::ItemSettingsMap out;

    for(int i = 0 ; i < ui->tabWidget->count(); i++)
    {
        ItemSettingsEditor *editor = static_cast<ItemSettingsEditor*>(ui->tabWidget->widget(i));

        QtMsgType t = static_cast<QtMsgType>(editor->property("type").toInt());
        out[t] = editor->getSettings();
    }

    return out;
}

void ItemSettingsMapEditor::on_applyButton_clicked()
{
    accept();
}

void ItemSettingsMapEditor::on_cancelButton_clicked()
{
    reject();
}

void ItemSettingsMapEditor::on_resetToDefBtn_clicked()
{
    setSettingsMap(CustomWidgetsQt::makeDefaultSettings());
}

void ItemSettingsMapEditor::on_loadButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Выберите файл"), qApp->applicationDirPath(), "*.lwbin");
    if(path.isEmpty())
    {
        return;
    }

    loadLayoutFromFile(path);
}

void ItemSettingsMapEditor::on_saveButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Сохранить в файл"), qApp->applicationDirPath(), "*.lwbin");
    if(path.isEmpty())
    {
        return;
    }

    LayoutSaver saver;
    saver["styleConfig"] = QVariant::fromValue(getSettingsMap());
    saver.saveToFile(path);
    QMessageBox::information(this, tr("Успешно"), tr("Файл сохранен [%1]").arg(path));
}


void ItemSettingsMapEditor::on_actionLoadLayout1_triggered()
{
    setSettingsMap(CustomWidgetsQt::makeDefaultSettings());
}

void ItemSettingsMapEditor::on_actionLoadLayout2_triggered()
{
    loadLayoutFromFile(":/CustomWidgets/LogWindow2/settings/layout2.lwbin");
}

void ItemSettingsMapEditor::loadLayoutFromFile(const QString &_path)
{
    LayoutSaver saver;
    saver.loadFromFile(_path);

    if(saver.contains("styleConfig"))
    {
        setSettingsMap(saver["styleConfig"].value<CustomWidgetsQt::ItemSettingsMap>());
    } else
    {
        QMessageBox::information(this, tr("Ошибка"), tr("Ошибка загрузки файла [%1]").arg(_path));
    }
}
