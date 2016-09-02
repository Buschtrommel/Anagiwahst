#ifndef PROPERTY_P_H
#define PROPERTY_P_H

#include "property.h"

class PropertyPrivate
{
public:
    PropertyPrivate() :
        id(0),
        revision(0),
        designable(QStringLiteral("true")),
        scriptable(QStringLiteral("true")),
        stored(true),
        user(false),
        constant(false),
        final(false),
        privateClass(false),
        pointer(false),
        argsByRef(false)
    {}

    ~PropertyPrivate() {}

    int id;
    QString name;
    QString type;
    QString read;
    QString write;
    QString member;
    QString reset;
    QString notify;
    quint8 revision;
    QString designable;
    QString scriptable;
    bool stored;
    bool user;
    bool constant;
    bool final;
    QString brief;
    QString comment;
    bool privateClass;
    QString defaultValue;
    bool pointer;
    bool argsByRef;
};

#endif // PROPERTY_P_H
