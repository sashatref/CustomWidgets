#include "../HtmlEditor/HtmlEditor.h"
#include "HtmlEditorPlugin.h"

namespace CustomWidgetsQt
{

HtmlEditorPlugin::HtmlEditorPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void HtmlEditorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool HtmlEditorPlugin::isInitialized() const
{
    return initialized;
}

QWidget *HtmlEditorPlugin::createWidget(QWidget *parent)
{
    HtmlEditor *widget = new HtmlEditor(parent);
    return widget;
}

QString HtmlEditorPlugin::name() const
{
    return "CustomWidgetsQt::HtmlEditor";
}

QString HtmlEditorPlugin::group() const
{
    return "Custom_widgets";
}

QIcon HtmlEditorPlugin::icon() const
{
    return QIcon();
}

QString HtmlEditorPlugin::toolTip() const
{
    return "";
}

QString HtmlEditorPlugin::whatsThis() const
{
    return "";
}

bool HtmlEditorPlugin::isContainer() const
{
    return false;
}

QString HtmlEditorPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"CustomWidgetsQt::HtmlEditor\" name=\"htmlEditor\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>350</width>\n"
           "    <height>500</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString HtmlEditorPlugin::includeFile() const
{
    return "CustomWidgets/HtmlEditor/HtmlEditor.h";
}

}
