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

#include "propertycreator.h"
#include "property.h"
#include <QtDebug>
#include <QStringBuilder>
#include <QRegularExpression>

const QList<PropertyCreator::FunctionType> PropertyCreator::m_functionTypes = {PropertyCreator::Getter, PropertyCreator::Setter, PropertyCreator::Resetter, PropertyCreator::Notifier};

PropertyCreator::PropertyCreator(const QList<Property *> &properties, const QString &className, PropertyModel::ClassType type, int tabSize, PropertyModel::CommentsPosition commentsPosition, const QStringList &namespaces) :
    m_properties(properties), m_className(className), m_type(type), m_tabSize(tabSize), m_commentsPosition(commentsPosition), m_namespaces(namespaces), m_privateClass(false)
{
#ifdef QT_DEBUG
    qDebug() << "Constructing a PropertyCreator for class" << m_className << "with an indent of" << m_tabSize;
#endif
    m_propertiesCount = m_properties.count();
    m_dc = QStringLiteral("::");
    
    if (!namespaces.isEmpty()) {
        for (const QString &ns : namespaces) {
            m_headerProtector.append(ns.toUpper());
        }
    }
    m_headerProtector.append(className.toUpper());
    
    if (!properties.isEmpty()) {
        for (const Property *p : properties) {
            if (p->privateClass()) {
                m_privateClass = true;
                break;
            }
        }
    }
    
    setIndent();
}


PropertyCreator::~PropertyCreator()
{
#ifdef QT_DEBUG
    qDebug() << "Destroying a PropertyCreator for class" << m_className;
#endif
}


