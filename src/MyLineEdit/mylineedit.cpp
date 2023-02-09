#include "../project_pch.h"
#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{

}

void MyLineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    InfoWindow(text()).exec();
    QLineEdit::mouseDoubleClickEvent(event);
}
