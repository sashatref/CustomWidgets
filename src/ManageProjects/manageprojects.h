#ifndef MANAGE_PROJECTS_H
#define MANAGE_PROJECTS_H

#include <QDialog>
#include <QVariantMap>

#include "../export.h"

namespace Ui {
class ManageProjects;
}

/*!
 * \brief The ManageProjects class виджет для загрузки/удаления проекта
 */

class WIDGET_EXPORT ManageProjects : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(int rowHeight READ getRowHeight WRITE setRowHeight RESET resetRowHeight)
    Q_PROPERTY(bool alternatingRowColors READ getAlternatingRowColors WRITE setAlternatingRowColors)
    Q_PROPERTY(QFont listWidgetFont READ getListWidgetFont WRITE setListWidgetFont RESET resetListWidgetFont)

public:
    explicit ManageProjects(QWidget *parent = 0);
    ~ManageProjects();

    /*!
     * \brief setProjectMap устанавливает список проектов, которые будут отображены в списке.
     * значение ключей будут установлены в качестве названий, значений QVariant - установлено в data(Qt::UserRole)
     * \param _projectList
     */
    void setProjectMap(const QVariantMap &_projectList);

    /*!
     * \brief getProjectMap возвращает список проектов
     * \return
     */
    QVariantMap getProjectMap() const;

    /*!
     * \brief setRowHeight устанавливает высоту каждой строки
     * \param _height
     */
    void setRowHeight(int _height);

    /*!
     * \brief getRowHeight возвращает высоту строки
     * \return
     */
    int getRowHeight() const;
    void resetRowHeight();

    /*!
     * \brief setAlternatingRowColors устанавливает флаг использования альтернативных цветов для чередующихся строк
     * \param _isTrue
     */
    void setAlternatingRowColors(bool _isTrue);

    /*!
     * \brief getAlternatingRowColors возвращает флаг использования альтернативных цветов для чередующихся строк
     * \return
     */
    bool getAlternatingRowColors() const;

    /*!
     * \brief setListWidgetFont устанавливает шрифт для списка
     * \param _font
     */
    void setListWidgetFont(const QFont &_font);

    /*!
     * \brief getListWidgetFont возвращает шрифт для списка
     * \return
     */
    QFont getListWidgetFont() const;
    void resetListWidgetFont();

signals:
    /*!
     * \brief projectMapChanged срабатывает при нажатие кнокпи "Применить" или "Открыть проект"
     * \param _projectMap
     */
    void projectMapChanged(const QVariantMap &_projectMap);

    /*!
     * \brief loadProject срабатывает при нажатие кнопки "Открыть проект"
     * \param _project
     */
    void loadProject2(const QString &_projectName, const QVariant &_project);
    void loadProject(const QVariant &_project);

private slots:
    void on_loadButton_clicked();
    void on_removeButton_clicked();
    void on_applyButton_clicked();

    void onListWidgetItemChanged();

private:
    Ui::ManageProjects *ui;

    int m_rowHeight;
};

#endif //MANAGE_PROJECTS_H
