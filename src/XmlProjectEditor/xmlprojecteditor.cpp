#include "../project_pch.h"
#include "xmlprojecteditor.h"
#include "ui_xmlprojecteditor.h"

#include "xmlitemdelegate.h"

void XmlProjectEditor::loadFunction(QTreeWidget *_treeWidget, QTreeWidgetItem *_parentItem, const QDomNode * const _nodeItem)
{
    QTreeWidgetItem *subitem = new QTreeWidgetItem();
    subitem->setFlags(subitem->flags() | Qt::ItemIsEditable);
    subitem->setText(0, _nodeItem->toElement().nodeName());

    if(_nodeItem->isText())
    {
        _parentItem->setText(2, _nodeItem->toText().nodeValue().trimmed());
        return;
    }

    if(!_parentItem)
    {
        _treeWidget->addTopLevelItem(subitem);
        _parentItem = subitem;
    } else
    {
        _parentItem->addChild(subitem);
    }

    QVariantMap attributes;
    for(int j = 0 ; j < _nodeItem->attributes().size(); j++)
    {
        QDomAttr attr = _nodeItem->toElement().attributes().item(j).toAttr();
        attributes[attr.name()] = attr.value();
    }

    subitem->setData(1, Qt::UserRole, attributes);
    subitem->setData(1, Qt::DisplayRole, XmlItemDelegate::variantMapToString(attributes));

    for(int i = 0 ; i < _nodeItem->childNodes().size(); i++)
    {
        QDomNode node = _nodeItem->childNodes().at(i);
        loadFunction(_treeWidget, subitem, &node);
    }
}

void XmlProjectEditor::saveFunction(QTreeWidget *_treeWidget, QTreeWidgetItem *_parentItem, QDomNode * const _parentNode, QDomDocument * const _doc)
{
    if(!_parentItem) {return;}

    QString nodeName        = _parentItem->text(0);
    QVariantMap attributes  = _parentItem->data(1, Qt::UserRole).toMap();
    QString nodeValue       = _parentItem->text(2);

    QDomElement element = _doc->createElement(nodeName);

    element.appendChild(_doc->createTextNode(nodeValue));
    for(int i = 0 ; i < attributes.keys().size(); i++)
    {
        QString attrName = attributes.keys().at(i);
        QString attrValue = attributes[attrName].toString();
        element.setAttribute(attrName, attrValue);
    }

    _parentNode->appendChild(element);

    for(int i = 0 ; i < _parentItem->childCount(); i++)
    {
        saveFunction(_treeWidget, _parentItem->child(i), &element, _doc);
    }
}

void XmlProjectEditor::createNode(QTreeWidget *_treeWidget, QTreeWidgetItem *_parent)
{
    QTreeWidgetItem *child = new QTreeWidgetItem();
    child->setFlags(child->flags() | Qt::ItemIsEditable);
    child->setText(0, "child");

    if(_parent)
    {
        _parent->addChild(child);
        _treeWidget->expandItem(_parent);
    } else
    {
        _treeWidget->addTopLevelItem(child);
    }

    _treeWidget->editItem(child, 0);
}

void XmlProjectEditor::editNode(QTreeWidget *_treeWidget, QTreeWidgetItem *_selectedItem)
{
    _treeWidget->editItem(_selectedItem, 0);
}

XmlProjectEditor::XmlProjectEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XmlProjectEditor),
    m_copyItemList(),
    m_rowHeight(16),
    m_isCheckChildren(true)
{
    ui->setupUi(this);

    iniUiElements();

    connect(ui->treeWidget->model(), &QAbstractItemModel::dataChanged, this, &XmlProjectEditor::onItemChanged);
}

XmlProjectEditor::~XmlProjectEditor()
{
    delete ui;
}

QTreeWidget *XmlProjectEditor::getTreeWidget() const
{
    return ui->treeWidget;
}

void XmlProjectEditor::setCustomDelegate(QAbstractItemDelegate * const _delegate)
{
    ui->treeWidget->setItemDelegate(_delegate);
}

