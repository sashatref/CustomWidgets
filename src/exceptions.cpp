#include "exceptions.h"

namespace CustomWidgets
{
    BaseException::BaseException(const QString &_text) :
        HelperLibrary::UserExceptions::BaseException(QString("CustomWidgets | %1").arg(_text).toStdString().c_str())
    {

    }

    ToObjectException::ToObjectException(const QVariant &_value):
        BaseException(QString(
                          "You must register \"%1\" <%2> to \"QObject*\" converter before using this function.\n"
                          "Invoke this code at start of programm:\n"
                          "QMetaType::registerConverter<%1, QObject*>([](const %1 &_value)\n"
                          "{\n"
                          "    return const_cast<%1*>(&_value);\n"
                          "});")
                      .arg(_value.typeName())
                      .arg(_value.userType())
                      )
    {

    }
}

