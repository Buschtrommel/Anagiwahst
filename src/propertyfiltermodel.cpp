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

#include "propertyfiltermodel.h"
#include "property.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

PropertyFilterModel::PropertyFilterModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    connect(&m_propertyModel, &PropertyModel::rowCountChanged, this, &PropertyFilterModel::countChanged);
    setSourceModel(&m_propertyModel);
    sort(0);
}


PropertyFilterModel::~PropertyFilterModel()
{

}


Property *PropertyFilterModel::createProperty(const QString &name, const QString &type, bool r, bool w, bool m, bool u, bool n, bool d, bool usePropertyName)
{
    return m_propertyModel.createProperty(name, type, r, w, m, u, n, d, usePropertyName);
}


void PropertyFilterModel::expandProperty(Property *p)
{
    m_propertyModel.expandProperty(p);
}

bool PropertyFilterModel::deleteProperty(Property *p)
{
    return m_propertyModel.deleteProperty(p);
}


bool PropertyFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    Property *l = sourceModel()->data(source_left, PropertyModel::Item).value<Property*>();
    Property *r = sourceModel()->data(source_right, PropertyModel::Item).value<Property*>();

    return l->order() < r->order();
}

QList<Property*> PropertyFilterModel::getProperties() const
{
    return m_propertyModel.getProperties();
}

/*!
 * \property PropertyFilterModel::unitId
 * \brief Database ID of the unit this property belongs to.
 *
 * \par Access functions:
 * \li int unitId() const
 * \li void setUnitId(int nUnitId)
 *
 * \par Notifier signal:
 * \li void unitIdChanged(int unitId)
 */

/*!
 * \fn void  PropertyFilterModel::unitIdChanged(int unitId)
 * \brief Notifier function for the \link PropertyFilterModel::unitId unitId \endlink property.
 * \sa PropertyFilterModel::unitId() PropertyFilterModel::setUnitId()
 */

/*!
 * \brief Getter function for the \link PropertyFilterModel::unitId unitId \endlink property.
 * \sa PropertyFilterModel::setUnitId() PropertyFilterModel::unitIdChanged()
 */
int PropertyFilterModel::unitId() const { return m_propertyModel.unitId(); }

/*!
 * \brief Setter function for the \link PropertyFilterModel::unitId unitId \endlink property.
 * \sa PropertyFilterModel::unitId() PropertyFilterModel::unitIdChanged()
 */
void PropertyFilterModel::setUnitId(int nUnitId)
{
    if (m_propertyModel.unitId() != nUnitId) {
        m_propertyModel.setUnitId(nUnitId);
#ifdef QT_DEBUG
        qDebug() << "Changed unitId to" << nUnitId;
#endif
        Q_EMIT unitIdChanged(unitId());
    }
}


/*!
 * \property PropertyFilterModel::search
 * \brief Search string.
 *
 * \par Access functions:
 * \li QString search() const
 * \li void setSearch(const QString &nSearch)
 *
 * \par Notifier signal:
 * \li void searchChanged(const QString &search)
 */

/*!
 * \fn void  PropertyFilterModel::searchChanged(const QString &search)
 * \brief Notifier function for the \link PropertyFilterModel::search search \endlink property.
 * \sa PropertyFilterModel::search() PropertyFilterModel::setSearch()
 */

/*!
 * \brief Getter function for the \link PropertyFilterModel::search search \endlink property.
 * \sa PropertyFilterModel::setSearch() PropertyFilterModel::searchChanged()
 */
QString PropertyFilterModel::search() const { return m_search; }

/*!
 * \brief Setter function for the \link PropertyFilterModel::search search \endlink property.
 * \sa PropertyFilterModel::search() PropertyFilterModel::searchChanged()
 */
void PropertyFilterModel::setSearch(const QString &nSearch)
{
    if (nSearch != m_search) {
        m_search = nSearch;
#ifdef QT_DEBUG
        qDebug() << "Changed search to" << m_search;
#endif
        Q_EMIT searchChanged(search());
    }
}


int PropertyFilterModel::count() const
{
    return m_propertyModel.rowCount();
}
