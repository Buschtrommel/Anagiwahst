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

#include "project.h"
#include <QSqlQuery>
#include <QVariant>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

/*!
 * \class Project
 * \brief Contains information and settings for a single project.
 */


/*!
 * \brief Constructs a new Project object with default values and the given \a parent.
 */
Project::Project(QObject *parent) : QObject(parent)
{
}


Project::Project(int id, QString name, QString license, QString namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, QString tmpl, QDateTime createdAt, QDateTime updatedAt, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_name(name),
    m_license(license),
    m_namespaces(namespaces),
    m_read(read),
    m_write(write),
    m_member(member),
    m_reset(reset),
    m_notify(notify),
    m_propread(propread),
    m_docmethod(docmethod),
    m_tmpl(tmpl),
    m_createdAt(createdAt),
    m_updatedAt(updatedAt)
{
}


/*!
 * \brief Deconstructs the Project object.
 */
Project::~Project()
{
}


/*!
 * \property Project::id
 * \brief Database ID of the project.
 *
 * \par Access functions:
 * \li int id() const
 * \li void setId(int nId)
 *
 * \par Notifier signal:
 * \li void idChanged(int id)
 */

/*!
 * \fn void  Project::idChanged(int id)
 * \brief Notifier function for the \link Project::id id \endlink property.
 * \sa Project::id() Project::setId()
 */

/*!
 * \brief Getter function for the \link Project::id id \endlink property.
 * \sa Project::setId() Project::idChanged()
 */
int Project::id() const { return m_id; }

/*!
 * \brief Setter function for the \link Project::id id \endlink property.
 * \sa Project::id() Project::idChanged()
 */
void Project::setId(int nId)
{
    if (nId != m_id) {
        m_id = nId;
#ifdef QT_DEBUG
        qDebug() << "Changed id to" << m_id;
#endif
        Q_EMIT idChanged(id());
    }
}


/*!
 * \property Project::name
 * \brief Name of the project.
 *
 * \par Access functions:
 * \li QString name() const
 * \li void setName(const QString &nName)
 *
 * \par Notifier signal:
 * \li void nameChanged(const QString &name)
 */

/*!
 * \fn void  Project::nameChanged(const QString &name)
 * \brief Notifier function for the \link Project::name name \endlink property.
 * \sa Project::name() Project::setName()
 */

/*!
 * \brief Getter function for the \link Project::name name \endlink property.
 * \sa Project::setName() Project::nameChanged()
 */
QString Project::name() const { return m_name; }

/*!
 * \brief Setter function for the \link Project::name name \endlink property.
 * \sa Project::name() Project::nameChanged()
 */
void Project::setName(const QString &nName)
{
    if (nName != m_name) {
        m_name = nName;
#ifdef QT_DEBUG
        qDebug() << "Changed name to" << m_name;
#endif
        Q_EMIT nameChanged(name());
    }
}


/*!
 * \property Project::license
 * \brief Optional project default license header text.
 *
 * \par Access functions:
 * \li QString license() const
 * \li void setLicense(const QString &nLicense)
 *
 * \par Notifier signal:
 * \li void licenseChanged(const QString &license)
 */

/*!
 * \fn void  Project::licenseChanged(const QString &license)
 * \brief Notifier function for the \link Project::license license \endlink property.
 * \sa Project::license() Project::setLicense()
 */

/*!
 * \brief Getter function for the \link Project::license license \endlink property.
 * \sa Project::setLicense() Project::licenseChanged()
 */
QString Project::license() const { return m_license; }

/*!
 * \brief Setter function for the \link Project::license license \endlink property.
 * \sa Project::license() Project::licenseChanged()
 */
void Project::setLicense(const QString &nLicense)
{
    if (nLicense != m_license) {
        m_license = nLicense;
#ifdef QT_DEBUG
        qDebug() << "Changed license to" << m_license;
#endif
        Q_EMIT licenseChanged(license());
    }
}


/*!
 * \property Project::namespaces
 * \brief Optional default namespaces for the project.
 *
 * \par Access functions:
 * \li QString namespaces() const
 * \li void setNamespaces(const QString &nNamespaces)
 *
 * \par Notifier signal:
 * \li void namespacesChanged(const QString &namespaces)
 */

/*!
 * \fn void  Project::namespacesChanged(const QString &namespaces)
 * \brief Notifier function for the \link Project::namespaces namespaces \endlink property.
 * \sa Project::namespaces() Project::setNamespaces()
 */

/*!
 * \brief Getter function for the \link Project::namespaces namespaces \endlink property.
 * \sa Project::setNamespaces() Project::namespacesChanged()
 */
QString Project::namespaces() const { return m_namespaces; }

/*!
 * \brief Setter function for the \link Project::namespaces namespaces \endlink property.
 * \sa Project::namespaces() Project::namespacesChanged()
 */
void Project::setNamespaces(const QString &nNamespaces)
{
    if (nNamespaces != m_namespaces) {
        m_namespaces = nNamespaces;
#ifdef QT_DEBUG
        qDebug() << "Changed namespaces to" << m_namespaces;
#endif
        Q_EMIT namespacesChanged(namespaces());
    }
}


/*!
 * \property Project::read
 * \brief Project default for creating read methods.
 *
 * \par Access functions:
 * \li bool read() const
 * \li void setRead(bool nRead)
 *
 * \par Notifier signal:
 * \li void readChanged(bool read)
 */

/*!
 * \fn void  Project::readChanged(bool read)
 * \brief Notifier function for the \link Project::read read \endlink property.
 * \sa Project::read() Project::setRead()
 */

/*!
 * \brief Getter function for the \link Project::read read \endlink property.
 * \sa Project::setRead() Project::readChanged()
 */
bool Project::read() const { return m_read; }

/*!
 * \brief Setter function for the \link Project::read read \endlink property.
 * \sa Project::read() Project::readChanged()
 */
void Project::setRead(bool nRead)
{
    if (nRead != m_read) {
        m_read = nRead;
#ifdef QT_DEBUG
        qDebug() << "Changed read to" << m_read;
#endif
        Q_EMIT readChanged(read());
    }
}


/*!
 * \property Project::write
 * \brief Project default for creating write functions.
 *
 * \par Access functions:
 * \li bool write() const
 * \li void setWrite(bool nWrite)
 *
 * \par Notifier signal:
 * \li void writeChanged(bool write)
 */

/*!
 * \fn void  Project::writeChanged(bool write)
 * \brief Notifier function for the \link Project::write write \endlink property.
 * \sa Project::write() Project::setWrite()
 */

/*!
 * \brief Getter function for the \link Project::write write \endlink property.
 * \sa Project::setWrite() Project::writeChanged()
 */
bool Project::write() const { return m_write; }

/*!
 * \brief Setter function for the \link Project::write write \endlink property.
 * \sa Project::write() Project::writeChanged()
 */
void Project::setWrite(bool nWrite)
{
    if (nWrite != m_write) {
        m_write = nWrite;
#ifdef QT_DEBUG
        qDebug() << "Changed write to" << m_write;
#endif
        Q_EMIT writeChanged(write());
    }
}


/*!
 * \property Project::member
 * \brief Project default for creating member.
 *
 * \par Access functions:
 * \li bool member() const
 * \li void setMember(bool nMember)
 *
 * \par Notifier signal:
 * \li void memberChanged(bool member)
 */

/*!
 * \fn void  Project::memberChanged(bool member)
 * \brief Notifier function for the \link Project::member member \endlink property.
 * \sa Project::member() Project::setMember()
 */

/*!
 * \brief Getter function for the \link Project::member member \endlink property.
 * \sa Project::setMember() Project::memberChanged()
 */
bool Project::member() const { return m_member; }

/*!
 * \brief Setter function for the \link Project::member member \endlink property.
 * \sa Project::member() Project::memberChanged()
 */
void Project::setMember(bool nMember)
{
    if (nMember != m_member) {
        m_member = nMember;
#ifdef QT_DEBUG
        qDebug() << "Changed member to" << m_member;
#endif
        Q_EMIT memberChanged(member());
    }
}


/*!
 * \property Project::reset
 * \brief Project default for creating reset function.
 *
 * \par Access functions:
 * \li bool reset() const
 * \li void setReset(bool nReset)
 *
 * \par Notifier signal:
 * \li void resetChanged(bool reset)
 */

/*!
 * \fn void  Project::resetChanged(bool reset)
 * \brief Notifier function for the \link Project::reset reset \endlink property.
 * \sa Project::reset() Project::setReset()
 */

/*!
 * \brief Getter function for the \link Project::reset reset \endlink property.
 * \sa Project::setReset() Project::resetChanged()
 */
bool Project::reset() const { return m_reset; }

/*!
 * \brief Setter function for the \link Project::reset reset \endlink property.
 * \sa Project::reset() Project::resetChanged()
 */
void Project::setReset(bool nReset)
{
    if (nReset != m_reset) {
        m_reset = nReset;
#ifdef QT_DEBUG
        qDebug() << "Changed reset to" << m_reset;
#endif
        Q_EMIT resetChanged(reset());
    }
}


/*!
 * \property Project::notify
 * \brief Project default for creating notify functions.
 *
 * \par Access functions:
 * \li bool notify() const
 * \li void setNotify(bool nNotify)
 *
 * \par Notifier signal:
 * \li void notifyChanged(bool notify)
 */

/*!
 * \fn void  Project::notifyChanged(bool notify)
 * \brief Notifier function for the \link Project::notify notify \endlink property.
 * \sa Project::notify() Project::setNotify()
 */

/*!
 * \brief Getter function for the \link Project::notify notify \endlink property.
 * \sa Project::setNotify() Project::notifyChanged()
 */
bool Project::notify() const { return m_notify; }

/*!
 * \brief Setter function for the \link Project::notify notify \endlink property.
 * \sa Project::notify() Project::notifyChanged()
 */
void Project::setNotify(bool nNotify)
{
    if (nNotify != m_notify) {
        m_notify = nNotify;
#ifdef QT_DEBUG
        qDebug() << "Changed notify to" << m_notify;
#endif
        Q_EMIT notifyChanged(notify());
    }
}


/*!
 * \property Project::propread
 * \brief Project default for using the property name for the read function.
 *
 * \par Access functions:
 * \li bool propread() const
 * \li void setPropread(bool nPropread)
 *
 * \par Notifier signal:
 * \li void propreadChanged(bool propread)
 */

/*!
 * \fn void  Project::propreadChanged(bool propread)
 * \brief Notifier function for the \link Project::propread propread \endlink property.
 * \sa Project::propread() Project::setPropread()
 */

/*!
 * \brief Getter function for the \link Project::propread propread \endlink property.
 * \sa Project::setPropread() Project::propreadChanged()
 */
bool Project::propread() const { return m_propread; }

/*!
 * \brief Setter function for the \link Project::propread propread \endlink property.
 * \sa Project::propread() Project::propreadChanged()
 */
void Project::setPropread(bool nPropread)
{
    if (nPropread != m_propread) {
        m_propread = nPropread;
#ifdef QT_DEBUG
        qDebug() << "Changed propread to" << m_propread;
#endif
        Q_EMIT propreadChanged(propread());
    }
}


/*!
 * \property Project::docmethod
 * \brief Project default fore documenting methods.
 *
 * \par Access functions:
 * \li bool docmethod() const
 * \li void setDocmethod(bool nDocmethod)
 *
 * \par Notifier signal:
 * \li void docmethodChanged(bool docmethod)
 */

/*!
 * \fn void  Project::docmethodChanged(bool docmethod)
 * \brief Notifier function for the \link Project::docmethod docmethod \endlink property.
 * \sa Project::docmethod() Project::setDocmethod()
 */

/*!
 * \brief Getter function for the \link Project::docmethod docmethod \endlink property.
 * \sa Project::setDocmethod() Project::docmethodChanged()
 */
bool Project::docmethod() const { return m_docmethod; }

/*!
 * \brief Setter function for the \link Project::docmethod docmethod \endlink property.
 * \sa Project::docmethod() Project::docmethodChanged()
 */
void Project::setDocmethod(bool nDocmethod)
{
    if (nDocmethod != m_docmethod) {
        m_docmethod = nDocmethod;
#ifdef QT_DEBUG
        qDebug() << "Changed docmethod to" << m_docmethod;
#endif
        Q_EMIT docmethodChanged(docmethod());
    }
}

/*!
 * \property Project::tmpl
 * \brief Default template for this project.
 *
 * \par Access functions:
 * \li QString tmpl() const
 * \li void setTmpl(const QString &nTmpl)
 *
 * \par Notifier signal:
 * \li void tmplChanged(const QString &tmpl)
 */

/*!
 * \fn void  Project::tmplChanged(const QString &tmpl)
 * \brief Notifier function for the \link Project::tmpl tmpl \endlink property.
 * \sa Project::tmpl() Project::setTmpl()
 */

/*!
 * \brief Getter function for the \link Project::tmpl tmpl \endlink property.
 * \sa Project::setTmpl() Project::tmplChanged()
 */
QString Project::tmpl() const { return m_tmpl; }

/*!
 * \brief Setter function for the \link Project::tmpl tmpl \endlink property.
 * \sa Project::tmpl() Project::tmplChanged()
 */
void Project::setTmpl(const QString &nTmpl)
{
    if (nTmpl != m_tmpl) {
        m_tmpl = nTmpl;
#ifdef QT_DEBUG
        qDebug() << "Changed tmpl to" << m_tmpl;
#endif
        Q_EMIT tmplChanged(tmpl());
    }
}

/*!
 * \property Project::createdAt
 * \brief Date and time the project has been created.
 *
 * \par Access functions:
 * \li QDateTime createdAt() const
 * \li void setCreatedAt(const QDateTime &nCreatedAt)
 *
 * \par Notifier signal:
 * \li void createdAtChanged(const QDateTime &createdAt)
 */

/*!
 * \fn void  Project::createdAtChanged(const QDateTime &createdAt)
 * \brief Notifier function for the \link Project::createdAt createdAt \endlink property.
 * \sa Project::createdAt() Project::setCreatedAt()
 */

/*!
 * \brief Getter function for the \link Project::createdAt createdAt \endlink property.
 * \sa Project::setCreatedAt() Project::createdAtChanged()
 */
QDateTime Project::createdAt() const { return m_createdAt; }

/*!
 * \brief Setter function for the \link Project::createdAt createdAt \endlink property.
 * \sa Project::createdAt() Project::createdAtChanged()
 */
void Project::setCreatedAt(const QDateTime &nCreatedAt)
{
    if (nCreatedAt != m_createdAt) {
        m_createdAt = nCreatedAt;
#ifdef QT_DEBUG
        qDebug() << "Changed createdAt to" << m_createdAt;
#endif
        Q_EMIT createdAtChanged(createdAt());
    }
}


/*!
 * \property Project::updatedAt
 * \brief Date and time the project has been updated.
 *
 * \par Access functions:
 * \li QDateTime updatedAt() const
 * \li void setUpdatedAt(const QDateTime &nUpdatedAt)
 *
 * \par Notifier signal:
 * \li void updatedAtChanged(const QDateTime &updatedAt)
 */

/*!
 * \fn void  Project::updatedAtChanged(const QDateTime &updatedAt)
 * \brief Notifier function for the \link Project::updatedAt updatedAt \endlink property.
 * \sa Project::updatedAt() Project::setUpdatedAt()
 */

/*!
 * \brief Getter function for the \link Project::updatedAt updatedAt \endlink property.
 * \sa Project::setUpdatedAt() Project::updatedAtChanged()
 */
QDateTime Project::updatedAt() const { return m_updatedAt; }

/*!
 * \brief Setter function for the \link Project::updatedAt updatedAt \endlink property.
 * \sa Project::updatedAt() Project::updatedAtChanged()
 */
void Project::setUpdatedAt(const QDateTime &nUpdatedAt)
{
    if (nUpdatedAt != m_updatedAt) {
        m_updatedAt = nUpdatedAt;
#ifdef QT_DEBUG
        qDebug() << "Changed updatedAt to" << m_updatedAt;
#endif
        Q_EMIT updatedAtChanged(updatedAt());
    }
}



Project *Project::fromDb(const QSqlQuery *q, QObject *parent)
{
    Project *prj = nullptr;

    Q_ASSERT_X(q, "construct Project from DB", "invalid query pointer");

    prj = new Project(q->value(0).toInt(),
                      q->value(1).toString(),
                      q->value(2).toString(),
                      q->value(3).toString(),
                      q->value(4).toBool(),
                      q->value(5).toBool(),
                      q->value(6).toBool(),
                      q->value(7).toBool(),
                      q->value(8).toBool(),
                      q->value(9).toBool(),
                      q->value(10).toBool(),
                      q->value(11).toString(),
                      QDateTime::fromTime_t(q->value(12).toUInt(), Qt::LocalTime),
                      QDateTime::fromTime_t(q->value(13).toUInt(), Qt::LocalTime),
                      parent);

    return prj;
}
