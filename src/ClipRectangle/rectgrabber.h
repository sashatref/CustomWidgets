#ifndef RECTGRABBER_H
#define RECTGRABBER_H

#include <QObject>
#include "../export.h"

class ClipRectangle;

class WIDGET_EXPORT RectGrabber : public QObject
{
    Q_OBJECT
public:
    RectGrabber();
    ~RectGrabber();

    void show();

signals:
    void rectSelected(const QRect &_rect);

private:
    QList<ClipRectangle*> m_clippers;
};

#endif // RECTGRABBER_H
