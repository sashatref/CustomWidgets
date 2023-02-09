#include "../project_pch.h"
#include "consoleeditor.h"
#include "ui_consoleeditor.h"
#include "priv/customtexteditor.h"

namespace CustomWidgetsQt
{

struct ConsoleEditorP
{
    QFileSystemWatcher m_fileWatcher;
    QString m_fileName;
};

ConsoleEditor::ConsoleEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleEditor),
    p(new ConsoleEditorP())
{
    ui->setupUi(this);

    updateStyle();

    connect(&p->m_fileWatcher, &QFileSystemWatcher::fileChanged, this, &ConsoleEditor::onFileChanged);
}

ConsoleEditor::~ConsoleEditor()
{
    delete ui;
    delete p;
}

void ConsoleEditor::setFileName(const QString &_fileName)
{
    if(!p->m_fileName.isEmpty())
    {
        p->m_fileWatcher.removePath(p->m_fileName);
    }

    p->m_fileName = _fileName;

    if(!p->m_fileWatcher.addPath(p->m_fileName))
    {
        QMessageBox::warning(this,
                             tr("Ошибка"),
                             tr("Файл <%1> не может быть отслежен")
                             .arg(p->m_fileName));
    }

    setFileLabel(p->m_fileName);
    onFileChanged(p->m_fileName);

    //qDebug() << ui->textEdit->verticalScrollBar()->maximum();

    //ui->textEdit->verticalScrollBar()->setSliderPosition(200);
}

QString ConsoleEditor::getFileName() const
{
    return p->m_fileName;
}

void ConsoleEditor::updateLanguage()
{
    ui->retranslateUi(this);
}

void ConsoleEditor::updateStyle()
{
    ui->clearFileButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Erase1));
    ui->configButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Services1));
}

void ConsoleEditor::onFileChanged(const QString &_path)
{
    if(_path != p->m_fileName) return;

    const int scrollPos = ui->textEdit->verticalScrollBar()->value();

    ui->textEdit->setPlainText(Text::readFromFile(p->m_fileName));
    ui->textEdit->verticalScrollBar()->setValue(scrollPos);
}

void ConsoleEditor::setFileLabel(const QString &_filePath)
{
    ui->fileLabel->setText(tr("Файл: %1").arg(_filePath));
}

QVariant ConsoleEditor::saveWidgetState() const
{
    LayoutSaver saver;

    saver.saveGeometry(this, "geometry");

    return saver;
}

void ConsoleEditor::loadWidgetState(const QVariant &_state)
{
    const LayoutSaver saver(_state.toMap());

    saver.loadGeometry(this, "geometry");

}

QString ConsoleEditor::getWidgetUniqueName() const
{
    return objectName();
}

void ConsoleEditor::on_clearFileButton_clicked()
{
    int res = QMessageBox::question(this,
                                    tr("Очистить?"),
                                    tr("Очистить файл лога <%1>")
                                    .arg(p->m_fileName));
    if(res != QMessageBox::Yes) return;

    QFile file(p->m_fileName);
    if(file.open(QFile::WriteOnly|QFile::Truncate))
    {
        QMessageBox::information(this,
                                 tr("Успешно"),
                                 tr("Файл <%1> успешно очещен").arg(p->m_fileName));
    } else
    {
        QMessageBox::warning(this,
                             tr("Ошибка"),
                             tr("Ошибка очистки файла <%1>").arg(p->m_fileName));
    }
}

}


void CustomWidgetsQt::ConsoleEditor::changeEvent(QEvent *event)
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
