/* Anagiwahst - A Qt Property Editor/Creator
 *
 * Copyright (c) 2015 Buschtrommel/Matthias Fehring <kontakt@buschmann23.de>
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
#include "propertycreator.h"
#include "propertywriter.h"
#include "property.h"
#include <QtDebug>
#include <QStringList>

/*!
 * \brief Constructs an empty PropertyModel object.
 */
PropertyModel::PropertyModel(QObject *parent) : QAbstractListModel(parent)
{
    m_privateClass = false;
    m_type = PrivateClass;
    m_commentsPosition = InCode;
    m_usePropertyName = false;
    m_lastAddedId = -1;

    m_ints = QStringList({QStringLiteral("unsigned char"), QStringLiteral("signed char"), QStringLiteral("short"), QStringLiteral("short int"), QStringLiteral("signed short"), QStringLiteral("signed short int"), QStringLiteral("unsigned short"), QStringLiteral("unsigned short int"), QStringLiteral("int"), QStringLiteral("signed"), QStringLiteral("signed int"), QStringLiteral("unsigned int"), QStringLiteral("long"), QStringLiteral("long int"), QStringLiteral("signed long"), QStringLiteral("signed long int"), QStringLiteral("unsigned long"), QStringLiteral("unsigned long int"), QStringLiteral("long long"), QStringLiteral("long long int"), QStringLiteral("signed long long"), QStringLiteral("signed long long int"), QStringLiteral("unsigned long long"), QStringLiteral("unsigned long long int"), QStringLiteral("qint8"), QStringLiteral("qint16"), QStringLiteral("qint32"), QStringLiteral("qint64"), QStringLiteral("qintptr"), QStringLiteral("qlonglong"), QStringLiteral("quint8"), QStringLiteral("quint16"), QStringLiteral("quint32"), QStringLiteral("quint64"), QStringLiteral("quintptr"), QStringLiteral("qulonglong"), QStringLiteral("uchar"), QStringLiteral("uint"), QStringLiteral("ulong"), QStringLiteral("ushort")});

    m_floats = QStringList({QStringLiteral("float"), QStringLiteral("double"), QStringLiteral("long double"), QStringLiteral("qreal")});

	m_hasDefaultConstructor = QStringList({QStringLiteral("QString"), QStringLiteral("QStringList"), QStringLiteral("QUrl"), QStringLiteral("QDateTime")});

#ifdef QT_DEBUG
    qDebug() << "Constructed PropertyModel" << this;
#endif
}


/*!
 * \brief Destroys the PropertyModel object and all data items.
 */
PropertyModel::~PropertyModel()
{

#ifdef QT_DEBUG
    qDebug() << "Deconstucted PropertyModel" << this;
#endif
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
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (m_properties.size()-1)) {
        return QVariant();
    }

    Property *prop = m_properties.at(index.row());

    if (role == Item) {
        return QVariant::fromValue<Property*>(prop);
    } else {
        return QVariant();
    }
}





