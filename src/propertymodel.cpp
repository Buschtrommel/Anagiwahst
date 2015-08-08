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
#include "property.h"
#include <QtDebug>

const int PropertyModel::IdRole = Qt::UserRole + 1;
const int PropertyModel::NameRole = Qt::UserRole + 2;
const int PropertyModel::TypeRole = Qt::UserRole + 3;
const int PropertyModel::ReadRole = Qt::UserRole + 4;
const int PropertyModel::WriteRole = Qt::UserRole + 5;
const int PropertyModel::MemberRole = Qt::UserRole + 6;
const int PropertyModel::ResetRole = Qt::UserRole + 7;
const int PropertyModel::NotifyRole = Qt::UserRole + 8;
const int PropertyModel::RevisionRole = Qt::UserRole + 9;
const int PropertyModel::DesignableRole = Qt::UserRole + 10;
const int PropertyModel::ScriptableRole = Qt::UserRole + 11;
const int PropertyModel::StoredRole = Qt::UserRole + 12;
const int PropertyModel::UserRole = Qt::UserRole + 13;
const int PropertyModel::ConstantRole = Qt::UserRole + 14;
const int PropertyModel::FinalRole = Qt::UserRole + 15;
const int PropertyModel::BriefRole = Qt::UserRole + 16;
const int PropertyModel::CommentRole = Qt::UserRole + 17;
const int PropertyModel::PrivateRole = Qt::UserRole + 18;
const int PropertyModel::DefaultRole = Qt::UserRole + 19;

PropertyModel::PropertyModel()
{
    m_properties = QList<Property*>();

    m_roles = QAbstractItemModel::roleNames();
    m_roles.insert(IdRole, QByteArrayLiteral("id"));
    m_roles.insert(NameRole, QByteArrayLiteral("name"));
    m_roles.insert(TypeRole, QByteArrayLiteral("type"));
    m_roles.insert(ReadRole, QByteArrayLiteral("read"));
    m_roles.insert(WriteRole, QByteArrayLiteral("write"));
    m_roles.insert(MemberRole, QByteArrayLiteral("member"));
    m_roles.insert(ResetRole, QByteArrayLiteral("reset"));
    m_roles.insert(NotifyRole, QByteArrayLiteral("notify"));
    m_roles.insert(RevisionRole, QByteArrayLiteral("revision"));
    m_roles.insert(DesignableRole, QByteArrayLiteral("designable"));
    m_roles.insert(ScriptableRole, QByteArrayLiteral("scriptable"));
    m_roles.insert(StoredRole, QByteArrayLiteral("stored"));
    m_roles.insert(UserRole, QByteArrayLiteral("user"));
    m_roles.insert(ConstantRole, QByteArrayLiteral("constant"));
    m_roles.insert(FinalRole, QByteArrayLiteral("final"));
    m_roles.insert(BriefRole, QByteArrayLiteral("brief"));
    m_roles.insert(CommentRole, QByteArrayLiteral("comment"));
    m_roles.insert(PrivateRole, QByteArrayLiteral("private"));
    m_roles.insert(DefaultRole, QByteArrayLiteral("default"));

    m_fileUrl = QUrl();
    m_className = QStringLiteral("");
    m_privateClass = false;

#ifdef QT_DEBUG
    qDebug() << "Constructed PropertyModel" << this;
#endif
}


PropertyModel::~PropertyModel()
{
    while (!m_properties.isEmpty()) {
        delete m_properties.takeLast();
    }

    m_properties.clear();

#ifdef QT_DEBUG
    qDebug() << "Deconstucted PropertyModel" << this;
#endif
}


QHash<int, QByteArray> PropertyModel::roleNames() const
{
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

    switch(role) {
    case IdRole:
        return QVariant::fromValue(prop->id);
    case NameRole:
        return QVariant::fromValue(prop->name);
    case TypeRole:
        return QVariant::fromValue(prop->type);
    case ReadRole:
        return QVariant::fromValue(prop->read);
    case WriteRole:
        return QVariant::fromValue(prop->write);
    case MemberRole:
        return QVariant::fromValue(prop->member);
    case ResetRole:
        return QVariant::fromValue(prop->reset);
    case NotifyRole:
        return QVariant::fromValue(prop->notify);
    case RevisionRole:
        return QVariant::fromValue(prop->revision);
    case DesignableRole:
        return QVariant::fromValue(prop->designable);
    case ScriptableRole:
        return QVariant::fromValue(prop->scriptable);
    case StoredRole:
        return QVariant::fromValue(prop->stored);
    case UserRole:
        return QVariant::fromValue(prop->user);
    case ConstantRole:
        return QVariant::fromValue(prop->constant);
    case FinalRole:
        return QVariant::fromValue(prop->final);
    case BriefRole:
        return QVariant::fromValue(prop->brief);
    case CommentRole:
        return QVariant::fromValue(prop->comment);
    case PrivateRole:
        return QVariant::fromValue(prop->privateClass);
    case DefaultRole:
        return QVariant::fromValue(prop->defaultValue);
    default:
        return QVariant();
    }
}





