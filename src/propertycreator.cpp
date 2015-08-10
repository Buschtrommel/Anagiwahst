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

PropertyCreator::PropertyCreator(QList<Property *> properties, const QString &className, int tabSize) :
    m_properties(properties), m_className(className), m_tabSize(tabSize)
{
#ifdef QT_DEBUG
    qDebug() << "Constructing a PropertyCreator for class" << m_className << "with an indent of" << m_tabSize;
#endif
    m_propertiesCount = m_properties.count();
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

    Property *prop = nullptr;

    bool privateClass = false;

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (prop->privateClass) {
            privateClass = true;
            break;
        }

    }

    QString result("");
    QString uClassName = m_className.toUpper();

    result += QLatin1String("#ifndef ") % uClassName % QLatin1String("_H\n#define ") % uClassName % QLatin1String("_H\n\n#include <QObject>\n\n");

    if (privateClass) {
        result += QLatin1String("class ") % m_className % QLatin1String("Private;\n\n");
    }

    result += QLatin1String("/*!\n * \\brief The ") % m_className % QLatin1String(" class.\n */\nclass ") % m_className % QLatin1String(" : public QObject\n{\n") % m_indent % QLatin1String("Q_OBJECT\n");

    if (privateClass) {
        result += m_indent % QLatin1String("Q_DECLARE_PRIVATE(") % m_className % QLatin1String(")\n");
    }

    for (int i = 0; i < m_propertiesCount; i++) {

        prop = m_properties.at(i);

        result += m_indent % QLatin1String("Q_PROPERTY(") % prop->type % QLatin1String(" ") % prop->name;

        if (!prop->member.isEmpty()) {
            result += QLatin1String(" MEMBER ") % prop->member;
        }

        if (!prop->read.isEmpty()) {
            result += QLatin1String(" READ ") % prop->read;
        }

        if (!prop->write.isEmpty()) {
            result += QLatin1String(" WRITE ") % prop->write;
        }

        if (!prop->reset.isEmpty()) {
            result += QLatin1String(" RESET ") % prop->reset;
        }

        if (!prop->notify.isEmpty()) {
            result += QLatin1String(" NOTIFY ") % prop->notify;
        }

        if (prop->revision > 0) {
            result += QLatin1String(" REVISION ") % QString::number(prop->revision);
        }

        if (prop->designable != QLatin1String("true")) {
            result += QLatin1String(" DESIGNABLE ") % prop->designable;
        }

        if (prop->scriptable != QLatin1String("true")) {
            result += QLatin1String(" SCRIPTABLE ") % prop->scriptable;
        }

        if (!prop->stored) {
            result += QLatin1String(" STORED false");
        }

        if (prop->user) {
            result += QLatin1String(" USER true");
        }

        if (prop->constant) {
            result += QLatin1String(" CONSTANT");
        }

        if (prop->final) {
            result += QLatin1String(" FINAL");
        }

        result += QLatin1String(")\n");
    }

    result += QLatin1String("public:\n") % m_indent % m_className % QLatin1String("();\n") % m_indent % QLatin1String("~") % m_className % QLatin1Literal("();\n\n");

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (!prop->read.isEmpty()) {
            result += m_indent % prop->type % QLatin1String(" ") % prop->read % QLatin1String("() const;\n");
        }

    }

    result += QLatin1String("\n");

    // Start building the set function int the public part of the header file.

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (!prop->write.isEmpty()) {
            result += m_indent % QLatin1String("void ") % prop->write % QLatin1String("(const ") % prop->type % QLatin1String(" &") % prop->name % QLatin1String(");\n");
        }

    }

    result += QLatin1String("\n");

    // Start building the reset function in the public part of the header file.

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (!prop->reset.isEmpty()) {
            result += m_indent % QLatin1String("void ") % prop->reset % QLatin1String("();\n");
        }
    }

    result += QLatin1String("\n");

    // Start building the notify functions in the signal part of the header file.

    result += QLatin1String("signals:\n");

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (!prop->notify.isEmpty()) {
            result += m_indent % QLatin1String("void ") % prop->notify % QLatin1String("(const ") % prop->type % QLatin1String(" &") % prop->name % QLatin1String(");\n");
        }

    }

    result += QLatin1String("\n");

    // Start building the private variables section.

    result += QLatin1String("private:\n");

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (!prop->privateClass) {
            result += m_indent % prop->type % QLatin1String(" m_") % prop->name % QLatin1String(";\n");
        }
    }

    result += QLatin1String("\n");

    if (privateClass) {
        result += QLatin1String("protected:\n") % m_indent % m_className % QLatin1String("Private *d_ptr;\n\n");
    }

    result += QLatin1String("};\n\n#endif // ") % uClassName % QLatin1String("_H\n");

    return result;
}





