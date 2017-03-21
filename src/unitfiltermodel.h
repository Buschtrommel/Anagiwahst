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

#ifndef UNITFILTERMODEL_H
#define UNITFILTERMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "unitmodel.h"

class UnitFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int projectId READ projectId WRITE setProjectId NOTIFY projectIdChanged)
    Q_PROPERTY(SortingRole sortingRole READ sortingRole WRITE setSortingRole NOTIFY sortingRoleChanged)
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
public:
    explicit UnitFilterModel(QObject *parent = nullptr);
    ~UnitFilterModel();

    enum SortingRole : quint8 {
        Id = 0,
        Name = 1,
        Created = 2,
        Updated = 3
    };
    Q_ENUM(SortingRole)

    int projectId() const;
    SortingRole sortingRole() const;
    QString search() const;

    void setProjectId(int nProjectId);
    void setSortingRole(UnitFilterModel::SortingRole nSortingRole);
    void setSearch(const QString &nSearch);

    Q_INVOKABLE Unit *createUnit(const QString &name, const QString &license, const QString &namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, const QString &tmpl);
    Q_INVOKABLE bool updateUnit(int id, const QString &name, const QString &license, const QString &namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, const QString &tmpl);
    Q_INVOKABLE bool deleteUnit(int id);

    Q_INVOKABLE Unit *get(int row) const;

Q_SIGNALS:
    void projectIdChanged(int projectId);
    void sortingRoleChanged(SortingRole sortingRole);
    void searchChanged(const QString &search);

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override final;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override final;

private:
    UnitModel m_unitModel;
    SortingRole m_sortingRole = Name;
    QString m_search;

    Q_DISABLE_COPY(UnitFilterModel)
};

#endif // UNITFILTERMODEL_H
