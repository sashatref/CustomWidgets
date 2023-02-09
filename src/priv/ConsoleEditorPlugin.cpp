#include "ConsoleEditorPlugin.h"
#include "../ConsoleEditor/consoleeditor.h"

namespace CustomWidgetsQt
{

ConsoleEditorPlugin::ConsoleEditorPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void ConsoleEditorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool ConsoleEditorPlugin::isInitialized() const
{
    return initialized;
}

QWidget *ConsoleEditorPlugin::createWidget(QWidget *parent)
{
    return new CustomWidgetsQt::ConsoleEditor(parent);
}

QString ConsoleEditorPlugin::name() const
{
    return "CustomWidgetsQt::ConsoleEditor";
}

QString ConsoleEditorPlugin::group() const
{
    return "Custom_widgets";
}

QIcon ConsoleEditorPlugin::icon() const
{
    return QIcon();
}

QString ConsoleEditorPlugin::toolTip() const
{
    return "";
}

QString ConsoleEditorPlugin::whatsThis() const
{
    return "";
}

bool ConsoleEditorPlugin::isContainer() const
{
    return false;
}

QString ConsoleEditorPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"CustomWidgetsQt::ConsoleEditor\" name=\"consoleEditor\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>150</width>\n"
           "    <height>200</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString ConsoleEditorPlugin::includeFile() const
{
    return "CustomWidgets/ConsoleEditor/ConsoleEditor.h";
}

}