QString PropertyCreator::createHeader()
{
    if (m_properties.isEmpty()) {
        return QString();
    }

    QString result;

    result += QLatin1String("#ifndef ") % m_headerProtector % QLatin1String("_H\n#define ") % m_headerProtector % QLatin1String("_H\n\n#include <QObject>\n");

    if (m_type == PropertyModel::SharedData && m_privateClass) {
        result += QLatin1String("#include <QSharedDataPointer>\n");
    }

    if (!m_namespaces.isEmpty()) {
        result += QLatin1String("\n");
        for (int i = 0; i < m_namespaces.count(); ++i) {
            result += QLatin1String("namespace ") % m_namespaces.at(i) % QLatin1String(" {\n");
        }
        result += QLatin1String("\n\n");
    }

    result += QLatin1String("");

    if (m_commentsPosition == PropertyModel::InFronOfHeader) {

        result += QLatin1String("\n\n") % buildClassComment() % QLatin1String("\n\n");

        for (const Property *p : m_properties) {

            result += buildPropertyComment(p);

            if (!p->read().isEmpty()) {
                result += buildReadComment(p) % QLatin1String("\n");
            }

            if (!p->write().isEmpty()) {
                result += buildWriteComment(p) % QLatin1String("\n");
            }

            if (!p->reset().isEmpty()) {
                result += buildResetComment(p) % QLatin1String("\n");
            }

            if (!p->notify().isEmpty()) {
                result += buildNotifyComment(p) % QLatin1String("\n");
            }

            result += QLatin1String("\n\n");
        }

        result += QLatin1String("\n\n\n");
    }

    result += QLatin1String("\n");

    if (m_privateClass) {
        result += QLatin1String("class ") % m_className % QLatin1String("Private;\n\n");
    }

    if (m_commentsPosition != PropertyModel::InFronOfHeader) {
        result += buildClassComment();
    }

    result += QLatin1String("class ") % m_className % QLatin1String(" : public QObject\n{\n") % m_indent % QLatin1String("Q_OBJECT\n");

    for (const Property *p : m_properties) {

        if (m_commentsPosition == PropertyModel::InHeader) {
            result += buildPropertyComment(p);
        }

        result += m_indent % QLatin1String("Q_PROPERTY(") % p->type() % QLatin1String(" ");

        if (p->pointer()) {
            result += QLatin1String("*");
        }

        result += p->name();

        if (!p->member().isEmpty()) {
            result += QLatin1String(" MEMBER ") % p->member();
        }

        if (!p->read().isEmpty()) {
            result += QLatin1String(" READ ") % p->read();
        }

        if (!p->write().isEmpty()) {
            result += QLatin1String(" WRITE ") % p->write();
        }

        if (!p->reset().isEmpty()) {
            result += QLatin1String(" RESET ") % p->reset();
        }

        if (!p->notify().isEmpty()) {
            result += QLatin1String(" NOTIFY ") % p->notify();
        }

        if (p->revision() > 0) {
            result += QLatin1String(" REVISION ") % QString::number(p->revision());
        }

        if (p->designable() != QLatin1String("true")) {
            result += QLatin1String(" DESIGNABLE ") % p->designable();
        }

        if (p->scriptable() != QLatin1String("true")) {
            result += QLatin1String(" SCRIPTABLE ") % p->scriptable();
        }

        if (!p->stored()) {
            result += QLatin1String(" STORED false");
        }

        if (p->user()) {
            result += QLatin1String(" USER true");
        }

        if (p->constant()) {
            result += QLatin1String(" CONSTANT");
        }

        if (p->final()) {
            result += QLatin1String(" FINAL");
        }

        result += QLatin1String(")\n");
    }

    result += QLatin1String("public:\n");
    
    
    // build the default constructor
    
    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent % QLatin1String("/*!\n") % m_indent % QLatin1String(" * \\brief Constructs a new ") % m_className % QLatin1String(" object with default values and the given \\a parent.\n") % m_indent % QLatin1String(" */\n");
    }
    
    result += m_indent % QLatin1String("explicit ") % m_className % QLatin1String("(QObject *parent = nullptr);\n\n");
    
    
    
    
    
    // Start building an overloaded constructor with all properties as arguments.
    
    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent % QLatin1String("/*!\n") % m_indent % QLatin1String(" * \\brief Constructs a new ") % m_className % QLatin1String(" object with the given arguments and \\a parent.\n") % m_indent % QLatin1String(" */\n");
    }
    
    result += m_indent;
    
    if (m_properties.count() == 1) {
        result += QLatin1String("explicit ");
    }
    
    result += m_className % QLatin1String("(");
    
    QStringList overloadArgs;
    
    for (const Property *p : m_properties) {
        overloadArgs.append(buildArg(p, true));
    }
    
    result += overloadArgs.join(QStringLiteral(", "));
    
    result += QLatin1String(", QObject *parent = nullptr);\n\n");
    
    
    
    
    
    
    // build the destrcutor
    
    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent % QLatin1String("/*!\n") % m_indent % QLatin1String(" * \\brief Deconstructs the ") % m_className % QLatin1String(" object.\n") % m_indent % QLatin1String(" */\n");
    }
    
    result += m_indent % QLatin1String("~") % m_className % QLatin1Literal("();\n\n");
    
    
    

    // Start building the get funciton in the public part of the header file

    for (const Property *p : m_properties) {

        if (!p->read().isEmpty()) {
            if (m_commentsPosition == PropertyModel::InHeader) {
                result += buildReadComment(p);
            }
            result += buildReadPrototype(p);
        }

    }

    result += QLatin1String("\n");

    // Start building the set function in the public part of the header file.

    for (const Property *p : m_properties) {

        if (!p->write().isEmpty()) {
            if (m_commentsPosition == PropertyModel::InHeader) {
                result += buildWriteComment(p);
            }
            result += buildWritePrototype(p);

        }

    }

    result += QLatin1String("\n");

    // Start building the reset function in the public part of the header file.

    for (const Property *p : m_properties) {

        if (!p->reset().isEmpty()) {
            if (m_commentsPosition == PropertyModel::InHeader) {
                result += buildResetComment(p);
            }
            result += buildResetPrototype(p);
        }
    }

    result += QLatin1String("\n");

    // Start building the notify functions in the signal part of the header file.

    result += QLatin1String("Q_SIGNALS:\n");

    for (const Property *p : m_properties) {

        if (!p->notify().isEmpty()) {
            if (m_commentsPosition == PropertyModel::InHeader) {
                result += buildNotifyComment(p);
            }
            result += buildNotifyPrototype(p);
        }

    }

    result += QLatin1String("\n");

	// Start building the protected member section.

	if (m_privateClass) {
		result += QLatin1String("protected:\n");

        switch (m_type) {
        case PropertyModel::PrivateClass:
            result += m_indent % QLatin1String("const QScopedPointer<") % m_className % QLatin1String("Private> d_ptr;\n");
            break;
        case PropertyModel::SharedData:
            result += m_indent % QLatin1String("QSharedDataPointer<") % m_className % QLatin1String("Private> d;\n");
            break;
        default:
            break;
        }

        result += QLatin1String("\n");
    }

    // Start building the private variables section.

    result += QLatin1String("private:\n") % m_indent % QLatin1String("Q_DISABLE_COPY(") % m_className % QLatin1String(")\n");

	if (m_type == PropertyModel::PrivateClass && m_privateClass) {
        result += m_indent % QLatin1String("Q_DECLARE_PRIVATE(") % m_className % QLatin1String(")\n");
    }

    for (const Property *p : m_properties) {

        if (!p->privateClass()) {
            result += m_indent % p->type();
            if (p->pointer()) {
                result += QLatin1String(" *m_");
            } else {
                result += QLatin1String(" m_");
            }
            result += p->name() % QLatin1String(";\n");
        }
    }

    result += QLatin1String("\n};");

    if (!m_namespaces.isEmpty()) {
        result += QLatin1String("\n\n");

        for (int i = 0; i < m_namespaces.size(); ++i) {
            result += QLatin1String("}\n");
        }
    }

    result += QLatin1String("\n\n#endif // ") % m_headerProtector % QLatin1String("_H\n");

    return result;
}





