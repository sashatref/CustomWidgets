#ifndef CONSOLEEDITOR_H
#define CONSOLEEDITOR_H

#include <QWidget>

#include "../export.h"

#include <HelperLibrary/Widgets/isavewidget.h>

namespace Ui {
class ConsoleEditor;
}

namespace CustomWidgetsQt
{

struct ConsoleEditorP;

class WIDGET_EXPORT ConsoleEditor :
        public QWidget,
        public ISaveWidget
{
    Q_OBJECT
public:
    explicit ConsoleEditor(QWidget *parent = 0);
    ~ConsoleEditor();

    void setFileName(const QString &_fileName);
    QString getFileName() const;

private:
    Ui::ConsoleEditor *ui;
    ConsoleEditorP *p;
    void updateLanguage();
    void updateStyle();

private slots:
    void onFileChanged(const QString &_path);
    void setFileLabel(const QString &_filePath);
    void on_clearFileButton_clicked();

public:
    virtual QVariant saveWidgetState() const override;
    virtual void loadWidgetState(const QVariant &_state) override;
    virtual QString getWidgetUniqueName() const override;

    // QWidget interface
protected:
    virtual void changeEvent(QEvent *event) override;
};

}

#endif // CONSOLEEDITOR_H
