#include "../project_pch.h"
#include "progressdialog.h"
#include "ui_progressdialog.h"

ProgressDialog::ProgressDialog(const QString &_labelText, QWidget *) :
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->label->setText(_labelText);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

QLabel *ProgressDialog::getLabel() const
{
    return ui->label;
}

QProgressBar *ProgressDialog::getProgressBar() const
{
    return ui->progressBar;
}

QPushButton *ProgressDialog::getButton() const
{
    return ui->cancelButton;
}

void ProgressDialog::setCancelable(bool _isCancelable)
{
    ui->cancelButton->setVisible(_isCancelable);
}

void ProgressDialog::setContinouse(bool _isContinouse)
{
    ui->progressBar->setTextVisible(!_isContinouse);
    ui->progressBar->setMaximum(_isContinouse ? 0 : 100);
}

void ProgressDialog::setIsWindowModal(bool _isModal)
{
    QWidget::setWindowModality(_isModal ? Qt::ApplicationModal : Qt::NonModal);
}

void ProgressDialog::setMaximum(int _maximumValue)
{
    ui->progressBar->setMaximum(_maximumValue);
}

void ProgressDialog::setCurrentValue(int _currentValue)
{
    ui->progressBar->setValue(_currentValue);
}

void ProgressDialog::on_cancelButton_clicked()
{
    emit cancelButtonClicked();
    close();
}