QString PropertyCreator::createPrivate()
{
    if (!m_privateClass) {
        return QString();
    }
    
    if (m_properties.isEmpty()) {
        return QString();
    }

    bool defaultValuePresent = false;
    
    for (const Property *p : m_properties) {
        if (!p->defaultValue().isEmpty()) {
            defaultValuePresent = true;
            break;
        }
    }

    QString result = QLatin1String("");

    result += QLatin1String("#ifndef ") % m_headerProtector % QLatin1String("_P_H\n#define ") % m_headerProtector % QLatin1String("_P_H\n\n");

    if (m_type == PropertyModel::SharedData) {
        result += QLatin1String("#include <QSharedData>\n");
    }

    result += QLatin1String("#include \"") % m_className.toLower() % QLatin1String(".h\"\n\n");

    if (!m_namespaces.isEmpty()) {
        for (int i = 0; i < m_namespaces.count(); ++i) {
            result += QLatin1String("namespace ") % m_namespaces.at(i) % QLatin1String(" {\n");
        }
        result += QLatin1String("\n\n");
    }

    result += QLatin1String("class ") % m_className % QLatin1String("Private");

    if (m_type == PropertyModel::SharedData) {
        result += QLatin1String(" : public QSharedData");
    }

    result += QLatin1String("\n{\npublic:\n");

    QString x2Indent;
    x2Indent += m_indent % m_indent;

    result += m_indent % m_className % QLatin1String("Private()");
    
    
    

    if (defaultValuePresent) {
        result += QLatin1String(" :\n");
        
        for (const Property *p : m_properties) {
            
            if (p->privateClass() && !p->defaultValue().isEmpty()) {
                result += x2Indent % p->name() % QLatin1String("(") % p->defaultValue() % QLatin1String("),\n");
            }
            
        }

        result.chop(2);
        result += QLatin1String("\n") % m_indent % QLatin1String("{}\n\n");

    } else {
        result += QLatin1String(" {}\n\n");
    }
    
    
    
    // create overloaded constructor containing all properties as arguments
    
    
    result += m_indent;
    
    if (m_properties.count() == 1) {
        result += QLatin1String("explicit ");
    }
    
    result += m_className %  QLatin1String("Private(");
    
    QStringList overloadArgs;
    
    for (const Property *p : m_properties) {
        if (p->privateClass()) {
            overloadArgs.append(buildArg(p, false, true));
        }
    }
    
    result += overloadArgs.join(QStringLiteral(", "));
    
    result += QLatin1String(") :\n");
    
    for (const Property *p : m_properties) {
        
        if (p->privateClass()) {
            QString un = p->name();
            un[0] = un[0].toUpper();
            result += x2Indent % p->name() % QLatin1String("(n") % un % QLatin1String("),\n");
        }        
    }
    
    result.chop(2);
    result += QLatin1String("\n") % m_indent % QLatin1String("{}\n\n");
    

    if (m_type == PropertyModel::SharedData) {

        result += m_indent % m_className % QLatin1String("Private(const ") % m_className % QLatin1String("Private &other) :\n") % x2Indent % QLatin1String("QSharedData(other),\n");
        
        for (const Property *p : m_properties) {
            
            if (p->privateClass()) {
                result += x2Indent % p->name() % QLatin1String("(other.") % p->name() % QLatin1String("),\n");
            }
            
        }

        result.chop(2);
        result += QLatin1String("\n") % m_indent % QLatin1String("{}\n\n");
    }

    result += m_indent % QLatin1String("~") % m_className % QLatin1String("Private() {}\n\n");
    
    for (const Property *p : m_properties) {
        
        if (p->privateClass()) {
            result += m_indent % p->type() % QLatin1String(" ");
            
            if (p->pointer()) {
                result += QLatin1String("*");
            }
            
            result += p->name() % QLatin1String(";\n");
        }
        
    }

    result += QLatin1String("};\n\n");

    if (!m_namespaces.isEmpty()) {

        for (int i = 0; i < m_namespaces.size(); ++i) {
            result += QLatin1String("}\n");
        }
        result += QLatin1String("\n");
    }

    result += QLatin1String("#endif // ") % m_headerProtector % QLatin1String("_P_H\n");

    return result;
}