void PropertyModel::loadData()
{
//    QFile file(getFileUrl().toLocalFile());

//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        qCritical() << "Failed to open file:" << getFileUrl();
//        return;
//    }

//    setClassName(QStringLiteral(""));
//    QTextStream in(&file);

//    int id = 0;

//    while (!in.atEnd()) {

//        QString line = in.readLine();
//        QString trimmed = line.trimmed();

//        if (trimmed.startsWith(QLatin1String("class"), Qt::CaseInsensitive) && !trimmed.endsWith(QLatin1String(";"))) {

//            QStringList classPartList = trimmed.split(' ');

//            if (!classPartList.isEmpty()) {

//                for (int i = 0; i < classPartList.size(); ++i) {

//                    if (classPartList.at(i) == QLatin1String(":")) {
//                        setClassName(classPartList.at(i-1));
//                    }

//                }
//            }

//            if (getClassName().isEmpty()) {
//                setClassName(classPartList.last());
//            }
//        }


//        if (trimmed.startsWith(QLatin1String("Q_DECLARE_PRIVATE"))) {
//            QString privDecl = trimmed;
//            privDecl.remove(0,18);
//            privDecl.chop(1);

//            setPrivateClass(privDecl == getClassName());
//        }


//        if (trimmed.startsWith(QLatin1String("Q_PROPERTY"), Qt::CaseInsensitive)) {

//            id++;

//            trimmed.remove(0,11);
//            trimmed.chop(1);

//            QString lastPart = QLatin1String("");

//            QStringList propertyParts = trimmed.split(' ');
//            quint8 propertyPartsCount = propertyParts.size();
//            QString type = propertyParts.at(0);
//            QString name = propertyParts.at(1);
//            QString read = QLatin1String("");
//            QString write = QLatin1String("");
//            QString member = QLatin1String("");
//            QString reset = QLatin1String("");
//            QString notify = QLatin1String("");
//            quint8 revision = 0;
//            QString designable = QStringLiteral("true");
//            QString scriptable = QStringLiteral("true");
//            bool stored = true;
//            bool user = false;
//            bool constant = false;
//            bool final = false;
//            QString brief = QStringLiteral("This property holds");
//            QString comment = QLatin1String("");
//            bool pointer = false;


//            for (quint8 i = 2; i < propertyPartsCount; i++) {

//                QString part = propertyParts.at(i);

//                if (lastPart == QLatin1String("READ")) {
//                    read = part;
//                } else if (lastPart == QLatin1String("WRITE")) {
//                    write = part;
//                } else if (lastPart == QLatin1String("MEMBER")) {
//                    member = part;
//                } else if (lastPart == QLatin1String("RESET")) {
//                    reset = part;
//                } else if (lastPart == QLatin1String("NOTIFY")) {
//                    notify = part;
//                } else if (lastPart == QLatin1String("REVISION")) {
//                    revision = part.toInt();
//                } else if (lastPart == QLatin1String("DESIGNABLE")) {
//                    designable = part;
//                } else if (lastPart == QLatin1String("SCRIPTABLE")) {
//                    scriptable = part;
//                } else if (lastPart == QLatin1String("STORED")) {
//                    stored = part == QLatin1String("true");
//                } else if (lastPart == QLatin1String("USER")) {
//                    user = part == QLatin1String("true");
//                }

//                if (part == QLatin1String("CONSTANT")) {
//                    constant = true;
//                }

//                if (part == QLatin1String("FINAL")) {
//                    final = true;
//                }

//                lastPart = part;
//            }

//            beginInsertRows(QModelIndex(), rowCount(), rowCount());


//            Property *prop = new Property;
//            prop->id = id;
//            prop->name = name;
//            prop->type = type;
//            prop->read = read;
//            prop->write = write;
//            prop->member = member;
//            prop->reset = reset;
//            prop->notify = notify;
//            prop->revision = revision;
//            prop->designable = designable;
//            prop->scriptable = scriptable;
//            prop->stored = stored;
//            prop->user = user;
//            prop->constant = constant;
//            prop->final = final;
//            prop->brief = brief;
//            prop->comment = comment;
//            prop->privateClass = isPrivateClass();
//            prop->defaultValue = QStringLiteral("");
//            prop->pointer = pointer;

//            m_properties.append(prop);

//            endInsertRows();
//        }

//    }

//    file.close();
}






