#include "../project_pch.h"
#include "lastprojectsmenu.h"

LastProjectsMenu::LastProjectsMenu(QObject *parent) :
    QObject         (parent),
    m_pathList      (0),
    m_actionList    (),
    m_menu          (0),
    m_maxItemCount  (10)
{

}

void LastProjectsMenu::setMaxItemCount(int _count)
{
    m_maxItemCount = _count;
}

int LastProjectsMenu::maxItemCount() const
{
    return m_maxItemCount;
}

QAction *LastProjectsMenu::createAction(const QString &_path, QMenu * const _menu, int _index)
{
    QAction *act = new QAction(_menu);
    act->setData(_path);
    act->setText(QString::number(_index) + " | " + Text::getShortFilePath(_path, 65));

    connect(act, &QAction::triggered, this, &LastProjectsMenu::onActionClick);
    return act;
}

//проверяем есть ли файл в списке, если есть, то удаляем и вставляем в начало списка,
//проверяем не вышел ли массив за пределы maxItemCount, если это так, то удаляем лишние элементы
//создаем меню заново и посылаем сигнал на загрузку
void LastProjectsMenu::openFile(const QString &_path)
{
    if(m_pathList->contains(_path))
    {
        m_pathList->removeOne(_path);
    }

    m_pathList->insert(0, _path);

    while(m_pathList->size() > m_maxItemCount)
    {
        m_pathList->removeLast();
    }

    initMenu(m_pathList, m_menu);

    emit loadProject(_path);
}

//создаем меню на основе _values
//удаляем дубликаты, удаляем все предыдущие меню, создаем виджет разделитель "недавние файлы"
//создаем меню для каждого элемента из _values
void LastProjectsMenu::initMenu(QStringList *_values, QMenu * const _menu)
{
    m_pathList = _values;
    m_pathList->removeDuplicates();
    m_menu = _menu;

    qDeleteAll(m_actionList);
    m_actionList.clear();

    for(int i = 0 ; i < _values->size(); i++)
    {
        QAction *act = createAction(_values->at(i), _menu, i + 1);
        _menu->addAction(act);
        m_actionList.append(act);
    }
}

//обработчик нажатия на пункт меню
void LastProjectsMenu::onActionClick()
{
    QAction *act = static_cast<QAction*>(sender());
    openFile(act->data().toString());
}
