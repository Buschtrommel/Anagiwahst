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

#include "propertymodel.h"
#include "propertywriter.h"
#include "property.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QSqlDatabase>
//#include <QtDebug>
//#include <QStringList>
//#include <grantlee5/grantlee/engine.h>
//#include <grantlee5/grantlee/template.h>
//#include <grantlee5/grantlee/context.h>
//#include <QStandardPaths>

const QStringList PropertyModel::m_ints = QStringList({QStringLiteral("unsigned char"), QStringLiteral("signed char"), QStringLiteral("short"), QStringLiteral("short int"), QStringLiteral("signed short"), QStringLiteral("signed short int"), QStringLiteral("unsigned short"), QStringLiteral("unsigned short int"), QStringLiteral("int"), QStringLiteral("signed"), QStringLiteral("signed int"), QStringLiteral("unsigned int"), QStringLiteral("long"), QStringLiteral("long int"), QStringLiteral("signed long"), QStringLiteral("signed long int"), QStringLiteral("unsigned long"), QStringLiteral("unsigned long int"), QStringLiteral("long long"), QStringLiteral("long long int"), QStringLiteral("signed long long"), QStringLiteral("signed long long int"), QStringLiteral("unsigned long long"), QStringLiteral("unsigned long long int"), QStringLiteral("qint8"), QStringLiteral("qint16"), QStringLiteral("qint32"), QStringLiteral("qint64"), QStringLiteral("qintptr"), QStringLiteral("qlonglong"), QStringLiteral("quint8"), QStringLiteral("quint16"), QStringLiteral("quint32"), QStringLiteral("quint64"), QStringLiteral("quintptr"), QStringLiteral("qulonglong"), QStringLiteral("uchar"), QStringLiteral("uint"), QStringLiteral("ulong"), QStringLiteral("ushort")});

const QStringList PropertyModel::m_floats = QStringList({QStringLiteral("float"), QStringLiteral("double"), QStringLiteral("long double"), QStringLiteral("qreal")});

const QStringList PropertyModel::m_hasDefaultConstructor = QStringList({QStringLiteral("QString"), QStringLiteral("QStringList"), QStringLiteral("QUrl"), QStringLiteral("QDateTime")});

/*!
 * \brief Constructs an empty PropertyModel object.
 */
PropertyModel::PropertyModel(QObject *parent) : QAbstractListModel(parent)
{
//    m_tmpl_loader = QSharedPointer<Grantlee::FileSystemTemplateLoader>(new Grantlee::FileSystemTemplateLoader);
//    m_tmpl_loader->setTemplateDirs({QStandardPaths::writableLocation(QStandardPaths::DataLocation).append(QLatin1String("/templates")), QStringLiteral(TMPL_DIR)});

//    m_tmpl_engine = new Grantlee::Engine(this);
//    m_tmpl_engine->setSmartTrimEnabled(true);
//    m_tmpl_engine->addTemplateLoader(m_tmpl_loader);
}


/*!
 * \brief Destroys the PropertyModel object and all data items.
 */
PropertyModel::~PropertyModel()
{

}


QHash<int, QByteArray> PropertyModel::roleNames() const
{
    QHash<int, QByteArray> m_roles = QAbstractItemModel::roleNames();
    m_roles.insert(Item, QByteArrayLiteral("item"));
    return m_roles;
}


int PropertyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_properties.size();
}




QModelIndex PropertyModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}



QVariant PropertyModel::data(const QModelIndex &index, int role) const
{
    QVariant retVal;

    if (!index.isValid() || (index.row() > (m_properties.size()-1))) {
        return retVal;
    }

    if (role == Item) {
        retVal.setValue<Property*>(m_properties.at(index.row()));
    }

    return retVal;
}


int PropertyModel::unitId() const { return m_unitId; }

void PropertyModel::setUnitId(int nUnitId)
{
    if (m_unitId != nUnitId) {
        m_unitId = nUnitId;
        clear();

        if (m_unitId > -1) {
            QSqlQuery q;
            if (Q_UNLIKELY(!q.prepare(QStringLiteral("SELECT id, unit, name, type, read, write, member, reset, notify, revision, designable, scriptable, stored, user, constant, final, brief, comment, defval, pointer, argsbyref, docmethod, created_at, updated_at, ordering FROM properties WHERE unit = ?")))) {
                qCritical("Failed to pepare query for properties: %s", qUtf8Printable(q.lastError().text()));
                return;
            }

            q.addBindValue(m_unitId);

            if (Q_UNLIKELY(!q.exec())) {
                qCritical("Failed to execute query for properties: %s", qUtf8Printable(q.lastError().text()));
                return;
            }

            QList<Property*> _properties;
            while (q.next()) {
                _properties.append(Property::fromDb(&q, this));
            }

            if (!_properties.empty()) {
                beginInsertRows(QModelIndex(), 0, _properties.size()-1);

                m_properties = _properties;

                endInsertRows();
            }
        }

        Q_EMIT rowCountChanged(rowCount());
    }
}



