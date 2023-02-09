#include "project_pch.h"
#include "rectgrabber.h"

#include "ClipRectangle.h"

RectGrabber::RectGrabber()
{
    QList<QScreen*> screens = QApplication::screens();

    for(int i = 0 ; i < screens.size(); i++)
    {
        QRect r = screens.at(i)->geometry();

        ClipRectangle *clipR = new ClipRectangle(i);
        connect(clipR, &ClipRectangle::globalRect, this, &RectGrabber::rectSelected);
        clipR->setGeometry(r);
        m_clippers.append(clipR);
    }
}

RectGrabber::~RectGrabber()
{
    qDeleteAll(m_clippers);
}

void RectGrabber::show()
{
    for(int i = 0 ; i < m_clippers.size(); i++)
    {
        m_clippers.at(i)->show();
    }
}
