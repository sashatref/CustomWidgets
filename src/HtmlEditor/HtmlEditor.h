#ifndef HTMLEDITOR_H
#define HTMLEDITOR_H

#include <QMap>
#include <QPointer>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;
QT_END_NAMESPACE

#include "../export.h"

namespace Ui
{
    class HtmlEditor;
}

namespace CustomWidgetsQt
{

class WIDGET_EXPORT HtmlEditor : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(bool readOnly READ getReadOnly WRITE setReadOnly)
public:
    HtmlEditor(QWidget *parent = 0);

    bool load(const QString &f);

    void loadHtml(const QString &_html);

    QString saveHtml() const;
    QString savePlaintText() const;

    //properties
    bool getReadOnly() const;
    void setReadOnly(bool _isReadOnly);

    //~properties
public slots:
    void fileNew();

protected:
    virtual void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;

private slots:
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();
    void filePrint();
    void filePrintPreview();
    void filePrintPdf();

    void textBold();
    void textUnderline();
    void textItalic();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textStyle(int styleIndex);
    void textColor();
    void textAlign(QAction *a);

    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();

    void clipboardDataChanged();
    void printPreview(QPrinter *);

    void on_actionAddImage_triggered();

private:
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    bool maybeSave();
    void setCurrentFileName(const QString &fileName);

    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);

    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;

    QString fileName;

    Ui::HtmlEditor *ui;
    bool m_isReadOnly;
};

}

#endif // HTMLEDITOR_H
