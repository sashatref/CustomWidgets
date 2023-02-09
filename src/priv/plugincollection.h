#ifndef PLUGIN_COLLECTION_H
#define PLUGIN_COLLECTION_H

#include <QtDesigner/QtDesigner>

/*!
 * \brief объявление виджетов которые будут доступны в QtDesigner
 */

class PluginsCollection : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetsInterface")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
public:
    PluginsCollection(QObject *parent = 0);

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> widgets;
};

#endif //PLUGIN_COLLECTION_H
