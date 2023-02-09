#include "groupcomboboxplugin.h"
#include "../GroupComboBox/groupcombobox.h"

GroupComboBoxPlugin::GroupComboBoxPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void GroupComboBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool GroupComboBoxPlugin::isInitialized() const
{
    return initialized;
}

QWidget *GroupComboBoxPlugin::createWidget(QWidget *parent)
{
    return new GroupComboBox(parent);
}

QString GroupComboBoxPlugin::name() const
{
    return "GroupComboBox";
}

QString GroupComboBoxPlugin::group() const
{
    return "Custom widgets";
}

QIcon GroupComboBoxPlugin::icon() const
{
    return QIcon();
}

QString GroupComboBoxPlugin::toolTip() const
{
    return "";
}

QString GroupComboBoxPlugin::whatsThis() const
{
    return "";
}

bool GroupComboBoxPlugin::isContainer() const
{
    return false;
}

QString GroupComboBoxPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"GroupComboBox\" name=\"groupComboBox\">\n"
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

QString GroupComboBoxPlugin::includeFile() const
{
    return "CustomWidgets/GroupComboBox/groupcombobox.h";
}