QString PropertyCreator::createCode()
{
    if (m_properties.isEmpty()) {
        return QString();
    }


    QString doubleIndent = m_indent % m_indent;

    QString result = QLatin1String("");

    result += QLatin1String("#include \"") % m_className.toLower();
    if (m_privateClass) {
        result += QLatin1String("_p.h\"\n");
    } else {
        result += QLatin1String(".h\"\n");
    }

    result += QLatin1String("#ifdef QT_DEBUG\n#include <QtDebug>\n#endif\n\n");

    if (!m_namespaces.isEmpty()) {
        for (int i = 0; i < m_namespaces.size(); ++i) {
            result += QLatin1String("using namespace ") % m_namespaces.at(i) % QLatin1String(";\n");
        }
        result += QLatin1String("\n");
    }

    if (m_commentsPosition == PropertyModel::InCode) {
        result += QLatin1String("/*!\n * \\brief Constructs a new ") % m_className % QLatin1String(" object with default values and the given \\a parent.\n */\n");
    }

    result += m_className % m_dc % m_className % QLatin1String("(QObject *parent) :\n") % m_indent % QLatin1String("QObject(parent)");

    if (m_privateClass && m_type == PropertyModel::PrivateClass) {
        result += QLatin1String(", d_ptr(new ") % m_className % QLatin1String("Private)\n");
    } else {
        result += QLatin1String("\n");
    }

    result += QLatin1String("{\n");

    if (m_privateClass && m_type == PropertyModel::SharedData) {
        result += m_indent % QLatin1String("d = new ") % m_className % QLatin1String("Private;\n");
    }

    for (const Property *p : m_properties) {


        if (!p->privateClass() && !p->defaultValue().isEmpty()) {

            result += m_indent % getVariablePrefix(p->privateClass()) % p->name() % QLatin1String(" = ") % p->defaultValue() % QLatin1String(";\n");

        }

    }

    result += QLatin1String("}\n\n\n");
    
    
    // build an overloaded constructor
    
    if (m_commentsPosition == PropertyModel::InCode) {
        result += QLatin1String("/*!\n * \\brief Constructs a new ") % m_className % QLatin1String(" object with the given arguments and \\a parent.\n */\n");
    }
    
    result += m_className % m_dc % m_className % QLatin1String("(");
    
    QStringList overloadArgs;
    
    for (const Property *p : m_properties) {
        overloadArgs.append(buildArg(p, true));
    }
    
    result += overloadArgs.join(QStringLiteral(", "));
    
    result += QLatin1String(", QObject *parent) :\n") % m_indent % QLatin1String("QObject(parent)");
    
    if (m_privateClass && m_type == PropertyModel::PrivateClass) {
        result += QLatin1String(", d_ptr(new ") % m_className % QLatin1String("Private(");
        
        QStringList privInitList;
        for (const Property *p : m_properties) {
            if (p->privateClass()) {
                privInitList.append(p->name());
            }
        }
        
        if (!privInitList.isEmpty()) {
            result += privInitList.join(QStringLiteral(", ")) % QLatin1String(")");
        }
        
        result += QLatin1String(")");
    }
    
    QStringList localPrivs;
    for (const Property *p : m_properties) {
        if (!p->privateClass()) {
            
            QString s(QStringLiteral("m_"));
            s += p->name() % QLatin1String("(") % p->name() % QLatin1String(")");
            localPrivs.append(s);
        }
    }
    
    if (!localPrivs.isEmpty()) {
        result += QLatin1String(", ");
        result += localPrivs.join(", ");
    }
    
    result += QLatin1String("\n{\n}\n\n\n");
    
    
    
    // build the destructor
    
    if (m_commentsPosition == PropertyModel::InCode) {
        result += QLatin1String("/*!\n * \\brief Deconstructs the ") % m_className % QLatin1String(" object.\n */\n");
    }

    result += m_className % QLatin1String("::~") % m_className % QLatin1String("()\n{\n");

    result += QLatin1String("}\n\n\n");
    
    


    for (const Property *p : m_properties) {

        // prepared stuff
        QLatin1String varPrefix = getVariablePrefix(p->privateClass());


        if (m_commentsPosition == PropertyModel::InCode) {

            result += buildPropertyComment(p);

        }


        if (!p->notify().isEmpty() && m_commentsPosition == PropertyModel::InCode) {

            result += buildNotifyComment(p) % QLatin1String("\n");

        }


        if (!p->read().isEmpty()) {

            if (m_commentsPosition == PropertyModel::InCode) {
                result += buildReadComment(p);
            }


            result += p->type();

            if (p->pointer()) {
                result += QLatin1String(" *");
            } else {
                result += QLatin1String(" ");
            }


            result += m_className % m_dc % buildReadFunction(p) % QLatin1String(" { ");

            if (p->privateClass() && m_type == PropertyModel::PrivateClass) {
                result += getPointerMacro(true, false);
            }

            result += QLatin1String("return ") % varPrefix % p->name() % QLatin1String("; }\n\n");
        }



        if (!p->write().isEmpty()) {

            if (m_commentsPosition == PropertyModel::InCode) {
                result += buildWriteComment(p);
            }

            QString argName = p->name();

            if (p->name() == p->read()) {
                argName[0] = argName[0].toUpper();
                argName.prepend(QLatin1String("n"));
            }

            result += QLatin1String("void ") % m_className % m_dc % buildWriteFunction(p) % QLatin1String("\n{\n");

            if (p->privateClass() && m_type == PropertyModel::PrivateClass) {
                result += m_indent % getPointerMacro();
            }

            if (!p->notify().isEmpty()) {

                result += m_indent % QLatin1String("if (") % argName % QLatin1String(" != ") % varPrefix % p->name() % QLatin1String(") {\n");

                result += doubleIndent % varPrefix % p->name() % QLatin1String(" = ") % argName % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % doubleIndent % QLatin1String("qDebug() << \"Changed ") % p->name() % QLatin1String(" to\" << ") % varPrefix % p->name() % QLatin1String(";\n#endif\n");

                result += doubleIndent % QLatin1String("Q_EMIT ") % p->notify() % QLatin1String("(");

                if (!p->read().isEmpty()) {
                    result += p->read() % QLatin1String("()");
                } else {
                    result += varPrefix % p->name();
                }

                result += QLatin1String(");\n") % m_indent % QLatin1String("}\n");

            } else {

                result += m_indent % varPrefix % p->name() % QLatin1String(" = ") % p->name() % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % m_indent % QLatin1String("qDebug() << \" Set ") % p->name() % QLatin1String(" to\" << ") % varPrefix % p->name() % QLatin1String(";\n#endif\n");

            }

            result += QLatin1String("}\n\n");

        }






        if (!p->reset().isEmpty()) {

            if (m_commentsPosition == PropertyModel::InCode) {
                result += buildResetComment(p);
            }

            result += QLatin1String("void ") % m_className % m_dc % buildResetFunction(p) % QLatin1String("\n{\n");

            if (p->privateClass()) {
                result += m_indent % getPointerMacro();
            }

            QString defValue = p->defaultValue().isEmpty() ? getDefaultValue(p->type(), p->pointer()) : p->defaultValue();


            if (!p->notify().isEmpty()) {

                result += m_indent % QLatin1String("if (") % defValue % QLatin1String(" != ") % varPrefix % p->name() % QLatin1String(") {\n");

                result += doubleIndent % varPrefix % p->name() % QLatin1String(" = ") % defValue % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % doubleIndent % QLatin1String("qDebug() << \"Reset ") % p->name() % QLatin1String(" to its default value\" << ") % defValue % QLatin1String(";\n#endfi\n");

                result += doubleIndent % QLatin1String("Q_EMIT ") % p->notify() % QLatin1String("(");

                if (!p->read().isEmpty()) {
                    result += p->read() % QLatin1String("()");
                } else {
                    result += varPrefix % p->name();
                }

                result += QLatin1String(");\n") % m_indent % QLatin1String("}\n");


            } else {

                result += m_indent % varPrefix % p->name() % QLatin1String(" = ") % defValue % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % doubleIndent % QLatin1String("qDebug() << \"Reset ") % p->name() % QLatin1String(" to its default value\" << ") % defValue % QLatin1String(";\n#endfi\n");

            }

            result += QLatin1String("}\n\n");

        }



        result += QLatin1String("\n\n\n");

    }

    return result;
}



