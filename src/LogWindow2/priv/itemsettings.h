#pragma once

namespace CustomWidgetsQt
{


class ItemSettings
{
public:
    ItemSettings(const QColor &_backgroundColor = QColor(),
                 const QColor &_textColor = QColor(),
                 const QFont &_font = QFont(),
                 int _rowHeight = 24,
                 const QString &_tooltipPrefix = QString(),
                 const QString &_copyPrefix = QString()):
        m_backgroundColor(_backgroundColor),
        m_textColor(_textColor),
        m_font(_font),
        m_rowHeight(_rowHeight),
        m_toolTipPrefix(_tooltipPrefix),
        m_copyPrefix(_copyPrefix)
    {}

    QColor m_backgroundColor;
    QColor m_textColor;
    QFont m_font;
    int m_rowHeight;
    QString m_toolTipPrefix;
    QString m_copyPrefix;    
};

typedef QMap<QtMsgType, ItemSettings> ItemSettingsMap;

ItemSettingsMap makeDefaultSettings();
ItemSettingsMap makeDefault2Settings();

}

QDataStream &operator <<(QDataStream &s, const CustomWidgetsQt::ItemSettings &_v);
QDataStream &operator >>(QDataStream &s, CustomWidgetsQt::ItemSettings &_v);

QDataStream &operator <<(QDataStream &s, const QtMsgType &_v);
QDataStream &operator >>(QDataStream &s, QtMsgType &_v);


Q_DECLARE_METATYPE(CustomWidgetsQt::ItemSettings)
Q_DECLARE_METATYPE(CustomWidgetsQt::ItemSettingsMap)

