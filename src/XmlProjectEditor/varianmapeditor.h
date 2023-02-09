#ifndef VARIANTMAP_EDITOR_H
#define VARIANTMAP_EDITOR_H

#include <QDialog>
#include <QVariantMap>

#include "../export.h"

namespace Ui {
class VarianMapEditor;
}

class WIDGET_EXPORT VarianMapEditor : public QDialog
{
    Q_OBJECT

public:
    enum Button
    {
        None = 0,
        SaveButton = 1,
        LoadButton = 2
    };
    Q_DECLARE_FLAGS(Buttons, Button)
    Q_FLAG(Buttons)

    explicit VarianMapEditor(QWidget *parent = 0);
    virtual ~VarianMapEditor();

    void setVariantMap(const QVariantMap &_map);
    QVariantMap getVariantMap() const;

    void addItem(const QString &key, const QVariant &_value);

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;
    virtual void showEvent(QShowEvent *) override;
    virtual void saveData(const QString &_filePath);
    virtual void loadData(const QString &_filePath);
    virtual QString openDialogFilter() const;
    virtual VarianMapEditor::Buttons getButtonsHint() const;

private slots:
    void on_applyButton_clicked();
    void on_closeButton_clicked();
    void on_removeButton_clicked();
    void on_addButton_clicked();
    void on_loadFromFileButton_clicked();
    void on_saveToFileButton_clicked();
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::VarianMapEditor *ui;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(VarianMapEditor::Buttons)

#endif //VARIANTMAP_EDITOR_H
