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

#include "propertywriter.h"
#include <QtDebug>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <grantlee5/grantlee/engine.h>
#include <grantlee5/grantlee/template.h>
#include <grantlee5/grantlee/context.h>
#include <QStandardPaths>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

#include "unit.h"
#include "propertyfiltermodel.h"
#include "property.h"

/*!
 * \class PropertyWriter
 * \brief The PropertyWriter class.
 */


/*!
 * \brief Constructs a new PropertyWriter object with default values and the given \a parent.
 */
PropertyWriter::PropertyWriter(QObject *parent) : QObject(parent)
{
    m_tmpl_loader = QSharedPointer<Grantlee::FileSystemTemplateLoader>(new Grantlee::FileSystemTemplateLoader);
    m_tmpl_loader->setTemplateDirs({QStandardPaths::writableLocation(QStandardPaths::DataLocation).append(QLatin1String("/templates")), QStringLiteral(TMPL_DIR)});

    m_tmpl_engine = new Grantlee::Engine(this);
    m_tmpl_engine->setSmartTrimEnabled(true);
    m_tmpl_engine->addTemplateLoader(m_tmpl_loader);
}


PropertyWriter::~PropertyWriter()
{

}


void PropertyWriter::createProperties()
{
    Q_ASSERT_X(m_unit, "create properties", "invalid unit");
    Q_ASSERT_X(m_propertyModel, "create properties", "invalid property model");

    QStringList namespaces;
    if (!m_unit->namespaces().isEmpty()) {
        QString nsString = m_unit->namespaces().simplified();
        nsString.remove(QStringLiteral(" "));
        if (!nsString.isEmpty()) {
            namespaces = nsString.split(QChar(','));
        }
    }

    QStringList parentClasses = {QStringLiteral("QObject")};

    m_tmpl_loader->setTheme(QStringLiteral("default_qobject"));

    QVariantHash mapping;
    mapping.insert(QStringLiteral("props"), QVariant::fromValue<QList<Property*>>(m_propertyModel->getProperties()));
    mapping.insert(QStringLiteral("class"), m_unit->name());
    mapping.insert(QStringLiteral("parentclasses"), parentClasses);
    mapping.insert(QStringLiteral("commentposition"), m_commentsPosition);
    mapping.insert(QStringLiteral("namespaces"), namespaces);
    mapping.insert(QStringLiteral("debugout"), true);
    const QString license = m_unit->license().trimmed();
    if (!license.isEmpty()) {
        mapping.insert(QStringLiteral("license"), license);
    }
    Grantlee::Context c(mapping);

    Grantlee::Template t = m_tmpl_engine->loadByName(QStringLiteral("header.tpl"));
    QString out = t->render(&c);
    if (t->error() != Grantlee::NoError) {
        out = t->errorString();
    }
    setHeaderContent(out);

    t = m_tmpl_engine->loadByName(QStringLiteral("private.tpl"));
    out = t->render(&c);
    if (t->error() != Grantlee::NoError) {
        out = t->errorString();
    }
    setPrivateContent(out);

    t = m_tmpl_engine->loadByName(QStringLiteral("code.tpl"));
    out = t->render(&c);
    if (t->error() != Grantlee::NoError) {
        out = t->errorString();
    }
    setCodeContent(out);
}


bool PropertyWriter::saveAll(const QUrl &directory) const
{
    bool retVal = false;

    const QString path = directory.toLocalFile();

    if (write(HeaderFile, path, m_unit->name(), m_headerContent)) {
        if (write(PrivateHeaderFile, path, m_unit->name(), m_privateContent)) {
            if (write(CodeFile, path, m_unit->name(), m_codeContent)) {
                retVal = true;
            }
        }
    }

    return retVal;
}


/*!
 * \property PropertyWriter::headerContent
 * \brief Content of the header file.
 *
 * \par Access functions:
 * \li QString headerContent() const
 * \li void setHeaderContent(const QString &nHeaderContent)
 *
 * \par Notifier signal:
 * \li void headerContentChanged(const QString &headerContent)
 */

/*!
 * \fn void  PropertyWriter::headerContentChanged(const QString &headerContent)
 * \brief Notifier function for the \link PropertyWriter::headerContent headerContent \endlink property.
 * \sa PropertyWriter::headerContent() PropertyWriter::setHeaderContent()
 */

/*!
 * \brief Getter function for the \link PropertyWriter::headerContent headerContent \endlink property.
 * \sa PropertyWriter::setHeaderContent() PropertyWriter::headerContentChanged()
 */
QString PropertyWriter::headerContent() const { return m_headerContent; }

