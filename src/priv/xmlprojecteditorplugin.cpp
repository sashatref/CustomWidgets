#include "xmlprojecteditorplugin.h"
#include "../XmlProjectEditor/xmlprojecteditor.h"

XmlProjectEditorPlugin::XmlProjectEditorPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void XmlProjectEditorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool XmlProjectEditorPlugin::isInitialized() const
{
    return initialized;
}

QWidget *XmlProjectEditorPlugin::createWidget(QWidget *parent)
{
    return new XmlProjectEditor(parent);
}

QString XmlProjectEditorPlugin::name() const
{
    return "XmlProjectEditor";
}

QString XmlProjectEditorPlugin::group() const
{
    return "Custom widgets";
}

QIcon XmlProjectEditorPlugin::icon() const
{
    return QIcon();
}

QString XmlProjectEditorPlugin::toolTip() const
{
    return "";
}

QString XmlProjectEditorPlugin::whatsThis() const
{
    return "";
}

bool XmlProjectEditorPlugin::isContainer() const
{
    return false;
}

QString XmlProjectEditorPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XmlProjectEditor\" name=\"xmlProjectEditor\">\n"
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

QString XmlProjectEditorPlugin::includeFile() const
{
    return "CustomWidgets/XmlProjectEditor/xmlprojecteditor.h";
}
