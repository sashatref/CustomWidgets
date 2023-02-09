#ifndef LISTVIEWMODEL_H
#define LISTVIEWMODEL_H

#include "project_pch.h"

#include "itemsettings.h"

namespace CustomWidgetsQt
{

struct DataStorage
{
    DataStorage(const QString &_text = "", const QVariant &_v = QVariant());

    QString text;
    QVariant data;
};

class ListViewModel : public QAbstractListModel
{
public:
    ListViewModel(QObject *_parent = 0);

    bool updateModel();

    void addMessage(const QString &_msg, QtMsgType _type, const QVariant &_userData);

    void clearAll();

    QString makeText(const QList<int> &_rows);
    QString makeAllText();

    ItemSettingsMap m_configMap;

    QModelIndex getLastRow() const;
    QModelIndex getFirstRow() const;

    int maximumMsgCount = 1000000;
    int msgCheckOverhead = 100000;

public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

private:
    QString makeText(const QPair<QtMsgType, DataStorage> &_msg);
    QList<QPair<QtMsgType, DataStorage>> getMessages(const QList<int> &_rows) const;
    bool isValidRow(int _row) const;

    void checkForMaxMsgCount();

    QList<QPair<QtMsgType, DataStorage>> m_messages;

    void initBaseConfig();

    bool m_needToUpdate = false;
};

}

#endif // LISTVIEWMODEL_H
