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

#include "dbmanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QFileInfo>

DBManager::DBManager()
{

}


void DBManager::check()
{
    const QFileInfo dbfile(QStandardPaths::writableLocation(QStandardPaths::DataLocation).append(QLatin1String("/database.sqlite")));
    const bool dbexists = dbfile.exists();

    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    db.setDatabaseName(dbfile.absoluteFilePath());

    if (!db.open()) {
        qFatal("Failed to open database: %s", qUtf8Printable(db.lastError().text()));
    }

    QSqlQuery q(db);

    if (!q.exec(QStringLiteral("PRAGMA foreign_keys = ON"))) {
        qFatal("Failed to activate foreign key support: %s", qUtf8Printable(db.lastError().text()));
    }

    if (!dbexists) {

        qInfo("Creating database: %s", qUtf8Printable(dbfile.absoluteFilePath()));

        if (!db.transaction()) {
            qFatal("Failed to start database transaction: %s", qUtf8Printable(db.lastError().text()));
        }

        if (!q.exec(QStringLiteral("CREATE TABLE projects ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "name TEXT NOT NULL, "
                                   "license TEXT, "
                                   "namespace TEXT, "
                                   "read INTEGER NOT NULL DEFAULT 1, "
                                   "write INTEGER NOT NULL DEFAULT 1, "
                                   "member INTEGER NOT NULL DEFAULT 0, "
                                   "reset INTEGER NOT NULL DEFAULT 0, "
                                   "notify INTEGER NOT NULL DEFAULT 1, "
                                   "propread INTEGER NOT NULL DEFAULT 0, "
                                   "docmethod INTEGER NOT NULL DEFAULT 1, "
                                   "created_at INTEGER NOT NULL DEFAULT 0, "
                                   "updated_at INTEGER NOT NULL DEFAULT 0"
                                   ")"))) {
            qFatal("Failed to create project table: %s", qUtf8Printable(q.lastError().text()));
        }

        if (!q.exec(QStringLiteral("CREATE INDEX prj_idx ON projects (id)"))) {
            qFatal("Failed to create prj_idx index: %s", qUtf8Printable(q.lastError().text()));
        }

        if (!q.exec(QStringLiteral("CREATE TABLE units ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "project INTEGER NOT NULL, "
                                   "name TEXT NOT NULL, "
                                   "license TEXT, "
                                   "namespace TEXT, "
                                   "read INTEGER NOT NULL DEFAULT 1, "
                                   "write INTEGER NOT NULL DEFAULT 1, "
                                   "member INTEGER NOT NULL DEFAULT 0, "
                                   "reset INTEGER NOT NULL DEFAULT 0, "
                                   "notify INTEGER NOT NULL DEFAULT 1, "
                                   "propread INTEGER NOT NULL DEFAULT 0, "
                                   "docmethod INTEGER NOT NULL DEFAULT 1, "
                                   "created_at INTEGER NOT NULL DEFAULT 0, "
                                   "updated_at INTEGER NOT NULL DEFAULT 0, "
                                   "FOREIGN KEY(project) REFERENCES projects(id) ON DELETE CASCADE"
                                   ")"))) {
            qFatal("Failed to create units table: %s", qUtf8Printable(q.lastError().text()));
        }

        if (!q.exec(QStringLiteral("CREATE INDEX units_idx ON units (id)"))) {
            qFatal("Failed to create units_idx index: %s", qUtf8Printable(q.lastError().text()));
        }

        if (!q.exec(QStringLiteral("CREATE INDEX units_prj_idx ON units (id, project)"))) {
            qFatal("Failed to create units_orj_idx index: %s", qUtf8Printable(q.lastError().text()));
        }

        if (!q.exec(QStringLiteral("CREATE TABLE properties ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "unit INTEGER NOT NULL, "
                                   "name TEXT NOT NULL, "
                                   "type TEXT NOT NULL, "
                                   "read TEXT, "
                                   "write TEXT, "
                                   "notify TEXT, "
                                   "member TEXT, "
                                   "reset TEXT, "
                                   "revision INTEGER DEFAULT 0, "
                                   "designable TEXT, "
                                   "scriptable TEXT, "
                                   "stored INTEGER NOT NULL DEFAULT 1, "
                                   "user INTEGER NOT NULL DEFAULT 0, "
                                   "constant INTEGER NOT NULL DEFAULT 0, "
                                   "final INTEGER NOT NULL DEFAULT 0, "
                                   "pointer INTEGER NOT NULL DEFAULT 0, "
                                   "argsbyref INTEGER NOT NULL DEFAULT 0, "
                                   "docmethod INTEGER NOT NULL DEFAULT 1, "
                                   "defval TEXT, "
                                   "brief TEXT, "
                                   "comment TEXT, "
                                   "created_at INTEGER NOT NULL DEFAULT 0, "
                                   "updated_at INTEGER NOT NULL DEFAULT 0, "
                                   "FOREIGN KEY (unit) REFERENCES units(id) ON DELETE CASCADE"
                                   ")"))) {
            qFatal("Failed to create properties table: %s", qUtf8Printable(q.lastError().text()));
        }

        if (!q.exec(QStringLiteral("CREATE INDEX props_idx ON properties (id)"))) {
            qFatal("Failed to create props_idx index: %s", qUtf8Printable(q.lastError().text()));
        }

        if (!q.exec(QStringLiteral("CREATE INDEX props_unit_idx ON properties (id, unit)"))) {
            qFatal("Failed to create props_unit_idx index: %s", qUtf8Printable(q.lastError().text()));
        }

        if (!q.exec(QStringLiteral("CREATE TABLE system (key TEXT UNIQUE, value INTEGER NOT NULL)"))) {
            qFatal("Failed to create system table: %s", qUtf8Printable(q.lastError().text()));
        }

        if (!q.exec(QStringLiteral("INSERT INTO system (key, value) VALUES ('version', 1)"))) {
            qFatal("Failed to insert table version information: %s", qUtf8Printable(q.lastError().text()));
        }

        if (!db.commit()) {
            qFatal("Failed to commit database transaction: %s", qUtf8Printable(db.lastError().text()));
        }
    }
}
