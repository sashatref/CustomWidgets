#ifndef LOG_WINDOW2_H
#define LOG_WINDOW2_H

#include <HelperLibrary/Widgets/extendedwidget.h>
#include "../export.h"

namespace Ui {
    class LogWindow2;
}

/*!
 * \brief The LogWindow class виджет для отображения логов программы с цветовой подстветкой для сообщений разных типов
 * с возможность очистки списка, копирования выделенных/всех строк, промотка в конец/начало
 */

namespace CustomWidgetsQt
{

class LogWindow2P;
class WIDGET_EXPORT LogWindow2 : public ExtendedWidget
{
    Q_OBJECT
    Q_PROPERTY(int updateInterval READ getUpdateInterval WRITE setUpdateInterval RESET resetUpdateInterval)
    Q_PROPERTY(int maxMsgCount READ getMaximumMsgCount WRITE setMaximumMsgCount RESET resetMaximumMsgCount)
    Q_PROPERTY(int msgOverheadCount READ getMsgOverhead WRITE setMsgOverhead RESET resetMsgOverhead)
    Q_PROPERTY(bool textWindowVisible READ getTextWindowVisible WRITE setTextWindowVisible)

    Q_PROPERTY(QPixmap backgroundImage READ getBackgroundPixmap WRITE setBackgroundPixmap)
    Q_PROPERTY(double imageOpacity READ getImageOpacity WRITE setImageOpacity)
    Q_PROPERTY(QSize imagePadding READ getImagePadding WRITE setImagePadding)
    friend class LogWindow2P;
public:
    LogWindow2(QWidget *parent = 0);
    virtual ~LogWindow2();

    QAction *getClearAllAction();

public slots:
    void addMessage(const QString &_text, QtMsgType _logLevel);
    void addMessage(const QString &_text, QtMsgType _logLevel, const QVariant &_userData);

    void scrollToBottom();

public:
    void setTextWindowVisible(bool _isVisible);
    bool getTextWindowVisible() const;

    /*!
     * \brief setUpdateInterval если включено использование очереди, то устанавливает интервал вычитывания сообщений из очереди
     * \param _ms
     */
    void setUpdateInterval(int _ms);
    int getUpdateInterval() const;
    void resetUpdateInterval();

    void clear();

    void setBackgroundPixmap(const QPixmap &_pixmap);
    QPixmap getBackgroundPixmap() const;

    void setImageOpacity(double _opacity);
    double getImageOpacity() const;

    void setImagePadding(const QSize &_size);
    QSize getImagePadding() const;

    void setMaximumMsgCount(int _count);
    int getMaximumMsgCount() const;
    void resetMaximumMsgCount();

    void setMsgOverhead(int _count);
    int getMsgOverhead() const;
    void resetMsgOverhead();

public slots:
    QString getAllText() const;

signals:
    void addSingleRowContextMenu(QMenu *_menu, const QVariant &_v);

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void onSelectAllSlot();
    void onUnselectAllSlot();
    void onClearAllSlot();
    void onScrollToEndSlot();
    void onScrollToStartSlot();
    void onCopySelectedSlot();
    void onCopyAllSlot();

    void on_actionShowTextDetail_triggered(bool checked);
    void on_actionWordWrap_triggered(bool checked);

private:
    Ui::LogWindow2 *ui;
    LogWindow2P *p;

public:
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;

protected:
    virtual void initUiComponets() override;
    virtual void initConnections() override;
};

}


#endif //LOG_WINDOW2_H
