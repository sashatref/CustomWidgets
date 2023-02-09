#ifndef ITEMSETTINGSEDITOR_H
#define ITEMSETTINGSEDITOR_H

#include <QWidget>
#include "itemsettings.h"

namespace Ui {
class ItemSettingsEditor;
}

class ItemSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ItemSettingsEditor(QWidget *parent = nullptr);
    ~ItemSettingsEditor();

    void setSettings(const CustomWidgetsQt::ItemSettings &_s);
    CustomWidgetsQt::ItemSettings getSettings();

private slots:
    void on_bgColorConfBtn_clicked();
    void on_textColorConfBtn_clicked();
    void on_fontConfgBtn_clicked();

    void on_rowHeightSpin_valueChanged(int arg1);

private:
    Ui::ItemSettingsEditor *ui;

    void updateTestStyle();
    void updateFields();

    QString makeRgbaColor(const QColor &_col);

    CustomWidgetsQt::ItemSettings m_config;
};

#endif // ITEMSETTINGSEDITOR_H
