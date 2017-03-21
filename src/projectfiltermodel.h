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

#ifndef PROJECTFILTERMODEL_H
#define PROJECTFILTERMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

class ProjectFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(SortingRole sortingRole READ sortingRole WRITE setSortingRole NOTIFY sortingRoleChanged)
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
public:
    enum SortingRole : quint8 {
        Id = 0,
        Name = 1,
        Created = 2,
        Updated = 3
    };
    Q_ENUM(SortingRole)

    explicit ProjectFilterModel(SortingRole sortingRole = Name, QObject *parent = nullptr);
    ~ProjectFilterModel();

    SortingRole sortingRole() const;
    QString search() const;

    void setSortingRole(SortingRole nSortingRole);
    void setSearch(const QString &nSearch);

Q_SIGNALS:
    void sortingRoleChanged(SortingRole sortingRole);
    void searchChanged(const QString &search);

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    SortingRole m_sortingRole = Name;
    QString m_search;

    Q_DISABLE_COPY(ProjectFilterModel)
};

#endif // PROJECTFILTERMODEL_H