void XmlProjectEditor::iniUiElements()
{
    QAction *sep1 = new QAction(ui->treeWidget);
    sep1->setSeparator(true);
    QAction *sep2 = new QAction(ui->treeWidget);
    sep2->setSeparator(true);
    QAction *sep3 = new QAction(ui->treeWidget);
    sep3->setSeparator(true);

    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::Interactive);
    ui->treeWidget->addAction(ui->actionAddSubNode);
    ui->treeWidget->addAction(ui->actionEditNode);
    ui->treeWidget->addAction(ui->actionRemoveNode);
    ui->treeWidget->addAction(sep1);
    ui->treeWidget->addAction(ui->actionExpandSubItems);
    ui->treeWidget->addAction(ui->actionCollapseSubItems);
    ui->treeWidget->addAction(sep2);
    ui->treeWidget->addAction(ui->actionExpandAll);
    ui->treeWidget->addAction(ui->actionCollapseAll);
    ui->treeWidget->addAction(sep3);
    ui->treeWidget->addAction(ui->actionCopyNode);
    ui->treeWidget->addAction(ui->actionPasteNode);

    ui->actionPasteNode->setEnabled(false);

    ui->treeWidget->setItemDelegate(new XmlItemDelegate(this));
}

void XmlProjectEditor::loadFromXml(const QDir &_path)
{
    loadFromText(Text::readFromFile(_path.path()));
}

void XmlProjectEditor::loadFromText(const QString &_text)
{
    QDomDocument doc;
    doc.setContent(_text);

    QDomElement rootElement = doc.documentElement();

    preLoad();
    loadFunction(ui->treeWidget, 0, &rootElement);
    ui->treeWidget->expandAll();
    ui->treeWidget->header()->resizeSections(QHeaderView::Stretch);
}



void loadJson(QTreeWidget *_treeWidget, QTreeWidgetItem *_parentItem, const QVariantMap &_item)
{
    QTreeWidgetItem *subitem = new QTreeWidgetItem();
    subitem->setFlags(subitem->flags());
    subitem->setText(0, _item["label"].toString());
    subitem->setText(2, _item["path"].toString());

    bool isChecked = _item["checked"].toBool();

    subitem->setCheckState(0, isChecked ? Qt::Checked : Qt::Unchecked);

    if(!_parentItem)
    {
        _treeWidget->addTopLevelItem(subitem);
        _parentItem = subitem;
    } else
    {
        _parentItem->addChild(subitem);
    }

    QVariantList childList = _item["children"].toList();

    for(int i = 0 ; i < childList.size(); i++)
    {
        QVariantMap map = childList.at(i).toMap();
        loadJson(_treeWidget, subitem, map);
    }
}


void XmlProjectEditor::onItemChanged(const QModelIndex &topLeft, const QModelIndex &/*bottomRight*/, const QVector<int> &/*_roles*/)
{
    if(m_isCheckChildren)
    {
        QTreeWidgetItem *item = static_cast<QTreeWidgetItem*>(topLeft.internalPointer());

        QList<QTreeWidgetItem*> childItems = TreeWidgetUtils::getAllSubItems(item);
        for(int i = 0 ; i < childItems.size(); i++)
        {
            childItems.at(i)->setCheckState(0, item->checkState(0));
        }
    }
}

void XmlProjectEditor::loadFromJson(const QString &_json)
{
    clear();
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(_json.toUtf8(), &error);
    QVariantMap m = document.object().toVariantMap();

    //preLoad();
    loadJson(ui->treeWidget, 0, m);
    ui->treeWidget->expandAll();
    ui->treeWidget->header()->resizeSections(QHeaderView::Stretch);
}

void saveJson(QTreeWidget *_treeWidget, QTreeWidgetItem *_parentItem, QVariantMap &_item)
{
    if(!_parentItem) return;

    const QString label = _parentItem->text(0);
    const QString path = _parentItem->text(2);
    const bool isChecked = _parentItem->checkState(0) == Qt::Checked;

    QVariantList children;

    for(int i = 0 ; i < _parentItem->childCount(); i++)
    {
        QVariantMap itemMap;
        saveJson(_treeWidget, _parentItem->child(i), itemMap);
        children.append(itemMap);
    }

    _item["label"] = label;
    _item["path"] = path;
    _item["checked"] = isChecked;
    _item["children"] = children;
}

QString XmlProjectEditor::saveToJson()
{
    QVariantMap m;

    saveJson(ui->treeWidget, ui->treeWidget->topLevelItem(0), m);

    return QJsonDocument(QJsonObject::fromVariantMap(m)).toJson();
}



void XmlProjectEditor::saveToXml(const QDir &_path)
{
    QDomDocument doc;
    doc.appendChild(doc.createProcessingInstruction("xml",
                                                        QString("version=\"%1\" encoding=\"%2\"")
                                                        .arg("1.0")
                                                        .arg("UTF-8")));

    saveFunction(ui->treeWidget, getTreeWidget()->topLevelItem(0), &doc, &doc);
    Text::writeToFile(_path.path(), doc.toString(4).toUtf8(), false);
}