Property *PropertyModel::addProperty(const QString &name, const QString &type, bool r, bool w, bool m, bool u, bool n, bool p)
{
    if (name.isEmpty() || type.isEmpty()) {
        return nullptr;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

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

        if (!m_usePropertyName) {

            read[0] = read[0].toUpper();
            if (type == QLatin1String("bool")) {
                if (name.contains(QStringLiteral("enabled"), Qt::CaseInsensitive)) {
                    read.prepend(QStringLiteral("is"));
                } else {
                    read.prepend(QStringLiteral("has"));
                }
            } else {
                read.prepend(QStringLiteral("get"));
            }
        }
    }

    if (w) {
        write = propName;
        write[0] = write[0].toUpper();
        write.prepend("set");
    }


    if (m) {
        member = propName;
        member.prepend(QStringLiteral("m_"));
    }

    if (u) {
        reset = propName;
        reset[0] = reset[0].toUpper();
        reset.prepend(QStringLiteral("unset"));
    }


    if (n) {
        notify = propName;
        notify.append("Changed");
    }

    Property *prop = new Property(m_lastAddedId + 1, propName, type, read, write, member, reset, notify, p, getDefaultValue(type, pointer), getArgsByRef(type, pointer), pointer, this);

    m_properties.append(prop);

    endInsertRows();

    m_lastAddedId = prop->id();

    return prop;
}





void PropertyModel::deleteProperty(int idx)
{
    if (idx < 0) {
        return;
    }

    if (idx > (rowCount()-1)) {
        return;
    }

    beginRemoveRows(QModelIndex(), idx, idx);

    delete m_properties.takeAt(idx);

    endRemoveRows();
}



QString PropertyModel::createOutput(ResultFileType type) const
{
    QStringList namespaces;
    if (!m_namespaces.isEmpty()) {
        QString ns = m_namespaces.simplified();
        ns.remove(QStringLiteral(" "));
        if (!ns.isEmpty()) {
            namespaces = ns.split(QStringLiteral(","));
        }
    }
    PropertyCreator creator(m_properties, getClassName(), m_type, 4, m_commentsPosition, namespaces);
    switch(type) {
    case HeaderFile:
        return creator.createHeader();
    case PrivateHeaderFile:
        return creator.createPrivate();
    case CodeFile:
        return creator.createCode();
    default:
        return QString();
    }
}





bool PropertyModel::saveToDirectory(ResultFileType type, const QString &directory) const
{
    QString data = createOutput(type);

    if (data.isEmpty()) {
        return true;
    }

    switch(type) {
    case HeaderFile:
        return PropertyWriter::write(PropertyWriter::HeaderFile, directory, getClassName(), data);
    case PrivateHeaderFile:
        return PropertyWriter::write(PropertyWriter::PrivateHeaderFile, directory, getClassName(), data);
    case CodeFile:
        return PropertyWriter::write(PropertyWriter::CodeFile, directory, getClassName(), data);
    default:
        return false;
    }
}





bool PropertyModel::saveToFile(ResultFileType type, const QUrl &file) const
{
    QString data = createOutput(type);

    return PropertyWriter::writeFile(file.toLocalFile(), data);
}





