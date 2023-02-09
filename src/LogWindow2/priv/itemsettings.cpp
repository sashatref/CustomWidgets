#include "itemsettings.h"

Q_DECLARE_METATYPE(QtMsgType)

PS_REGISTER_CONSTRUCTOR_FUNC([]
{
    qRegisterMetaTypeStreamOperators<QtMsgType>();
    qRegisterMetaTypeStreamOperators<CustomWidgetsQt::ItemSettings>();
    qRegisterMetaTypeStreamOperators<CustomWidgetsQt::ItemSettingsMap>();
});


QDataStream &operator <<(QDataStream &s, const CustomWidgetsQt::ItemSettings &_v)
{
    int version = 1;
    s
            << version
            << _v.m_backgroundColor
            << _v.m_copyPrefix
            << _v.m_font
            << _v.m_rowHeight
            << _v.m_textColor
            << _v.m_toolTipPrefix;

    return s;
}

QDataStream &operator >>(QDataStream &s, CustomWidgetsQt::ItemSettings &_v)
{
    int version = 0;
    s >> version;

    switch(version)
    {
    case 1:
        s
                >> _v.m_backgroundColor
                >> _v.m_copyPrefix
                >> _v.m_font
                >> _v.m_rowHeight
                >> _v.m_textColor
                >> _v.m_toolTipPrefix;
    }

    return s;
}

QDataStream &operator >>(QDataStream &s, QtMsgType &_v)
{
    int t = 0;
    s >> t;
    _v = static_cast<QtMsgType>(t);
    return s;
}

QDataStream &operator <<(QDataStream &s, const QtMsgType &_v)
{
    s << static_cast<int>(_v);
    return s;
}

namespace CustomWidgetsQt
{
ItemSettingsMap makeDefaultSettings()
{
    ItemSettingsMap out;

    QFont baseFont;
    const int baseRowHeight = 24;

    out[QtDebugMsg] = ItemSettings(QColor(0x00, 0x00, 0xFF, 0x80),
                                   Qt::white, baseFont, baseRowHeight, QObject::tr("Отладка"), ("d"));

    out[QtInfoMsg] = ItemSettings(Qt::white,
                                  Qt::black, baseFont, baseRowHeight, QObject::tr("Текст"), "i");

    out[QtWarningMsg] = ItemSettings(QColor(0xFF, 0xFF, 0x00, 0x50),
                                     Qt::black, baseFont, baseRowHeight, QObject::tr("Предупреждение"), "w");

    out[QtCriticalMsg] = ItemSettings(QColor(0xD9, 0x06, 0x06, 0x80),
                                      Qt::black, baseFont, baseRowHeight, QObject::tr("Тревога"), "c");

    out[QtFatalMsg] = ItemSettings(QColor(0xD9, 0x06, 0x06),
                                   QColor("white"), baseFont, baseRowHeight, QObject::tr("Критическая ошибка"), "f");

    return out;
}

ItemSettingsMap makeDefault2Settings()
{
    ItemSettingsMap out;

    QFont baseFont;
    const int baseRowHeight = 24;

    out[QtDebugMsg] = ItemSettings(Qt::white, QColor(0, 85, 0, 255),
                                   baseFont, baseRowHeight, QObject::tr("Отладка"), ("d"));

    {
        QFont f;
        f.setWeight(QFont::Bold);
        out[QtWarningMsg] = ItemSettings(Qt::white, QColor(0, 0, 127, 255),
                                         f, baseRowHeight, QObject::tr("Предупреждение"), "w");
    }

    {
        QFont f;
        f.setPointSize(10);
        f.setWeight(QFont::Bold);
        out[QtCriticalMsg] = ItemSettings(Qt::white,
                                          Qt::red, f, baseRowHeight, QObject::tr("Тревога"), "c");
    }

    out[QtFatalMsg] = ItemSettings(QColor(217, 6, 6),
                                   Qt::white, baseFont, baseRowHeight, QObject::tr("Критическая ошибка"), "f");

    out[QtInfoMsg] = ItemSettings(Qt::white, Qt::blue, baseFont, baseRowHeight, QObject::tr("Текст"), "i");

    return out;
}






}


