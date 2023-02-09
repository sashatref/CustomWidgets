#ifndef RESIZABLE_VIEW_H
#define RESIZABLE_VIEW_H

#include <QWidget>

#include "../export.h"

namespace CustomWidgetsQt
{

class ResizableViewPrivate;

/*!
 * \brief Виджет который позволяет отображать QPixmap изображение.
 * при этом изображение меняет размеры при изменение размеров самого виджета.
 * есть возможность установки отступов от краев лево-право-низ-верх
 */

class WIDGET_EXPORT ResizableView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize margin READ getMarginSize WRITE setMarginSize)
    Q_PROPERTY(QPixmap image READ getPixmap WRITE setPixmap NOTIFY pixmapChanged)
public:
    ResizableView(QWidget *parent = 0);
    virtual ~ResizableView();

    /*!
     * \brief задает изображение, которое будет отображаться
     */
    void setPixmap(const QPixmap &_pixmap);

    /*!
     * \brief возвращает изображение, которое отображается на виджете
     */
    QPixmap getPixmap();

    /*!
     * \brief устанавливает отступы размещения изображения на виджете
     */
    void setMarginSize(const QSize &_marginSize);

    /*!
     * \brief возвращает отступы размерещния изображения на виджете
     */
    QSize getMarginSize() const;

    /*!
     * \brief очищает изображение
     */
    void clear();

    void setDefaultSaveName(const QString &_saveFileName);
    QString getDefaultSaveName() const;

signals:
    void pixmapChanged(const QPixmap &_p);

protected:
    virtual bool eventFilter(QObject *_object, QEvent *_event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

private:
    ResizableViewPrivate *m_private;
};

}

#endif //RESIZABLE_VIEW_H


