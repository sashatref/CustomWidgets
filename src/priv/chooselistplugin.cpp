#include "chooselistplugin.h"
#include "../ChooseList/chooselist.h"

ChooseListPlugin::ChooseListPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void ChooseListPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool ChooseListPlugin::isInitialized() const
{
    return initialized;
}

QWidget *ChooseListPlugin::createWidget(QWidget *parent)
{
    return new ChooseList(parent);
}

QString ChooseListPlugin::name() const
{
    return "ChooseList";
}

QString ChooseListPlugin::group() const
{
    return "Custom widgets";
}

QIcon ChooseListPlugin::icon() const
{
    return QIcon();
}

QString ChooseListPlugin::toolTip() const
{
    return "";
}

QString ChooseListPlugin::whatsThis() const
{
    return "";
}

bool ChooseListPlugin::isContainer() const
{
    return false;
}

QString ChooseListPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"ChooseList\" name=\"chooseList\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>200</width>\n"
           "    <height>51</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString ChooseListPlugin::includeFile() const
{
    return "CustomWidgets/ChooseList/chooselist.h";
}
