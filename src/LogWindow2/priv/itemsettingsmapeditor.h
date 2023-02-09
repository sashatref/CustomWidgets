#ifndef ITEMSETTINGSMAPEDITOR_H
#define ITEMSETTINGSMAPEDITOR_H

#include <QDialog>
#include "itemsettings.h"

namespace Ui {
class ItemSettingsMapEditor;
}

class ItemSettingsMapEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ItemSettingsMapEditor(QWidget *parent = nullptr);
    ~ItemSettingsMapEditor();

    void setSettingsMap(const CustomWidgetsQt::ItemSettingsMap &_editor);
    CustomWidgetsQt::ItemSettingsMap getSettingsMap() const;

private slots:
    void on_applyButton_clicked();
    void on_cancelButton_clicked();
    void on_resetToDefBtn_clicked();
    void on_loadButton_clicked();
    void on_saveButton_clicked();
    void on_actionLoadLayout1_triggered();
    void on_actionLoadLayout2_triggered();

private:
    Ui::ItemSettingsMapEditor *ui;

    void loadLayoutFromFile(const QString &_path);
};

#endif // ITEMSETTINGSMAPEDITOR_H
