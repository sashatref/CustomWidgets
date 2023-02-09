#include "listviewmodel.h"

namespace CustomWidgetsQt
{

ListViewModel::ListViewModel(QObject *_parent):
    QAbstractListModel(_parent)
{
    initBaseConfig();
}

bool ListViewModel::updateModel()
{
    if(m_needToUpdate)
    {
        beginResetModel();
        checkForMaxMsgCount();
        endResetModel();
        m_needToUpdate = false;
        return true;
    }

    return false;
}

void ListViewModel::addMessage(const QString &_msg, QtMsgType _type, const QVariant &_userData)
{
    m_messages.append(qMakePair(_type, DataStorage(_msg, _userData)));
    m_needToUpdate = true;
}

void ListViewModel::clearAll()
{
    m_messages.clear();
    m_needToUpdate = true;
}

QList<QPair<QtMsgType, DataStorage> > ListViewModel::getMessages(const QList<int> &_rows) const
{
    QList<QPair<QtMsgType, DataStorage> > out;

    for(auto &row : _rows)
    {
        out << m_messages[row];
    }

    return out;
}

QString ListViewModel::makeText(const QList<int> &_rows)
{
    QStringList out;

    for(auto &item : _rows)
    {
        if(isValidRow(item))
        {
            out << makeText(m_messages.at(item));
        }
    }

    return out.join("\r\n");
}

QString ListViewModel::makeAllText()
{
    QStringList out;

    for(auto &item : m_messages)
    {
        out << makeText(item);
    }

    return out.join("\r\n");
}

QModelIndex ListViewModel::getLastRow() const
{
    return index(m_messages.size() - 1);
}

QModelIndex ListViewModel::getFirstRow() const
{
    return index(0);
}


QString ListViewModel::makeText(const QPair<QtMsgType, DataStorage> &_msg)
{
    return QString("(%1) | %2").arg(m_configMap[_msg.first].m_copyPrefix).arg(_msg.second.text);
}



int ListViewModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_messages.size();
}

QVariant ListViewModel::data(const QModelIndex &index, int role) const
{
    QVariant out;

    const int row = index.row();

    if(!index.isValid() || row < 0 || row >= m_messages.size())
    {
        return out;
    }

    const QPair<QtMsgType, DataStorage> &item = m_messages.at(row);
    const ItemSettings &config = m_configMap[item.first];

    if(index.isValid() && index.row() < m_messages.size())
    {
        switch(role)
        {
        case Qt::DisplayRole:
            out = m_messages[index.row()].second.text;
            break;

        case Qt::SizeHintRole:
            out = QSize(config.m_rowHeight, config.m_rowHeight);
            break;

        case Qt::BackgroundColorRole:
            out = config.m_backgroundColor;
            break;

        case Qt::TextColorRole:
            out = config.m_textColor;
            break;

        case Qt::ToolTipRole:
            out = QString("%1: %2").arg(config.m_toolTipPrefix).arg(item.second.text);
            break;

        case Qt::FontRole:
            out = config.m_font;
            break;
        case Qt::UserRole:
            out = m_messages[index.row()].second.data;
            break;
        }
    }

    return out;
}

bool ListViewModel::isValidRow(int _row) const
{
    return _row > -1 && _row < m_messages.size();
}

void ListViewModel::checkForMaxMsgCount()
{
    const int diff = m_messages.size() - maximumMsgCount;
    if (diff > msgCheckOverhead)
    {
        m_messages.erase(m_messages.begin(), m_messages.begin() + diff);
    }
}

void ListViewModel::initBaseConfig()
{
    m_configMap = makeDefaultSettings();
}

DataStorage::DataStorage(const QString &_text, const QVariant &_v):
    text(_text),
    data(_v)
{

}

}