bool PropertyModel::saveAll(const QUrl &directory) const
{
    QString path = directory.toLocalFile();

    if (saveToDirectory(HeaderFile, path)) {
        if(saveToDirectory(PrivateHeaderFile, path)) {
            if (saveToDirectory(CodeFile, path)) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}




QVariant PropertyModel::getData(const QString &role, int idx) const
{
    return data(index(idx), roleNames().key(role.toUtf8()));
}




//bool PropertyModel::updateData(const QString &role, int idx, const QVariant &value)
//{
//    if (data(index(idx), roleNames().key(role.toUtf8())) == value) {
//        return false;
//    }

//    if (idx < 0) {
//        qCritical() << "Index" << idx << "is out of range.";
//        return false;
//    }

//    if (idx > rowCount()-1) {
//        qCritical() << "Index" << idx << "is out of range.";
//        return false;
//    }

//#ifdef QT_DEBUG
//    qDebug() << "Updating role" << role << "at position" << idx << "to" << value;
//#endif

//    Property *prop = m_properties.at(idx);

//    switch(roleNames().key(role.toUtf8())) {
//    case NameRole:
//        prop->name = value.toString();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, NameRole));
//        return true;
//    case TypeRole:
//        prop->type = value.toString();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, TypeRole));
//        return true;
//    case ReadRole:
//        prop->read = value.toString();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, ReadRole));
//        return true;
//    case WriteRole:
//        prop->write = value.toString();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, WriteRole));
//        return true;
//    case ResetRole:
//        prop->reset = value.toString();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, ResetRole));
//        return true;
//    case NotifyRole:
//        prop->notify = value.toString();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, NotifyRole));
//        return true;
//    case RevisionRole:
//        prop->revision = quint8(value.toInt());
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, RevisionRole));
//        return true;
//    case DesignableRole:
//        prop->designable = value.toString();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, DesignableRole));
//        return true;
//    case ScriptableRole:
//        prop->scriptable = value.toString();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, ScriptableRole));
//        return true;
//    case StoredRole:
//        prop->stored = value.toBool();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, StoredRole));
//        return true;
//    case UserRole:
//        prop->user = value.toBool();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, UserRole));
//        return true;
//    case ConstantRole:
//        prop->constant = value.toBool();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, ConstantRole));
//        return true;
//    case FinalRole:
//        prop->final = value.toBool();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, FinalRole));
//        return true;
//    case BriefRole:
//        prop->brief = value.toString();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, BriefRole));
//        return true;
//    case CommentRole:
//        prop->comment = value.toString();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, CommentRole));
//        return true;
//    case PrivateRole:
//        prop->privateClass = value.toBool();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, PrivateRole));
//        return true;
//    case DefaultRole:
//        prop->defaultValue = value.toString();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, DefaultRole));
//        return true;
//    case PointerRole:
//        prop->pointer = value.toBool();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, PointerRole));
//        return true;
//    case ArgsByRefRole:
//        prop->argsByRef = value.toBool();
//        emit dataChanged(index(idx), index(idx), QVector<int>(1, ArgsByRefRole));
//        return true;
//    default:
//        return false;
//    }
//}




/*!
 * \property PropertyModel::fileUrl
 * \brief This property holds
 *
 * \par Access functions:
 * <TABLE><TR><TD>QUrl</TD><TD>getFileUrl() const</TD></TR><TR><TD>void</TD><TD>setFileUrl(const QUrl & nFileUrl)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>fileUrlChanged(const QUrl & nFileUrl)</TD></TR></TABLE>
 */

/*!
 * \fn PropertyModel::fileUrlChanged()
 * \brief
 *
 * Part of the \link PropertyModel::fileUrl fileUrl \endlink property.
 */

/*!
 * \brief
 *
 * Part of the \link PropertyModel::fileUrl fileUrl \endlink property.
 */
QUrl PropertyModel::getFileUrl() const { return m_fileUrl; }

/*!
 * \brief
 *
 * Part of the \link PropertyModel::fileUrl fileUrl \endlink property.
 */
void PropertyModel::setFileUrl(const QUrl &nFileUrl)
{
    if (nFileUrl != m_fileUrl) {
        m_fileUrl = nFileUrl;
#ifdef QT_DEBUG
        qDebug() << "Changed fileUrl to" << getFileUrl();
#endif
        emit fileUrlChanged(getFileUrl());
        emit fileNameChanged(getFileUrl().fileName());
        loadData();
    }
}






/*!
 * \property PropertyModel::fileName
 * \brief This property holds
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>getFileName() const</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>fileNameChanged(const QString & nFileName)</TD></TR></TABLE>
 */

/*!
 * \fn PropertyModel::fileNameChanged()
 * \brief
 *
 * Part of the \link PropertyModel::fileName fileName \endlink property.
 */

/*!
 * \brief
 *
 * Part of the \link PropertyModel::fileName fileName \endlink property.
 */
QString PropertyModel::getFileName() const { return getFileUrl().fileName(); }






/*!
 * \property PropertyModel::className
 * \brief This property holds
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>getClassName() const</TD></TR><TR><TD>void</TD><TD>setClassName(const QString & nClassName)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>classNameChanged(const QString & nClassName)</TD></TR></TABLE>
 */

/*!
 * \fn PropertyModel::classNameChanged()
 * \brief
 *
 * Part of the \link PropertyModel::className className \endlink property.
 */

