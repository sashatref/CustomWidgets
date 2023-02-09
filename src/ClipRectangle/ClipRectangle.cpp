#include "../project_pch.h"
#include "ClipRectangle.h"

ClipRectangle::ClipRectangle(int _index, QWidget *_parent):
    QWidget         (_parent),
    m_startPoint    (),
    m_endPoint      (),
    m_index         (_index),
    m_isMoved       (false)
{
    setWindowFlags(Qt::ToolTip);
    setWindowOpacity(0.5);
}

ClipRectangle::~ClipRectangle()
{

}

void ClipRectangle::mousePressEvent(QMouseEvent *event)
{
    m_startPoint = event->globalPos();
}

void ClipRectangle::mouseReleaseEvent(QMouseEvent *event)
{
    m_endPoint = event->globalPos();

    QRect rect(m_startPoint, m_endPoint);
    emit globalRect(rect);

    this->close();
}

void ClipRectangle::mouseMoveEvent(QMouseEvent *event)
{
    m_isMoved = true;
    m_endPoint = event->globalPos();
    repaint();
}

void ClipRectangle::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);

    painter.fillRect(rect(), Qt::black);

    painter.setBrush(Qt::red);

    QPoint start = this->mapFromGlobal(m_startPoint);
    QPoint end = this->mapFromGlobal(m_endPoint);

    QFont font = painter.font();
    painter.setPen(Qt::black);
    font.setPixelSize(160);
    painter.setFont(font);

    QTextOption o;
    o.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    painter.drawText(QRect(0,0, width(), height()), QString::number(m_index), o);

    if(m_isMoved)
    {
        painter.drawRect(QRect(start, end));
    }
}
