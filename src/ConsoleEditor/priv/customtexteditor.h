#ifndef CUSTOMTEXTEDITOR_H
#define CUSTOMTEXTEDITOR_H

#include <QPlainTextEdit>
#include <QTextEdit>

namespace CustomWidgetsQt
{

class CustomTextEditor : public QTextEdit
{
public:
    CustomTextEditor(QWidget *_parent = 0);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

}

#endif // CUSTOMTEXTEDITOR_H
