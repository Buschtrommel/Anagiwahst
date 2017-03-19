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
