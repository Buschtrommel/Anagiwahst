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

class Property;

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
    
    enum FunctionType {
        Getter,
        Setter,
        Resetter,
        Notifier
    };

private:
    void setIndent();
    QLatin1String getVariablePrefix(bool privateClass);
    QString getDefaultValue(const QString &type, bool pointer = false);
    QString getPointerMacro(bool constant = false, bool newLine = true);
    QString buildTableRow(const QString &firstCol, const QString &secondCol);
    
    QString buildClassComment();
    QString buildPropertyComment(const Property *prop);
    
    QString buildReadFunction(const Property *prop);
    QString buildWriteFunction(const Property *prop);
    QString buildResetFunction(const Property *prop);
    
    QString buildReadPrototype(const Property *prop);
    QString buildWritePrototype(const Property *prop);
    QString buildResetPrototype(const Property *prop);
    QString buildNotifyPrototype(const Property *prop);
    
    QString buildReadComment(const Property *prop);
    QString buildWriteComment(const Property *prop);
    QString buildResetComment(const Property *prop);
    QString buildNotifyComment(const Property *prop);
    QString buildSeeAlsoComment(const Property *prop, FunctionType ftype);
    
    QString buildPartOfStatement(const Property *prop);
    QString buildFuncArg(const Property *prop, bool notify = false);
    QString buildArg(const Property *prop, bool notify = false, bool forcePrefix = false);

    const QList<Property*> m_properties;
    int m_propertiesCount;
    QString m_className;
    QString m_indent;
    PropertyModel::ClassType m_type;
    int m_tabSize;
    PropertyModel::CommentsPosition m_commentsPosition;
    QString m_dc;
    const QStringList m_namespaces;
    QString m_headerProtector;
    bool m_privateClass;
    static const QList<FunctionType> m_functionTypes;
};

#endif // PROPERTYCREATOR_H
