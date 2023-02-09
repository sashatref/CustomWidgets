#include "../project_pch.h"
#include "HtmlEditorDialog.h"
#include "ui_HtmlEditorDialog.h"

#include "HtmlEditor.h"

namespace CustomWidgetsQt
{

HtmlEditorDialog::HtmlEditorDialog(QWidget *parent) :
    ExtendedDialog      (parent),
    ui                  (new Ui::HtmlEditorDialog),
    m_isPlain           (false)
{
    ui->setupUi(this);

    initAll();
}

HtmlEditorDialog::~HtmlEditorDialog()
{
    delete ui;
}

void HtmlEditorDialog::setReadOnly(bool _isReadOnly)
{
    ui->saveAsHtmlButton->setEnabled(!_isReadOnly);
    ui->saveAsTextButton->setEnabled(!_isReadOnly);
    ui->htmlEditor->setReadOnly(_isReadOnly);
}

void HtmlEditorDialog::loadHtml(const QString &_html)
{
    ui->htmlEditor->loadHtml(_html);
}

QString HtmlEditorDialog::saveHtml() const
{
    return m_isPlain ? ui->htmlEditor->savePlaintText() : ui->htmlEditor->saveHtml();
}

HtmlEditor *HtmlEditorDialog::getHtmlEditor() const
{
    return ui->htmlEditor;
}

void HtmlEditorDialog::on_closeButton_clicked()
{
    reject();
}

void HtmlEditorDialog::on_saveAsTextButton_clicked()
{
    m_isPlain = true;
    accept();
}

void HtmlEditorDialog::on_saveAsHtmlButton_clicked()
{
    m_isPlain = false;
    accept();;
}

void HtmlEditorDialog::updateLanguage()
{
    ui->retranslateUi(this);
}

void HtmlEditorDialog::updateStyle()
{
    ui->closeButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
}

}


