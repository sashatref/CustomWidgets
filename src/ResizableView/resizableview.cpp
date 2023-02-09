#include "../project_pch.h"
#include "resizableview.h"

namespace CustomWidgetsQt
{

class ResizableViewPrivate
{
public:
    ResizableViewPrivate() :
        m_saveFileName      ("image.png"),
        m_pixmap            (),
        m_marginSize        (4,4),
        m_graphicsView      (new QGraphicsView()),
        m_scene             (new QGraphicsScene()),
        m_vBoxLayout        (new QVBoxLayout()),
        m_pixmapItem        (0)
    {
        m_graphicsView->setScene(m_scene);
        m_scene->addPixmap(m_pixmap);
        m_pixmapItem = m_scene->addPixmap(QPixmap());
    }

    ~ResizableViewPrivate()
    {
        delete m_graphicsView;
        delete m_vBoxLayout;
        delete m_scene;
    }

    void updatePixmap()
    {
        int width = m_graphicsView->width() - m_marginSize.width();
        int height = m_graphicsView->height() - m_marginSize.height();

        if(!m_pixmap.isNull())
        {
            QPixmap scaledPixmap = m_pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::FastTransformation);
            m_pixmapItem->setPixmap(scaledPixmap);

            int offsetX = (width - scaledPixmap.size().width()) / 2;
            int offsetY = (height - scaledPixmap.size().height()) / 2;

            m_pixmapItem->setOffset(offsetX, offsetY);
        } else
        {
            m_pixmapItem->setPixmap(QPixmap());
        }

        m_scene->setSceneRect(0,0, width, height);
    }

    QString m_saveFileName;
    QPixmap m_pixmap;
    QSize m_marginSize;
    QGraphicsView *m_graphicsView;
    QGraphicsScene *m_scene;
    QVBoxLayout *m_vBoxLayout;
    QGraphicsPixmapItem *m_pixmapItem;
};



ResizableView::ResizableView(QWidget *parent):
    QWidget(parent),
    m_private(new ResizableViewPrivate())
{
    m_private->m_graphicsView->installEventFilter(this);

    m_private->m_vBoxLayout->setMargin(0);
    m_private->m_vBoxLayout->setSpacing(0);

    QWidget::setLayout(m_private->m_vBoxLayout);
    m_private->m_vBoxLayout->addWidget(m_private->m_graphicsView);
}

ResizableView::~ResizableView()
{
    delete m_private;
}

void ResizableView::setPixmap(const QPixmap &_pixmap)
{
    m_private->m_pixmap = _pixmap;
    m_private->updatePixmap();

    emit pixmapChanged(_pixmap);
}

QPixmap ResizableView::getPixmap()
{
    return m_private->m_pixmap;
}

void ResizableView::setMarginSize(const QSize &_marginSize)
{
    m_private->m_marginSize = _marginSize;
    m_private->updatePixmap();
}

QSize ResizableView::getMarginSize() const
{
    return m_private->m_marginSize;
}

void ResizableView::clear()
{
    m_private->m_pixmap = QPixmap();
    m_private->updatePixmap();
}

void ResizableView::setDefaultSaveName(const QString &_saveFileName)
{
    m_private->m_saveFileName = _saveFileName;
}

QString ResizableView::getDefaultSaveName() const
{
    return m_private->m_saveFileName;
}

bool ResizableView::eventFilter(QObject *_object, QEvent *_event)
{
    if(_object == m_private->m_graphicsView)
    {
        if(_event->type() == QEvent::Resize)
        {
            m_private->updatePixmap();
        }
    }

    return QObject::eventFilter(_object, _event);
}

void ResizableView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QAction *action = new QAction(IconsEnum::getIcon(IconsEnum::SP_Save1),
                                  tr("Сохранить изображение..."),
                                  &menu);

    connect(action, &QAction::triggered, [this]()
    {
        QString file = QFileDialog::getSaveFileName(this,
                                                    tr("Выберите файл для сохранения..."),
                                                    m_private->m_saveFileName,
                                                    "Images(*.png *.jpg)",
                                                    0);
        if(!file.isEmpty())
        {
            m_private->m_pixmap.save(file, "PNG");
        }
    });

    menu.addAction(action);
    menu.exec(event->globalPos());
}

}



