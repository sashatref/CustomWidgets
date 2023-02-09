#ifndef XMLPROJECT_EDITOR_H
#define XMLPROJECT_EDITOR_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QDir>
#include <functional>
#include <QDomNodeList>

#include "../export.h"

namespace Ui {
class XmlProjectEditor;
}

typedef std::function<void(QTreeWidget*, QTreeWidgetItem*, const QDomNode *const)> LoadFunction;
typedef std::function<void(QTreeWidget*, QTreeWidgetItem*, QDomNode *const, QDomDocument *const)> SaveFunction;
typedef std::function<void(QTreeWidget*, QTreeWidgetItem*, const QString&)> CreateNodeHandler;

class WIDGET_EXPORT XmlProjectEditor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int rowHeight READ getRowHeight WRITE setRowHeight RESET resetRowHeight)
public:


    explicit XmlProjectEditor(QWidget *parent = 0);
    virtual ~XmlProjectEditor();

    QTreeWidget *getTreeWidget() const;

    void setCustomDelegate(QAbstractItemDelegate *const _delegate);

    void loadFromText(const QString &_text);

    void loadFromJson(const QString &_json);
    QString saveToJson();

    void loadFromXml(const QDir &_path);
    void saveToXml(const QDir &_path);

    void setRowHeight(int _height);
    int getRowHeight() const;
    void resetRowHeight();

    virtual QString getNodePath(QTreeWidgetItem *const item) const;

    void clear();

    QTreeWidgetItem *getTopItem() const;

    void setCheckState(QTreeWidgetItem *_item, Qt::CheckState _state);

protected:
    virtual void preLoad(){}
    virtual void loadFunction(QTreeWidget *_treeWidget, QTreeWidgetItem *_parentItem, const QDomNode *const _nodeItem);
    virtual void saveFunction(QTreeWidget *_treeWidget, QTreeWidgetItem *_parent, QDomNode *const _nodeItem, QDomDocument *const _doc);
    virtual void createNode(QTreeWidget *_treeWidget, QTreeWidgetItem *_parent);
    virtual void editNode(QTreeWidget *_treeWidget, QTreeWidgetItem *_selectedItem);

    void keyPressEvent(QKeyEvent *e) override;

private slots:
    // -------- slots
    void on_actionAddSubNode_triggered();
    void on_actionEditNode_triggered();
    void on_actionRemoveNode_triggered();
    void on_actionCollapseAll_triggered();
    void on_actionExpandAll_triggered();
    void on_actionCopyNode_triggered();
    void on_actionPasteNode_triggered();
    void on_actionExpandSubItems_triggered();
    void on_actionCollapseSubItems_triggered();
    // ------- /slots

    void onItemChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

private:
    Ui::XmlProjectEditor *ui;

    QList<QTreeWidgetItem*> m_copyItemList;
    int m_rowHeight;
    bool m_isCheckChildren;

    void iniUiElements();
};

#endif //XMLPROJECT_EDITOR_H
