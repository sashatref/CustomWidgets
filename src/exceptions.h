#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QString>
#include <QVariant>
#include <exception>

#include <HelperLibrary/Exceptions/userexception.h>

#include "export.h"

namespace CustomWidgets
{
    class WIDGET_EXPORT BaseException : HelperLibrary::UserExceptions::BaseException
    {
    public:
        BaseException(const QString &_text);
    };

    class WIDGET_EXPORT ToObjectException : public BaseException
    {
    public:
        ToObjectException(const QVariant &_value);
    };
}


#endif //EXCEPTIONS_H