void PropertyModel::loadData()
{
    QFile file(getFileUrl().toLocalFile());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Failed to open file:" << getFileUrl();
        return;
    }

    setClassName(QStringLiteral(""));
    QTextStream in(&file);

    int id = 0;

    while (!in.atEnd()) {

        QString line = in.readLine();
        QString trimmed = line.trimmed();

        if (trimmed.startsWith(QLatin1String("class"), Qt::CaseInsensitive) && !trimmed.endsWith(QLatin1String(";"))) {

            QStringList classPartList = trimmed.split(" ");

            if (!classPartList.isEmpty()) {

                for (int i = 0; i < classPartList.size(); ++i) {

                    if (classPartList.at(i) == QLatin1String(":")) {
                        setClassName(classPartList.at(i-1));
                    }

                }
            }

            if (getClassName().isEmpty()) {
                setClassName(classPartList.last());
            }
        }


        if (trimmed.startsWith("Q_DECLARE_PRIVATE")) {
            QString privDecl = trimmed;
            privDecl.remove(0,18);
            privDecl.chop(1);

            setPrivateClass(privDecl == getClassName());
        }


        if (trimmed.startsWith(QLatin1String("Q_PROPERTY"), Qt::CaseInsensitive)) {

            id++;

            trimmed.remove(0,11);
            trimmed.chop(1);

            QString lastPart("");

            QStringList propertyParts = trimmed.split(" ");
            quint8 propertyPartsCount = propertyParts.size();
            QString type = propertyParts.at(0);
            QString name = propertyParts.at(1);
            QString read("");
            QString write("");
            QString member("");
            QString reset("");
            QString notify("");
            quint8 revision = 0;
            QString designable("true");
            QString scriptable("true");
            bool stored = true;
            bool user = false;
            bool constant = false;
            bool final = false;
            QString brief("This property holds");
            QString comment("");


            for (quint8 i = 2; i < propertyPartsCount; i++) {

                QString part = propertyParts.at(i);

                if (lastPart == QLatin1String("READ")) {
                    read = part;
                } else if (lastPart == QLatin1String("WRITE")) {
                    write = part;
                } else if (lastPart == QLatin1String("MEMBER")) {
                    member = part;
                } else if (lastPart == QLatin1String("RESET")) {
                    reset = part;
                } else if (lastPart == QLatin1String("NOTIFY")) {
                    notify = part;
                } else if (lastPart == QLatin1String("REVISION")) {
                    revision = part.toInt();
                } else if (lastPart == QLatin1String("DESIGNABLE")) {
                    designable = part;
                } else if (lastPart == QLatin1String("SCRIPTABLE")) {
                    scriptable = part;
                } else if (lastPart == QLatin1String("STORED")) {
                    stored = part == QLatin1String("true");
                } else if (lastPart == QLatin1String("USER")) {
                    user = part == QLatin1String("true");
                }

                if (part == QLatin1String("CONSTANT")) {
                    constant = true;
                }

                if (part == QLatin1String("FIANL")) {
                    final = true;
                }

                lastPart = part;
            }

            beginInsertRows(QModelIndex(), rowCount(), rowCount());


            Property *prop = new Property;
            prop->id = id;
            prop->name = name;
            prop->type = type;
            prop->read = read;
            prop->write = write;
            prop->member = member;
            prop->reset = reset;
            prop->notify = notify;
            prop->revision = revision;
            prop->designable = designable;
            prop->scriptable = scriptable;
            prop->stored = stored;
            prop->user = user;
            prop->constant = constant;
            prop->final = final;
            prop->brief = brief;
            prop->comment = comment;
            prop->privateClass = isPrivateClass();
            prop->defaultValue = QStringLiteral("");

            m_properties.append(prop);

            endInsertRows();
        }

    }

    file.close();
}