void XmlProjectEditor::setRowHeight(int _height)
{
    m_rowHeight = _height;

    //TODO:: доделать
//    for(int i = 0 ; i < ui->treeWidget->topLevelItemCount(); i++)
//    {
//        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
//        item->setSizeHint(0, );
//    }
}

int XmlProjectEditor::getRowHeight() const
{
    return m_rowHeight;
}

void XmlProjectEditor::resetRowHeight()
{
    setRowHeight(16);
}

QString XmlProjectEditor::getNodePath(QTreeWidgetItem * const item) const
{
    QStringList pathItems;

    QTreeWidgetItem *currentItem = item;

    if(!currentItem) return "";

    do
    {
        pathItems.insert(0, currentItem->text(0));
        currentItem = currentItem->parent();
    }while(currentItem);

    return pathItems.join("/");
}

void XmlProjectEditor::clear()
{
    ui->treeWidget->clear();
    m_copyItemList.clear();
}

QTreeWidgetItem *XmlProjectEditor::getTopItem() const
{
    return getTreeWidget()->topLevelItem(0);
}

void XmlProjectEditor::setCheckState(QTreeWidgetItem *_item, Qt::CheckState _state)
{
    m_isCheckChildren = false;

    _item->setCheckState(0, _state);

    m_isCheckChildren = true;
}


void XmlProjectEditor::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Delete)
    {
        on_actionRemoveNode_triggered();
    }
}

void XmlProjectEditor::on_actionAddSubNode_triggered()
{
    QList<QTreeWidgetItem*> selected = ui->treeWidget->selectedItems();
    createNode(ui->treeWidget, selected.size() ? selected.first() : 0);
}

void XmlProjectEditor::on_actionEditNode_triggered()
{
    QList<QTreeWidgetItem*> selected = ui->treeWidget->selectedItems();
    if(selected.size() > 0)
    {
        editNode(ui->treeWidget, selected.first());
    }
}

void XmlProjectEditor::on_actionRemoveNode_triggered()
{
    QList<QTreeWidgetItem*> selected = ui->treeWidget->selectedItems();

    qDeleteAll(selected);

    //проверяем, нет ли кого-то из удаляемых в буфере для копирования
    //если есть, то эти значения удаляем из буфера
    for(int i = m_copyItemList.size() - 1; i > -1; i--)
    {
        if(selected.contains(m_copyItemList.at(i)))
        {
            m_copyItemList.removeAt(i);
        }
    }

    //если буфер пустой, то деактивируем пункт меню
    if(m_copyItemList.size() == 0)
    {
        ui->actionPasteNode->setEnabled(false);
    }
}

void XmlProjectEditor::on_actionCollapseAll_triggered()
{
    ui->treeWidget->collapseAll();
}

void XmlProjectEditor::on_actionExpandAll_triggered()
{
    ui->treeWidget->expandAll();
}

void XmlProjectEditor::on_actionCopyNode_triggered()
{
    QList<QTreeWidgetItem*> selected = ui->treeWidget->selectedItems();
    if(selected.size() > 0)
    {
        m_copyItemList = selected;
        ui->actionPasteNode->setEnabled(true);
    }
}

void XmlProjectEditor::on_actionPasteNode_triggered()
{
    QList<QTreeWidgetItem*> selected = ui->treeWidget->selectedItems();
    if(selected.size() > 0)
    {
        QList<QTreeWidgetItem*> items;
        for(int i = 0 ; i < m_copyItemList.size(); i++)
        {
            items.append(m_copyItemList.at(i)->clone());
            selected.first()->addChildren(items);
        }
    }
}


void expandItems(QTreeWidget *const tree, QTreeWidgetItem *const item, bool expand)
{
    if(!item->childCount()) return;

    expand ? tree->expandItem(item) : tree->collapseItem(item);
    for(int i = 0 ; i < item->childCount(); i++)
    {
        expandItems(tree, item->child(i), expand);
    }
}

void XmlProjectEditor::on_actionExpandSubItems_triggered()
{
    QList<QTreeWidgetItem*> selected = ui->treeWidget->selectedItems();
    if(selected.size() > 0)
    {
        expandItems(ui->treeWidget, selected.first(), true);
    }
}

void XmlProjectEditor::on_actionCollapseSubItems_triggered()
{
    QList<QTreeWidgetItem*> selected = ui->treeWidget->selectedItems();
    if(selected.size() > 0)
    {
        expandItems(ui->treeWidget, selected.first(), false);
    }
}




