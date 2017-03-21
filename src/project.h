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

#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QDateTime>

class QSqlQuery;

class Project : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString license READ license WRITE setLicense NOTIFY licenseChanged)
    Q_PROPERTY(QString namespaces READ namespaces WRITE setNamespaces NOTIFY namespacesChanged)
    Q_PROPERTY(bool read READ read WRITE setRead NOTIFY readChanged)
    Q_PROPERTY(bool write READ write WRITE setWrite NOTIFY writeChanged)
    Q_PROPERTY(bool member READ member WRITE setMember NOTIFY memberChanged)
    Q_PROPERTY(bool reset READ reset WRITE setReset NOTIFY resetChanged)
    Q_PROPERTY(bool notify READ notify WRITE setNotify NOTIFY notifyChanged)
    Q_PROPERTY(bool propread READ propread WRITE setPropread NOTIFY propreadChanged)
    Q_PROPERTY(bool docmethod READ docmethod WRITE setDocmethod NOTIFY docmethodChanged)
    Q_PROPERTY(QString tmpl READ tmpl WRITE setTmpl NOTIFY tmplChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
public:
    explicit Project(QObject *parent = nullptr);
    Project(int id, QString name, QString license, QString namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, QString tmpl, QDateTime createdAt, QDateTime updatedAt, QObject *parent = nullptr);
    ~Project();

    int id() const;
    QString name() const;
    QString license() const;
    QString namespaces() const;
    bool read() const;
    bool write() const;
    bool member() const;
    bool reset() const;
    bool notify() const;
    bool propread() const;
    bool docmethod() const;
    QString tmpl() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;

    void setId(int nId);
    void setName(const QString &nName);
    void setLicense(const QString &nLicense);
    void setNamespaces(const QString &nNamespaces);
    void setRead(bool nRead);
    void setWrite(bool nWrite);
    void setMember(bool nMember);
    void setReset(bool nReset);
    void setNotify(bool nNotify);
    void setPropread(bool nPropread);
    void setDocmethod(bool nDocmethod);
    void setTmpl(const QString &nTmpl);
    void setCreatedAt(const QDateTime &nCreatedAt);
    void setUpdatedAt(const QDateTime &nUpdatedAt);

    static Project *fromDb(const QSqlQuery *q, QObject *parent = nullptr);

Q_SIGNALS:
    void idChanged(int id);
    void nameChanged(const QString &name);
    void licenseChanged(const QString &license);
    void namespacesChanged(const QString &namespaces);
    void readChanged(bool read);
    void writeChanged(bool write);
    void memberChanged(bool member);
    void resetChanged(bool reset);
    void notifyChanged(bool notify);
    void propreadChanged(bool propread);
    void docmethodChanged(bool docmethod);
    void tmplChanged(const QString &tmpl);
    void createdAtChanged(const QDateTime &createdAt);
    void updatedAtChanged(const QDateTime &updatedAt);

private:
    int m_id = 0;
    QString m_name;
    QString m_license;
    QString m_namespaces;
    bool m_read = true;
    bool m_write = true;
    bool m_member = false;
    bool m_reset = false;
    bool m_notify = true;
    bool m_propread = false;
    bool m_docmethod = true;
    QString m_tmpl;
    QDateTime m_createdAt;
    QDateTime m_updatedAt;

    Q_DISABLE_COPY(Project)
};


#endif // PROJECT_H
