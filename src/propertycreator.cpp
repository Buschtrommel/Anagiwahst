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

PropertyCreator::PropertyCreator(const QList<Property *> &properties, const QString &className, PropertyModel::ClassType type, int tabSize, PropertyModel::CommentsPosition commentsPosition) :
    m_properties(properties), m_className(className), m_type(type), m_tabSize(tabSize), m_commentsPosition(commentsPosition)
{
#ifdef QT_DEBUG
    qDebug() << "Constructing a PropertyCreator for class" << m_className << "with an indent of" << m_tabSize;
#endif
    m_propertiesCount = m_properties.count();
    m_dc = QStringLiteral("::");
    setIndent();
}


// PropertyCreator::~PropertyCreator()
// {
// #ifdef QT_DEBUG
//     qDebug() << "Destroying a PropertyCreator for class" << m_className;
// #endif
// }


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

    QString result = QLatin1String("");
    QString uClassName = m_className.toUpper();


    result += QLatin1String("#ifndef ") % uClassName % QLatin1String("_H\n#define ") % uClassName % QLatin1String("_H\n\n#include <QObject>\n");

    if (m_commentsPosition == PropertyModel::InFronOfHeader) {

        result += QLatin1String("\n\n") % buildClassComment() % QLatin1String("\n\n");

        for (int i = 0; i < m_propertiesCount; ++i) {

            prop = m_properties.at(i);

            result += buildPropertyComment(prop);

            if (!prop->read.isEmpty()) {
                result += buildReadComment(prop) % QLatin1String("\n");
            }

            if (!prop->write.isEmpty()) {
                result += buildWriteComment(prop) % QLatin1String("\n");
            }

            if (!prop->reset.isEmpty()) {
                result += buildResetComment(prop) % QLatin1String("\n");
            }

            if (!prop->notify.isEmpty()) {
                result += buildNotifyComment(prop) % QLatin1String("\n");
            }

            result += QLatin1String("\n\n");
        }

        result += QLatin1String("\n\n\n");
    }

    if (m_type == PropertyModel::SharedData && privateClass) {
        result += QLatin1String("#include <QSharedDataPointer>\n");
    }

    result += QLatin1String("\n");

    if (privateClass) {
        result += QLatin1String("class ") % m_className % QLatin1String("Private;\n\n");
    }

    if (m_commentsPosition != PropertyModel::InFronOfHeader) {
        result += buildClassComment();
    }

    result += QLatin1String("class ") % m_className % QLatin1String(" : public QObject\n{\n") % m_indent % QLatin1String("Q_OBJECT\n");

    for (int i = 0; i < m_propertiesCount; i++) {

        prop = m_properties.at(i);

        if (m_commentsPosition == PropertyModel::InHeader) {
            result += buildPropertyComment(prop);
        }

        result += m_indent % QLatin1String("Q_PROPERTY(") % prop->type % QLatin1String(" ");

        if (prop->pointer) {
            result += QLatin1String("*");
        }

        result += prop->name;

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

    result += QLatin1String("public:\n") % m_indent % QLatin1String("explicit ") % m_className % QLatin1String("(QObject parent = nullptr);\n") % m_indent % QLatin1String("~") % m_className % QLatin1Literal("();\n\n");

    // Start building the get funciton in the public part of the header file

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (!prop->read.isEmpty()) {
            if (m_commentsPosition == PropertyModel::InHeader) {
                result += buildReadComment(prop);
            }
            result += buildReadPrototype(prop);
        }

    }

    result += QLatin1String("\n");

    // Start building the set function in the public part of the header file.

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (!prop->write.isEmpty()) {
            if (m_commentsPosition == PropertyModel::InHeader) {
                result += buildWriteComment(prop);
            }
            result += buildWritePrototype(prop);

        }

    }

    result += QLatin1String("\n");

    // Start building the reset function in the public part of the header file.

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (!prop->reset.isEmpty()) {
            if (m_commentsPosition == PropertyModel::InHeader) {
                result += buildResetComment(prop);
            }
            result += buildResetPrototype(prop);
        }
    }

    result += QLatin1String("\n");

    // Start building the notify functions in the signal part of the header file.

    result += QLatin1String("signals:\n");

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (!prop->notify.isEmpty()) {
            if (m_commentsPosition == PropertyModel::InHeader) {
                result += buildNotifyComment(prop);
            }
            result += buildNotifyPrototype(prop);
        }

    }

    result += QLatin1String("\n");

	// Start building the protected member section.

	if (privateClass) {
		result += QLatin1String("protected:\n");

        switch (m_type) {
        case PropertyModel::PrivateClass:
            result += m_indent % m_className % QLatin1String("Private * const d_ptr;\n\n");
            break;
        case PropertyModel::SharedData:
            result += m_indent % QLatin1String("QSharedDataPointer<") % m_className % QLatin1String("Private> d;\n\n");
            break;
        default:
            break;
        }

        result += QLatin1String("\n");
    }

    // Start building the private variables section.

    result += QLatin1String("private:\n") % m_indent % QLatin1String("Q_DISABLE_COPY(") % m_className % QLatin1String(")\n");

	if (m_type == PropertyModel::PrivateClass && privateClass) {
        result += m_indent % QLatin1String("Q_DECLARE_PRIVATE(") % m_className % QLatin1String(")\n");
    }

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (!prop->privateClass) {
            result += m_indent % prop->type;
            if (prop->pointer) {
                result += QLatin1String(" *m_");
            } else {
                result += QLatin1String(" m_");
            }
            result += prop->name % QLatin1String(";\n");
        }
    }

    result += QLatin1String("\n");

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
	bool defaultValuePresent = false;

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (prop->privateClass) {
            privateClass = true;
        }

        if (!prop->defaultValue.isEmpty()) {
			defaultValuePresent = true;
		}

    }

    if (!privateClass) {
        return QString();
    }

    QString uClassName = m_className.toUpper();


    QString result = QLatin1String("");

    result += QLatin1String("#ifndef ") % uClassName % QLatin1String("_P_H\n#define ") % uClassName % QLatin1String("_P_H\n\n");

    if (m_type == PropertyModel::SharedData) {
        result += QLatin1String("#include <QSharedData>\n");
    }

    result += QLatin1String("#include \"") % m_className.toLower() % QLatin1String(".h\"\n\n");

    result += QLatin1String("class ") % m_className % QLatin1String("Private");

    if (m_type == PropertyModel::SharedData) {
        result += QLatin1String(" : public QSharedData");
    }

    result += QLatin1String("\n{\npublic:\n");

	QString x2Indent;
	x2Indent += m_indent % m_indent;

	result += m_indent % m_className % QLatin1String("Private(") % m_className % QLatin1String(" *parent = nullptr)");

	if (defaultValuePresent) {
		result += QLatin1String(" :\n");

		for (int i = 0; i < m_propertiesCount; ++i) {

            prop = m_properties.at(i);

			if (prop->privateClass && !prop->defaultValue.isEmpty()) {
				result += x2Indent % prop->name % QLatin1String("(") % prop->defaultValue % QLatin1String("),\n");
			}
        }

        result.chop(2);
        result += QLatin1String("\n") % m_indent % QLatin1String("{}\n\n");

	} else {
		result += QLatin1String(" {}\n\n");
	}

    if (m_type == PropertyModel::SharedData) {

        result += m_indent % m_className % QLatin1String("Private(const ") % m_className % QLatin1String("Private &other) :\n") % x2Indent % QLatin1String("QSharedData(other),\n");

        for (int i = 0; i < m_propertiesCount; ++i) {

            prop = m_properties.at(i);

            if (prop->privateClass) {
                result += x2Indent % prop->name % QLatin1String("(other.") % prop->name % QLatin1String("),\n");
            }

        }

        result.chop(2);
		result += QLatin1String("\n") % m_indent % QLatin1String("{}\n\n");
    }

    result += m_indent % QLatin1String("~") % m_className % QLatin1String("Private() {}\n\n");

    for (int i = 0; i < m_propertiesCount; ++i) {

		prop = m_properties.at(i);

		if (prop->privateClass) {
			result += m_indent % prop->type % QLatin1String(" ");

			if (prop->pointer) {
				result += QLatin1String("*");
			}

			result += prop->name % QLatin1String(";\n");
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

    QString doubleIndent = m_indent % m_indent;

    QString result = QLatin1String("");

    result += QLatin1String("#include \"") % m_className.toLower();
    if (privateClass) {
        result += QLatin1String("_p.h\"\n");
    } else {
        result += QLatin1String(".h\"\n");
    }

    result += QLatin1String("#ifdef QT_DEBUG\n#include <QtDebug>\n#endif\n\n/*!\n * \\brief Constructs a new ") % m_className % QLatin1String(" object.\n */\n");

    result += m_className % m_dc % m_className % QLatin1String("()");

    if (privateClass && m_type == PropertyModel::PrivateClass) {
        result += QLatin1String(" :\n") % m_indent % QLatin1String("d_ptr(new ") % m_className % QLatin1String("Private(this))\n");
    } else {
        result += QLatin1String("\n");
    }

    result += QLatin1String("{\n");

    if (privateClass && m_type == PropertyModel::SharedData) {
        result += m_indent % QLatin1String("d = new ") % m_className % QLatin1String("Private(this);\n");
    }

    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        if (!prop->privateClass && !prop->defaultValue.isEmpty()) {

            result += m_indent % getVariablePrefix(prop->privateClass) % prop->name % QLatin1String(" = ") % prop->defaultValue % QLatin1String(";\n");

        }

    }

    result += QLatin1String("}\n\n\n");

    result += QLatin1String("/*!\n * \\brief Deconstructs the ") % m_className % QLatin1String(" object.\n */\n");

    result += m_className % QLatin1String("::~") % m_className % QLatin1String("()\n{\n");

    if (privateClass && m_type == PropertyModel::PrivateClass) {
        result += m_indent % QLatin1String("delete d_ptr;\n");
    }

    result += QLatin1String("}\n\n\n");


    for (int i = 0; i < m_propertiesCount; ++i) {

        prop = m_properties.at(i);

        // prepared stuff
        QLatin1String varPrefix = getVariablePrefix(prop->privateClass);


        if (m_commentsPosition == PropertyModel::InCode) {

            result += buildPropertyComment(prop);

        }


        if (!prop->notify.isEmpty() && m_commentsPosition == PropertyModel::InCode) {

            result += buildNotifyComment(prop) % QLatin1String("\n");

        }


        if (!prop->read.isEmpty()) {

            if (m_commentsPosition == PropertyModel::InCode) {
                result += buildReadComment(prop);
            }


            result += prop->type;

            if (prop->pointer) {
                result += QLatin1String(" *");
            } else {
                result += QLatin1String(" ");
            }


            result += m_className % m_dc % buildReadFunction(prop) % QLatin1String(" { ");

            if (prop->privateClass && m_type == PropertyModel::PrivateClass) {
                result += getPointerMacro(true, false);
            }

            result += QLatin1String("return ") % varPrefix % prop->name % QLatin1String("; }\n\n");
        }



        if (!prop->write.isEmpty()) {

            if (m_commentsPosition == PropertyModel::InCode) {
                result += buildWriteComment(prop);
            }

            QString argName = prop->name;

            if (prop->name == prop->read) {
                argName[0] = argName[0].toUpper();
                argName.prepend(QLatin1String("n"));
            }

            result += QLatin1String("void ") % m_className % m_dc % buildWriteFunction(prop) % QLatin1String("\n{\n");

            if (prop->privateClass && m_type == PropertyModel::PrivateClass) {
                result += m_indent % getPointerMacro();
            }

            if (!prop->notify.isEmpty()) {

                result += m_indent % QLatin1String("if (") % argName % QLatin1String(" != ") % varPrefix % prop->name % QLatin1String(") {\n");

                result += doubleIndent % varPrefix % prop->name % QLatin1String(" = ") % argName % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % doubleIndent % QLatin1String("qDebug() << \"Changed ") % prop->name % QLatin1String(" to\" << ") % varPrefix % prop->name % QLatin1String(";\n#endif\n");

                result += doubleIndent % QLatin1String("emit ") % prop->notify % QLatin1String("(");

                if (!prop->read.isEmpty()) {
                    result += prop->read % QLatin1String("()");
                } else {
                    result += varPrefix % prop->name;
                }

                result += QLatin1String(");\n") % m_indent % QLatin1String("}\n");

            } else {

                result += m_indent % varPrefix % prop->name % QLatin1String(" = ") % prop->name % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % m_indent % QLatin1String("qDebug() << \" Set ") % prop->name % QLatin1String(" to\" << ") % varPrefix % prop->name % QLatin1String(";\n#endif\n");

            }

            result += QLatin1String("}\n\n");

        }






        if (!prop->reset.isEmpty()) {

            if (m_commentsPosition == PropertyModel::InCode) {
                result += buildResetComment(prop);
            }

            result += QLatin1String("void ") % m_className % m_dc % buildResetFunction(prop) % QLatin1String("\n{\n");

            if (prop->privateClass) {
                result += m_indent % getPointerMacro();
            }

            QString defValue = prop->defaultValue.isEmpty() ? getDefaultValue(prop->type, prop->pointer) : prop->defaultValue;


            if (!prop->notify.isEmpty()) {

                result += m_indent % QLatin1String("if (") % defValue % QLatin1String(" != ") % varPrefix % prop->name % QLatin1String(") {\n");

                result += doubleIndent % varPrefix % prop->name % QLatin1String(" = ") % defValue % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % doubleIndent % QLatin1String("qDebug() << \"Reset ") % prop->name % QLatin1String(" to its default value\" << ") % defValue % QLatin1String(";\n#endfi\n");

                result += doubleIndent % QLatin1String("emit ") % prop->notify % QLatin1String("(");

                if (!prop->read.isEmpty()) {
                    result += prop->read % QLatin1String("()");
                } else {
                    result += varPrefix % prop->name;
                }

                result += QLatin1String(");\n") % m_indent % QLatin1String("}\n");


            } else {

                result += m_indent % varPrefix % prop->name % QLatin1String(" = ") % defValue % QLatin1String(";\n");

                result += QLatin1String("#ifdef QT_DEBUG\n") % doubleIndent % QLatin1String("qDebug() << \"Reset ") % prop->name % QLatin1String(" to its default value\" << ") % defValue % QLatin1String(";\n#endfi\n");

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



QString PropertyCreator::buildPropertyComment(Property *prop)
{
    QString result = QLatin1String("");

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }

    result += QStringLiteral("/*!\n");

    if (m_commentsPosition != PropertyModel::InHeader) {
        result += QLatin1String(" * \\property ") % m_className % m_dc % prop->name % QLatin1String("\n");
    }

    if (prop->brief.isEmpty() && prop->comment.isEmpty()) {

        if (m_commentsPosition == PropertyModel::InHeader) {
            result += m_indent % QLatin1String(" * \\brief The ") % prop->name % QLatin1String(" property.\n") % m_indent % QLatin1String(" *\n");
        } else {
            result += QLatin1String(" * \\brief The ") % prop->name % QLatin1String(" property.\n *\n");
        }

    } else {

        if (!prop->brief.isEmpty()) {
            if (m_commentsPosition == PropertyModel::InHeader) {
                result += m_indent % QLatin1String(" * \\brief ") % prop->brief % QLatin1String("\n") % m_indent % QLatin1String(" *\n");
            } else {
                result += QLatin1String(" * \\brief ") % prop->brief % QLatin1String("\n *\n");
            }
        }

        if (!prop->comment.isEmpty()) {
            if (prop->brief.isEmpty()) {
                if (m_commentsPosition == PropertyModel::InHeader) {
                    result += m_indent;
                }
                result += QLatin1String(" *\n");
            }

            if (!prop->comment.isEmpty()) {
                if (prop->brief.isEmpty()) {
                    if (m_commentsPosition == PropertyModel::InHeader) {
                        result += m_indent;
                    }
                    result += QLatin1String(" *\n");
                }

                if (prop->comment.size() > 100) {
                    QStringList paragraphs = prop->comment.split(QRegularExpression(QStringLiteral("\\n")), QString::SkipEmptyParts);

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
                    result += m_indent % QLatin1String(" * ") % prop->comment % QLatin1String("\n") % m_indent % QLatin1String(" *\n");
                } else {
                    result += QLatin1String(" * ") % prop->comment % QLatin1String("\n *\n");
                }
            }
        }
    }

    if (!prop->read.isEmpty() || !prop->write.isEmpty() || !prop->reset.isEmpty()) {

        if (m_commentsPosition == PropertyModel::InHeader) {
            result += m_indent % QLatin1String(" * \\par Access functions:\n") % m_indent % QLatin1String(" * <TABLE>");
        } else {
            result += QLatin1String(" * \\par Access functions:\n * <TABLE>");
        }

        if (!prop->read.isEmpty()) {
            if (prop->pointer) {
                result += buildTableRow(prop->type % QStringLiteral("*"), buildReadFunction(prop));
            } else {
                result += buildTableRow(prop->type, buildReadFunction(prop));
            }
        }

        if (!prop->write.isEmpty()) {
            result += buildTableRow(QStringLiteral("void"), buildWriteFunction(prop));
        }

        if (!prop->reset.isEmpty()) {
            result += buildTableRow(QStringLiteral("void"), buildResetFunction(prop));
        }

        result += QLatin1String("</TABLE>\n");
    }

    if (!prop->notify.isEmpty()) {

        if (m_commentsPosition == PropertyModel::InHeader) {
            result += m_indent % QLatin1String(" * \\par Notifier signal:\n") % m_indent % QLatin1String(" * <TABLE>");
        } else {
            result += QLatin1String(" * \\par Notifier signal:\n * <TABLE>");
        }

//         if (prop->pointer) {
//             result += buildTableRow(QStringLiteral("void"), prop->notify % QLatin1String("(") % prop->type % QLatin1String(" * ") % prop->name % QLatin1String(")"));
//         } else {
//             result += buildTableRow(QStringLiteral("void"), prop->notify % QLatin1String("(const ") % prop->type % QLatin1String(" & ") % prop->name % QLatin1String(")"));
//         }
        result += buildTableRow(QStringLiteral("void"), prop->notify % buildFuncArg(prop, true));

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



QString PropertyCreator::buildReadFunction(Property *prop)
{
    QString readFunc = prop->read % QLatin1String("() const");

    return readFunc;
}



QString PropertyCreator::buildWriteFunction(Property *prop)
{
    QString writeFunc;

//     if (prop->pointer) {
//         writeFunc = prop->write % QLatin1String("(") % prop->type % QLatin1String(" * ") % prop->name % QLatin1String(")");
//     } else {
//         writeFunc = prop->write % QLatin1String("(const ") % prop->type % QLatin1String(" & ") % prop->name % QLatin1String(")");
//     }
    writeFunc = prop->write % buildFuncArg(prop);

    return writeFunc;
}




QString PropertyCreator::buildResetFunction(Property *prop)
{
    QString resetFunc = prop->reset % QLatin1String("()");

    return resetFunc;
}



QString PropertyCreator::buildPartOfStatement(Property *prop)
{
    if (m_commentsPosition == PropertyModel::InHeader) {
        QString partOf = m_indent % QLatin1String(" * \\brief Part of the \\link ") % m_className % m_dc % prop->name % QLatin1String(" ") % prop->name % QLatin1String(" \\endlink property.\n") % m_indent;
        return partOf;
    } else {
        QString partOf = QLatin1String(" * \\brief Part of the \\link ") % m_className % m_dc % prop->name % QLatin1String(" ") % prop->name % QLatin1String(" \\endlink property.\n");
        return partOf;
    }
}



QString PropertyCreator::buildReadComment(Property *prop)
{
    QString result = QLatin1String("");

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }

    result += QLatin1String("/*!\n");

    if (m_commentsPosition == PropertyModel::InFronOfHeader) {
        result += QLatin1String(" * \\fn ") % prop->type;
        if (prop->pointer) {
            result += QLatin1String(" *");
        } else {
            result += QLatin1String(" ");
        }

        result += m_className % m_dc % prop->read % QLatin1String("()\n");
    }

    result += buildPartOfStatement(prop) % QLatin1String(" */\n");

    return result;
}



QString PropertyCreator::buildWriteComment(Property *prop)
{
    QString result = QLatin1String("");

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }

    result += QLatin1String("/*!\n");

    if (m_commentsPosition == PropertyModel::InFronOfHeader) {
        result += QLatin1String(" * \\fn void ") % m_className % m_dc % prop->write % buildFuncArg(prop) % QLatin1String("\n");
    }

    result += buildPartOfStatement(prop) % QLatin1String(" */\n");

    return result;
}



QString PropertyCreator::buildResetComment(Property *prop)
{
    QString result = QLatin1String("");

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent;
    }

    result += QLatin1String("/*!\n");

    if (m_commentsPosition == PropertyModel::InFronOfHeader) {
        result += QLatin1String(" * \\fn void ") % m_className % m_dc % prop->reset % QLatin1String("()\n");
    }

    result += buildPartOfStatement(prop) % QLatin1String(" */\n");

    return result;
}


QString PropertyCreator::buildNotifyComment(Property *prop)
{
    QString result = QLatin1String("");

    if (m_commentsPosition == PropertyModel::InHeader) {
        result += m_indent % QLatin1String("/*!\n");
    } else {
        result += QLatin1String("/*!\n");
    }

    if (m_commentsPosition != PropertyModel::InHeader) {
        result += QLatin1String(" * \\fn void ") % m_className % m_dc % prop->notify % buildFuncArg(prop, true) % QLatin1String("\n");
    }

    result += buildPartOfStatement(prop) % QLatin1String(" */\n");

    return result;
}




QString PropertyCreator::buildWritePrototype(Property *prop)
{
    QString result = m_indent % QLatin1String("void ") % prop->write % buildFuncArg(prop) % QLatin1String(";\n");

    return result;
}



QString PropertyCreator::buildReadPrototype(Property *prop)
{
    QString result;

    result += m_indent % prop->type % QLatin1String(" ");

    if (prop->pointer) {
        result += QLatin1String("*");
    }

    result += prop->read % QLatin1String("() const;\n");

    return result;
}


QString PropertyCreator::buildResetPrototype(Property *prop)
{
    QString result = m_indent % QLatin1String("void ") % prop->reset % QLatin1String("();\n");

    return result;
}


QString PropertyCreator::buildNotifyPrototype(Property *prop)
{
    QString result = m_indent % QLatin1String("void ") % prop->notify % buildFuncArg(prop, true) % QLatin1String(";\n");

    return result;
}




QString PropertyCreator::buildFuncArg(Property *prop, bool notify)
{
    QString result = QStringLiteral("(");

    if (!prop->pointer && prop->argsByRef) {
        result += QLatin1String("const ");
    }

    result += prop->type;

    if (!prop->pointer) {
        if (!prop->argsByRef) {
            result += ' ';
        } else {
            result += QLatin1String(" &");
        }
    } else {
        result += QLatin1String(" *");
    }

    if ((prop->name != prop->read) || notify) {
        result += prop->name % QLatin1String(")");
    } else {
        QString name = prop->name;
        name[0] = name[0].toUpper();
        name.prepend(QLatin1String("n"));
        result += name % QLatin1String(")");
    }

    return result;
}



