#include "mylineeditplugin.h"
#include "../MyLineEdit/mylineedit.h"

MyLineEditPlugin::MyLineEditPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void MyLineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool MyLineEditPlugin::isInitialized() const
{
    return initialized;
}

QWidget *MyLineEditPlugin::createWidget(QWidget *parent)
{
    return new MyLineEdit(parent);
}

QString MyLineEditPlugin::name() const
{
    return "MyLineEdit";
}

QString MyLineEditPlugin::group() const
{
    return "Custom widgets";
}

QIcon MyLineEditPlugin::icon() const
{
    return QIcon();
}

QString MyLineEditPlugin::toolTip() const
{
    return "";
}

QString MyLineEditPlugin::whatsThis() const
{
    return "";
}

bool MyLineEditPlugin::isContainer() const
{
    return false;
}

QString MyLineEditPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"MyLineEdit\" name=\"myLineEdit\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>300</width>\n"
           "    <height>200</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString MyLineEditPlugin::includeFile() const
{
    return "CustomWidgets/MyLineEdit/MyLineEdit.h";
}
