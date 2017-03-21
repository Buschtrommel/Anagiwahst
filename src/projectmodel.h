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

#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QObject>
#include <QAbstractListModel>

class Project;

class ProjectModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ProjectModel(QObject *parent = nullptr);
    ~ProjectModel();

    enum Roles {
        Item	= Qt::UserRole + 1
    };

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override final;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override final;
    QHash<int, QByteArray> roleNames() const override final;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override final;

    Q_INVOKABLE Project *createProject(QString name, QString license, QString namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, QString tmpl);
    Q_INVOKABLE bool updateProject(int id, QString name, QString license, QString namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, QString tmpl);
    Q_INVOKABLE bool deleteProject(int id);

private:
    QList<Project*> m_projects;

    Project *findById(int id) const;
    QModelIndex indexById(int id) const;
};

#endif // PROJECTMODEL_H
