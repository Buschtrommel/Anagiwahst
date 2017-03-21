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

#include "unit.h"
#include <QSqlQuery>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

/*!
 * \class Unit
 * \brief Contains infromation about a single translation unit (class, etc).
 */


/*!
 * \brief Constructs a new Unit object with default values and the given \a parent.
 */
Unit::Unit(QObject *parent) : QObject(parent)
{
}


/*!
 * \brief Constructs a new Unit object with the given parameters and \a parent.
 */
Unit::Unit(int id, int projectId, const QString &name, const QString &license, const QString &namespaces, bool read, bool write, bool member, bool reset, bool notify, bool propread, bool docmethod, const QString &tmpl, const QDateTime &createdAt, const QDateTime &updatedAt, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_projectId(projectId),
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
 * \brief Deconstructs the Unit object.
 */
Unit::~Unit()
{
}


/*!
 * \property Unit::id
 * \brief Database ID.
 *
 * \par Access functions:
 * \li int id() const
 * \li void setId(int nId)
 *
 * \par Notifier signal:
 * \li void idChanged(int id)
 */

/*!
 * \fn void  Unit::idChanged(int id)
 * \brief Notifier function for the \link Unit::id id \endlink property.
 * \sa Unit::id() Unit::setId() 
 */

/*!
 * \brief Getter function for the \link Unit::id id \endlink property.
 * \sa Unit::setId() Unit::idChanged()
 */
int Unit::id() const { return m_id; }

/*!
 * \brief Setter function for the \link Unit::id id \endlink property.
 * \sa Unit::id() Unit::idChanged()
 */
void Unit::setId(int nId)
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
 * \property Unit::projectId
 * \brief Project database ID.
 *
 * \par Access functions:
 * \li int projectId() const
 * \li void setProjectId(int nProjectId)
 *
 * \par Notifier signal:
 * \li void projectIdChanged(int projectId)
 */

/*!
 * \fn void  Unit::projectIdChanged(int projectId)
 * \brief Notifier function for the \link Unit::projectId projectId \endlink property.
 * \sa Unit::projectId() Unit::setProjectId() 
 */

/*!
 * \brief Getter function for the \link Unit::projectId projectId \endlink property.
 * \sa Unit::setProjectId() Unit::projectIdChanged()
 */
int Unit::projectId() const { return m_projectId; }

/*!
 * \brief Setter function for the \link Unit::projectId projectId \endlink property.
 * \sa Unit::projectId() Unit::projectIdChanged()
 */
void Unit::setProjectId(int nProjectId)
{
    if (nProjectId != m_projectId) {
        m_projectId = nProjectId;
#ifdef QT_DEBUG
        qDebug() << "Changed projectId to" << m_projectId;
#endif
        Q_EMIT projectIdChanged(projectId());
    }
}


/*!
 * \property Unit::name
 * \brief Name of the unit/class.
 *
 * \par Access functions:
 * \li QString name() const
 * \li void setName(const QString &nName)
 *
 * \par Notifier signal:
 * \li void nameChanged(const QString &name)
 */

/*!
 * \fn void  Unit::nameChanged(const QString &name)
 * \brief Notifier function for the \link Unit::name name \endlink property.
 * \sa Unit::name() Unit::setName() 
 */

/*!
 * \brief Getter function for the \link Unit::name name \endlink property.
 * \sa Unit::setName() Unit::nameChanged()
 */
QString Unit::name() const { return m_name; }

/*!
 * \brief Setter function for the \link Unit::name name \endlink property.
 * \sa Unit::name() Unit::nameChanged()
 */
void Unit::setName(const QString &nName)
{
    if (nName != m_name) {
        m_name = nName;
#ifdef QT_DEBUG
        qDebug() << "Changed name to" << m_name;
#endif
        Q_EMIT nameChanged(name());
        Q_EMIT displayNameChanged(displayName());
    }
}


/*!
 * \property Unit::license
 * \brief License header text.
 *
 * \par Access functions:
 * \li QString license() const
 * \li void setLicense(const QString &nLicense)
 *
 * \par Notifier signal:
 * \li void licenseChanged(const QString &license)
 */

/*!
 * \fn void  Unit::licenseChanged(const QString &license)
 * \brief Notifier function for the \link Unit::license license \endlink property.
 * \sa Unit::license() Unit::setLicense() 
 */

/*!
 * \brief Getter function for the \link Unit::license license \endlink property.
 * \sa Unit::setLicense() Unit::licenseChanged()
 */
QString Unit::license() const { return m_license; }

/*!
 * \brief Setter function for the \link Unit::license license \endlink property.
 * \sa Unit::license() Unit::licenseChanged()
 */
void Unit::setLicense(const QString &nLicense)
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
 * \property Unit::namespaces
 * \brief Comma separated list of namespaces.
 *
 * \par Access functions:
 * \li QString namespaces() const
 * \li void setNamespaces(const QString &nNamespaces)
 *
 * \par Notifier signal:
 * \li void namespacesChanged(const QString &namespaces)
 */

/*!
 * \fn void  Unit::namespacesChanged(const QString &namespaces)
 * \brief Notifier function for the \link Unit::namespaces namespaces \endlink property.
 * \sa Unit::namespaces() Unit::setNamespaces() 
 */

/*!
 * \brief Getter function for the \link Unit::namespaces namespaces \endlink property.
 * \sa Unit::setNamespaces() Unit::namespacesChanged()
 */
QString Unit::namespaces() const { return m_namespaces; }

/*!
 * \brief Setter function for the \link Unit::namespaces namespaces \endlink property.
 * \sa Unit::namespaces() Unit::namespacesChanged()
 */
void Unit::setNamespaces(const QString &nNamespaces)
{
    if (nNamespaces != m_namespaces) {
        m_namespaces = nNamespaces;
#ifdef QT_DEBUG
        qDebug() << "Changed namespaces to" << m_namespaces;
#endif
        Q_EMIT namespacesChanged(namespaces());
        Q_EMIT displayNameChanged(displayName());
    }
}


/*!
 * \property Unit::read
 * \brief Unit default for creating read methods.
 *
 * \par Access functions:
 * \li bool read() const
 * \li void setRead(bool nRead)
 *
 * \par Notifier signal:
 * \li void readChanged(bool read)
 */

/*!
 * \fn void  Unit::readChanged(bool read)
 * \brief Notifier function for the \link Unit::read read \endlink property.
 * \sa Unit::read() Unit::setRead() 
 */

/*!
 * \brief Getter function for the \link Unit::read read \endlink property.
 * \sa Unit::setRead() Unit::readChanged()
 */
bool Unit::read() const { return m_read; }

/*!
 * \brief Setter function for the \link Unit::read read \endlink property.
 * \sa Unit::read() Unit::readChanged()
 */
void Unit::setRead(bool nRead)
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
 * \property Unit::write
 * \brief Unit default for creating write methods.
 *
 * \par Access functions:
 * \li bool write() const
 * \li void setWrite(bool nWrite)
 *
 * \par Notifier signal:
 * \li void writeChanged(bool write)
 */

/*!
 * \fn void  Unit::writeChanged(bool write)
 * \brief Notifier function for the \link Unit::write write \endlink property.
 * \sa Unit::write() Unit::setWrite() 
 */

/*!
 * \brief Getter function for the \link Unit::write write \endlink property.
 * \sa Unit::setWrite() Unit::writeChanged()
 */
bool Unit::write() const { return m_write; }

/*!
 * \brief Setter function for the \link Unit::write write \endlink property.
 * \sa Unit::write() Unit::writeChanged()
 */
void Unit::setWrite(bool nWrite)
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
 * \property Unit::member
 * \brief Unit default for creating property member.
 *
 * \par Access functions:
 * \li bool member() const
 * \li void setMember(bool nMember)
 *
 * \par Notifier signal:
 * \li void memberChanged(bool member)
 */

/*!
 * \fn void  Unit::memberChanged(bool member)
 * \brief Notifier function for the \link Unit::member member \endlink property.
 * \sa Unit::member() Unit::setMember() 
 */

/*!
 * \brief Getter function for the \link Unit::member member \endlink property.
 * \sa Unit::setMember() Unit::memberChanged()
 */
bool Unit::member() const { return m_member; }

/*!
 * \brief Setter function for the \link Unit::member member \endlink property.
 * \sa Unit::member() Unit::memberChanged()
 */
void Unit::setMember(bool nMember)
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
 * \property Unit::reset
 * \brief Unit default for creating reset functions.
 *
 * \par Access functions:
 * \li bool reset() const
 * \li void setReset(bool nReset)
 *
 * \par Notifier signal:
 * \li void resetChanged(bool reset)
 */

/*!
 * \fn void  Unit::resetChanged(bool reset)
 * \brief Notifier function for the \link Unit::reset reset \endlink property.
 * \sa Unit::reset() Unit::setReset() 
 */

/*!
 * \brief Getter function for the \link Unit::reset reset \endlink property.
 * \sa Unit::setReset() Unit::resetChanged()
 */
bool Unit::reset() const { return m_reset; }

/*!
 * \brief Setter function for the \link Unit::reset reset \endlink property.
 * \sa Unit::reset() Unit::resetChanged()
 */
void Unit::setReset(bool nReset)
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
 * \property Unit::notify
 * \brief Unit default for creating notify functions.
 *
 * \par Access functions:
 * \li bool notify() const
 * \li void setNotify(bool nNotify)
 *
 * \par Notifier signal:
 * \li void notifyChanged(bool notify)
 */

/*!
 * \fn void  Unit::notifyChanged(bool notify)
 * \brief Notifier function for the \link Unit::notify notify \endlink property.
 * \sa Unit::notify() Unit::setNotify() 
 */

/*!
 * \brief Getter function for the \link Unit::notify notify \endlink property.
 * \sa Unit::setNotify() Unit::notifyChanged()
 */
bool Unit::notify() const { return m_notify; }

/*!
 * \brief Setter function for the \link Unit::notify notify \endlink property.
 * \sa Unit::notify() Unit::notifyChanged()
 */
void Unit::setNotify(bool nNotify)
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
 * \property Unit::propread
 * \brief Unit default for using property name for read method.
 *
 * \par Access functions:
 * \li bool propread() const
 * \li void setPropread(bool nPropread)
 *
 * \par Notifier signal:
 * \li void propreadChanged(bool propread)
 */

/*!
 * \fn void  Unit::propreadChanged(bool propread)
 * \brief Notifier function for the \link Unit::propread propread \endlink property.
 * \sa Unit::propread() Unit::setPropread() 
 */

/*!
 * \brief Getter function for the \link Unit::propread propread \endlink property.
 * \sa Unit::setPropread() Unit::propreadChanged()
 */
bool Unit::propread() const { return m_propread; }

/*!
 * \brief Setter function for the \link Unit::propread propread \endlink property.
 * \sa Unit::propread() Unit::propreadChanged()
 */
void Unit::setPropread(bool nPropread)
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
 * \property Unit::docmethod
 * \brief Unit default for documenting methods.
 *
 * \par Access functions:
 * \li bool docmethod() const
 * \li void setDocmethod(bool nDocmethod)
 *
 * \par Notifier signal:
 * \li void docmethodChanged(bool docmethod)
 */

/*!
 * \fn void  Unit::docmethodChanged(bool docmethod)
 * \brief Notifier function for the \link Unit::docmethod docmethod \endlink property.
 * \sa Unit::docmethod() Unit::setDocmethod() 
 */

/*!
 * \brief Getter function for the \link Unit::docmethod docmethod \endlink property.
 * \sa Unit::setDocmethod() Unit::docmethodChanged()
 */
bool Unit::docmethod() const { return m_docmethod; }

/*!
 * \brief Setter function for the \link Unit::docmethod docmethod \endlink property.
 * \sa Unit::docmethod() Unit::docmethodChanged()
 */
void Unit::setDocmethod(bool nDocmethod)
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
 * \property Unit::tmpl
 * \brief Unit default template.
 *
 * \par Access functions:
 * \li QString tmpl() const
 * \li void setTmpl(const QString &nTmpl)
 *
 * \par Notifier signal:
 * \li void tmplChanged(const QString &tmpl)
 */

/*!
 * \fn void  Unit::tmplChanged(const QString &tmpl)
 * \brief Notifier function for the \link Unit::tmpl tmpl \endlink property.
 * \sa Unit::tmpl() Unit::setTmpl() 
 */

/*!
 * \brief Getter function for the \link Unit::tmpl tmpl \endlink property.
 * \sa Unit::setTmpl() Unit::tmplChanged()
 */
QString Unit::tmpl() const { return m_tmpl; }

/*!
 * \brief Setter function for the \link Unit::tmpl tmpl \endlink property.
 * \sa Unit::tmpl() Unit::tmplChanged()
 */
void Unit::setTmpl(const QString &nTmpl)
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
 * \property Unit::createdAt
 * \brief Date and time this unis has been created.
 *
 * \par Access functions:
 * \li QDateTime createdAt() const
 * \li void setCreatedAt(const QDateTime &nCreatedAt)
 *
 * \par Notifier signal:
 * \li void createdAtChanged(const QDateTime &createdAt)
 */

/*!
 * \fn void  Unit::createdAtChanged(const QDateTime &createdAt)
 * \brief Notifier function for the \link Unit::createdAt createdAt \endlink property.
 * \sa Unit::createdAt() Unit::setCreatedAt() 
 */

/*!
 * \brief Getter function for the \link Unit::createdAt createdAt \endlink property.
 * \sa Unit::setCreatedAt() Unit::createdAtChanged()
 */
QDateTime Unit::createdAt() const { return m_createdAt; }

/*!
 * \brief Setter function for the \link Unit::createdAt createdAt \endlink property.
 * \sa Unit::createdAt() Unit::createdAtChanged()
 */
void Unit::setCreatedAt(const QDateTime &nCreatedAt)
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
 * \property Unit::updatedAt
 * \brief Date and time this unit has been updated.
 *
 * \par Access functions:
 * \li QDateTime updatedAt() const
 * \li void setUpdatedAt(const QDateTime &nUpdatedAt)
 *
 * \par Notifier signal:
 * \li void updatedAtChanged(const QDateTime &updatedAt)
 */

/*!
 * \fn void  Unit::updatedAtChanged(const QDateTime &updatedAt)
 * \brief Notifier function for the \link Unit::updatedAt updatedAt \endlink property.
 * \sa Unit::updatedAt() Unit::setUpdatedAt() 
 */

/*!
 * \brief Getter function for the \link Unit::updatedAt updatedAt \endlink property.
 * \sa Unit::setUpdatedAt() Unit::updatedAtChanged()
 */
QDateTime Unit::updatedAt() const { return m_updatedAt; }

/*!
 * \brief Setter function for the \link Unit::updatedAt updatedAt \endlink property.
 * \sa Unit::updatedAt() Unit::updatedAtChanged()
 */
void Unit::setUpdatedAt(const QDateTime &nUpdatedAt)
{
    if (nUpdatedAt != m_updatedAt) {
        m_updatedAt = nUpdatedAt;
#ifdef QT_DEBUG
        qDebug() << "Changed updatedAt to" << m_updatedAt;
#endif
        Q_EMIT updatedAtChanged(updatedAt());
    }
}


/*!
 * \property Unit::displayName
 * \brief Display name of this unit.
 *
 * The display name consists of namespaces and the unit name.
 *
 * \par Access functions:
 * \li QString displayName() const
 *
 * \par Notifier signal:
 * \li void displayNameChanged(const QString &displayName)
 */

/*!
 * \fn void  Unit::displayNameChanged(const QString &displayName)
 * \brief Notifier function for the \link Unit::displayName displayName \endlink property.
 * \sa Unit::displayName()
 */

/*!
 * \brief Getter function for the \link Unit::displayName displayName \endlink property.
 * \sa Unit::displayNameChanged()
 */
QString Unit::displayName() const
{
    QString dn;

    if (m_namespaces.isEmpty()) {
        dn = m_name;
    } else {
        dn = m_namespaces;
        dn.replace(QChar(','), QLatin1String("::"));
        dn.append(QLatin1String("::")).append(m_name);
    }

    return dn;
}


Unit *Unit::fromDb(const QSqlQuery *q, QObject *parent)
{
    Unit *u = nullptr;

    Q_ASSERT_X(q, "construct Unit from DB", "invalid query pointer");

    u = new Unit(q->value(0).toInt(),
                 q->value(1).toInt(),
                 q->value(2).toString(),
                 q->value(3).toString(),
                 q->value(4).toString(),
                 q->value(5).toBool(),
                 q->value(6).toBool(),
                 q->value(7).toBool(),
                 q->value(8).toBool(),
                 q->value(9).toBool(),
                 q->value(10).toBool(),
                 q->value(11).toBool(),
                 q->value(12).toString(),
                 QDateTime::fromTime_t(q->value(13).toUInt(), Qt::LocalTime),
                 QDateTime::fromTime_t(q->value(14).toUInt(), Qt::LocalTime),
                 parent);

    return u;
}