QString PropertyCreator::createPrivate()
{
    if (m_properties.isEmpty()) {
        return QString();
    }

    Property *prop = nullptr;

    bool privateClass = false;

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (prop->privateClass) {
            privateClass = true;
            break;
        }

    }

    if (!privateClass) {
        return QString();
    }

    QString uClassName = m_className.toUpper();


    QString result("");
    result += QLatin1String("#ifndef ") % uClassName % QLatin1String("_P_H\n#define ") % uClassName % QLatin1String("_P_H\n\n#include \"") % m_className.toLower() % QLatin1String(".h\"\n\nclass ") % m_className % QLatin1String("Private\n{\npublic:\n");

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (prop->privateClass) {
            result += m_indent % prop->type % QLatin1String(" ") % prop->name % QLatin1String(";\n");
        }

    }

    result += QLatin1String("};\n\n#endif // ") % uClassName % QLatin1String("_P_H\n");

    return result;
}





QString PropertyCreator::createCode()
{
    if (m_properties.isEmpty()) {
        return QString();
    }



    Property *prop = nullptr;

    bool privateClass = false;

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (prop->privateClass) {
            privateClass = true;
            break;
        }

    }


    // prepared stuff
    QLatin1String dc("::");
    QString doubleIndent = m_indent % m_indent;



    QString result("");

    result += QLatin1String("#include \"") % m_className.toLower();
    if (privateClass) {
        result += QLatin1String("_p.h\"\n");
    } else {
        result += QLatin1String(".h\"\n");
    }

    result += QLatin1String("#ifdef QT_DEBUG\n#include <QtDebug>\n#endif\n\n/*!\n * \\brief Constructs an empty ") % m_className % QLatin1String(".\n */\n");

    result += m_className % dc % m_className % QLatin1String("()");

    if (privateClass) {
        result += QLatin1String(" :\n") % m_indent % QLatin1String("d_ptr(new ") % m_className % QLatin1String("Private)\n");
    } else {
        result += QLatin1String("\n");
    }

    result += QLatin1String("{\n");

    if (privateClass) {
        result += m_indent % getPointerMacro();
    }

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        result += m_indent % getVariablePrefix(prop->privateClass) % prop->name % QLatin1String(" = ");

        if (!prop->defaultValue.isEmpty()) {
            result += prop->defaultValue % QLatin1String(";\n");
        } else {
            result += getDefaultValue(prop->type) % QLatin1String(";\n");
        }

    }

    result += QLatin1String("}\n\n\n");

    result += QLatin1String("/*!\n * \\brief Deconstructs ") % m_className % QLatin1String(".\n */\n");

    result += m_className % QLatin1String("::~") % m_className % QLatin1String("()\n{\n");

    if (privateClass) {
        result += m_indent % QLatin1String("delete d_ptr;\n");
    }

    result += QLatin1String("}\n\n\n");


    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        // prepared stuff
        QLatin1String varPrefix = getVariablePrefix(prop->privateClass);
        QString readFunc = prop->read % QLatin1String("() const");
        QString writeFunc = prop->write % QLatin1String("(const ") % prop->type % QLatin1String(" & ") % prop->name % QLatin1String(")");
        QString resetFunc = prop->reset % QLatin1String("()");
        QString partOf = QLatin1String(" * \\brief Part of the \\link ") % m_className % dc % prop->name % QLatin1String(" ") % prop->name % QLatin1String(" \\endlink property.\n");


        result += QLatin1String("/*!\n * \\property ") % m_className % dc % prop->name % QLatin1String("\n");

        if (prop->brief.isEmpty() && prop->comment.isEmpty()) {

            result += QLatin1String(" * \\brief The ") % prop->name % QLatin1String(" property.\n *\n");

        } else {

            if (!prop->brief.isEmpty()) {
                result += QLatin1String(" * \\brief ") % prop->brief % QLatin1String("\n *\n");
            }

            if (!prop->comment.isEmpty()) {
                if (prop->brief.isEmpty()) {
                    result += QLatin1String(" *\n");
                }

                if (prop->comment.size() > 100) {
                    QStringList paragraphs = prop->comment.split(QRegularExpression("\\n"), QString::SkipEmptyParts);

                    for (int i = 0; i < paragraphs.size(); ++i) {

                        result += QLatin1String(" * ");

                        int combinedSize = 0;

                        QStringList words = paragraphs.at(i).split(" ");

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

                        result += QLatin1String("\n *\n");

                    }

                } else {
                    result += QLatin1String(" * ") % prop->comment % QLatin1String("\n *\n");
                }
            }

        }

        if (!prop->read.isEmpty() || !prop->write.isEmpty() || !prop->reset.isEmpty()) {
            result += QLatin1String(" * \\par Access functions:\n * <TABLE>");

            if (!prop->read.isEmpty()) {
                result += buildTableRow(prop->type, readFunc);
//                result += QLatin1String("<TR><TD>") % prop->type % QLatin1String("</TD><TD>") % prop->read % QLatin1String("() const</TD></TR>");
            }

            if (!prop->write.isEmpty()) {
                result += buildTableRow(QStringLiteral("void"), writeFunc);
//                result += QLatin1String("<TR><TD>void</TD><TD>") % prop->write % QLatin1String("(const ") % prop->type % QLatin1String(" & ") % prop->name % QLatin1String(")</TD></TR>");
            }

            if (!prop->reset.isEmpty()) {
                result += buildTableRow(QStringLiteral("void"), resetFunc);
//                result += QLatin1String("<TR><TD>void</TD><TD>") % prop->reset % QLatin1String("()</TD></TR>");
            }

            result += QLatin1String("</TABLE>\n");
        }

        if (!prop->notify.isEmpty()) {

            result += QLatin1String(" * \\par Notifier signal:\n * <TABLE>") % buildTableRow(QStringLiteral("void"), prop->notify % QLatin1String("(const ") % prop->type % QLatin1String(" & ") % prop->name % QLatin1String(")")) % QLatin1String("</TABLE>\n");
//            result += QLatin1String(" * \\par Notifier signal:\n * <TABLE><TR><TD>void</TD><TD>") % prop->notify % QLatin1String("(const ") % prop->type % QLatin1String(" & ") % prop->name % QLatin1String(")</TD></TR></TABLE>\n");

        }

        result += QLatin1String(" */\n\n");


        if (!prop->notify.isEmpty()) {

            result += QLatin1String("/*!\n * \\fn ") % m_className % dc % prop->notify % QLatin1String("()\n");
            result += partOf % QLatin1String(" */\n\n");

        }


        if (!prop->read.isEmpty()) {

            result += QLatin1String("/*!\n") % partOf % QLatin1String(" */\n");
            result += prop->type % QLatin1String(" ") % m_className % dc % readFunc % QLatin1String(" { ");

            if (prop->privateClass) {
                result += getPointerMacro(true, false);
            }

            result += QLatin1String("return ") % varPrefix % prop->name % QLatin1String("; }\n\n");
        }



        if (!prop->write.isEmpty()) {

            result += QLatin1String("/*!\n") % partOf % QLatin1String(" */\n");
            result += QLatin1String("void ") % m_className % dc % writeFunc % QLatin1String("\n{\n");

            if (prop->privateClass) {
                result += m_indent % getPointerMacro();
            }

            if (!prop->notify.isEmpty()) {

                result += m_indent % QLatin1String("if (") % prop->name % QLatin1String(" != ") % varPrefix % prop->name % QLatin1String(") {\n");

                result += doubleIndent % varPrefix % prop->name % QLatin1String(" = ") % prop->name % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % doubleIndent % QLatin1String("qDebug() << \"Changed ") % prop->name % QLatin1String(" to \" << ") % varPrefix % prop->name % QLatin1String(";\n#endif\n");

                result += doubleIndent % QLatin1String("emit ") % prop->notify % QLatin1String("(");

                if (!prop->read.isEmpty()) {
                    result += prop->read % QLatin1String("()");
                } else {
                    result += varPrefix % prop->name;
                }

                result += QLatin1String(");\n") % m_indent % QLatin1String("}\n");

            } else {

                result += m_indent % varPrefix % prop->name % QLatin1String(" = ") % prop->name % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % m_indent % QLatin1String("qDebug() << \" Set ") % prop->name % QLatin1String(" to \" << ") % varPrefix % prop->name % QLatin1String(";\n#endif\n");

            }

            result += QLatin1String("}\n\n");

        }






        if (!prop->reset.isEmpty()) {

            result += QLatin1String("/*!\n") % partOf % QLatin1String(" */\n");
            result += QLatin1String("void ") % m_className % dc % resetFunc % QLatin1String("\n{\n");

            if (prop->privateClass) {
                result += m_indent % getPointerMacro();
            }

            QString defValue = prop->defaultValue.isEmpty() ? getDefaultValue(prop->type) : prop->defaultValue;


            if (!prop->notify.isEmpty()) {

                result += m_indent % QLatin1String("if (") % defValue % QLatin1String(" != ") % varPrefix % prop->name % QLatin1String(") {\n");

                result += doubleIndent % varPrefix % prop->name % QLatin1String(" = ") % defValue % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % doubleIndent % QLatin1String("qDebug() << \"Reset ") % prop->name % QLatin1String(" to its default value \" << ") % defValue % QLatin1String(";\n#endfi\n");

                result += doubleIndent % QLatin1String("emit ") % prop->notify % QLatin1String("(");

                if (!prop->read.isEmpty()) {
                    result += prop->read % QLatin1String("()");
                } else {
                    result += varPrefix % prop->name;
                }

                result += QLatin1String(");\n") % m_indent % QLatin1String("}\n");


            } else {

                result += m_indent % varPrefix % prop->name % QLatin1String(" = ") % defValue % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % doubleIndent % QLatin1String("qDebug() << \"Reset ") % prop->name % QLatin1String(" to its default value \" << ") % defValue % QLatin1String(";\n#endfi\n");

            }

            result += QLatin1String("}\n\n");

        }



        result += QLatin1String("\n\n\n");

    }

    return result;
}



QString PropertyCreator::getPointerMacro(bool constant, bool newLine)
{
    QString result("Q_D(");

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



QString PropertyCreator::getDefaultValue(const QString &type)
{
    QStringList ints = {"unsigned char", "signed char", "short", "short int", "signed short", "signed short int", "unsigned short", "unsigned short int", "int", "signed", "signed int", "unsigned int", "long", "long int", "signed long", "signed long int", "unsigned long", "unsigned long int", "long long", "long long int", "signed long long", "signed long long int", "unsigned long long", "unsigned long long int", "qint8", "qint16", "qint32", "qint64", "qintptr", "qlonglong", "quint8", "quint16", "quint32", "quint64", "quintptr", "qulonglong", "uchar", "uint", "ulong", "ushort"};

    QStringList floats = {"float", "double", "long double", "qreal"};

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
        m_indent = QString(" ");
        break;
    case 2:
        m_indent = QString("  ");
        break;
    case 3:
        m_indent = QString("   ");
        break;
    case 4:
        m_indent = QString("    ");
        break;
    case 5:
        m_indent = QString("     ");
        break;
    case 6:
        m_indent = QString("      ");
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