QString PropertyCreator::getPointerMacro(bool constant, bool newLine)
{
    QString result = QStringLiteral("Q_D(");

    if (constant) {
        result += QLatin1String("const ");
    }

    result += m_className % QLatin1String("); ");

    if (newLine) {
        result += QLatin1String("\n");
    }

    return result;
}



QLatin1String PropertyCreator::getVariablePrefix(bool privateClass)
{
    return privateClass ? QLatin1String("d->") : QLatin1String("m_");
}



QString PropertyCreator::getDefaultValue(const QString &type, bool pointer)
{
    if (pointer) {
        return QStringLiteral("nullptr");
    }

    QStringList ints = {QStringLiteral("unsigned char"), QStringLiteral("signed char"), QStringLiteral("short"), QStringLiteral("short int"), QStringLiteral("signed short"), QStringLiteral("signed short int"), QStringLiteral("unsigned short"), QStringLiteral("unsigned short int"), QStringLiteral("int"), QStringLiteral("signed"), QStringLiteral("signed int"), QStringLiteral("unsigned int"), QStringLiteral("long"), QStringLiteral("long int"), QStringLiteral("signed long"), QStringLiteral("signed long int"), QStringLiteral("unsigned long"), QStringLiteral("unsigned long int"), QStringLiteral("long long"), QStringLiteral("long long int"), QStringLiteral("signed long long"), QStringLiteral("signed long long int"), QStringLiteral("unsigned long long"), QStringLiteral("unsigned long long int"), QStringLiteral("qint8"), QStringLiteral("qint16"), QStringLiteral("qint32"), QStringLiteral("qint64"), QStringLiteral("qintptr"), QStringLiteral("qlonglong"), QStringLiteral("quint8"), QStringLiteral("quint16"), QStringLiteral("quint32"), QStringLiteral("quint64"), QStringLiteral("quintptr"), QStringLiteral("qulonglong"), QStringLiteral("uchar"), QStringLiteral("uint"), QStringLiteral("ulong"), QStringLiteral("ushort")};

    QStringList floats = {QStringLiteral("float"), QStringLiteral("double"), QStringLiteral("long double"), QStringLiteral("qreal")};

    if (ints.contains(type, Qt::CaseInsensitive)) {
        return QStringLiteral("0");
    } else if (floats.contains(type, Qt::CaseInsensitive)) {
        return QStringLiteral("0.0");
    } else if (type == QLatin1String("QString")) {
        return QStringLiteral("QStringLiteral(\"\")");
    } else if (type == QLatin1String("bool")) {
        return QStringLiteral("false");
    } else {
        QString result = type % QLatin1String("()");
        return result;
    }
}



void PropertyCreator::setIndent()
{
    switch(m_tabSize) {
    case 1:
        m_indent = QStringLiteral(" ");
        break;
    case 2:
        m_indent = QStringLiteral("  ");
        break;
    case 3:
        m_indent = QStringLiteral("   ");
        break;
    case 4:
        m_indent = QStringLiteral("    ");
        break;
    case 5:
        m_indent = QStringLiteral("     ");
        break;
    case 6:
        m_indent = QStringLiteral("      ");
        break;
    default:
        m_indent = QString();
        break;
    }
}




