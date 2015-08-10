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
    QTextStream errOut(stdout, QIODevice::WriteOnly);

    if (!forceOverwrite) {

        QDir destDir(path);

        QStringList filters;
        filters << className.toLower().append(".cpp");
        filters << className.toLower().append("_p.h");
        filters << className.toLower().append(".h");

        QStringList entries = destDir.entryList(filters, QDir::Files);

        if (!entries.isEmpty()) {

            errOut << tr("There are already files using the specified class name as file name. Use the -f option if you want to overwrite these files.") << "\n";
            errOut.flush();
            return false;
        }

    }


    if (!path.endsWith("/")) {
        path.append("/");
    }

    path.append(className.toLower());

    switch (type) {
    case HeaderFile:
        path.append(".h");
        break;
    case PrivateHeaderFile:
        path.append("_p.h");
        break;
    case CodeFile:
        path.append(".cpp");
        break;
    default:
        break;
    }

    QFile outFile(path);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << outFile.errorString();
        qFatal("Can not write to file.");
        return false;
    }

    QTextStream out(&outFile);
    out << data;
    out.flush();

    outFile.close();

    errOut << tr("Successfully wrote file %1").arg(path) << "\n";

    return true;
}
