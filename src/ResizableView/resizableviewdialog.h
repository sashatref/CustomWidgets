#ifndef RESIZABLE_VIEW_DIALOG_H
#define RESIZABLE_VIEW_DIALOG_H

#include <QDialog>

#include "../export.h"

namespace Ui {
class ResizableViewDialog;
}

class QWidget;

namespace CustomWidgetsQt
{

class WIDGET_EXPORT ResizableViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResizableViewDialog(QWidget *parent = 0);
    ~ResizableViewDialog();

    QPixmap getPixmap() const;
    void setPixmap(const QPixmap &_pixmap);

    void addWidget(QWidget *const _widget, int _index);

private slots:
    void on_applyButton_clicked();
    void on_clearButton_clicked();
    void on_loadButton_clicked();

    void on_resizeButton_clicked();

private:
    Ui::ResizableViewDialog *ui;

    void updateStyle();

    // QWidget interface
protected:
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;
};

}

#endif // RESIZABLE_VIEW_DIALOG_H
