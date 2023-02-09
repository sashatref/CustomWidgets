#ifndef CHOOSELIST_H
#define CHOOSELIST_H

#include <QDialog>
#include <QVariantList>
#include "../export.h"

namespace Ui {
class ChooseList;
}

/*!
 * \brief виджет который представялет из себя два QListWidget,
 */

class WIDGET_EXPORT ChooseList : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QFont labelsFont READ getLabelsFont WRITE setLabelsFont)
    Q_PROPERTY(QFont listFont READ getListFont WRITE setListFont)
    Q_PROPERTY(QSize buttonsSize READ getButtonsSize WRITE setButtonsSize)
    Q_PROPERTY(QSize rowSizeHint READ getRowSize WRITE setRowSize)
    Q_PROPERTY(bool test READ getTest WRITE setTest RESET clearTest)
    Q_PROPERTY(bool applyCloseButtons READ getCloseApplyButtonVisible WRITE setCloseApplyButtonVisible)
public:
    ChooseList(QWidget *parent = 0);
    ~ChooseList();

    void setCloseApplyButtonVisible(bool _isVisible);
    bool getCloseApplyButtonVisible() const;

    /*!
     * \brief setAllElementsList
     * \param _valuesList - список значений для отображения, для пользовательских классов должнен быть указан
     * property значение которого будет показывать. или зарегистрирован toString конвертер
     * \param _propertyToShow - свойство значение которого будет отображено в списке
     * \param _sortProperty - свойство по которому элементы будут отсортированы в списке
     */
    void setAllElementsList(const QVector<QVariant> &_valuesList, const QString &_propertyToShow = "", const QString &_sortProperty = "");

    /*!
     * \brief getAllElementsList
     * \return возвращает список значений списка всех элементов
     */
    const QVector<QVariant> &getAllElementsList();

    /*!
     * \brief setSelectedElementsList
     * \param _valuesList - список значений для отображения в списке выбранных элементов.
     * элементы должны присутствовать и в списке AllElements, иначе лишние будут удалены.
     */
    void setSelectedElementsList(const QVector<QVariant> &_valuesList);

    /*!
     * \brief getSelectedElementsList
     * \return возвращает список элементов из списка selectedElements
     */
    const QVector<QVariant> &getSelectedElementsList();

    /*!
     * \brief setLabelsFont
     * \param _font устанавливает шрифт для названия таблиц сверху виджета
     */
    void setLabelsFont(const QFont &_font);

    /*!
     * \brief getLabelsFont
     * \return возвращает шрифт надписей - названий таблиц сверху виджета
     */
    const QFont &getLabelsFont();

    /*!
     * \brief setListFont
     * \param _font устанавливает шрифт для списков
     */
    void setListFont(const QFont &_font);

    /*!
     * \brief getListFont
     * \return возвращает шрифт списков
     */
    const QFont &getListFont();

    /*!
     * \brief setButtonsSize
     * \param _buttonSize устанавливает размер для кнопок < ; >
     */
    void setButtonsSize(const QSize &_buttonSize);

    /*!
     * \brief getButtonsSize
     * \return возвращает размер кнопок < ; >
     */
    const QSize &getButtonsSize() const;

    /*!
     * \brief setRowSize
     * \param _rowSize устанавливает размер одного элемента списка
     */
    void setRowSize(const QSize &_rowSize);

    /*!
     * \brief getRowSize
     * \return возвращает размер одного элемента списка
     */
    const QSize &getRowSize() const;

    /*!
     * \brief setTest
     * \param _test зполняет списки тестовым набором значений, удобно для настройки шрифтов, размеров
     */
    void setTest(bool _test);
    void clearTest();
    bool getTest();

    /*!
     * \brief translate перевод надписей элементов ui
     */
    void translate();

    /*!
     * \brief getShowProperty
     * \return получает свойство, по которому устанавливается названия строк
     */
    const QString &getShowProperty() const;

    /*!
     * \brief getSortProperty
     * \return получает свойство, по которому сортируются строки в списке
     */
    const QString &getSortProperty() const;

signals:
    void selectedElementsListChanged(const QVector<QVariant> &_values);
    void itemAdded(const QVariant &_item);
    void itemRemoved(const QVariant &_item);

private slots:
    void on_addItemButton_clicked();
    void on_removeItemButton_clicked();
    void onListItemSelected();
    void on_closeButton_clicked();
    void on_applyButton_clicked();

private:
    void updateStyle();
    void updateLanguage();

    Ui::ChooseList *ui;

    QVector<QVariant> m_allElementsList;
    QVector<QVariant> m_selectedElementsList;

    QSize m_rowSize;
    QSize m_buttonSize;
    QFont m_listFont;
    QFont m_labelFont;

    QString m_propertyToShow;
    QString m_propertyToSort;

    bool m_isTest;

    /*!
     * \brief заново формирует selectedElementsList и отправляет сигннал selectedElementsListChanged();
     */
    void recountSelectedItems();

    /*!
     * \brief проверяем чтоб все значения из selectedList присутствовали и в allList, иначе удаляем лишние
     */
    void filterSelectedList();

    // QWidget interface
protected:
    virtual void changeEvent(QEvent *event) override;
};

#endif //CHOOSELIST_H
