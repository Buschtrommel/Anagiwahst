/* Anagiwahst - A Qt Property Editor/Creator
 *
 * Copyright (c) 2015-2017 Buschtrommel/Matthias Fehring <kontakt@buschmann23.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "projectfiltermodel.h"
#include "projectmodel.h"
#include "project.h"
#include <QDateTime>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

ProjectFilterModel::ProjectFilterModel(SortingRole sortingRole, QObject *parent) :
    QSortFilterProxyModel(parent), m_sortingRole(sortingRole)
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    sort(0, Qt::DescendingOrder);
}


ProjectFilterModel::~ProjectFilterModel()
{

}


bool ProjectFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    Project *l = sourceModel()->data(source_left, ProjectModel::Item).value<Project*>();
    Project *r = sourceModel()->data(source_right, ProjectModel::Item).value<Project*>();

    switch(m_sortingRole) {
    case Id:
        return l->id() < r->id();
    case Created:
        return l->createdAt() < r->createdAt();
    case Updated:
        return l->updatedAt() < r->updatedAt();
    default:
        return QString::localeAwareCompare(l->name(), r->name()) < 0;
    }
}



bool ProjectFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex idx = sourceModel()->index(source_row, 0, source_parent);

    return sourceModel()->data(idx, ProjectModel::Item).value<Project*>()->name().contains(filterRegExp());
}




/*!
 * \property ProjectFilterModel::sortingRole
 * \brief Role used to sort the model.
 *
 * \par Access functions:
 * \li SortingRole sortingRole() const
 * \li void setSortingRole(SortingRole nSortingRole)
 *
 * \par Notifier signal:
 * \li void sortingRoleChanged(SortingRole sortingRole)
 */

/*!
 * \fn void  ProjectFilterModel::sortingRoleChanged(SortingRole sortingRole)
 * \brief Notifier function for the \link ProjectFilterModel::sortingRole sortingRole \endlink property.
 * \sa ProjectFilterModel::sortingRole() ProjectFilterModel::setSortingRole()
 */

/*!
 * \brief Getter function for the \link ProjectFilterModel::sortingRole sortingRole \endlink property.
 * \sa ProjectFilterModel::setSortingRole() ProjectFilterModel::sortingRoleChanged()
 */
ProjectFilterModel::SortingRole ProjectFilterModel::sortingRole() const { return m_sortingRole; }

/*!
 * \brief Setter function for the \link ProjectFilterModel::sortingRole sortingRole \endlink property.
 * \sa ProjectFilterModel::sortingRole() ProjectFilterModel::sortingRoleChanged()
 */
void ProjectFilterModel::setSortingRole(SortingRole nSortingRole)
{
    if (nSortingRole != m_sortingRole) {
        m_sortingRole = nSortingRole;
#ifdef QT_DEBUG
        qDebug() << "Changed sortingRole to" << m_sortingRole;
#endif
        Q_EMIT sortingRoleChanged(sortingRole());
    }
}


/*!
 * \property ProjectFilterModel::search
 * \brief Search string
 *
 * \par Access functions:
 * \li QString search() const
 * \li void setSearch(const QString &nSearch)
 *
 * \par Notifier signal:
 * \li void searchChanged(const QString &search)
 */

/*!
 * \fn void  ProjectFilterModel::searchChanged(const QString &search)
 * \brief Notifier function for the \link ProjectFilterModel::search search \endlink property.
 * \sa ProjectFilterModel::search() ProjectFilterModel::setSearch()
 */

/*!
 * \brief Getter function for the \link ProjectFilterModel::search search \endlink property.
 * \sa ProjectFilterModel::setSearch() ProjectFilterModel::searchChanged()
 */
QString ProjectFilterModel::search() const { return m_search; }

/*!
 * \brief Setter function for the \link ProjectFilterModel::search search \endlink property.
 * \sa ProjectFilterModel::search() ProjectFilterModel::searchChanged()
 */
void ProjectFilterModel::setSearch(const QString &nSearch)
{
    if (nSearch != m_search) {
        m_search = nSearch;
#ifdef QT_DEBUG
        qDebug() << "Changed search to" << m_search;
#endif
        setFilterFixedString(search());
        Q_EMIT searchChanged(search());
    }
}