bool PropertyModel::addProperty(const QString &name, const QString &type, bool r, bool w, bool m, bool u, bool n, bool p)
{
    if (name.isEmpty() || type.isEmpty()) {
        return false;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    Property *prop = new Property;

    prop->id = rowCount();
    prop->name = name;
    prop->type = type;

    if (r) {
        QString read = name;
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

        prop->read = read;

    }

    if (w) {
        QString write = name;
        write[0] = write[0].toUpper();
        write.prepend("set");

        prop->write = write;
    }


    if (m) {
        QString member = name;
        member.prepend(QStringLiteral("m_"));

        prop->member = member;
    }

    if (u) {
        QString reset = name;
        reset[0] = reset[0].toUpper();
        reset.prepend(QStringLiteral("unset"));

        prop->reset = reset;
    }


    if (n) {
        QString notify = name;
        notify.append("Changed");

        prop->notify = notify;
    }

    prop->revision = 0;
    prop->designable = QStringLiteral("true");
    prop->scriptable = QStringLiteral("true");
    prop->stored = true;
    prop->user = false;
    prop->constant = false;
    prop->final = false;
    prop->brief = QString();
    prop->comment = QString();
    prop->privateClass = p;
    prop->defaultValue = QString();

    m_properties.append(prop);

    endInsertRows();

    return true;
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






QString PropertyModel::createHeader() const
{
    PropertyCreator creator(m_properties, getClassName(), 4);
    return creator.createHeader();
}



QString PropertyModel::createPrivate() const
{
    PropertyCreator creator(m_properties, getClassName(), 4);
    return creator.createPrivate();
}


QString PropertyModel::createCode() const
{
    PropertyCreator creator(m_properties, getClassName(), 4);
    return creator.createCode();
}



QVariant PropertyModel::getData(const QString &role, int idx)
{
    return data(index(idx), roleNames().key(role.toUtf8()));
}




bool PropertyModel::updateData(const QString &role, int idx, const QVariant &value)
{
    if (data(index(idx), roleNames().key(role.toUtf8())) == value) {
        return false;
    }

    if (idx < 0) {
        qCritical() << "Index" << idx << "is out of range.";
        return false;
    }

    if (idx > rowCount()-1) {
        qCritical() << "Index" << idx << "is out of range.";
        return false;
    }

#ifdef QT_DEBUG
    qDebug() << "Updating role" << role << "at position" << idx << "to" << value;
#endif

    Property *prop = m_properties.at(idx);

    switch(roleNames().key(role.toUtf8())) {
    case NameRole:
        prop->name = value.toString();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, NameRole));
        return true;
    case TypeRole:
        prop->type = value.toString();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, TypeRole));
        return true;
    case ReadRole:
        prop->read = value.toString();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, ReadRole));
        return true;
    case WriteRole:
        prop->write = value.toString();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, WriteRole));
        return true;
    case ResetRole:
        prop->reset = value.toString();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, ResetRole));
        return true;
    case NotifyRole:
        prop->notify = value.toString();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, NotifyRole));
        return true;
    case RevisionRole:
        prop->revision = quint8(value.toInt());
        emit dataChanged(index(idx), index(idx), QVector<int>(1, RevisionRole));
        return true;
    case DesignableRole:
        prop->designable = value.toString();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, DesignableRole));
        return true;
    case ScriptableRole:
        prop->scriptable = value.toString();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, ScriptableRole));
        return true;
    case StoredRole:
        prop->stored = value.toBool();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, StoredRole));
        return true;
    case UserRole:
        prop->user = value.toBool();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, UserRole));
        return true;
    case ConstantRole:
        prop->constant = value.toBool();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, ConstantRole));
        return true;
    case FinalRole:
        prop->final = value.toBool();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, FinalRole));
        return true;
    case BriefRole:
        prop->brief = value.toString();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, BriefRole));
        return true;
    case CommentRole:
        prop->comment = value.toString();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, CommentRole));
        return true;
    case PrivateRole:
        prop->privateClass = value.toBool();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, PrivateRole));
        return true;
    case DefaultRole:
        prop->defaultValue = value.toString();
        emit dataChanged(index(idx), index(idx), QVector<int>(1, DefaultRole));
        return true;
    default:
        return false;
    }
}




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
 * <TABLE><TR><TD>bool</TD><TD>isPrivateClass() const</TD></TR><TR><TD>void</TD><TD>setPrivateClass(const bool & nPrivateClass)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>privateClassChanged(const bool & nPrivateClass)</TD></TR></TABLE>
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
void PropertyModel::setPrivateClass(const bool &nPrivateClass)
{
    if (nPrivateClass != m_privateClass) {
        m_privateClass = nPrivateClass;
#ifdef QT_DEBUG
        qDebug() << "Changed privateClass to" << isPrivateClass();
#endif
        emit privateClassChanged(isPrivateClass());
    }
}