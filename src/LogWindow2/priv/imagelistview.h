#ifndef IMAGELISTVIEW_H
#define IMAGELISTVIEW_H

#include <QListView>

class ImageListView : public QListView
{
    Q_OBJECT
    Q_PROPERTY(QPixmap backgroundImage READ getBackgorundPixmap WRITE setBackgroundPixmap)
    Q_PROPERTY(double imageOpacity READ getImageOpacity WRITE setImageOpacity)
    Q_PROPERTY(QSize imagePadding READ getImagePadding WRITE setImagePadding)
public:
    ImageListView(QWidget *_parent = nullptr);

    void setBackgroundPixmap(const QPixmap &_pixmap);
    QPixmap getBackgorundPixmap() const;

    void setImageOpacity(double _opacity);
    double getImageOpacity() const;

    void setImagePadding(const QSize &_size);
    QSize getImagePadding() const;

signals:
    void endKeyPressed();
    void homeKeyPressed();
    void copySelectedPressed();
    void copyAllPressed();
    void deleteAllPressed();
    void selectAllPressed();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    QPixmap m_backgroundImage;
    double m_imageOpacity;
    QSize m_padding;
};

#endif // IMAGELISTVIEW_H
