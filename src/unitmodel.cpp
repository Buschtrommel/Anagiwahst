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

#include "unitmodel.h"
#include "unit.h"
#include <QSqlQuery>
#include <QSqlError>

UnitModel::UnitModel(QObject *parent) : QAbstractListModel(parent)
{

}


UnitModel::~UnitModel()
{

}


QHash<int, QByteArray> UnitModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Item, QByteArrayLiteral("item"));
    return roles;
}


int UnitModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_units.size();
}


QModelIndex UnitModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex idx;

    if (hasIndex(row, column, parent)) {
        idx = createIndex(row, column);
    }

    return idx;
}


QVariant UnitModel::data(const QModelIndex &index, int role) const
{
    QVariant val;

    if (!index.isValid() || (index.row() >= m_units.size())) {
        return val;
    }

    if (role == Item) {
        val.setValue<Unit*>(m_units.at(index.row()));
    }

    return val;
}



void UnitModel::clear()
{
    if (Q_LIKELY(!m_units.empty())) {
        beginRemoveRows(QModelIndex(), 0, m_units.size()-1);

        qDeleteAll(m_units);
        m_units.clear();

        endRemoveRows();
    }
}


int UnitModel::projectId() const { return m_projectId; }

void UnitModel::setProjectId(int projectId)
{
    if (m_projectId != projectId) {
        m_projectId = projectId;
        clear();

        if (m_projectId > -1) {

            QSqlQuery q;
            if (!q.prepare(QStringLiteral("SELECT id, project, name, license, namespaces, read, write, member, reset, notify, propread, docmethod, template, created_at, updated_at FROM units WHERE project = ?"))) {
                qCritical("Failed to prepare database query for requesting units: %s", qUtf8Printable(q.lastError().text()));
                return;
            }

            q.addBindValue(projectId);

            if (!q.exec()) {
                qCritical("Failed to execute database query for requesting units: %s", qUtf8Printable(q.lastError().text()));
                return;
            }

            QList<Unit*> _units;
            while (q.next()) {
                _units.append(Unit::fromDb(&q, this));
            }

            if (!_units.empty()) {
                beginInsertRows(QModelIndex(), 0, _units.size()-1);

                m_units = _units;

                endInsertRows();
            }
        }
    }
}


Unit *UnitModel::findById(int id) const
{
    Unit *u = nullptr;

    if (Q_LIKELY(!m_units.empty())) {
        for (int i = 0; i < m_units.size(); ++i) {
            if (m_units.at(i)->id() == id) {
                u = m_units.at(i);
                break;
            }
        }
    }

    if (!u) {
        qWarning("Unit ID %i not found.", id);
    }

    return u;
}


QModelIndex UnitModel::indexById(int id) const
{
    QModelIndex idx;

    int row = -1;
    if (Q_LIKELY(!m_units.empty())) {
        for (int i = 0; i < m_units.size(); ++i) {
            if (m_units.at(i)->id() == id) {
                row = i;
                break;
            }
        }
    }

    if (row > -1) {
        idx = index(row);
    } else {
        qWarning("Unit ID %i not found.", id);
    }

    return idx;
}


Unit *UnitModel::createUnit(int projectId, const QString &name, const QString &license, const QString &namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, const QString &tmpl)
{
    Unit *u = nullptr;

    QSqlQuery q;

    if (Q_UNLIKELY(!q.prepare(QStringLiteral("INSERT INTO units (project, name, license, namespaces, read, write, member, reset, notify, propread, docmethod, template, created_at, updated_at) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?)")))) {
        qCritical("Failed to prepare to insert new unit into database: %s", qUtf8Printable(q.lastError().text()));
        return u;
    }

    const QDateTime currentUtc = QDateTime::currentDateTimeUtc();
    const QDateTime currentLocal = currentUtc.toLocalTime();

    q.addBindValue(projectId);
    q.addBindValue(name);
    q.addBindValue(license);
    q.addBindValue(namespaces);
    q.addBindValue(read);
    q.addBindValue(write);
    q.addBindValue(member);
    q.addBindValue(reset);
    q.addBindValue(notify);
    q.addBindValue(propread);
    q.addBindValue(docmethod);
    q.addBindValue(tmpl);
    q.addBindValue(currentLocal.toTime_t());
    q.addBindValue(currentLocal.toTime_t());

    if (Q_UNLIKELY(!q.exec())) {
        qCritical("Failed to insert new unit into database: %s", qUtf8Printable(q.lastError().text()));
        return u;
    }

    u = new Unit(q.lastInsertId().toInt(), projectId, name, license, namespaces, read, write, member, reset, notify, propread, docmethod, tmpl, currentLocal, currentLocal, this);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_units.append(u);

    endInsertRows();;

    return u;
}


bool UnitModel::updateUnit(int id, const QString &name, const QString &license, const QString &namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, const QString &tmpl)
{
    bool retVal = false;

    Unit *u = findById(id);
    if (u) {
        QSqlQuery q;
        if (Q_UNLIKELY(!q.prepare(QStringLiteral("UPDATE units SET name = ?, license = ?, namespaces = ?, read = ?, write = ?, member = ?, reset = ?, notify = ?, propread = ?, docmethod = ?, template = ?, updated_at = ? WHERE id = ?")))) {
            qCritical("Failed to prepare unit update in database: %s", qUtf8Printable(q.lastError().text()));
            return retVal;
        }

        const QDateTime currentUtc = QDateTime::currentDateTimeUtc();
        const QDateTime currentLocal = currentUtc.toLocalTime();

        q.addBindValue(name);
        q.addBindValue(license);
        q.addBindValue(namespaces);
        q.addBindValue(read);
        q.addBindValue(write);
        q.addBindValue(member);
        q.addBindValue(reset);
        q.addBindValue(notify);
        q.addBindValue(propread);
        q.addBindValue(docmethod);
        q.addBindValue(tmpl);
        q.addBindValue(currentUtc.toTime_t());
        q.addBindValue(id);

        if (Q_UNLIKELY(!q.exec())) {
            qCritical("Failed to update unit in database: %s", qUtf8Printable(q.lastError().text()));
            return retVal;
        }

        u->setName(name);
        u->setLicense(license);
        u->setNamespaces(namespaces);
        u->setRead(read);
        u->setWrite(write);
        u->setMember(member);
        u->setReset(reset);
        u->setNotify(notify);
        u->setPropread(propread);
        u->setDocmethod(docmethod);
        u->setTmpl(tmpl);
        u->setUpdatedAt(currentLocal);

        retVal = true;
    }

    return retVal;
}



bool UnitModel::deleteUnit(int id)
{
    bool retVal = false;

    const QModelIndex idx = indexById(id);
    if (idx.isValid()) {

        QSqlQuery q;
        if (Q_UNLIKELY(!q.prepare(QStringLiteral("DELETE FROM units WHERE id = ?")))) {
            qCritical("Failed to prepare units deletion in database: %s", qUtf8Printable(q.lastError().text()));
            return retVal;
        }

        q.addBindValue(id);

        if (Q_UNLIKELY(!q.exec())) {
            qCritical("Failed to delete unit from database: %s", qUtf8Printable(q.lastError().text()));
            return retVal;
        }

        beginRemoveRows(QModelIndex(), idx.row(), idx.row());

        delete m_units.takeAt(idx.row());

        endRemoveRows();

        retVal = true;
    }

    return retVal;
}
