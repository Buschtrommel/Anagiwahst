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

PropertyWriter::PropertyWriter()
{

}


PropertyWriter::~PropertyWriter()
{

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
