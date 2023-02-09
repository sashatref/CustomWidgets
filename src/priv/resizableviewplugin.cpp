#include "resizableviewplugin.h"
#include "../ResizableView/resizableview.h"

namespace CustomWidgetsQt
{

ResizableViewPlugin::ResizableViewPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void ResizableViewPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool ResizableViewPlugin::isInitialized() const
{
    return initialized;
}

QWidget *ResizableViewPlugin::createWidget(QWidget *parent)
{
    return new ResizableView(parent);
}

QString ResizableViewPlugin::name() const
{
    return "CustomWidgetsQt::ResizableView";
}

QString ResizableViewPlugin::group() const
{
    return "Custom_widgets";
}

QIcon ResizableViewPlugin::icon() const
{
    return QIcon();
}

QString ResizableViewPlugin::toolTip() const
{
    return "";
}

QString ResizableViewPlugin::whatsThis() const
{
    return "";
}

bool ResizableViewPlugin::isContainer() const
{
    return false;
}

QString ResizableViewPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"CustomWidgetsQt::ResizableView\" name=\"resizableView\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>250</width>\n"
           "    <height>250</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString ResizableViewPlugin::includeFile() const
{
    return "CustomWidgets/ResizableView/resizableview.h";
}

}