/*!
 * \brief Setter function for the \link PropertyWriter::headerContent headerContent \endlink property.
 * \sa PropertyWriter::headerContent() PropertyWriter::headerContentChanged()
 */
void PropertyWriter::setHeaderContent(const QString &nHeaderContent)
{
    if (nHeaderContent != m_headerContent) {
        m_headerContent = nHeaderContent;
#ifdef QT_DEBUG
        qDebug() << "Changed headerContent to" << m_headerContent;
#endif
        Q_EMIT headerContentChanged(headerContent());
    }
}


/*!
 * \property PropertyWriter::privateContent
 * \brief Content of the private header file.
 *
 * \par Access functions:
 * \li QString privateContent() const
 * \li void setPrivateContent(const QString &nPrivateContent)
 *
 * \par Notifier signal:
 * \li void privateContentChanged(const QString &privateContent)
 */

/*!
 * \fn void  PropertyWriter::privateContentChanged(const QString &privateContent)
 * \brief Notifier function for the \link PropertyWriter::privateContent privateContent \endlink property.
 * \sa PropertyWriter::privateContent() PropertyWriter::setPrivateContent()
 */

/*!
 * \brief Getter function for the \link PropertyWriter::privateContent privateContent \endlink property.
 * \sa PropertyWriter::setPrivateContent() PropertyWriter::privateContentChanged()
 */
QString PropertyWriter::privateContent() const { return m_privateContent; }

/*!
 * \brief Setter function for the \link PropertyWriter::privateContent privateContent \endlink property.
 * \sa PropertyWriter::privateContent() PropertyWriter::privateContentChanged()
 */
void PropertyWriter::setPrivateContent(const QString &nPrivateContent)
{
    if (nPrivateContent != m_privateContent) {
        m_privateContent = nPrivateContent;
#ifdef QT_DEBUG
        qDebug() << "Changed privateContent to" << m_privateContent;
#endif
        Q_EMIT privateContentChanged(privateContent());
    }
}


/*!
 * \property PropertyWriter::codeContent
 * \brief Content of the code file.
 *
 * \par Access functions:
 * \li QString codeContent() const
 * \li void setCodeContent(const QString &nCodeContent)
 *
 * \par Notifier signal:
 * \li void codeContentChanged(const QString &codeContent)
 */

/*!
 * \fn void  PropertyWriter::codeContentChanged(const QString &codeContent)
 * \brief Notifier function for the \link PropertyWriter::codeContent codeContent \endlink property.
 * \sa PropertyWriter::codeContent() PropertyWriter::setCodeContent()
 */

/*!
 * \brief Getter function for the \link PropertyWriter::codeContent codeContent \endlink property.
 * \sa PropertyWriter::setCodeContent() PropertyWriter::codeContentChanged()
 */
QString PropertyWriter::codeContent() const { return m_codeContent; }

/*!
 * \brief Setter function for the \link PropertyWriter::codeContent codeContent \endlink property.
 * \sa PropertyWriter::codeContent() PropertyWriter::codeContentChanged()
 */
void PropertyWriter::setCodeContent(const QString &nCodeContent)
{
    if (nCodeContent != m_codeContent) {
        m_codeContent = nCodeContent;
#ifdef QT_DEBUG
        qDebug() << "Changed codeContent to" << m_codeContent;
#endif
        Q_EMIT codeContentChanged(codeContent());
    }
}


/*!
 * \property PropertyWriter::unit
 * \brief Unit the properties belongs to.
 *
 * \par Access functions:
 * \li Unit *unit() const
 * \li void setUnit(Unit *nUnit)
 *
 * \par Notifier signal:
 * \li void unitChanged(Unit *unit)
 */

/*!
 * \fn void  PropertyWriter::unitChanged(Unit *unit)
 * \brief Notifier function for the \link PropertyWriter::unit unit \endlink property.
 * \sa PropertyWriter::unit() PropertyWriter::setUnit()
 */

/*!
 * \brief Getter function for the \link PropertyWriter::unit unit \endlink property.
 * \sa PropertyWriter::setUnit() PropertyWriter::unitChanged()
 */
Unit *PropertyWriter::unit() const { return m_unit; }

/*!
 * \brief Setter function for the \link PropertyWriter::unit unit \endlink property.
 * \sa PropertyWriter::unit() PropertyWriter::unitChanged()
 */
void PropertyWriter::setUnit(Unit *nUnit)
{
    if (nUnit != m_unit) {
        m_unit = nUnit;
#ifdef QT_DEBUG
        qDebug() << "Changed unit to" << m_unit;
#endif
        Q_EMIT unitChanged(unit());
    }
}


