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

#ifndef PROPERTYMODEL_H
#define PROPERTYMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QUrl>
#include <QFile>
#include <QTextStream>

struct Property;

/*!
 * \brief The PropertyModel class
 */
class PropertyModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(ResultFileType)
    Q_ENUMS(ClassType)
    Q_ENUMS(CommentsPosition)
    Q_PROPERTY(QUrl fileUrl READ getFileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
    Q_PROPERTY(QString fileName READ getFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString className READ getClassName WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(bool privateClass READ isPrivateClass WRITE setPrivateClass NOTIFY privateClassChanged)
    Q_PROPERTY(ClassType type READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(CommentsPosition commentsPosition READ getCommentsPosition WRITE setCommentsPosition NOTIFY commentsPositionChanged)
    Q_PROPERTY(bool usePropertyName READ hasUsePropertyName WRITE setUsePropertyName NOTIFY usePropertyNameChanged)
public:
    explicit PropertyModel();
    ~PropertyModel();

    enum ResultFileType {
        HeaderFile,
        PrivateHeaderFile,
        CodeFile
    };

    enum ClassType {
        PrivateClass    = 0,
        SharedData      = 1
    };
    
    enum CommentsPosition {
        InCode          = 0,
        InHeader        = 1,
        InFronOfHeader  = 2
    };

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_FINAL;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_FINAL;
    virtual QHash<int, QByteArray> roleNames() const Q_DECL_FINAL;
    virtual QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const Q_DECL_FINAL;

    static const int IdRole;
    static const int NameRole;
    static const int TypeRole;
    static const int ReadRole;
    static const int WriteRole;
    static const int MemberRole;
    static const int ResetRole;
    static const int NotifyRole;
    static const int RevisionRole;
    static const int DesignableRole;
    static const int ScriptableRole;
    static const int StoredRole;
    static const int UserRole;
    static const int ConstantRole;
    static const int FinalRole;
    static const int BriefRole;
    static const int CommentRole;
    static const int PrivateRole;
    static const int DefaultRole;
    static const int PointerRole;

    QUrl getFileUrl() const;
    QString getFileName() const;
    QString getClassName() const;
    bool isPrivateClass() const;
    ClassType getType() const;
    CommentsPosition getCommentsPosition() const;
    bool hasUsePropertyName() const;
    
    void setFileUrl(const QUrl &nFileUrl);
    void setClassName(const QString &nClassName);
    void setPrivateClass(const bool &nPrivateClass);
    void setType(const ClassType &type);
    void setCommentsPosition(const CommentsPosition &commentsPosition);
    void setUsePropertyName(const bool &usePropertyName);

    void loadData();
    Q_INVOKABLE bool addProperty(const QString &name, const QString &type, bool r = true, bool w = true, bool m = false, bool u = false, bool n = true, bool p = false);
    Q_INVOKABLE void deleteProperty(int idx);
    Q_INVOKABLE QString createOutput(ResultFileType type) const;
    Q_INVOKABLE bool saveToDirectory(ResultFileType type, const QString &directory) const;
    Q_INVOKABLE bool saveToFile(ResultFileType type, const QUrl &file) const;
    Q_INVOKABLE bool saveAll(const QUrl &directory) const;
    Q_INVOKABLE QVariant getData(const QString &role, int idx) const;
    Q_INVOKABLE bool updateData(const QString &role, int idx, const QVariant &value);

signals:
    void fileUrlChanged(const QUrl &nFileUrl);
    void fileNameChanged(const QString &nFileName);
    void classNameChanged(const QString &nClassName);
    void privateClassChanged(const bool &nPrivateClass);
    void typeChanged(const ClassType &type);
    void commentsPositionChanged(const CommentsPosition &commentsPosition);
    void usePropertyNameChanged(const bool &usePropertyName);

private:
    QList<Property*> m_properties;
    QHash<int, QByteArray> m_roles;

    QUrl m_fileUrl;
    QString m_className;
    bool m_privateClass;
    ClassType m_type;
    CommentsPosition m_commentsPosition;
    bool m_usePropertyName;

    QString getDefaultValue(const QString &type, bool pointer = false);
};

#endif // PROPERTYMODEL_H
