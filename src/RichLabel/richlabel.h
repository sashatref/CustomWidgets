#ifndef RICH_LABEL_H
#define RICH_LABEL_H

#include <QLabel>
#include "../export.h"

/*!
 * \brief Label которые изменяет размер текста в зависимости от своих размеров
 */

class WIDGET_EXPORT RichLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(bool stretchText READ stretchText WRITE setStretchText)
    Q_PROPERTY(QSize margins READ margins WRITE setMargins)
public:
    RichLabel(QWidget *parent = 0);

    /*!
     * \brief задает флаг, будет ли размер текста изменятся вместе с размерами виджета
     */
    void setStretchText(bool value);

    /*!
     * \brief получает флаг, будет ли размер текста изменятся вместе с размерами виджета
     */
    bool stretchText() const {return m_stretchText;}

    /*!
     * \brief задает отступы для текста от края виджета
     */
    void setMargins(const QSize &_value);

    /*!
     * \brief получает отступы для текста от края виджета
     */
    QSize margins() const { return m_margins; }

protected:
    /*!
     * \brief реализация отрисовки текста, в зависимости от размера виджета и отступов
     * заданных через setMargins
     */
    void paintEvent(QPaintEvent *event) override;

private:
    bool m_stretchText;
    QSize m_margins;
};

#endif //RICH_LABEL_H