/*!
 * \property PropertyWriter::propertyModel
 * \brief The model containing the properties.
 *
 * \par Access functions:
 * \li PropertyFilterModel *propertyModel() const
 * \li void setPropertyModel(PropertyFilterModel *nPropertyModel)
 *
 * \par Notifier signal:
 * \li void propertyModelChanged(PropertyFilterModel *propertyModel)
 */

/*!
 * \fn void  PropertyWriter::propertyModelChanged(PropertyFilterModel *propertyModel)
 * \brief Notifier function for the \link PropertyWriter::propertyModel propertyModel \endlink property.
 * \sa PropertyWriter::propertyModel() PropertyWriter::setPropertyModel()
 */

/*!
 * \brief Getter function for the \link PropertyWriter::propertyModel propertyModel \endlink property.
 * \sa PropertyWriter::setPropertyModel() PropertyWriter::propertyModelChanged()
 */
PropertyFilterModel *PropertyWriter::propertyModel() const { return m_propertyModel; }

/*!
 * \brief Setter function for the \link PropertyWriter::propertyModel propertyModel \endlink property.
 * \sa PropertyWriter::propertyModel() PropertyWriter::propertyModelChanged()
 */
void PropertyWriter::setPropertyModel(PropertyFilterModel *nPropertyModel)
{
    if (nPropertyModel != m_propertyModel) {
        m_propertyModel = nPropertyModel;
#ifdef QT_DEBUG
        qDebug() << "Changed propertyModel to" << m_propertyModel;
#endif
        Q_EMIT propertyModelChanged(propertyModel());
    }
}


/*!
 * \property PropertyWriter::commentsPosition
 * \brief The position the comments should be placed.
 *
 * \par Access functions:
 * \li CommentsPosition commentsPosition() const
 * \li void setCommentsPosition(CommentsPosition nCommentsPosition)
 *
 * \par Notifier signal:
 * \li void commentsPositionChanged(CommentsPosition commentsPosition)
 */

/*!
 * \fn void  PropertyWriter::commentsPositionChanged(CommentsPosition commentsPosition)
 * \brief Notifier function for the \link PropertyWriter::commentsPosition commentsPosition \endlink property.
 * \sa PropertyWriter::commentsPosition() PropertyWriter::setCommentsPosition()
 */

/*!
 * \brief Getter function for the \link PropertyWriter::commentsPosition commentsPosition \endlink property.
 * \sa PropertyWriter::setCommentsPosition() PropertyWriter::commentsPositionChanged()
 */
PropertyWriter::CommentsPosition PropertyWriter::commentsPosition() const { return m_commentsPosition; }

/*!
 * \brief Setter function for the \link PropertyWriter::commentsPosition commentsPosition \endlink property.
 * \sa PropertyWriter::commentsPosition() PropertyWriter::commentsPositionChanged()
 */
void PropertyWriter::setCommentsPosition(CommentsPosition nCommentsPosition)
{
    if (nCommentsPosition != m_commentsPosition) {
        m_commentsPosition = nCommentsPosition;
#ifdef QT_DEBUG
        qDebug() << "Changed commentsPosition to" << m_commentsPosition;
#endif
        Q_EMIT commentsPositionChanged(commentsPosition());
        createProperties();
    }
}




bool PropertyWriter::write(WriteFileType type, QString path, const QString &className, const QString &data, bool forceOverwrite)
{
    if (data.isEmpty()) {
        return true;
    }

    if (!path.endsWith('/')) {
        path.append('/');
    }

    path.append(className.toLower());

    switch (type) {
    case HeaderFile:
        path.append(QLatin1String(".h"));
        break;
    case PrivateHeaderFile:
        path.append(QLatin1String("_p.h"));
        break;
    case CodeFile:
        path.append(QLatin1String(".cpp"));
        break;
    default:
        break;
    }

    return writeFile(path, data, forceOverwrite);
}




bool PropertyWriter::writeFile(const QString &fileName, const QString &data, bool forceOverwrite)
{
    if (data.isEmpty()) {
        return true;
    }

    QTextStream errOut(stdout, QIODevice::WriteOnly);

    QFile outFile(fileName);

    if (!forceOverwrite) {
        if (outFile.exists()) {
            errOut << tr("There is already a file with that name. Use the -f option if you want to overwrite this file.") << "\n";
            errOut.flush();
            return false;
        }
    }

    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << outFile.errorString();
        return false;
    }

    QTextStream out(&outFile);
    out << data;
    out.flush();

    outFile.close();

    errOut << tr("Successfully wrote file %1").arg(fileName) << "\n";

    return true;
}
