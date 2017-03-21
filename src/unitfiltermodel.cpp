/* Anagiwahst - A Qt Property Editor/Creator
 *
 * Copyright (c) 2017 Buschtrommel/Matthias Fehring <kontakt@buschmann23.de>
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

#include "unitfiltermodel.h"
#include "unit.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

UnitFilterModel::UnitFilterModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    setSourceModel(&m_unitModel);
    sort(0);
}


/*!
 * \brief Deconstructs the UnitFilterModel object.
 */
UnitFilterModel::~UnitFilterModel()
{
}


/*!
 * \property UnitFilterModel::projectId
 * \brief ID of the project to load units from.
 *
 * \par Access functions:
 * \li int projectId() const
 * \li void setProjectId(int nProjectId)
 *
 * \par Notifier signal:
 * \li void projectIdChanged(int projectId)
 */

/*!
 * \fn void  UnitFilterModel::projectIdChanged(int projectId)
 * \brief Notifier function for the \link UnitFilterModel::projectId projectId \endlink property.
 * \sa UnitFilterModel::projectId() UnitFilterModel::setProjectId()
 */

/*!
 * \brief Getter function for the \link UnitFilterModel::projectId projectId \endlink property.
 * \sa UnitFilterModel::setProjectId() UnitFilterModel::projectIdChanged()
 */
int UnitFilterModel::projectId() const { return m_unitModel.projectId(); }

/*!
 * \brief Setter function for the \link UnitFilterModel::projectId projectId \endlink property.
 * \sa UnitFilterModel::projectId() UnitFilterModel::projectIdChanged()
 */
void UnitFilterModel::setProjectId(int nProjectId)
{
    if (nProjectId != m_unitModel.projectId()) {
        m_unitModel.setProjectId(nProjectId);
#ifdef QT_DEBUG
        qDebug() << "Changed projectId to" << m_unitModel.projectId();
#endif
        Q_EMIT projectIdChanged(projectId());
    }
}


/*!
 * \property UnitFilterModel::sortingRole
 * \brief Property to sort the content by.
 *
 * \par Access functions:
 * \li SortingRole sortingRole() const
 * \li void setSortingRole(SortingRole nSortingRole)
 *
 * \par Notifier signal:
 * \li void sortingRoleChanged(SortingRole sortingRole)
 */

/*!
 * \fn void  UnitFilterModel::sortingRoleChanged(const SortingRole &sortingRole)
 * \brief Notifier function for the \link UnitFilterModel::sortingRole sortingRole \endlink property.
 * \sa UnitFilterModel::sortingRole() UnitFilterModel::setSortingRole()
 */

/*!
 * \brief Getter function for the \link UnitFilterModel::sortingRole sortingRole \endlink property.
 * \sa UnitFilterModel::setSortingRole() UnitFilterModel::sortingRoleChanged()
 */
UnitFilterModel::SortingRole UnitFilterModel::sortingRole() const { return m_sortingRole; }

/*!
 * \brief Setter function for the \link UnitFilterModel::sortingRole sortingRole \endlink property.
 * \sa UnitFilterModel::sortingRole() UnitFilterModel::sortingRoleChanged()
 */
void UnitFilterModel::setSortingRole(SortingRole nSortingRole)
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
 * \property UnitFilterModel::search
 * \brief String to search the content for.
 *
 * \par Access functions:
 * \li QString search() const
 * \li void setSearch(const QString &nSearch)
 *
 * \par Notifier signal:
 * \li void searchChanged(const QString &search)
 */

/*!
 * \fn void  UnitFilterModel::searchChanged(const QString &search)
 * \brief Notifier function for the \link UnitFilterModel::search search \endlink property.
 * \sa UnitFilterModel::search() UnitFilterModel::setSearch()
 */

/*!
 * \brief Getter function for the \link UnitFilterModel::search search \endlink property.
 * \sa UnitFilterModel::setSearch() UnitFilterModel::searchChanged()
 */
QString UnitFilterModel::search() const { return m_search; }

/*!
 * \brief Setter function for the \link UnitFilterModel::search search \endlink property.
 * \sa UnitFilterModel::search() UnitFilterModel::searchChanged()
 */
void UnitFilterModel::setSearch(const QString &nSearch)
{
    if (nSearch != m_search) {
        m_search = nSearch;
#ifdef QT_DEBUG
        qDebug() << "Changed search to" << m_search;
#endif
        Q_EMIT searchChanged(search());
    }
}



bool UnitFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    Unit *l = sourceModel()->data(source_left, UnitModel::Item).value<Unit*>();
    Unit *r = sourceModel()->data(source_right, UnitModel::Item).value<Unit*>();

    switch(m_sortingRole) {
    case Id:
        return l->id() < r->id();
    case Created:
        return l->createdAt() < r->createdAt();
    case Updated:
        return l->updatedAt() < r->updatedAt();
    default:
        return l->displayName() < r->displayName();
    }
}


bool UnitFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex idx = sourceModel()->index(source_row, 0, source_parent);

    return sourceModel()->data(idx, UnitModel::Item).value<Unit*>()->displayName().contains(filterRegExp());
}


Unit *UnitFilterModel::createUnit(const QString &name, const QString &license, const QString &namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, const QString &tmpl)
{
    return m_unitModel.createUnit(name, license, namespaces, read, write, member, reset, notify, propread, docmethod, tmpl);
}


bool UnitFilterModel::updateUnit(int id, const QString &name, const QString &license, const QString &namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, const QString &tmpl)
{
    return m_unitModel.updateUnit(id, name, license, namespaces, read, write, member, reset, notify, propread, docmethod, tmpl);
}


bool UnitFilterModel::deleteUnit(int id)
{
    return m_unitModel.deleteUnit(id);
}


Unit *UnitFilterModel::get(int row) const
{
    Unit *u = nullptr;

    if (row > -1) {
        u = data(index(row, 0), UnitModel::Item).value<Unit*>();
    }

    return u;
}
