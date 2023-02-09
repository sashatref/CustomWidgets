#include "customtexteditor.h"

namespace CustomWidgetsQt
{

CustomTextEditor::CustomTextEditor(QWidget *_parent):
    QTextEdit(_parent)
{
    //setTextColor(Qt::white);

    QFont myFont("Times");
    myFont.setBold(false);
    myFont.setPointSize(13);

    setFont(myFont);
}

void CustomTextEditor::paintEvent(QPaintEvent *event)
{
    //QPainter painter(viewport());
    //painter.fillRect(rect(), Qt::black);

    QTextEdit::paintEvent(event);
}


}