/*!
 * \brief
 *
 * Part of the \link PropertyModel::className className \endlink property.
 */
QString PropertyModel::getClassName() const { return m_className; }

/*!
 * \brief
 *
 * Part of the \link PropertyModel::className className \endlink property.
 */
void PropertyModel::setClassName(const QString &nClassName)
{
    if (nClassName != m_className) {
        m_className = nClassName;
#ifdef QT_DEBUG
        qDebug() << "Changed className to" << getClassName();
#endif
        emit classNameChanged(getClassName());
    }
}






/*!
 * \property PropertyModel::privateClass
 * \brief This property holds
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>isPrivateClass() const</TD></TR><TR><TD>void</TD><TD>setPrivateClass(bool nPrivateClass)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>privateClassChanged(bool nPrivateClass)</TD></TR></TABLE>
 */

/*!
 * \fn PropertyModel::privateClassChanged()
 * \brief
 *
 * Part of the \link PropertyModel::privateClass privateClass \endlink property.
 */

/*!
 * \brief
 *
 * Part of the \link PropertyModel::privateClass privateClass \endlink property.
 */
bool PropertyModel::isPrivateClass() const { return m_privateClass; }

/*!
 * \brief
 *
 * Part of the \link PropertyModel::privateClass privateClass \endlink property.
 */
void PropertyModel::setPrivateClass(bool nPrivateClass)
{
    if (nPrivateClass != m_privateClass) {
        m_privateClass = nPrivateClass;
#ifdef QT_DEBUG
        qDebug() << "Changed privateClass to" << isPrivateClass();
#endif
        emit privateClassChanged(isPrivateClass());
    }
}





/*!
 * \property PropertyModel::type
 * \brief Sets the type of the class.
 *
 * The class type manages the style of the class parts.
 *
 * \par Access functions:
 * <TABLE><TR><TD>ClassType</TD><TD>getType() const</TD></TR><TR><TD>void</TD><TD>setType(ClassType type)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>typeChanged(ClassType type)</TD></TR></TABLE>
 */

/*!
 * \fn PropertyModel::typeChanged()
 * \brief Part of the \link PropertyModel::type type \endlink property.
 */

/*!
 * \brief Part of the \link PropertyModel::type type \endlink property.
 */
PropertyModel::ClassType PropertyModel::getType() const { return m_type; }

/*!
 * \brief Part of the \link PropertyModel::type type \endlink property.
 */
void PropertyModel::setType(ClassType type)
{
    if (type != m_type) {
        m_type = type;
#ifdef QT_DEBUG
        qDebug() << "Changed type to " << m_type;
#endif
        emit typeChanged(getType());
    }
}



/*!
 * \property PropertyModel::commentsPosition
 * \brief Defines where the comments will be inserted.
 *
 * \par Access functions:
 * <TABLE><TR><TD>CommentsPosition</TD><TD>getCommentsPosition() const</TD></TR><TR><TD>void</TD><TD>setCommentsPosition(CommentsPosition commentsPosition)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>commentsPositionChanged(CommentsPosition commentsPosition)</TD></TR></TABLE>
 */

/*!
 * \fn PropertyModel::commentsPositionChanged()
 * \brief Part of the \link PropertyModel::commentsPosition commentsPosition \endlink property.
 */

/*!
 * \brief Part of the \link PropertyModel::commentsPosition commentsPosition \endlink property.
 */
PropertyModel::CommentsPosition PropertyModel::getCommentsPosition() const { return m_commentsPosition; }

/*!
 * \brief Part of the \link PropertyModel::commentsPosition commentsPosition \endlink property.
 */
void PropertyModel::setCommentsPosition(CommentsPosition commentsPosition)
{
    if (commentsPosition != m_commentsPosition) {
        m_commentsPosition = commentsPosition;
#ifdef QT_DEBUG
        qDebug() << "Changed commentsPosition to" << m_commentsPosition;
#endif
        emit commentsPositionChanged(getCommentsPosition());
    }
}



