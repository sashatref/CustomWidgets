#include "../ManageProjects/manageprojects.h"
#include "manageprojectsplugin.h"

ManageProjectsPlugin::ManageProjectsPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void ManageProjectsPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool ManageProjectsPlugin::isInitialized() const
{
    return initialized;
}

QWidget *ManageProjectsPlugin::createWidget(QWidget *parent)
{
    QVariantMap m;
    m.insert("Project 1", 1);
    m.insert("Project 2", 2);
    m.insert("Project 3", 3);
    m.insert("Project 4", 4);
    m.insert("Project 5", 5);
    m.insert("Project 6", 6);
    m.insert("Project 7", 7);

    ManageProjects *widget = new ManageProjects(parent);
    widget->setProjectMap(m);
    return widget;
}

QString ManageProjectsPlugin::name() const
{
    return "ManageProjects";
}

QString ManageProjectsPlugin::group() const
{
    return "Custom widgets";
}

QIcon ManageProjectsPlugin::icon() const
{
    return QIcon();
}

QString ManageProjectsPlugin::toolTip() const
{
    return "";
}

QString ManageProjectsPlugin::whatsThis() const
{
    return "";
}

bool ManageProjectsPlugin::isContainer() const
{
    return false;
}

QString ManageProjectsPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"ManageProjects\" name=\"manageProjects\">\n"
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

QString ManageProjectsPlugin::includeFile() const
{
    return "CustomWidgets/manageprojects/manageprojects.h";
}