QString PropertyCreator::buildTableRow(const QString &firstCol, const QString &secondCol)
{
    QString result;

    result = QLatin1String("<TR><TD>") % firstCol % QLatin1String("</TD><TD>") % secondCol % QLatin1String("</TD></TR>");

    return result;
}




QString PropertyCreator::buildClassComment()
{
    QString result = QStringLiteral("/*!\n");
    if (m_commentsPosition == PropertyModel::InFronOfHeader) {
        result += QLatin1String(" * \\class ") % m_className % QLatin1String("\n");
    }
    result += QLatin1String(" * \\brief The ") % m_className % QLatin1String(" class.\n */\n");
    return result;
}



QString PropertyCreator::buildPropertyComment(const Property *prop)
{
    QString result = QLatin1String("");

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }

    result += QStringLiteral("/*!\n");

    if (m_commentsPosition != PropertyModel::InHeader) {
        result += QLatin1String(" * \\property ") % m_className % m_dc % prop->name() % QLatin1String("\n");
    }

    if (prop->brief().isEmpty() && prop->comment().isEmpty()) {

        if (m_commentsPosition == PropertyModel::InHeader) {
            result += m_indent % QLatin1String(" * \\brief The ") % prop->name() % QLatin1String(" property.\n") % m_indent % QLatin1String(" *\n");
        } else {
            result += QLatin1String(" * \\brief The ") % prop->name() % QLatin1String(" property.\n *\n");
        }

    } else {

        if (!prop->brief().isEmpty()) {
            if (m_commentsPosition == PropertyModel::InHeader) {
                result += m_indent % QLatin1String(" * \\brief ") % prop->brief() % QLatin1String("\n") % m_indent % QLatin1String(" *\n");
            } else {
                result += QLatin1String(" * \\brief ") % prop->brief() % QLatin1String("\n *\n");
            }
        }

        if (!prop->comment().isEmpty()) {
            if (prop->brief().isEmpty()) {
                if (m_commentsPosition == PropertyModel::InHeader) {
                    result += m_indent;
                }
                result += QLatin1String(" *\n");
            }

            if (!prop->comment().isEmpty()) {
                if (prop->brief().isEmpty()) {
                    if (m_commentsPosition == PropertyModel::InHeader) {
                        result += m_indent;
                    }
                    result += QLatin1String(" *\n");
                }

                if (prop->comment().size() > 100) {
                    QStringList paragraphs = prop->comment().split(QRegularExpression(QStringLiteral("\\n")), QString::SkipEmptyParts);

                    for (int i = 0; i < paragraphs.size(); ++i) {

                        if (m_commentsPosition == PropertyModel::InHeader) {
                            result += m_indent;
                        }

                        result += QLatin1String(" * ");

                        int combinedSize = 0;

                        QStringList words = paragraphs.at(i).split(' ');

                        for (int j = 0; j < words.size(); ++j) {

                            if (combinedSize < 100) {
                                result += words.at(j) % QLatin1String(" ");
                                combinedSize += words.at(j).size()+1;
                            } else {
                                result += QLatin1String("\n * ") % words.at(j);
                                combinedSize = 0;
                                combinedSize += words.at(j).size()+1;
                            }

                        }

                    }

                    if (m_commentsPosition == PropertyModel::InHeader) {
                        result += m_indent % QLatin1String("\n") % m_indent % QLatin1String(" *\n");
                    } else {
                        result += QLatin1String("\n *\n");
                    }

                }

            } else {

                if (m_commentsPosition == PropertyModel::InHeader) {
                    result += m_indent % QLatin1String(" * ") % prop->comment() % QLatin1String("\n") % m_indent % QLatin1String(" *\n");
                } else {
                    result += QLatin1String(" * ") % prop->comment() % QLatin1String("\n *\n");
                }
            }
        }
    }

    if (!prop->read().isEmpty() || !prop->write().isEmpty() || !prop->reset().isEmpty()) {

        if (m_commentsPosition == PropertyModel::InHeader) {
            result += m_indent % QLatin1String(" * \\par Access functions:\n") % m_indent % QLatin1String(" * <TABLE>");
        } else {
            result += QLatin1String(" * \\par Access functions:\n * <TABLE>");
        }

        if (!prop->read().isEmpty()) {
            if (prop->pointer()) {
                result += buildTableRow(prop->type() % QStringLiteral("*"), buildReadFunction(prop));
            } else {
                result += buildTableRow(prop->type(), buildReadFunction(prop));
            }
        }

        if (!prop->write().isEmpty()) {
            result += buildTableRow(QStringLiteral("void"), buildWriteFunction(prop));
        }

        if (!prop->reset().isEmpty()) {
            result += buildTableRow(QStringLiteral("void"), buildResetFunction(prop));
        }

        result += QLatin1String("</TABLE>\n");
    }

    if (!prop->notify().isEmpty()) {

        if (m_commentsPosition == PropertyModel::InHeader) {
            result += m_indent % QLatin1String(" * \\par Notifier signal:\n") % m_indent % QLatin1String(" * <TABLE>");
        } else {
            result += QLatin1String(" * \\par Notifier signal:\n * <TABLE>");
        }

//         if (prop->pointer) {
//             result += buildTableRow(QStringLiteral("void"), prop->notify() % QLatin1String("(") % prop->type() % QLatin1String(" * ") % prop->name() % QLatin1String(")"));
//         } else {
//             result += buildTableRow(QStringLiteral("void"), prop->notify() % QLatin1String("(const ") % prop->type() % QLatin1String(" & ") % prop->name() % QLatin1String(")"));
//         }
        result += buildTableRow(QStringLiteral("void"), prop->notify() % buildFuncArg(prop, true));

        result += QLatin1String("</TABLE>\n");

    }

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }

    result += QLatin1String(" */\n");

    if (m_commentsPosition != PropertyModel::InHeader) {
        result += QLatin1String("\n");
    }

    return result;
}



