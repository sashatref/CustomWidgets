#ifndef CLIP_RECTANGLE_H
#define CLIP_RECTANGLE_H

#include <QWidget>

#include "../export.h"


class WIDGET_EXPORT ClipRectangle : public QWidget
{
    Q_OBJECT
public:
    ClipRectangle(int _index, QWidget* _parent = 0);
    virtual ~ClipRectangle();

signals:
    void globalRect(const QRect &_rect);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QPoint m_startPoint;
    QPoint m_endPoint;
    int m_index;
    bool m_isMoved;
};

#endif //CLIP_RECTANGLE_H
