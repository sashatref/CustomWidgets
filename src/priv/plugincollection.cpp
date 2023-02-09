#include "plugincollection.h"
#include "richlabelplugin.h"
#include "chooselistplugin.h"
#include "resizableviewplugin.h"
#include "manageprojectsplugin.h"
#include "mycomboboxplugin.h"
#include "xmlprojecteditorplugin.h"
#include "mylineeditplugin.h"
#include "HtmlEditorPlugin.h"
#include "ConsoleEditorPlugin.h"
#include "groupcomboboxplugin.h"
#include "HistoryTextEditPlugin.h"
#include "logwindow2plugin.h"

PluginsCollection::PluginsCollection(QObject*)
{
    widgets
            << new RichLabelPlugin(this)
            << new ChooseListPlugin(this)
            << new ManageProjectsPlugin(this)
            << new MyComboBoxPlugin(this)
            << new XmlProjectEditorPlugin(this)
            << new MyLineEditPlugin(this)
            << new CustomWidgetsQt::HtmlEditorPlugin(this)
            << new CustomWidgetsQt::ResizableViewPlugin(this)
            << new CustomWidgetsQt::ConsoleEditorPlugin(this)
            << new GroupComboBoxPlugin(this)
            << new CustomWidgetsQt::HistoryTextEditPlugin(this)
            << new CustomWidgetsQt::LogWindow2Plugin(this);
}

QList<QDesignerCustomWidgetInterface *> PluginsCollection::customWidgets() const
{
    return widgets;
}
