#ifndef HISTORYTEXTEDIT_H
#define HISTORYTEXTEDIT_H

#include <QWidget>
#include "../export.h"

namespace Ui {
class HistoryTextEdit;
}

class ComboDelegate;

namespace CustomWidgetsQt
{

class WIDGET_EXPORT HistoryTextEdit : public QWidget, public ISaveWidget
{
    Q_OBJECT

public:
    explicit HistoryTextEdit(QWidget *parent = nullptr);
    ~HistoryTextEdit() override;

    QString getCurrentText();
    void setCurrentText(const QString &_text);
    void applyCurrentValue();

private:
    QStringList m_textValues;

    QCompleter *m_completer = nullptr;

    Ui::HistoryTextEdit *ui;
    QSize m_size = QSize(30, 30);
    ComboDelegate *m_delegate = nullptr;
    int m_maxHistoryCount = 20;

    QStringList getValues() const;
    void setValues(const QStringList &_values);

private slots:
    void removeRowSlot(int _index);

    // ISaveWidget interface
public:
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
    virtual QString getWidgetUniqueName() const override;
};

}

#endif // HISTORYTEXTEDIT_H
