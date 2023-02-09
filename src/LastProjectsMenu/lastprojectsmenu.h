#ifndef LAST_PROJECT_MENU_H
#define LAST_PROJECT_MENU_H

#include <QObject>

#include "../export.h"

class QStringList;
class QLabel;
class QMenu;
class QAction;

/*!
 * \brief The LastProjectsMenu class
 * Класс для создания меню последних используемых файлов.
 * Для работы класс необходимо выполнить initMenu, куда указать список последних проектов из настроек.
 * И пункт меню, куда будут добавлены все QAction
 * Подписаться на событие loadProject, которое будет срабатывать при клике пользователем на пункт меню.
 * Если нужно загружать проект иным способом, то делать это вызовом функции openFile.
 * Для того чтоб класс правильно добавил или передвинул путь файла в списке
 *
 * \example
 *      LastProjectsMenu *lastProjectMenu = new LastProjectsMenu(this);
        lastProjectMenu->initMenu(&m_settings.m_lastProjects, ui->menuFile);
        connect(m_lastProjectMenu, &LastProjectsMenu::loadProject, this, [this](const QString &_val)
        {
            ui->myProjectEditor->clear();
            ui->myProjectEditor->loadFromXml(QDir(_val));
        });

        и вызов где то далее по коду, к примеру после вызова диалога выбора файла:

        lastProjectMenu->openFile(<string>);
 */

class WIDGET_EXPORT LastProjectsMenu : public QObject
{
    Q_OBJECT
public:
    LastProjectsMenu(QObject* parent = 0);

    void setMaxItemCount(int _count);
    int maxItemCount() const;

    void initMenu(QStringList *_values, QMenu *const _menu);
    void openFile(const QString &_path);


signals:
    void loadProject(const QString &_path);

private slots:
    void onActionClick();

private:
    QAction *createAction(const QString &_path, QMenu *const _menu, int _index);

    QStringList *m_pathList;
    QList<QAction*> m_actionList;
    QMenu *m_menu;

    int m_maxItemCount;
};

#endif //LAST_PROJECT_MENU_H
