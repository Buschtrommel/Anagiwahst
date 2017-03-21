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

#include "projectmodel.h"
#include "project.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

ProjectModel::ProjectModel(QObject *parent) : QAbstractListModel(parent)
{
    QSqlQuery q(QStringLiteral("SELECT id, name, license, namespaces, read, write, member, reset, notify, propread, docmethod, template, created_at, updated_at FROM projects"));

    if (q.lastError().isValid()) {
        qFatal("Failed to query projects from the database: %s", qUtf8Printable(q.lastError().text()));
    }

    QList<Project*> prjs;
    while (q.next()) {
        prjs.append(Project::fromDb(&q, this));
    }

    if (!prjs.isEmpty()) {
        beginInsertRows(QModelIndex(), 0, prjs.size()-1);

        m_projects = prjs;

        endInsertRows();
    }
}


ProjectModel::~ProjectModel()
{

}



QHash<int, QByteArray> ProjectModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Item, QByteArrayLiteral("item"));
    return roles;
}



int ProjectModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_projects.size();
}


QModelIndex ProjectModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex idx;

    if (hasIndex(row, column, parent)) {
        idx = createIndex(row, column);
    }

    return idx;
}


QVariant ProjectModel::data(const QModelIndex &index, int role) const
{
    QVariant val;

    if (!index.isValid() || (index.row() > (m_projects.size()-1))) {
        return val;
    }

    if (role == Item) {
        val.setValue<Project*>(m_projects.at(index.row()));
    }

    return val;
}


Project *ProjectModel::findById(int id) const
{
    Project *prj = nullptr;

    if (Q_LIKELY(!m_projects.empty())) {
        for (int i = 0; i < m_projects.size(); ++i) {
            if (m_projects.at(i)->id() == id) {
                prj = m_projects.at(i);
                break;
            }
        }
    }

    if (!prj) {
        qWarning("Project ID %i not found.", id);
    }

    return prj;
}


QModelIndex ProjectModel::indexById(int id) const
{
    QModelIndex idx;

    int row = -1;
    if (Q_LIKELY(!m_projects.isEmpty())) {
        for (int i = 0; i < m_projects.size(); ++i) {
            if (m_projects.at(i)->id() == id) {
                row = i;
                break;
            }
        }
    }

    if (row > -1) {
        idx = index(row);
    } else {
        qWarning("Project ID %i not found.", id);
    }

    return idx;
}


Project *ProjectModel::createProject(QString name, QString license, QString namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, QString tmpl)
{
    Project *prj = nullptr;

    QSqlQuery q;

    if (!q.prepare(QStringLiteral("INSERT INTO projects (name, license, namespaces, read, write, member, reset, notify, propread, docmethod, template, created_at, updated_at) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)"))) {
        qCritical("Failed to prepare to insert new project into database: %s", qUtf8Printable(q.lastError().text()));
        return prj;
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
    q.addBindValue(currentUtc.toTime_t());

    if (!q.exec()) {
        qCritical("Failed to execute database query to insert new project into database: %s", qUtf8Printable(q.lastError().text()));
        return prj;
    }

    prj = new Project(q.lastInsertId().toInt(), name, license, namespaces, read, write, member, reset, notify, propread, docmethod, tmpl, currentLocal, currentLocal, this);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_projects.append(prj);

    endInsertRows();

    return prj;
}


bool ProjectModel::updateProject(int id, QString name, QString license, QString namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, QString tmpl)
{
    bool retVal = false;

    Project *prj = findById(id);
    if (prj) {
        QSqlQuery q;
        if (!q.prepare(QStringLiteral("UPDATE projects SET name = ?, license = ?, namespaces = ?, read = ?, write = ?, member = ?, reset = ?, notify = ?, propread = ?, docmethod = ?, template = ?, updated_at = ? WHERE id = ?"))) {
            qCritical("Failed to prepare updating project in database: %s", qUtf8Printable(q.lastError().text()));
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

        if (!q.exec()) {
            qCritical("Failed to execute database query to update project in database: %s", qUtf8Printable(q.lastError().text()));
            return retVal;
        }

        prj->setName(name);
        prj->setLicense(license);
        prj->setNamespaces(namespaces);
        prj->setRead(read);
        prj->setWrite(write);
        prj->setMember(member);
        prj->setReset(reset);
        prj->setNotify(notify);
        prj->setPropread(propread);
        prj->setDocmethod(docmethod);
        prj->setTmpl(tmpl);
        prj->setUpdatedAt(currentLocal);

        retVal = true;
    }

    return retVal;
}


bool ProjectModel::deleteProject(int id)
{
    bool retVal = false;

    const QModelIndex idx = indexById(id);
    if (idx.isValid()) {

        QSqlQuery q;
        if (!q.prepare(QStringLiteral("DELETE FROM projects WHERE id = ?"))) {
            qCritical("Failed to prepare project deletion from database: %s", qUtf8Printable(q.lastError().text()));
            return retVal;
        }

        q.addBindValue(id);

        if (!q.exec()) {
            qCritical("Failed to delete project from database:: %s", qUtf8Printable(q.lastError().text()));
            return retVal;
        }

        beginRemoveRows(QModelIndex(), idx.row(), idx.row());

        delete m_projects.takeAt(idx.row());

        endRemoveRows();

        retVal = true;
    }

    return retVal;
}
