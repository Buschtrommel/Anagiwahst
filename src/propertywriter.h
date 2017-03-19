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

#ifndef PROPERTYWRITER_H
#define PROPERTYWRITER_H

#include <QString>
#include <QCoreApplication>

/*!
 * \brief The PropertyWriter class
 */
class PropertyWriter
{
    Q_DECLARE_TR_FUNCTIONS(PropertyWriter)
public:
    PropertyWriter();
     ~PropertyWriter();

    enum WriteFileType {
        HeaderFile,
        PrivateHeaderFile,
        CodeFile
    };

    static bool write(WriteFileType type, QString path, const QString &className, const QString &data, bool forceOverwrite = false);
    static bool writeFile(const QString &fileName, const QString &data, bool forceOverwrite = false);
};

#endif // PROPERTYWRITER_H
