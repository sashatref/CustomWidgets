#include "HistoryTextEditPlugin.h"
#include "../HistoryTextEdit/historytextedit.h"

namespace CustomWidgetsQt
{

HistoryTextEditPlugin::HistoryTextEditPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void HistoryTextEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool HistoryTextEditPlugin::isInitialized() const
{
    return initialized;
}

QWidget *HistoryTextEditPlugin::createWidget(QWidget *parent)
{
    CustomWidgetsQt::HistoryTextEdit *widget = new CustomWidgetsQt::HistoryTextEdit(parent);
    return widget;
}

QString HistoryTextEditPlugin::name() const
{
    return "CustomWidgetsQt::HistoryTextEdit";
}

QString HistoryTextEditPlugin::group() const
{
    return "Custom_widgets";
}

QIcon HistoryTextEditPlugin::icon() const
{
    return QIcon();
}

QString HistoryTextEditPlugin::toolTip() const
{
    return "";
}

QString HistoryTextEditPlugin::whatsThis() const
{
    return "";
}

bool HistoryTextEditPlugin::isContainer() const
{
    return false;
}

QString HistoryTextEditPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"CustomWidgetsQt::HistoryTextEdit\" name=\"historyTextEdit\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>200</width>\n"
           "    <height>60</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString HistoryTextEditPlugin::includeFile() const
{
    return "CustomWidgets/HistoryTextEdit/historytextedit.h";
}

}
