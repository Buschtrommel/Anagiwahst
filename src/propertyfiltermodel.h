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

#ifndef PROPERTYFILTERMODEL_H
#define PROPERTYFILTERMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "propertymodel.h"

class Property;

class PropertyFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int unitId READ unitId WRITE setUnitId NOTIFY unitIdChanged STORED false)
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged STORED false)
public:
    explicit PropertyFilterModel(QObject *parent = nullptr);
    ~PropertyFilterModel();

    int unitId() const;
    QString search() const;
    int count() const;

    void setUnitId(int nUnitId);
    void setSearch(const QString &nSearch);

    Q_INVOKABLE Property *createProperty(const QString &name, const QString &type, bool r = true, bool w = true, bool m = false, bool u = false, bool n = true, bool d = true, bool usePropertyName = false);
    Q_INVOKABLE void expandProperty(Property *p);
    Q_INVOKABLE bool deleteProperty(Property *p);

    QList<Property*> getProperties() const;

Q_SIGNALS:
    void unitIdChanged(int unitId);
    void searchChanged(const QString &search);
    void countChanged(int count);

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override final;

private:
    PropertyModel m_propertyModel;
    QString m_search;

    Q_DISABLE_COPY(PropertyFilterModel)
};

#endif // PROPERTYFILTERMODEL_H