QString PropertyCreator::buildReadFunction(const Property *prop)
{
    QString readFunc = prop->read() % QLatin1String("() const");

    return readFunc;
}



QString PropertyCreator::buildWriteFunction(const Property *prop)
{
    QString writeFunc;

//     if (prop->pointer) {
//         writeFunc = prop->write % QLatin1String("(") % prop->type % QLatin1String(" * ") % prop->name % QLatin1String(")");
//     } else {
//         writeFunc = prop->write % QLatin1String("(const ") % prop->type % QLatin1String(" & ") % prop->name % QLatin1String(")");
//     }
    writeFunc = prop->write() % buildFuncArg(prop);

    return writeFunc;
}




QString PropertyCreator::buildResetFunction(const Property *prop)
{
    QString resetFunc = prop->reset() % QLatin1String("()");

    return resetFunc;
}



QString PropertyCreator::buildPartOfStatement(const Property *prop)
{
    if (m_commentsPosition == PropertyModel::InHeader) {
        QString partOf = m_indent % QLatin1String(" * \\brief Part of the \\link ") % m_className % m_dc % prop->name() % QLatin1String(" ") % prop->name() % QLatin1String(" \\endlink property.\n") % m_indent;
        return partOf;
    } else {
        QString partOf = QLatin1String(" * \\brief Part of the \\link ") % m_className % m_dc % prop->name() % QLatin1String(" ") % prop->name() % QLatin1String(" \\endlink property.\n");
        return partOf;
    }
}



QString PropertyCreator::buildReadComment(const Property *prop)
{
    QString result;

    if (!prop->documentMethods()) {
        return result;
    }

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }

    result += QLatin1String("/*!\n");

    if (m_commentsPosition == PropertyModel::InFronOfHeader) {
        result += QLatin1String(" * \\fn ") % prop->type();
        if (prop->pointer()) {
            result += QLatin1String(" *");
        } else {
            result += QLatin1String(" ");
        }

        result += m_className % m_dc % prop->read() % QLatin1String("()\n");
    }
    
    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }
    
    result += QLatin1String(" * \\brief Getter function for the \\link ") % m_className % m_dc % prop->name() % QLatin1String(" ") % prop->name() % QLatin1String(" \\endlink property.\n");
    result += buildSeeAlsoComment(prop, Getter);
    
    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }
    
    result += QLatin1String(" */\n"); 

    return result;
}



QString PropertyCreator::buildWriteComment(const Property *prop)
{
    QString result;

    if (!prop->documentMethods()) {
        return result;
    }

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }

    result += QLatin1String("/*!\n");

    if (m_commentsPosition == PropertyModel::InFronOfHeader) {
        result += QLatin1String(" * \\fn void ") % m_className % m_dc % prop->write() % buildFuncArg(prop) % QLatin1String("\n");
    }
    
    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }

    result += QLatin1String(" * \\brief Setter function for the \\link ") % m_className % m_dc % prop->name() % QLatin1String(" ") % prop->name() % QLatin1String(" \\endlink property.\n");
    
    if (!prop->notify().isEmpty()) {
    
        if (m_commentsPosition == PropertyModel::InHeader) {
            result += m_indent;
        }
        
        QString an = prop->name();
        
        if (prop->name() == prop->read()) {
            an[0] = an[0].toUpper();
            an.prepend(QChar('n'));
        }
        
        result += QLatin1String(" * Emits the ") % prop->notify() % QLatin1String("() signal if \\a ") % an % QLatin1String(" is not equal to the stored value.\n");
    
    }
    
    result += buildSeeAlsoComment(prop, Setter);
    
    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }
    
    result += QLatin1String(" */\n"); 

    return result;
}



QString PropertyCreator::buildResetComment(const Property *prop)
{
    QString result;

    if (!prop->documentMethods()) {
        return result;
    }

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }

    result += QLatin1String("/*!\n");

    if (m_commentsPosition == PropertyModel::InFronOfHeader) {
        result += QLatin1String(" * \\fn void ") % m_className % m_dc % prop->reset() % QLatin1String("()\n");
    }

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }
    
    result += QLatin1String(" * \\brief Resets the \\link ") % m_className % m_dc % prop->name() % QLatin1String(" ") % prop->name() % QLatin1String(" \\endlink property to the default value.\n");
    
    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }
    
    result += QLatin1String(" * If the default value is not euqal to the stored value, the ") % prop->notify() % QLatin1String("() signal will be emitted.\n");
    
    result += buildSeeAlsoComment(prop, Resetter);
    
    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }
    
    result += QLatin1String(" */\n"); 

    return result;
}


