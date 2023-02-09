#include "../project_pch.h"
#include "extcomboedit.h"


ExtComboEdit::ExtComboEdit(QWidget *parent) : QWidget(parent)
{
    m_combo = new QComboBox(this);
    m_addButton = new QToolButton(this);
    m_openButton = new QToolButton(this);
    m_type = -1;

    QHBoxLayout *lt = new QHBoxLayout(this);
    lt->setSpacing(0);
    lt->setMargin(0);
    lt->addWidget(m_combo);
    lt->addWidget(m_addButton);
    lt->addWidget(m_openButton);

    m_addButton->setIcon(QIcon(":/CustomWidgets/Images/add.png"));
    m_addButton->setText(tr("Add"));
    m_addButton->setToolTip(tr("Add"));

    m_openButton->setIcon(QIcon(":/CustomWidgets/Images/Open.png"));
    m_openButton->setText(tr("Open"));
    m_openButton->setToolTip(tr("Open"));

    connect(m_addButton, SIGNAL(clicked()), this, SLOT(onAddClick()));
    connect(m_openButton, SIGNAL(clicked()), this, SLOT(onOpenClick()));
}

void ExtComboEdit::setValuesList(const QMap<int, QString> &_values)
{
    m_combo->clear();

    for(int i = 0; i < _values.keys().size(); i++)
    {
        int key = _values.keys().at(i);
        m_combo->addItem(_values[key], key);
    }

    m_combo->setCurrentIndex(0);

    if(_values.count() == 0)
    {
        m_openButton->hide();
    } else
    {
        m_openButton->show();
    }
}

//QStringList ExtComboEdit::valuesList()
//{
//    QStringList values;
//    for(int i = 0; i < m_combo->count(); i++)
//    {
//        values.append(m_combo->itemText(i));
//    }
//    return values;
//}

void ExtComboEdit::setCurrentValue(const QString &value)
{
    m_combo->setCurrentText(value);
}

QString ExtComboEdit::currentValue()
{
    return m_combo->currentText();
}

void ExtComboEdit::setType(int value)
{
    m_type = value;
}

int ExtComboEdit::getType()
{
    return m_type;
}

void ExtComboEdit::addComboItem(QString item)
{
    Q_UNUSED(item);
}

void ExtComboEdit::removeComboItem(QString item)
{
    Q_UNUSED(item);
}

void ExtComboEdit::editComboItem(QString item)
{
    Q_UNUSED(item);
}

void ExtComboEdit::onAddClick()
{
    emit addClicked();
    emit addClicked(m_combo->currentText(), m_type);
}

void ExtComboEdit::onOpenClick()
{
    emit openClicked();
    emit openClicked(m_combo->currentText(), m_type);
}

