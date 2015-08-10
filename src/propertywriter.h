#ifndef PROPERTYWRITER_H
#define PROPERTYWRITER_H

#include <QString>
#include <QCoreApplication>

class PropertyWriter
{
    Q_DECLARE_TR_FUNCTIONS(PropertyWriter)

public:
    explicit PropertyWriter();
    ~PropertyWriter();

    enum WriteFileType {
        HeaderFile,
        PrivateHeaderFile,
        CodeFile
    };

    static bool write(WriteFileType type, QString path, const QString &className, const QString &data, bool forceOverwrite = false);
};

#endif // PROPERTYWRITER_H
