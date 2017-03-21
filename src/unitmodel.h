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

#ifndef UNITMODEL_H
#define UNITMODEL_H

#include <QObject>
#include <QAbstractListModel>

class Unit;

class UnitModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit UnitModel(QObject *parent = nullptr);
    ~UnitModel();

    enum Roles {
        Item = Qt::UserRole + 1
    };

    QHash<int, QByteArray> roleNames() const override final;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override final;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override final;
    QVariant data(const QModelIndex &index, int role) const override final;

    int projectId() const;
    void setProjectId(int projectId);

    Unit *createUnit(const QString &name, const QString &license, const QString &namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, const QString &tmpl);
    bool updateUnit(int id, const QString &name, const QString &license, const QString &namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, const QString &tmpl);
    bool deleteUnit(int id);

private:
    QList<Unit*> m_units;
    int m_projectId = -1;

    void clear();
    Unit *findById(int id) const;
    QModelIndex indexById(int id) const;
};

#endif // UNITMODEL_H
