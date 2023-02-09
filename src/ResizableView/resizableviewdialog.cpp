#include "../project_pch.h"
#include "resizableviewdialog.h"
#include "ui_resizableviewdialog.h"

namespace CustomWidgetsQt
{

QString getFileUrl(QDropEvent *event)
{
    /*
     * Из QDropEvent извлекаем путь к файлу
     */

    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        QUrl url = mimeData->urls().first();

        QFileInfo fi(url.toLocalFile());

        if(fi.suffix().compare("png", Qt::CaseInsensitive) == 0 || fi.suffix().compare("jpg", Qt::CaseInsensitive) == 0)
        {
            return url.toLocalFile();
        }
    }

    return QString();
}

ResizableViewDialog::ResizableViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResizableViewDialog)
{
    ui->setupUi(this);

    updateStyle();
}

ResizableViewDialog::~ResizableViewDialog()
{
    delete ui;
}

QPixmap ResizableViewDialog::getPixmap() const
{
    return ui->resizableView->getPixmap();
}

void ResizableViewDialog::setPixmap(const QPixmap &_pixmap)
{
    ui->resizableView->setPixmap(_pixmap);
}

void ResizableViewDialog::addWidget(QWidget * const _widget, int _index)
{
    ui->horizontalLayout->insertWidget(_index, _widget);
}

void ResizableViewDialog::on_loadButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Выберите файл...");
    if(path.isEmpty()) return;

    QPixmap img(path);
    ui->resizableView->setPixmap(img);
}

void ResizableViewDialog::updateStyle()
{
    ui->applyButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
    ui->loadButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_FileOpen1));
    ui->clearButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_FileDelete1));
    ui->resizeButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Replace1));
}

void ResizableViewDialog::on_applyButton_clicked()
{
    accept();
}

void ResizableViewDialog::on_clearButton_clicked()
{
    ui->resizableView->setPixmap(QPixmap());
}

void ResizableViewDialog::dragEnterEvent(QDragEnterEvent *event)
{
    if(!getFileUrl(event).isEmpty())
    {
        event->acceptProposedAction();
        return;
    }
    event->ignore();
}

void ResizableViewDialog::dropEvent(QDropEvent *event)
{
    {
        const QString filePath = getFileUrl(event);
        if(!filePath.isEmpty())
        {
            setPixmap(QPixmap(filePath));
        }
    }

    event->ignore();
}

void ResizableViewDialog::on_resizeButton_clicked()
{
    QPixmap p = getPixmap();

    QString currentSize = QString("%1x%2").arg(p.width()).arg(p.height());

    QString value = QInputDialog::getText(this,
                                          tr("Укажите новый размер"),
                                          tr("Укажите новый размер"), QLineEdit::Normal, currentSize);
    if(value.isEmpty())
    {
        return;
    }

    QStringList tokens = value.split("x");
    if(tokens.size() != 2)
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Неправильный формат размера"));
        return;
    }

    int width = tokens.first().toInt();
    int height = tokens.last().toInt();

    setPixmap(p.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

}





