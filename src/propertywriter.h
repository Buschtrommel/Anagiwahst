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

#ifndef PROPERTYWRITER_H
#define PROPERTYWRITER_H

#include <QObject>
#include <grantlee5/grantlee/templateloader.h>

class Unit;
class PropertyFilterModel;
class QUrl;

namespace Grantlee {
class Engine;
}

class PropertyWriter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString headerContent READ headerContent WRITE setHeaderContent NOTIFY headerContentChanged)
    Q_PROPERTY(QString privateContent READ privateContent WRITE setPrivateContent NOTIFY privateContentChanged)
    Q_PROPERTY(QString codeContent READ codeContent WRITE setCodeContent NOTIFY codeContentChanged)
    Q_PROPERTY(Unit *unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(PropertyFilterModel *propertyModel READ propertyModel WRITE setPropertyModel NOTIFY propertyModelChanged)
    Q_PROPERTY(CommentsPosition commentsPosition READ commentsPosition WRITE setCommentsPosition NOTIFY commentsPositionChanged)
public:
    explicit PropertyWriter(QObject *parent = nullptr);
     ~PropertyWriter();

    enum WriteFileType {
        HeaderFile,
        PrivateHeaderFile,
        CodeFile
    };
    Q_ENUM(WriteFileType)

    enum CommentsPosition {
        InCode          = 0,
        InHeader        = 1,
        InFronOfHeader  = 2
    };
    Q_ENUM(CommentsPosition)

    QString headerContent() const;
    QString privateContent() const;
    QString codeContent() const;
    Unit *unit() const;
    PropertyFilterModel *propertyModel() const;
    CommentsPosition commentsPosition() const;

    void setHeaderContent(const QString &nHeaderContent);
    void setPrivateContent(const QString &nPrivateContent);
    void setCodeContent(const QString &nCodeContent);
    void setUnit(Unit *nUnit);
    void setPropertyModel(PropertyFilterModel *nPropertyModel);
    void setCommentsPosition(CommentsPosition nCommentsPosition);

    Q_INVOKABLE void createProperties();
    Q_INVOKABLE bool saveAll(const QUrl &directory) const;

    static bool write(WriteFileType type, QString path, const QString &className, const QString &data, bool forceOverwrite = false);
    static bool writeFile(const QString &fileName, const QString &data, bool forceOverwrite = false);

Q_SIGNALS:
    void headerContentChanged(const QString &headerContent);
    void privateContentChanged(const QString &privateContent);
    void codeContentChanged(const QString &codeContent);
    void unitChanged(Unit *unit);
    void propertyModelChanged(PropertyFilterModel *propertyModel);
    void commentsPositionChanged(CommentsPosition commentsPosition);

private:
    QString m_headerContent;
    QString m_privateContent;
    QString m_codeContent;
    Unit *m_unit = nullptr;
    PropertyFilterModel *m_propertyModel = nullptr;
    CommentsPosition m_commentsPosition = InCode;

    Grantlee::Engine *m_tmpl_engine;
    QSharedPointer<Grantlee::FileSystemTemplateLoader> m_tmpl_loader;

    Q_DISABLE_COPY(PropertyWriter)
};

#endif // PROPERTYWRITER_H
