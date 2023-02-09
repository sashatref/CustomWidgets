#include "imagelistview.h"

ImageListView::ImageListView(QWidget *_parent):
    QListView(_parent)
{
    auto f = QOverload<>::of(&QWidget::repaint);

    connect(verticalScrollBar(), &QScrollBar::valueChanged, viewport(), f);
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, viewport(), f);
}

void ImageListView::setBackgroundPixmap(const QPixmap &_pixmap)
{
    m_backgroundImage = _pixmap;
    repaint();
}

QPixmap ImageListView::getBackgorundPixmap() const
{
    return m_backgroundImage;
}

void ImageListView::setImageOpacity(double _opacity)
{
    m_imageOpacity = _opacity;
    repaint();
}

double ImageListView::getImageOpacity() const
{
    return m_imageOpacity;
}

void ImageListView::setImagePadding(const QSize &_size)
{
    m_padding = _size;
    repaint();
}

QSize ImageListView::getImagePadding() const
{
    return m_padding;
}

void ImageListView::paintEvent(QPaintEvent *event)
{
    QListView::paintEvent(event);

    QPainter painter(viewport());
    if(m_backgroundImage.isNull()) {return;}

    painter.setOpacity(m_imageOpacity);

    QImage img = m_backgroundImage.scaled(viewport()->size() - QSize(m_padding.width() * 2, m_padding.height() * 2), Qt::KeepAspectRatio).toImage();
    painter.drawImage(m_padding.width(), viewport()->height() - img.height() - m_padding.height(), img);
}


void ImageListView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Home:
        emit homeKeyPressed();
        break;
    case Qt::Key_End:
        emit endKeyPressed();
        break;
    case Qt::Key_C:
        if(event->modifiers().testFlag(Qt::ControlModifier))
        {
            if(event->modifiers().testFlag(Qt::ShiftModifier))
            {
                emit copyAllPressed();
            } else
            {
                emit copySelectedPressed();
            }
        }
        break;
    case Qt::Key_Delete:
        if(event->modifiers().testFlag(Qt::ControlModifier))
        {
            emit deleteAllPressed();
        }
        break;
    case Qt::Key_A:
        if(event->modifiers().testFlag(Qt::ControlModifier))
        {
            emit selectAllPressed();
        }
        break;
    default:
        QListView::keyPressEvent(event);
        break;
    }
}
