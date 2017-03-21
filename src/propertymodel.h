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

#ifndef PROPERTYMODEL_H
#define PROPERTYMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QUrl>
#include <grantlee5/grantlee/templateloader.h>

class Property;
class QStringList;

namespace Grantlee {
class Engine;
}

/*!
 * \brief The PropertyModel class
 */
class PropertyModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QUrl fileUrl READ getFileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
    Q_PROPERTY(QString fileName READ getFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString className READ getClassName WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(bool privateClass READ isPrivateClass WRITE setPrivateClass NOTIFY privateClassChanged)
    Q_PROPERTY(CommentsPosition commentsPosition READ getCommentsPosition WRITE setCommentsPosition NOTIFY commentsPositionChanged)
    Q_PROPERTY(bool usePropertyName READ hasUsePropertyName WRITE setUsePropertyName NOTIFY usePropertyNameChanged)
    Q_PROPERTY(QString namespaces READ getNamespaces WRITE setNamespaces NOTIFY namespacesChanged)
public:
    explicit PropertyModel(QObject *parent = nullptr);
    ~PropertyModel();

    enum ResultFileType {
        HeaderFile,
        PrivateHeaderFile,
        CodeFile
    };
    Q_ENUM(ResultFileType)

    enum CommentsPosition {
        InCode          = 0,
        InHeader        = 1,
        InFronOfHeader  = 2
    };
    Q_ENUM(CommentsPosition)

	enum Roles {
		Item	= Qt::UserRole + 1
    };

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override final;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override final;
    QHash<int, QByteArray> roleNames() const override final;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override final;

    QUrl getFileUrl() const;
    QString getFileName() const;
    QString getClassName() const;
    bool isPrivateClass() const;
    CommentsPosition getCommentsPosition() const;
    bool hasUsePropertyName() const;
    QString getNamespaces() const;

    void setFileUrl(const QUrl &nFileUrl);
    void setClassName(const QString &nClassName);
    void setPrivateClass(bool nPrivateClass);
    void setCommentsPosition(CommentsPosition commentsPosition);
    void setUsePropertyName(bool usePropertyName);
    void setNamespaces(const QString &namespaces);

    Q_INVOKABLE Property *addProperty(const QString &name, const QString &type, bool r = true, bool w = true, bool m = false, bool u = false, bool n = true, bool d = true);
    Q_INVOKABLE void deleteProperty(int idx);
    Q_INVOKABLE QString createOutput(ResultFileType type) const;
    Q_INVOKABLE bool saveToDirectory(ResultFileType type, const QString &directory) const;
    Q_INVOKABLE bool saveToFile(ResultFileType type, const QUrl &file) const;
    Q_INVOKABLE bool saveAll(const QUrl &directory) const;
    Q_INVOKABLE QVariant getData(const QString &role, int idx) const;
    Q_INVOKABLE Property *getItemById(int id) const;
    Q_INVOKABLE Property *getItemByIndex(int idx) const;

signals:
    void fileUrlChanged(const QUrl &nFileUrl);
    void fileNameChanged(const QString &nFileName);
    void classNameChanged(const QString &nClassName);
    void privateClassChanged(bool nPrivateClass);
    void commentsPositionChanged(CommentsPosition commentsPosition);
    void usePropertyNameChanged(bool usePropertyName);
    void namespacesChanged(const QString &namespaces);

private:
    QList<Property*> m_properties;
    static const QStringList m_ints;
    static const QStringList m_floats;
    static const QStringList m_hasDefaultConstructor;

    QUrl m_fileUrl;
    QString m_className;
    bool m_privateClass = false;
    CommentsPosition m_commentsPosition = InCode;
    bool m_usePropertyName = false;
    QString m_namespaces;

    int m_lastAddedId = -1;

    QString getDefaultValue(const QString &type, bool pointer = false);
    bool getArgsByRef(const QString &type, bool pointer = false);

    Grantlee::Engine *m_tmpl_engine;
    QSharedPointer<Grantlee::FileSystemTemplateLoader> m_tmpl_loader;
};

#endif // PROPERTYMODEL_H
