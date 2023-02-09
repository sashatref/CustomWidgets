#ifndef PROGRESS_DIALOG_H
#define PROGRESS_DIALOG_H

#include <QWidget>
#include "../export.h"

/*!
 *@example
 *  MyProgressDialog *dialog = new MyProgressDialog();

    dialog->setIsWindowModal(true);
    dialog->setContinouse(true);
    dialog->show();

    MyThread *mythr = new MyThread();

    connect(mythr, &MyThread::finished, dialog, &MyProgressDialog::close);
    connect(mythr, &MyThread::onSetValue, dialog, &MyProgressDialog::setCurrentValue);
    connect(dialog, &MyProgressDialog::cancelButtonClicked, mythr, &MyThread::terminate);
    connect(dialog, &MyProgressDialog::cancelButtonClicked, mythr, &MyThread::deleteLater);

    mythr->start();
 */



namespace Ui {
class ProgressDialog;
}

class QLabel;
class QProgressBar;
class QPushButton;

class WIDGET_EXPORT ProgressDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressDialog(const QString &_labelText = "", QWidget *parent = 0);
    ~ProgressDialog();

    QLabel *getLabel() const;
    QProgressBar *getProgressBar() const;
    QPushButton *getButton() const;

    /*!
     * \brief setCancelable устанавливает будет ли отображена кнопка отмены
     * \param _isCancelable
     */
    void setCancelable(bool _isCancelable);

    /*!
     * \brief setContinouse true - будет спрятано отображение прогресса и установлен бессконечный прогрессбар
     * \param _isContinouse
     */
    void setContinouse(bool _isContinouse);

    /*!
     * \brief setIsWindowModal если true, то пока не пропадет окошко - делать ничего нельзя
     * если false, то можно продолжать работу
     * \param _isModal
     */
    void setIsWindowModal(bool _isModal);

public slots:
    void setMaximum(int _maximumValue);
    void setCurrentValue(int _currentValue);

signals:
    void cancelButtonClicked();

private slots:
    void on_cancelButton_clicked();

private:
    Ui::ProgressDialog *ui;
};

#endif //PROGRESS_DIALOG_H
