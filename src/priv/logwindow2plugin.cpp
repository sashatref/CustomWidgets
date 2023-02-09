#include "../LogWindow2/logwindow2.h"
#include "logwindow2plugin.h"

namespace CustomWidgetsQt
{

LogWindow2Plugin::LogWindow2Plugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void LogWindow2Plugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool LogWindow2Plugin::isInitialized() const
{
    return initialized;
}

QWidget *LogWindow2Plugin::createWidget(QWidget *parent)
{
    return new CustomWidgetsQt::LogWindow2(parent);
}

QString LogWindow2Plugin::name() const
{
    return "CustomWidgetsQt::LogWindow2";
}

QString LogWindow2Plugin::group() const
{
    return "Custom_widgets";
}

QIcon LogWindow2Plugin::icon() const
{
    return QIcon();
}

QString LogWindow2Plugin::toolTip() const
{
    return "";
}

QString LogWindow2Plugin::whatsThis() const
{
    return "";
}

bool LogWindow2Plugin::isContainer() const
{
    return false;
}

QString LogWindow2Plugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"CustomWidgetsQt::LogWindow2\" name=\"logWindow2\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>400</width>\n"
           "    <height>200</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString LogWindow2Plugin::includeFile() const
{
    return "CustomWidgets/logwindow2/logwindow2.h";
}

}