/*!
 * \property PropertyModel::usePropertyName
 * \brief Set to true to use the name of the property for the read function.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>hasUsePropertyName() const</TD></TR><TR><TD>void</TD><TD>setUsePropertyName(bool usePropertyName)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>usePropertyNameChanged(bool usePropertyName)</TD></TR></TABLE>
 */

/*!
 * \fn void PropertyModel::usePropertyNameChanged(const bool &usePropertyName)
 * \brief Part of the \link PropertyModel::usePropertyName usePropertyName \endlink property.
 */

/*!
 * \brief Part of the \link PropertyModel::usePropertyName usePropertyName \endlink property.
 */
bool PropertyModel::hasUsePropertyName() const { return m_usePropertyName; }

/*!
 * \brief Part of the \link PropertyModel::usePropertyName usePropertyName \endlink property.
 */
void PropertyModel::setUsePropertyName(bool usePropertyName)
{
    if (usePropertyName != m_usePropertyName) {
        m_usePropertyName = usePropertyName;
#ifdef QT_DEBUG
        qDebug() << "Changed usePropertyName to" << m_usePropertyName;
#endif
        emit usePropertyNameChanged(hasUsePropertyName());
    }
}





QString PropertyModel::getDefaultValue(const QString &type, bool pointer)
{
    if (pointer) {
        return QStringLiteral("nullptr");
    }

    if (m_ints.contains(type, Qt::CaseInsensitive)) {
        return QStringLiteral("0");
    } else if (m_floats.contains(type, Qt::CaseInsensitive)) {
        return QStringLiteral("0.0");
    } else if (type == QLatin1String("bool")) {
        return QStringLiteral("false");
	} else if (m_hasDefaultConstructor.contains(type, Qt::CaseInsensitive)) {
		return QString();
    } else {
        QString result = type;
        result.append(QStringLiteral("()"));
        return result;
    }
}


bool PropertyModel::getArgsByRef(const QString &type, bool pointer)
{
    if (pointer) {
        return false;
    }

    if (type == QLatin1String("bool")) {
        return false;
    } else if (m_floats.contains(type, Qt::CaseInsensitive)) {
        return false;
    } else if (m_ints.contains(type, Qt::CaseInsensitive)) {
        return false;
    } else {
        return true;
    }
}




Property *PropertyModel::getItemById(int id)
{
    if (id < 0) {
        return nullptr;
    }

    if (rowCount() <= 0) {
        return nullptr;
    }

    int idx = -1;

    for (int i = 0; i < m_properties.count(); ++i) {
        if (m_properties.at(i)->id() == id) {
            idx = i;
            break;
        }
    }

    if (idx > -1) {
        return m_properties.at(idx);
    } else {
        return nullptr;
    }
}


Property *PropertyModel::getItemByIndex(int idx)
{
    if (idx < 0) {
        return nullptr;
    }

    if (idx >= rowCount()) {
        return nullptr;
    }

    return m_properties.at(idx);
}




/*!
 * \property PropertyModel::namespaces
 * \brief Comma separated list of namespaces.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>getNamespaces() const</TD></TR><TR><TD>void</TD><TD>setNamespaces(const QString &namespaces)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>namespacesChanged(const QString &namespaces)</TD></TR></TABLE>
 */

/*!
 * \fn void PropertyModel::namespacesChanged(const QString &namespaces)
 * \brief Part of the \link PropertyModel::namespaces namespaces \endlink property.
 */

/*!
 * \brief Part of the \link PropertyModel::namespaces namespaces \endlink property.
 */
QString PropertyModel::getNamespaces() const { return m_namespaces; }

/*!
 * \brief Part of the \link PropertyModel::namespaces namespaces \endlink property.
 */
void PropertyModel::setNamespaces(const QString &namespaces)
{
    if (namespaces != m_namespaces) {
        m_namespaces = namespaces;
#ifdef QT_DEBUG
        qDebug() << "Changed namespaces to" << m_namespaces;
#endif
        emit namespacesChanged(getNamespaces());
    }
}


