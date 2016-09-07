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

#ifndef PROPERTYCREATOR_H
#define PROPERTYCREATOR_H

#include <QString>
#include <QList>
#include <QStringList>
#include "propertymodel.h"

struct Property;

/*!
 * \brief The PropertyCreator class
 */
class PropertyCreator
{
public:
    PropertyCreator(const QList<Property*> &properties, const QString &className, PropertyModel::ClassType type = PropertyModel::PrivateClass, int tabSize = 4, PropertyModel::CommentsPosition commentsPosition = PropertyModel::InCode, const QStringList &namespaces = QStringList());
     ~PropertyCreator();

    QString createHeader();
    QString createPrivate();
    QString createCode();

private:
    void setIndent();
    QLatin1String getVariablePrefix(bool privateClass);
    QString getDefaultValue(const QString &type, bool pointer = false);
    QString getPointerMacro(bool constant = false, bool newLine = true);
    QString buildTableRow(const QString &firstCol, const QString &secondCol);
    
    QString buildClassComment();
    QString buildPropertyComment(Property *prop);
    
    QString buildReadFunction(Property *prop);
    QString buildWriteFunction(Property *prop);
    QString buildResetFunction(Property *prop);
    
    QString buildReadPrototype(Property *prop);
    QString buildWritePrototype(Property *prop);
    QString buildResetPrototype(Property *prop);
    QString buildNotifyPrototype(Property *prop);
    
    QString buildReadComment(Property *prop);
    QString buildWriteComment(Property *prop);
    QString buildResetComment(Property *prop);
    QString buildNotifyComment(Property *prop);
    
    QString buildPartOfStatement(Property *prop);
    QString buildFuncArg(Property *prop, bool notify = false);

    QList<Property*> m_properties;
    int m_propertiesCount;
    QString m_className;
    QString m_indent;
    int m_tabSize;
    PropertyModel::ClassType m_type;
    PropertyModel::CommentsPosition m_commentsPosition;
    QString m_dc;
    QStringList m_namespaces;
};

#endif // PROPERTYCREATOR_H
