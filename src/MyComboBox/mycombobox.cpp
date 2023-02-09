#include "../project_pch.h"
#include "mycombobox.h"
#include "ui_mycombobox.h"

MyComboBox::MyComboBox(QWidget *parent) :
    ExtendedWidget  (parent),
    ui              (new Ui::MyComboBox)
{
    ui->setupUi(this);
    initAll();
}

MyComboBox::~MyComboBox()
{
    delete ui;
}

void MyComboBox::initValues(const QStringList &_values)
{
    m_presets = _values;
    m_lastPreset = ui->comboBox->currentText();

    disconnect(ui->comboBox, &QComboBox::currentTextChanged, this, &MyComboBox::comboBoxTextChanged);
    ui->comboBox->clear();

    qSort(m_presets.begin(), m_presets.end(), qLess<QString>());
    ui->comboBox->addItems(m_presets);
    ui->comboBox->setCurrentText(m_lastPreset);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MyComboBox::comboBoxTextChanged);
}

const QStringList &MyComboBox::getValues() const
{
    return m_presets;
}

void MyComboBox::setCurrentPreset(const QString &_preset)
{
    m_lastPreset = _preset;
    ui->comboBox->setCurrentText(m_lastPreset);
}

const QString &MyComboBox::getCurrentPreset() const
{
    return m_lastPreset;
}

void MyComboBox::setRemoveButtonVisible(bool _isVisible)
{
    ui->removeButton->setVisible(_isVisible);
}

bool MyComboBox::getRemoveButtonVisible() const
{
    return ui->removeButton->isVisible();
}

void MyComboBox::setComboEditable(bool _isEditable)
{
    ui->comboBox->setEditable(_isEditable);
}

bool MyComboBox::getComboEditable() const
{
    return ui->comboBox->isEditable();
}

void MyComboBox::on_saveButton_clicked()
{
    QString text = ui->comboBox->currentText();
    if (!text.trimmed().isEmpty())
    {
        if (!m_presets.contains(text))	//если пресета нет в списке
        {
            m_presets.append(text);
            emit presetSaved(text);
            initValues(m_presets);
            QMessageBox::information(this, tr("Предустановки"), QString(tr("Предустановка [%1] сохранена!")).arg(text));
        }
        else
        {
            if (QMessageBox::question(this,
                                      tr("Предустановки"),
                                      QString(tr("Предустановка [%1] существует, хотите перезаписать?")).arg(text),
                                      QMessageBox::Yes|QMessageBox::No)	 == QMessageBox::Yes)
            {
                QMessageBox::information(this, tr("Предустановки"), QString(tr("Предустановка [%1] перезаписана!")).arg(text));
                emit presetSaved(text);
            }
        }
    }
}

void MyComboBox::on_removeButton_clicked()
{
    QString text = ui->comboBox->currentText();
    if (!m_presets.contains(text))	//если в combobox указан несуществующий пресет, то ничего не делаем
    {
        return;
    }


    if (QMessageBox::question(this,
                              tr("Предустановки"),
                              QString(tr("Удалить предустановку [%1] ?")).arg(text),
                              QMessageBox::Yes|QMessageBox::No)	 == QMessageBox::Yes)
    {
        m_presets.removeAt(m_presets.indexOf(text));
        emit presetRemoved(text);
        initValues(m_presets);
        ui->comboBox->setCurrentText("");
    }
}

void MyComboBox::comboBoxTextChanged(const QString &_text)
{
    if(m_presets.contains(_text))
    {
        m_lastPreset = _text;
        emit presetLoaded(_text);
    }
}

void MyComboBox::setButtonsSize(const QSize &_size)
{
    ui->saveButton->setIconSize(_size);
    ui->removeButton->setIconSize(_size);
}

QSize MyComboBox::getButtonsSize() const
{
    return ui->saveButton->iconSize();
}

void MyComboBox::resetButtonsSize()
{
    setButtonsSize(QSize(32,32));
}

void MyComboBox::setComboSizePolicy(const QSizePolicy &_policy)
{
    ui->comboBox->setSizePolicy(_policy);
}

QSizePolicy MyComboBox::getComboSizePolicy() const
{
    return ui->comboBox->sizePolicy();
}

void MyComboBox::resetSizePolicy()
{
    setComboSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding));
}


QVariant MyComboBox::saveWidgetState() const
{
    return QVariant();
}

void MyComboBox::loadWidgetState(const QVariant &_state)
{
    Q_UNUSED(_state);
}

void MyComboBox::updateLanguage()
{
    ui->retranslateUi(this);
}

void MyComboBox::updateStyle()
{
    ui->removeButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
    ui->saveButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Save1));
}

void MyComboBox::initConnections()
{
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MyComboBox::comboBoxTextChanged);
}
