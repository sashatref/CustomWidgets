#include "mycomboboxplugin.h"
#include "../MyComboBox/mycombobox.h"

MyComboBoxPlugin::MyComboBoxPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void MyComboBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool MyComboBoxPlugin::isInitialized() const
{
    return initialized;
}

QWidget *MyComboBoxPlugin::createWidget(QWidget *parent)
{
    return new MyComboBox(parent);
}

QString MyComboBoxPlugin::name() const
{
    return "MyComboBox";
}

QString MyComboBoxPlugin::group() const
{
    return "Custom widgets";
}

QIcon MyComboBoxPlugin::icon() const
{
    return QIcon();
}

QString MyComboBoxPlugin::toolTip() const
{
    return "";
}

QString MyComboBoxPlugin::whatsThis() const
{
    return "";
}

bool MyComboBoxPlugin::isContainer() const
{
    return false;
}

QString MyComboBoxPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"MyComboBox\" name=\"myComboBox\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>200</width>\n"
           "    <height>24</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"sizePolicy\">\n"
           "    <sizepolicy hsizetype=\"Preferred\" vsizetype=\"Fixed\">\n"
           "      <horstretch>0</horstretch>\n"
           "      <verstretch>0</verstretch>\n"
           "     </sizepolicy>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString MyComboBoxPlugin::includeFile() const
{
    return "CustomWidgets/MyComboBox/mycombobox.h";
}
