#ifndef DROPDOWNP_H
#define DROPDOWNP_H

#include "../dropdown.h"

namespace CustomWidgetsQt
{

class DropdownP : public QObject
{
    Q_OBJECT
    Dropdown *q;
public:
    DropdownP(Dropdown *_q);

    QVariantList data;
};

}

#endif // DROPDOWNP_H
