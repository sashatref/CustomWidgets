#ifndef EXT_COMBO_EDIT_H
#define EXT_COMBO_EDIT_H

#include <QWidget>
#include "extcombotype.h"
#include "../export.h"

class QComboBox;
class QToolButton;
class WIDGET_EXPORT ExtComboEdit : public QWidget
{
    Q_OBJECT
public:
     ExtComboEdit(QWidget *parent = 0);

     void setValuesList(const QMap<int, QString> &_values);

     void setCurrentValue(const QString &value);
     QString currentValue();

     void setType(int value);
     int getType();

public slots:
     void addComboItem(QString item);
     void removeComboItem(QString item);
     void editComboItem(QString item);

private:
    QComboBox *m_combo;
    QToolButton *m_addButton, *m_openButton;
    int m_type;

signals:
    void addClicked(QString, int type);
    void addClicked();
    void openClicked();
    void openClicked(QString, int type);

private slots:
    void onAddClick();
    void onOpenClick();
};

#endif //EXT_COMBO_EDIT_H
