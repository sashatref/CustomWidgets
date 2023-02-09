#include "historytextedit.h"
#include "ui_historytextedit.h"
#include "priv/combodelegate.h"

namespace CustomWidgetsQt
{

PS_REGISTER_CONSTRUCTOR_FUNC([]
{
    qRegisterMetaTypeStreamOperators<QStringList>();
})

HistoryTextEdit::HistoryTextEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryTextEdit)
{
    ui->setupUi(this);

    m_delegate = new ComboDelegate(this);
    connect(m_delegate, &ComboDelegate::removeRow, this, &HistoryTextEdit::removeRowSlot);
    //ui->comboBox->setItemDelegate(m_delegate);
    //ui->comboBox->view()->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

HistoryTextEdit::~HistoryTextEdit()
{
    delete ui;
}

QString HistoryTextEdit::getCurrentText()
{
    return ui->lineEdit->text();
}

void HistoryTextEdit::setCurrentText(const QString &_text)
{
    ui->lineEdit->setText(_text);
}

void HistoryTextEdit::applyCurrentValue()
{
    m_textValues << ui->lineEdit->text();

    m_textValues.removeDuplicates();

    //int index = ui->comboBox->findText(ui->comboBox->currentText());
    //ui->comboBox->removeItem(index);

    //ui->comboBox->insertItem(0, ui->comboBox->currentText());
    //ui->comboBox->setItemData(0, m_size, Qt::SizeHintRole);
}

QStringList HistoryTextEdit::getValues() const
{
    return m_textValues;
}

void HistoryTextEdit::setValues(const QStringList &_values)
{
    m_textValues = _values;

    m_completer = new QCompleter(m_textValues, this);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
    m_completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);

    ui->lineEdit->setCompleter(m_completer);
}

void HistoryTextEdit::removeRowSlot(int /*_index*/)
{
    m_delegate->closeEditorIfOpened();
    //ui->comboBox->removeItem(_index);
}

void HistoryTextEdit::loadState(const LayoutSaver &_saver)
{
    setValues(_saver["comboValues"].toStringList());
}

void HistoryTextEdit::saveState(LayoutSaver &_saver) const
{
    _saver["comboValues"] = getValues();
}

QString HistoryTextEdit::getWidgetUniqueName() const
{
    return objectName();
}

}





