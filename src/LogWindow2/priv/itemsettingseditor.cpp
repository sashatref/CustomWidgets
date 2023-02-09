#include "itemsettingseditor.h"
#include "ui_itemsettingseditor.h"

ItemSettingsEditor::ItemSettingsEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemSettingsEditor)
{
    ui->setupUi(this);

    ui->testLineEdit->setAttribute(Qt::WA_TranslucentBackground, true);
}

ItemSettingsEditor::~ItemSettingsEditor()
{
    delete ui;
}

void ItemSettingsEditor::setSettings(const CustomWidgetsQt::ItemSettings &_s)
{
    m_config = _s;

    updateTestStyle();
    updateFields();
}

CustomWidgetsQt::ItemSettings ItemSettingsEditor::getSettings()
{
    m_config.m_rowHeight = ui->rowHeightSpin->value();

    return m_config;
}

void ItemSettingsEditor::on_bgColorConfBtn_clicked()
{
    QColorDialog dialog(this);
    dialog.setOption(QColorDialog::ShowAlphaChannel);
    dialog.setCurrentColor(m_config.m_backgroundColor);
    if(dialog.exec() == QDialog::Accepted)
    {
        m_config.m_backgroundColor = dialog.currentColor();
        updateTestStyle();
        updateFields();
    }
}

void ItemSettingsEditor::on_textColorConfBtn_clicked()
{
    QColorDialog dialog(this);
    dialog.setOption(QColorDialog::ShowAlphaChannel);
    dialog.setCurrentColor(m_config.m_textColor);
    if(dialog.exec() == QDialog::Accepted)
    {
        m_config.m_textColor = dialog.currentColor();
        updateTestStyle();
        updateFields();
    }
}

void ItemSettingsEditor::on_fontConfgBtn_clicked()
{
    QFontDialog dialog(m_config.m_font, this);
    if(dialog.exec() == QDialog::Accepted)
    {
        m_config.m_font = dialog.currentFont();
        updateTestStyle();
        updateFields();
    }
}

void ItemSettingsEditor::updateTestStyle()
{
    QString css = QString("color: %1; background-color: %2;")
            .arg(makeRgbaColor(m_config.m_textColor))
            .arg(makeRgbaColor(m_config.m_backgroundColor));

    ui->testLineEdit->setFont(m_config.m_font);
    ui->testLineEdit->setStyleSheet(css);
    ui->testLineEdit->setFixedHeight(m_config.m_rowHeight);
}

void ItemSettingsEditor::updateFields()
{
    ui->bgColorEdit->setText(makeRgbaColor(m_config.m_backgroundColor));
    ui->textColorEdit->setText(makeRgbaColor(m_config.m_textColor));
    ui->fontEdit->setText(m_config.m_font.toString());
    ui->rowHeightSpin->setValue(m_config.m_rowHeight);
}

QString ItemSettingsEditor::makeRgbaColor(const QColor &_col)
{
    return QString("rgba(%1, %2, %3, %4)")
            .arg(_col.red())
            .arg(_col.green())
            .arg(_col.blue())
            .arg(_col.alpha());
}

void ItemSettingsEditor::on_rowHeightSpin_valueChanged(int arg1)
{
    m_config.m_rowHeight = arg1;
    updateTestStyle();
}