Property *PropertyModel::createProperty(const QString &name, const QString &type, bool r, bool w, bool m, bool u, bool n, bool d, bool usePropertyName)
{
    Property *prop = nullptr;

    if (name.isEmpty() || type.isEmpty()) {
        return prop;
    }

    QString propName = name.simplified().remove(QStringLiteral(" "));
    bool pointer = false;
    QString read, write, member, reset, notify;

    if (propName.startsWith(QLatin1String("*"))) {
        pointer = true;
        propName.remove(0,1);
    }

    propName[0] = propName[0].toLower();

    if (r) {
        read = propName;

        if (!usePropertyName) {

            read[0] = read[0].toUpper();
            if (type == QLatin1String("bool")) {
                if (name.contains(QStringLiteral("enabled"), Qt::CaseInsensitive)) {
                    read.prepend(QLatin1String("is"));
                } else {
                    read.prepend(QLatin1String("has"));
                }
            } else {
                read.prepend(QLatin1String("get"));
            }
        }
    }

    if (w) {
        write = propName;
        write[0] = write[0].toUpper();
        write.prepend(QLatin1String("set"));
    }


    if (m) {
        member = propName;
        member.prepend(QLatin1String("m_"));
    }

    if (u) {
        reset = propName;
        reset[0] = reset[0].toUpper();
        reset.prepend(QLatin1String("unset"));
    }


    if (n) {
        notify = propName;
        notify.append(QLatin1String("Changed"));
    }

    QSqlQuery q;

    if (Q_UNLIKELY(!q.prepare(QStringLiteral("SELECT MAX(ordering) FROM properties WHERE unit = ?")))) {
        qCritical("Failed to prepare query for highest property order number: %s", qUtf8Printable(q.lastError().text()));
        return prop;
    }

    q.addBindValue(unitId());

    if (Q_UNLIKELY(!q.exec())) {
        qCritical("Failed to query highest property order number: %s", qUtf8Printable(q.lastError().text()));
        return prop;
    }

    int order = 0;
    if (q.next()) {
        order = q.value(0).toInt();
        order++;
    }

    if (Q_UNLIKELY(!q.prepare(QStringLiteral("INSERT INTO properties (unit, name, type, read, write, member, reset, notify, defval, argsbyref, pointer, docmethod, created_at, updated_at, ordering) "
                                             "VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)")))) {
        qCritical("Failed to prepare inserting new property into database: %s", qUtf8Printable(q.lastError().text()));
        return prop;
    }

    const QDateTime currentUtc = QDateTime::currentDateTimeUtc();
    const QDateTime currentLocal = currentUtc.toLocalTime();
    const QString defaultValue = getDefaultValue(type, pointer);
    const bool argsbyref = getArgsByRef(type, pointer);

    q.addBindValue(unitId());
    q.addBindValue(propName);
    q.addBindValue(type);
    q.addBindValue(read);
    q.addBindValue(write);
    q.addBindValue(member);
    q.addBindValue(reset);
    q.addBindValue(notify);
    q.addBindValue(defaultValue);
    q.addBindValue(argsbyref);
    q.addBindValue(pointer);
    q.addBindValue(d);
    q.addBindValue(currentUtc.toTime_t());
    q.addBindValue(currentUtc.toTime_t());
    q.addBindValue(order);

    if (Q_UNLIKELY(!q.exec())) {
        qCritical("Failed to insert new property into database: %s", qUtf8Printable(q.lastError().text()));
        return prop;
    }

    prop = new Property(q.lastInsertId().toInt(), unitId(), propName, type, read, write, member, reset, notify, getDefaultValue(type, pointer), getArgsByRef(type, pointer), pointer, d, currentLocal, currentLocal, order, this);
    prop->setExpanded(true);

    if (Q_UNLIKELY(!m_properties.empty())) {
        for (int i = 0; i < m_properties.size(); ++i) {
            m_properties.at(i)->setExpanded(false);
        }
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_properties.append(prop);

    endInsertRows();

    Q_EMIT rowCountChanged(rowCount());

    return prop;
}


bool PropertyModel::updateProperty(Property *p) const
{
    bool retVal = false;

    Q_ASSERT_X(p, "update property", "invalid property pointer");

    QSqlQuery q;

    if (Q_UNLIKELY(!q.prepare(QStringLiteral("UPDATE properties SET name = ?, type = ?, read = ?, write = ?, notify = ?, member = ?, reset = ?, revision = ?, designable = ?, scriptable = ?, "
                                             "stored = ?, user = ?, constant = ?, final = ?, pointer = ?, argsbyref = ?, docmethod = ?, defval = ?, brief = ?, comment = ?, updated_at = ? "
                                             "WHERE id = ?")))) {
        qCritical("Failed to prepare property update in database: %s", qUtf8Printable(q.lastError().text()));
        return retVal;
    }

    const QDateTime currentUtc = QDateTime::currentDateTimeUtc();
    const QDateTime currentLocal = currentUtc.toLocalTime();

    q.addBindValue(p->name());
    q.addBindValue(p->type());
    q.addBindValue(p->read());
    q.addBindValue(p->write());
    q.addBindValue(p->notify());
    q.addBindValue(p->member());
    q.addBindValue(p->reset());
    q.addBindValue(p->revision());
    q.addBindValue(p->designable());
    q.addBindValue(p->scriptable());
    q.addBindValue(p->stored());
    q.addBindValue(p->user());
    q.addBindValue(p->constant());
    q.addBindValue(p->final());
    q.addBindValue(p->pointer());
    q.addBindValue(p->argsByRef());
    q.addBindValue(p->documentMethods());
    q.addBindValue(p->defaultValue());
    q.addBindValue(p->brief());
    q.addBindValue(p->comment());
    q.addBindValue(currentUtc.toTime_t());
    q.addBindValue(p->id());

    if (Q_UNLIKELY(!q.exec())) {
        qCritical("Failed to execute property update in database: %s", qUtf8Printable(q.lastError().text()));
        return retVal;
    }

    p->setUpdatedAt(currentLocal);
    retVal = true;

    return retVal;
}


void PropertyModel::expandProperty(Property *p)
{
    Q_ASSERT_X(p, "expand property", "invalid pointer");

    if (Q_LIKELY(!m_properties.empty())) {
        for (int i = 0; i < m_properties.size(); ++i) {
            m_properties.at(i)->setExpanded(false);
        }
    }

    p->setExpanded(true);
}


bool PropertyModel::deleteProperty(Property *p)
{
    bool retVal = false;

    Q_ASSERT_X(p, "delete property", "invalid pointer");

    QSqlQuery q;
    if (Q_UNLIKELY(!q.prepare(QStringLiteral("DELETE FROM properties WHERE id = ?")))) {
        qCritical("Failed to prepare property deletion: %s", qUtf8Printable(q.lastError().text()));
        return retVal;
    }

    q.addBindValue(p->id());

    if (Q_UNLIKELY(!q.exec())) {
        qCritical("Failed to delete property: %s", qUtf8Printable(q.lastError().text()));
        return retVal;
    }

    retVal = true;

    int row = -1;
    for (int i = 0; i < m_properties.size(); ++i) {
        if (m_properties.at(i) == p) {
            row = i;
            break;
        }
    }

    beginRemoveRows(QModelIndex(), row, row);

    m_properties.removeAt(row);

    endRemoveRows();

    delete p;

    Q_EMIT rowCountChanged(rowCount());

    return retVal;
}



QList<Property*> PropertyModel::getProperties() const { return m_properties; }

//QString PropertyModel::createOutput(ResultFileType type) const
//{
//    QString out;

//    QStringList namespaces;
//    if (!m_namespaces.isEmpty()) {
//        QString ns = m_namespaces.simplified();
//        ns.remove(QStringLiteral(" "));
//        if (!ns.isEmpty()) {
//            namespaces = ns.split(QStringLiteral(","));
//        }
//    }

//    QStringList parentClasses = {QStringLiteral("QObject")};

//    m_tmpl_loader->setTheme(QStringLiteral("default_qobject"));

//    QString tmplFile;

//    switch(type) {
//    case HeaderFile:
//        tmplFile = QStringLiteral("header.tpl");
//        break;
//    case PrivateHeaderFile:
//        tmplFile = QStringLiteral("private.tpl");
//        break;
//    case CodeFile:
//        tmplFile = QStringLiteral("code.tpl");
//        break;
//    default:
//        break;
//    }

//    Grantlee::Template t = m_tmpl_engine->loadByName(tmplFile);

//    QVariantHash mapping;
//    mapping.insert(QStringLiteral("props"), QVariant::fromValue<QList<Property*>>(m_properties));
//    mapping.insert(QStringLiteral("class"), getClassName());
//    mapping.insert(QStringLiteral("parentclasses"), parentClasses);
//    mapping.insert(QStringLiteral("commentposition"), m_commentsPosition);
//    mapping.insert(QStringLiteral("namespaces"), namespaces);
//    mapping.insert(QStringLiteral("debugout"), true);

//    Grantlee::Context c(mapping);
//    out = t->render(&c);

//    if (t->error() != Grantlee::NoError) {
//        out = t->errorString();
//    }

//    return out;
//}





//bool PropertyModel::saveToDirectory(ResultFileType type, const QString &directory) const
//{
//    const QString data = createOutput(type);

//    if (data.isEmpty()) {
//        return true;
//    }

//    switch(type) {
//    case HeaderFile:
//        return PropertyWriter::write(PropertyWriter::HeaderFile, directory, getClassName(), data);
//    case PrivateHeaderFile:
//        return PropertyWriter::write(PropertyWriter::PrivateHeaderFile, directory, getClassName(), data);
//    case CodeFile:
//        return PropertyWriter::write(PropertyWriter::CodeFile, directory, getClassName(), data);
//    default:
//        return false;
//    }
//}





//bool PropertyModel::saveToFile(ResultFileType type, const QUrl &file) const
//{
//    const QString data = createOutput(type);

//    return PropertyWriter::writeFile(file.toLocalFile(), data);
//}





//bool PropertyModel::saveAll(const QUrl &directory) const
//{
//    bool retVal = false;

//    const QString path = directory.toLocalFile();

//    if (saveToDirectory(HeaderFile, path)) {
//        if(saveToDirectory(PrivateHeaderFile, path)) {
//            if (saveToDirectory(CodeFile, path)) {
//                retVal = true;
//            }
//        }
//    }

//    return retVal;
//}




//QVariant PropertyModel::getData(const QString &role, int idx) const
//{
//    return data(index(idx), roleNames().key(role.toUtf8()));
//}






///*!
// * \property PropertyModel::fileUrl
// * \brief This property holds
// *
// * \par Access functions:
// * <TABLE><TR><TD>QUrl</TD><TD>getFileUrl() const</TD></TR><TR><TD>void</TD><TD>setFileUrl(const QUrl & nFileUrl)</TD></TR></TABLE>
// * \par Notifier signal:
// * <TABLE><TR><TD>void</TD><TD>fileUrlChanged(const QUrl & nFileUrl)</TD></TR></TABLE>
// */

///*!
// * \fn PropertyModel::fileUrlChanged()
// * \brief
// *
// * Part of the \link PropertyModel::fileUrl fileUrl \endlink property.
// */

///*!
// * \brief
// *
// * Part of the \link PropertyModel::fileUrl fileUrl \endlink property.
// */
//QUrl PropertyModel::getFileUrl() const { return m_fileUrl; }

///*!
// * \brief
// *
// * Part of the \link PropertyModel::fileUrl fileUrl \endlink property.
// */
//void PropertyModel::setFileUrl(const QUrl &nFileUrl)
//{
//    if (nFileUrl != m_fileUrl) {
//        m_fileUrl = nFileUrl;
//#ifdef QT_DEBUG
//        qDebug() << "Changed fileUrl to" << getFileUrl();
//#endif
//        emit fileUrlChanged(getFileUrl());
//        emit fileNameChanged(getFileUrl().fileName());
//    }
//}






///*!
// * \property PropertyModel::fileName
// * \brief This property holds
// *
// * \par Access functions:
// * <TABLE><TR><TD>QString</TD><TD>getFileName() const</TD></TR></TABLE>
// * \par Notifier signal:
// * <TABLE><TR><TD>void</TD><TD>fileNameChanged(const QString & nFileName)</TD></TR></TABLE>
// */

///*!
// * \fn PropertyModel::fileNameChanged()
// * \brief
// *
// * Part of the \link PropertyModel::fileName fileName \endlink property.
// */

///*!
// * \brief
// *
// * Part of the \link PropertyModel::fileName fileName \endlink property.
// */
//QString PropertyModel::getFileName() const { return getFileUrl().fileName(); }






///*!
// * \property PropertyModel::className
// * \brief This property holds
// *
// * \par Access functions:
// * <TABLE><TR><TD>QString</TD><TD>getClassName() const</TD></TR><TR><TD>void</TD><TD>setClassName(const QString & nClassName)</TD></TR></TABLE>
// * \par Notifier signal:
// * <TABLE><TR><TD>void</TD><TD>classNameChanged(const QString & nClassName)</TD></TR></TABLE>
// */

///*!
// * \fn PropertyModel::classNameChanged()
// * \brief
// *
// * Part of the \link PropertyModel::className className \endlink property.
// */

///*!
// * \brief
// *
// * Part of the \link PropertyModel::className className \endlink property.
// */
//QString PropertyModel::getClassName() const { return m_className; }

///*!
// * \brief
// *
// * Part of the \link PropertyModel::className className \endlink property.
// */
//void PropertyModel::setClassName(const QString &nClassName)
//{
//    if (nClassName != m_className) {
//        m_className = nClassName;
//#ifdef QT_DEBUG
//        qDebug() << "Changed className to" << getClassName();
//#endif
//        emit classNameChanged(getClassName());
//    }
//}






///*!
// * \property PropertyModel::privateClass
// * \brief This property holds
// *
// * \par Access functions:
// * <TABLE><TR><TD>bool</TD><TD>isPrivateClass() const</TD></TR><TR><TD>void</TD><TD>setPrivateClass(bool nPrivateClass)</TD></TR></TABLE>
// * \par Notifier signal:
// * <TABLE><TR><TD>void</TD><TD>privateClassChanged(bool nPrivateClass)</TD></TR></TABLE>
// */

///*!
// * \fn PropertyModel::privateClassChanged()
// * \brief
// *
// * Part of the \link PropertyModel::privateClass privateClass \endlink property.
// */

///*!
// * \brief
// *
// * Part of the \link PropertyModel::privateClass privateClass \endlink property.
// */
//bool PropertyModel::isPrivateClass() const { return m_privateClass; }

///*!
// * \brief
// *
// * Part of the \link PropertyModel::privateClass privateClass \endlink property.
// */
//void PropertyModel::setPrivateClass(bool nPrivateClass)
//{
//    if (nPrivateClass != m_privateClass) {
//        m_privateClass = nPrivateClass;
//#ifdef QT_DEBUG
//        qDebug() << "Changed privateClass to" << isPrivateClass();
//#endif
//        emit privateClassChanged(isPrivateClass());
//    }
//}




///*!
// * \property PropertyModel::commentsPosition
// * \brief Defines where the comments will be inserted.
// *
// * \par Access functions:
// * <TABLE><TR><TD>CommentsPosition</TD><TD>getCommentsPosition() const</TD></TR><TR><TD>void</TD><TD>setCommentsPosition(CommentsPosition commentsPosition)</TD></TR></TABLE>
// * \par Notifier signal:
// * <TABLE><TR><TD>void</TD><TD>commentsPositionChanged(CommentsPosition commentsPosition)</TD></TR></TABLE>
// */

///*!
// * \fn PropertyModel::commentsPositionChanged()
// * \brief Part of the \link PropertyModel::commentsPosition commentsPosition \endlink property.
// */

///*!
// * \brief Part of the \link PropertyModel::commentsPosition commentsPosition \endlink property.
// */
//PropertyModel::CommentsPosition PropertyModel::getCommentsPosition() const { return m_commentsPosition; }

///*!
// * \brief Part of the \link PropertyModel::commentsPosition commentsPosition \endlink property.
// */
//void PropertyModel::setCommentsPosition(CommentsPosition commentsPosition)
//{
//    if (commentsPosition != m_commentsPosition) {
//        m_commentsPosition = commentsPosition;
//#ifdef QT_DEBUG
//        qDebug() << "Changed commentsPosition to" << m_commentsPosition;
//#endif
//        emit commentsPositionChanged(getCommentsPosition());
//    }
//}



///*!
// * \property PropertyModel::usePropertyName
// * \brief Set to true to use the name of the property for the read function.
// *
// * \par Access functions:
// * <TABLE><TR><TD>bool</TD><TD>hasUsePropertyName() const</TD></TR><TR><TD>void</TD><TD>setUsePropertyName(bool usePropertyName)</TD></TR></TABLE>
// * \par Notifier signal:
// * <TABLE><TR><TD>void</TD><TD>usePropertyNameChanged(bool usePropertyName)</TD></TR></TABLE>
// */

///*!
// * \fn void PropertyModel::usePropertyNameChanged(const bool &usePropertyName)
// * \brief Part of the \link PropertyModel::usePropertyName usePropertyName \endlink property.
// */

///*!
// * \brief Part of the \link PropertyModel::usePropertyName usePropertyName \endlink property.
// */
//bool PropertyModel::hasUsePropertyName() const { return m_usePropertyName; }

///*!
// * \brief Part of the \link PropertyModel::usePropertyName usePropertyName \endlink property.
// */
//void PropertyModel::setUsePropertyName(bool usePropertyName)
//{
//    if (usePropertyName != m_usePropertyName) {
//        m_usePropertyName = usePropertyName;
//#ifdef QT_DEBUG
//        qDebug() << "Changed usePropertyName to" << m_usePropertyName;
//#endif
//        emit usePropertyNameChanged(hasUsePropertyName());
//    }
//}





QString PropertyModel::getDefaultValue(const QString &type, bool pointer)
{
    QString retVal;

    if (pointer) {
        retVal = QStringLiteral("nullptr");
    } else {
        if (m_ints.contains(type, Qt::CaseInsensitive)) {
            retVal = QStringLiteral("0");
        } else if (m_floats.contains(type, Qt::CaseInsensitive)) {
            retVal = QStringLiteral("0.0");
        } else if (type == QLatin1String("bool")) {
            retVal = QStringLiteral("false");
        } else if (m_hasDefaultConstructor.contains(type, Qt::CaseInsensitive)) {
            retVal = QString();
        } else {
            retVal = type;
            retVal.append(QStringLiteral("()"));
        }
    }

    return retVal;
}


bool PropertyModel::getArgsByRef(const QString &type, bool pointer)
{
    bool retVal = false;

    if (!pointer) {
        if (type == QLatin1String("bool")) {
            retVal = false;
        } else if (m_floats.contains(type, Qt::CaseInsensitive)) {
            retVal = false;
        } else if (m_ints.contains(type, Qt::CaseInsensitive)) {
            retVal = false;
        } else {
            retVal = true;
        }
    }

    return retVal;
}




//Property *PropertyModel::getItemById(int id) const
//{
//    Property *prop = nullptr;

//    if ((id < 0) || (rowCount() <= 0)) {
//        return prop;
//    }

//    for (int i = 0; i < m_properties.count(); ++i) {
//        prop = m_properties.at(i);
//        if (prop->id() == id) {
//            break;
//        }
//    }

//    return prop;
//}


//Property *PropertyModel::getItemByIndex(int idx) const
//{
//    Property *prop = nullptr;

//    if ((idx < 0) || (idx >= rowCount())) {
//        return prop;
//    }

//    prop = m_properties.at(idx);

//    return prop;
//}




///*!
// * \property PropertyModel::namespaces
// * \brief Comma separated list of namespaces.
// *
// * \par Access functions:
// * <TABLE><TR><TD>QString</TD><TD>getNamespaces() const</TD></TR><TR><TD>void</TD><TD>setNamespaces(const QString &namespaces)</TD></TR></TABLE>
// * \par Notifier signal:
// * <TABLE><TR><TD>void</TD><TD>namespacesChanged(const QString &namespaces)</TD></TR></TABLE>
// */

///*!
// * \fn void PropertyModel::namespacesChanged(const QString &namespaces)
// * \brief Part of the \link PropertyModel::namespaces namespaces \endlink property.
// */

///*!
// * \brief Part of the \link PropertyModel::namespaces namespaces \endlink property.
// */
//QString PropertyModel::getNamespaces() const { return m_namespaces; }

///*!
// * \brief Part of the \link PropertyModel::namespaces namespaces \endlink property.
// */
//void PropertyModel::setNamespaces(const QString &namespaces)
//{
//    if (namespaces != m_namespaces) {
//        m_namespaces = namespaces;
//#ifdef QT_DEBUG
//        qDebug() << "Changed namespaces to" << m_namespaces;
//#endif
//        emit namespacesChanged(getNamespaces());
//    }
//}




void PropertyModel::clear()
{
    if (Q_LIKELY(!m_properties.empty())) {
        beginRemoveRows(QModelIndex(), 0, m_properties.size()-1);

        qDeleteAll(m_properties);
        m_properties.clear();

        endRemoveRows();
    }
}
