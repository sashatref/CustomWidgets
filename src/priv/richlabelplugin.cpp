#include "richlabelplugin.h"
#include "../RichLabel/richlabel.h"

RichLabelPlugin::RichLabelPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void RichLabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool RichLabelPlugin::isInitialized() const
{
    return initialized;
}

QWidget *RichLabelPlugin::createWidget(QWidget *parent)
{
    return new RichLabel(parent);
}

QString RichLabelPlugin::name() const
{
    return "RichLabel";
}

QString RichLabelPlugin::group() const
{
    return "Custom widgets";
}

QIcon RichLabelPlugin::icon() const
{
    return QIcon();
}

QString RichLabelPlugin::toolTip() const
{
    return "";
}

QString RichLabelPlugin::whatsThis() const
{
    return "";
}

bool RichLabelPlugin::isContainer() const
{
    return false;
}

QString RichLabelPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"RichLabel\" name=\"richLabel\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>47</width>\n"
           "    <height>13</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " <property name=\"text\">\n"
           "  <string>richLabel</string>\n"
           " </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString RichLabelPlugin::includeFile() const
{
    return "CustomWidgets/RichLabel/richlabel.h";
}
