#ifndef GROUPCOMBOBOX_H
#define GROUPCOMBOBOX_H

#include <QComboBox>
#include "../export.h"

class WIDGET_EXPORT GroupComboBox : public QComboBox
{
    Q_OBJECT
public:
    GroupComboBox(QWidget *_parent = 0);

    void addParentItem( const QString& text );
    void addChildItem( const QString& text, const QVariant& data );
};



#endif // GROUPCOMBOBOX_H
