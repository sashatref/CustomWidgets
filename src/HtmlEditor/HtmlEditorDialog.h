#ifndef HTMLEDITORDIALOG_H
#define HTMLEDITORDIALOG_H

#include <QDialog>
#include "../export.h"
#include <HelperLibrary/Widgets/extendeddialog.h>


namespace Ui {
class HtmlEditorDialog;
}

namespace CustomWidgetsQt
{

class HtmlEditor;

class WIDGET_EXPORT HtmlEditorDialog : public ExtendedDialog
{
    Q_OBJECT
public:
    explicit HtmlEditorDialog(QWidget *parent = 0);
    ~HtmlEditorDialog();

    void setReadOnly(bool _isReadOnly);

    void loadHtml(const QString &_html);
    QString saveHtml() const;

    HtmlEditor *getHtmlEditor() const;

private slots:
    void on_closeButton_clicked();
    void on_saveAsTextButton_clicked();
    void on_saveAsHtmlButton_clicked();

private:
    Ui::HtmlEditorDialog *ui;
    bool m_isPlain;

    // ExtendedDialog interface
public:
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
};

}

#endif // HTMLEDITORDIALOG_H