QString PropertyCreator::buildNotifyComment(const Property *prop)
{
    QString result;

    if (!prop->documentMethods()) {
        return result;
    }

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent % QLatin1String("/*!\n");
    } else {
        result += QLatin1String("/*!\n");
    }

    if (m_commentsPosition != PropertyModel::InHeader) {
        result += QLatin1String(" * \\fn void ") % m_className % m_dc % prop->notify() % buildFuncArg(prop, true) % QLatin1String("\n");
    }
    
    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }

    result += QLatin1String(" * \\brief This is emitted if the value of the \\link ") % m_className % m_dc % prop->name() % QLatin1String(" ") % prop->name() % QLatin1String(" \\endlink property changes.\n");
    
    result += buildSeeAlsoComment(prop, Notifier);
    
    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }
    
    result += QLatin1String(" */\n"); 

    return result;
}


QString PropertyCreator::buildSeeAlsoComment(const Property *prop, FunctionType ftype)
{
    QString result;
    
    QStringList saList;
    
    for (FunctionType ft : m_functionTypes) {
        if (ft != ftype) {
            QString s(m_className);
            s += m_dc;
            switch(ft) {
                case Getter:
                    s += prop->read();
                    break;
                case Setter:
                    s += prop->write();
                    break;
                case Resetter:
                    s += prop->reset();
                    break;
                case Notifier:
                    s += prop->notify();
                    break;
            }
            s += QLatin1String("()");
            switch(ft) {
                case Getter:
                    if (!prop->read().isEmpty()) {
                        saList.append(s);
                    }
                    break;
                case Setter:
                    if (!prop->write().isEmpty()) {
                        saList.append(s);
                    }
                    break;
                case Resetter:
                    if (!prop->reset().isEmpty()) {
                        saList.append(s);
                    }
                    break;
                case Notifier:
                    if (!prop->notify().isEmpty()) {
                        saList.append(s);
                    }
                    break;
            }
            
        }
    }
    
    if (!saList.isEmpty()) {
    
        if (m_commentsPosition == PropertyModel::InHeader) {
            result += m_indent;
        }
        
        result += QLatin1String(" * \\sa ") % saList.join(QStringLiteral(", ")) % QLatin1String("\n");
    
    }
    
    return result;
}



QString PropertyCreator::buildWritePrototype(const Property *prop)
{
    QString result = m_indent % QLatin1String("void ") % prop->write() % buildFuncArg(prop) % QLatin1String(";\n");

    return result;
}



QString PropertyCreator::buildReadPrototype(const Property *prop)
{
    QString result;

    result += m_indent % prop->type() % QLatin1String(" ");

    if (prop->pointer()) {
        result += QLatin1String("*");
    }

    result += prop->read() % QLatin1String("() const;\n");

    return result;
}


QString PropertyCreator::buildResetPrototype(const Property *prop)
{
    QString result = m_indent % QLatin1String("void ") % prop->reset() % QLatin1String("();\n");

    return result;
}


QString PropertyCreator::buildNotifyPrototype(const Property *prop)
{
    QString result = m_indent % QLatin1String("void ") % prop->notify() % buildFuncArg(prop, true) % QLatin1String(";\n");

    return result;
}




QString PropertyCreator::buildFuncArg(const Property *prop, bool notify)
{
    QString result = QStringLiteral("(");
    
    result.append(buildArg(prop, notify));
    
    result.append(QStringLiteral(")"));
    
    

//     if (!prop->pointer() && prop->argsByRef()) {
//         result += QLatin1String("const ");
//     }
// 
//     result += prop->type();
// 
//     if (!prop->pointer()) {
//         if (!prop->argsByRef()) {
//             result += ' ';
//         } else {
//             result += QLatin1String(" &");
//         }
//     } else {
//         result += QLatin1String(" *");
//     }
// 
//     if ((prop->name() != prop->read()) || notify) {
//         result += prop->name() % QLatin1String(")");
//     } else {
//         QString name = prop->name();
//         name[0] = name[0].toUpper();
//         name.prepend(QLatin1String("n"));
//         result += name % QLatin1String(")");
//     }

    return result;
}


QString PropertyCreator::buildArg(const Property *prop, bool notify, bool forcePrefix)
{
    QString result;
    
    if (!prop->pointer() && prop->argsByRef()) {
        result += QLatin1String("const ");
    }

    result += prop->type();

    if (!prop->pointer()) {
        if (!prop->argsByRef()) {
            result += ' ';
        } else {
            result += QLatin1String(" &");
        }
    } else {
        result += QLatin1String(" *");
    }
    
    if (((prop->name() == prop->read()) && !notify) || forcePrefix) {
        QString name = prop->name();
        name[0] = name[0].toUpper();
        name.prepend(QLatin1String("n"));
        result += name;
    } else {
        result += prop->name();
    }
    
    return result;
}
