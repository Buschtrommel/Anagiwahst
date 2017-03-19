#include "property.h"
#include <QRegularExpression>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

/*!
 * \brief Constructs a new Property object.
 */
Property::Property(QObject *parent) : QObject(parent)
{
}


/*!
 * \overload
 */
Property::Property(int id, const QString &name, const QString &type, const QString &read, const QString &write, const QString &member, const QString &reset, const QString &notify, const QString &defaultValue, bool argsByRef, bool pointer, bool docMethods, QObject *parent) :
    QObject(parent), m_id(id), m_name(name), m_type(type), m_read(read), m_write(write), m_member(member), m_reset(reset), m_notify(notify), m_defaultValue(defaultValue), m_argsByRef(argsByRef), m_pointer(pointer), m_documentMethods(docMethods)
{

}


/*!
 * \brief Deconstructs the Property object.
 */
Property::~Property()
{

}


/*!
 * \property Property::id
 * \brief Internal ID of this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>int</TD><TD>id() const</TD></TR><TR><TD>void</TD><TD>setId(int nId)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>idChanged(int id)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::idChanged(int id)
 * \brief Part of the \link Property::id id \endlink property.
 */

/*!
 * \brief Part of the \link Property::id id \endlink property.
 */
int Property::id() const { return m_id; }

/*!
 * \brief Part of the \link Property::id id \endlink property.
 */
void Property::setId(int nId)
{
    if (nId != m_id) {
        m_id = nId;
#ifdef QT_DEBUG
        qDebug() << "Changed id to" << m_id;
#endif
        emit idChanged(id());
    }
}




/*!
 * \property Property::name
 * \brief Name of this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>name() const</TD></TR><TR><TD>void</TD><TD>setName(const QString &nName)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>nameChanged(const QString &name)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::nameChanged(const QString &name)
 * \brief Part of the \link Property::name name \endlink property.
 */

/*!
 * \brief Part of the \link Property::name name \endlink property.
 */
QString Property::name() const { return m_name; }

/*!
 * \brief Part of the \link Property::name name \endlink property.
 */
void Property::setName(const QString &nName)
{
    if (nName != m_name) {
        m_name = nName;
#ifdef QT_DEBUG
        qDebug() << "Changed name to" << m_name;
#endif
        emit nameChanged(name());
    }
}




/*!
 * \property Property::type
 * \brief Type of this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>type() const</TD></TR><TR><TD>void</TD><TD>setType(const QString &nType)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>typeChanged(const QString &type)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::typeChanged(const QString &type)
 * \brief Part of the \link Property::type type \endlink property.
 */

/*!
 * \brief Part of the \link Property::type type \endlink property.
 */
QString Property::type() const { return m_type; }

/*!
 * \brief Part of the \link Property::type type \endlink property.
 */
void Property::setType(const QString &nType)
{
    if (nType != m_type) {
        m_type = nType;
#ifdef QT_DEBUG
        qDebug() << "Changed type to" << m_type;
#endif
        emit typeChanged(type());
    }
}




/*!
 * \property Property::read
 * \brief Getter function of this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>read() const</TD></TR><TR><TD>void</TD><TD>setRead(const QString &nRead)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>readChanged(const QString &read)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::readChanged(const QString &read)
 * \brief Part of the \link Property::read read \endlink property.
 */

/*!
 * \brief Part of the \link Property::read read \endlink property.
 */
QString Property::read() const { return m_read; }

/*!
 * \brief Part of the \link Property::read read \endlink property.
 */
void Property::setRead(const QString &nRead)
{
    if (nRead != m_read) {
        m_read = nRead;
#ifdef QT_DEBUG
        qDebug() << "Changed read to" << m_read;
#endif
        emit readChanged(read());
    }
}




/*!
 * \property Property::write
 * \brief Setter function of this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>write() const</TD></TR><TR><TD>void</TD><TD>setWrite(const QString &nWrite)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>writeChanged(const QString &write)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::writeChanged(const QString &write)
 * \brief Part of the \link Property::write write \endlink property.
 */

/*!
 * \brief Part of the \link Property::write write \endlink property.
 */
QString Property::write() const { return m_write; }

/*!
 * \brief Part of the \link Property::write write \endlink property.
 */
void Property::setWrite(const QString &nWrite)
{
    if (nWrite != m_write) {
        m_write = nWrite;
#ifdef QT_DEBUG
        qDebug() << "Changed write to" << m_write;
#endif
        emit writeChanged(write());
    }
}




/*!
 * \property Property::member
 * \brief Member used by this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>member() const</TD></TR><TR><TD>void</TD><TD>setMember(const QString &nMember)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>memberChanged(const QString &member)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::memberChanged(const QString &member)
 * \brief Part of the \link Property::member member \endlink property.
 */

/*!
 * \brief Part of the \link Property::member member \endlink property.
 */
QString Property::member() const { return m_member; }

/*!
 * \brief Part of the \link Property::member member \endlink property.
 */
void Property::setMember(const QString &nMember)
{
    if (nMember != m_member) {
        m_member = nMember;
#ifdef QT_DEBUG
        qDebug() << "Changed member to" << m_member;
#endif
        emit memberChanged(member());
    }
}




/*!
 * \property Property::reset
 * \brief Reset function of this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>reset() const</TD></TR><TR><TD>void</TD><TD>setReset(const QString &nReset)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>resetChanged(const QString &reset)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::resetChanged(const QString &reset)
 * \brief Part of the \link Property::reset reset \endlink property.
 */

/*!
 * \brief Part of the \link Property::reset reset \endlink property.
 */
QString Property::reset() const { return m_reset; }

/*!
 * \brief Part of the \link Property::reset reset \endlink property.
 */
void Property::setReset(const QString &nReset)
{
    if (nReset != m_reset) {
        m_reset = nReset;
#ifdef QT_DEBUG
        qDebug() << "Changed reset to" << m_reset;
#endif
        emit resetChanged(reset());
    }
}




/*!
 * \property Property::notify
 * \brief Signal function of this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>notify() const</TD></TR><TR><TD>void</TD><TD>setNotify(const QString &nNotify)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>notifyChanged(const QString &notify)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::notifyChanged(const QString &notify)
 * \brief Part of the \link Property::notify notify \endlink property.
 */

/*!
 * \brief Part of the \link Property::notify notify \endlink property.
 */
QString Property::notify() const { return m_notify; }

/*!
 * \brief Part of the \link Property::notify notify \endlink property.
 */
void Property::setNotify(const QString &nNotify)
{
    if (nNotify != m_notify) {
        m_notify = nNotify;
#ifdef QT_DEBUG
        qDebug() << "Changed notify to" << m_notify;
#endif
        emit notifyChanged(notify());
    }
}




/*!
 * \property Property::revision
 * \brief Revision of this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>quint8</TD><TD>revision() const</TD></TR><TR><TD>void</TD><TD>setRevision(quint8 nRevision)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>revisionChanged(quint8 revision)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::revisionChanged(quint8 revision)
 * \brief Part of the \link Property::revision revision \endlink property.
 */

/*!
 * \brief Part of the \link Property::revision revision \endlink property.
 */
quint8 Property::revision() const { return m_revision; }

/*!
 * \brief Part of the \link Property::revision revision \endlink property.
 */
void Property::setRevision(quint8 nRevision)
{
    if (nRevision != m_revision) {
        m_revision = nRevision;
#ifdef QT_DEBUG
        qDebug() << "Changed revision to" << m_revision;
#endif
        emit revisionChanged(revision());
    }
}




/*!
 * \property Property::designable
 * \brief The DESIGNABLE attribute indicates whether the property should be visible in the property editor of GUI design tool (e.g., Qt Designer).
 *
 * Most properties are DESIGNABLE (default true). Instead of true or false, you can specify a boolean member 
 * function.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>designable() const</TD></TR><TR><TD>void</TD><TD>setDesignable(const QString &nDesignable)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>designableChanged(const QString &designable)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::designableChanged(const QString &designable)
 * \brief Part of the \link Property::designable designable \endlink property.
 */

/*!
 * \brief Part of the \link Property::designable designable \endlink property.
 */
QString Property::designable() const { return m_designable; }

/*!
 * \brief Part of the \link Property::designable designable \endlink property.
 */
void Property::setDesignable(const QString &nDesignable)
{
    if (nDesignable != m_designable) {
        m_designable = nDesignable;
#ifdef QT_DEBUG
        qDebug() << "Changed designable to" << m_designable;
#endif
        emit designableChanged(designable());
    }
}




/*!
 * \property Property::scriptable
 * \brief The SCRIPTABLE attribute indicates whether this property should be accessible by a scripting engine (default true).
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>scriptable() const</TD></TR><TR><TD>void</TD><TD>setScriptable(const QString &nScriptable)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>scriptableChanged(const QString &scriptable)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::scriptableChanged(const QString &scriptable)
 * \brief Part of the \link Property::scriptable scriptable \endlink property.
 */

/*!
 * \brief Part of the \link Property::scriptable scriptable \endlink property.
 */
QString Property::scriptable() const { return m_scriptable; }

/*!
 * \brief Part of the \link Property::scriptable scriptable \endlink property.
 */
void Property::setScriptable(const QString &nScriptable)
{
    if (nScriptable != m_scriptable) {
        m_scriptable = nScriptable;
#ifdef QT_DEBUG
        qDebug() << "Changed scriptable to" << m_scriptable;
#endif
        emit scriptableChanged(scriptable());
    }
}




/*!
 * \property Property::stored
 * \brief The STORED attribute indicates whether the property should be thought of as existing on its own or as depending on other values.
 *
 * It also indicates whether the property value must be saved when storing the object's state. Most properties 
 * areSTORED (default true), but e.g., QWidget::minimumWidth() has STORED false, because its value is 
 * justtaken from the width component of property QWidget::minimumSize(), which is a QSize. 
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>stored() const</TD></TR><TR><TD>void</TD><TD>setStored(bool nStored)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>storedChanged(bool stored)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::storedChanged(bool stored)
 * \brief Part of the \link Property::stored stored \endlink property.
 */

/*!
 * \brief Part of the \link Property::stored stored \endlink property.
 */
bool Property::stored() const { return m_stored; }

/*!
 * \brief Part of the \link Property::stored stored \endlink property.
 */
void Property::setStored(bool nStored)
{
    if (nStored != m_stored) {
        m_stored = nStored;
#ifdef QT_DEBUG
        qDebug() << "Changed stored to" << m_stored;
#endif
        emit storedChanged(stored());
    }
}




/*!
 * \property Property::user
 * \brief The USER attribute indicates whether the property is designated as the user-facing or user-editable property for the class. 
 *
 * Normally, there is only one USER property per class (default false). e.g., QAbstractButton::checked 
 * isthe user editable property for (checkable) buttons. Note that QItemDelegate gets and sets a widget's 
 * USERproperty. 
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>user() const</TD></TR><TR><TD>void</TD><TD>setUser(bool nUser)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>userChanged(bool user)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::userChanged(bool user)
 * \brief Part of the \link Property::user user \endlink property.
 */

/*!
 * \brief Part of the \link Property::user user \endlink property.
 */
bool Property::user() const { return m_user; }

/*!
 * \brief Part of the \link Property::user user \endlink property.
 */
void Property::setUser(bool nUser)
{
    if (nUser != m_user) {
        m_user = nUser;
#ifdef QT_DEBUG
        qDebug() << "Changed user to" << m_user;
#endif
        emit userChanged(user());
    }
}




/*!
 * \property Property::constant
 * \brief he presence of the CONSTANT attibute indicates that the property value is constant.
 *
 * For a given object instance, the READ method of a constant property must return the same value every 
 * timeit is called. This constant value may be different for different instances of the object. A constant 
 * propertycannot have a WRITE method or a NOTIFY signal. 
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>constant() const</TD></TR><TR><TD>void</TD><TD>setConstant(bool nConstant)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>constantChanged(bool constant)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::constantChanged(bool constant)
 * \brief Part of the \link Property::constant constant \endlink property.
 */

/*!
 * \brief Part of the \link Property::constant constant \endlink property.
 */
bool Property::constant() const { return m_constant; }

/*!
 * \brief Part of the \link Property::constant constant \endlink property.
 */
void Property::setConstant(bool nConstant)
{
    if (nConstant != m_constant) {
        m_constant = nConstant;
#ifdef QT_DEBUG
        qDebug() << "Changed constant to" << m_constant;
#endif
        emit constantChanged(constant());
    }
}




/*!
 * \property Property::final
 * \brief he presence of the FINAL attribute indicates that the property will not be overridden by a derived class.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>final() const</TD></TR><TR><TD>void</TD><TD>setFinal(const bool &nFinal)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>finalChanged(const bool &final)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::finalChanged(const bool &final)
 * \brief Part of the \link Property::final final \endlink property.
 */

/*!
 * \brief Part of the \link Property::final final \endlink property.
 */
bool Property::final() const { return m_final; }

/*!
 * \brief Part of the \link Property::final final \endlink property.
 */
void Property::setFinal(const bool &nFinal)
{
    if (nFinal != m_final) {
        m_final = nFinal;
#ifdef QT_DEBUG
        qDebug() << "Changed final to" << m_final;
#endif
        emit finalChanged(final());
    }
}




/*!
 * \property Property::brief
 * \brief Brief description of this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>brief() const</TD></TR><TR><TD>void</TD><TD>setBrief(const QString &nBrief)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>briefChanged(const QString &brief)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::briefChanged(const QString &brief)
 * \brief Part of the \link Property::brief brief \endlink property.
 */

/*!
 * \brief Part of the \link Property::brief brief \endlink property.
 */
QString Property::brief() const { return m_brief; }

/*!
 * \brief Part of the \link Property::brief brief \endlink property.
 */
void Property::setBrief(const QString &nBrief)
{
    if (nBrief != m_brief) {
        m_brief = nBrief;
#ifdef QT_DEBUG
        qDebug() << "Changed brief to" << m_brief;
#endif
        emit briefChanged(brief());
    }
}




/*!
 * \property Property::comment
 * \brief Detailed description of this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>comment() const</TD></TR><TR><TD>void</TD><TD>setComment(const QString &nComment)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>commentChanged(const QString &comment)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::commentChanged(const QString &comment)
 * \brief Part of the \link Property::comment comment \endlink property.
 */

/*!
 * \brief Part of the \link Property::comment comment \endlink property.
 */
QString Property::comment() const { return m_comment; }

/*!
 * \brief Part of the \link Property::comment comment \endlink property.
 */
void Property::setComment(const QString &nComment)
{
    if (nComment != m_comment) {
        m_comment = nComment;
#ifdef QT_DEBUG
        qDebug() << "Changed comment to" << m_comment;
#endif
        emit commentChanged(comment());
    }
}





/*!
 * \property Property::defaultValue
 * \brief Default value of this property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>defaultValue() const</TD></TR><TR><TD>void</TD><TD>setDefaultValue(const QString &nDefaultValue)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>defaultValueChanged(const QString &defaultValue)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::defaultValueChanged(const QString &defaultValue)
 * \brief Part of the \link Property::defaultValue defaultValue \endlink property.
 */

/*!
 * \brief Part of the \link Property::defaultValue defaultValue \endlink property.
 */
QString Property::defaultValue() const { return m_defaultValue; }

/*!
 * \brief Part of the \link Property::defaultValue defaultValue \endlink property.
 */
void Property::setDefaultValue(const QString &nDefaultValue)
{
    if (nDefaultValue != m_defaultValue) {
        m_defaultValue = nDefaultValue;
#ifdef QT_DEBUG
        qDebug() << "Changed defaultValue to" << m_defaultValue;
#endif
        emit defaultValueChanged(defaultValue());
    }
}




/*!
 * \property Property::pointer
 * \brief True if this property is a pointer.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>pointer() const</TD></TR><TR><TD>void</TD><TD>setPointer(bool nPointer)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>pointerChanged(bool pointer)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::pointerChanged(bool pointer)
 * \brief Part of the \link Property::pointer pointer \endlink property.
 */

/*!
 * \brief Part of the \link Property::pointer pointer \endlink property.
 */
bool Property::pointer() const { return m_pointer; }

/*!
 * \brief Part of the \link Property::pointer pointer \endlink property.
 */
void Property::setPointer(bool nPointer)
{
    if (nPointer != m_pointer) {
        m_pointer = nPointer;
#ifdef QT_DEBUG
        qDebug() << "Changed pointer to" << m_pointer;
#endif
        emit pointerChanged(pointer());
    }
}




/*!
 * \property Property::argsByRef
 * \brief True if the parameters should be added as args by reference.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>argsByRef() const</TD></TR><TR><TD>void</TD><TD>setArgsByRef(bool nArgsByRef)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>argsByRefChanged(bool argsByRef)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::argsByRefChanged(bool argsByRef)
 * \brief Part of the \link Property::argsByRef argsByRef \endlink property.
 */

/*!
 * \brief Part of the \link Property::argsByRef argsByRef \endlink property.
 */
bool Property::argsByRef() const { return m_argsByRef; }

/*!
 * \brief Part of the \link Property::argsByRef argsByRef \endlink property.
 */
void Property::setArgsByRef(bool nArgsByRef)
{
    if (nArgsByRef != m_argsByRef) {
        m_argsByRef = nArgsByRef;
#ifdef QT_DEBUG
        qDebug() << "Changed argsByRef to" << m_argsByRef;
#endif
        emit argsByRefChanged(argsByRef());
    }
}




/*!
 * \property Property::documentMethods
 * \brief The documentMethods property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>documentMethods() const</TD></TR><TR><TD>void</TD><TD>setDocumentMethods(bool nDocumentMethods)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>documentMethodsChanged(bool documentMethods)</TD></TR></TABLE>
 */

/*!
 * \fn void Property::documentMethodsChanged(bool documentMethods)
 * \brief Part of the \link Property::documentMethods documentMethods \endlink property.
 */

/*!
 * \brief Part of the \link Property::documentMethods documentMethods \endlink property.
 */
bool Property::documentMethods() const { return m_documentMethods; }

/*!
 * \brief Part of the \link Property::documentMethods documentMethods \endlink property.
 */
void Property::setDocumentMethods(bool nDocumentMethods)
{
    if (nDocumentMethods != m_documentMethods) {
        m_documentMethods = nDocumentMethods;
#ifdef QT_DEBUG
        qDebug() << "Changed documentMethods to" << m_documentMethods;
#endif
        emit documentMethodsChanged(documentMethods());
    }
}



QStringList Property::commentParts() const
{
    QStringList parts;

    QString c = comment().trimmed();

    if (!c.isEmpty()) {
        if (c.size() > 100) {
            const QStringList paragraphs = c.split(QRegularExpression(QStringLiteral("\\n+")));
            if (Q_LIKELY(!paragraphs.isEmpty())) {
                for (const QString &paragraph : paragraphs) {
                    const QStringList wordParts = paragraph.split(QRegularExpression(QStringLiteral("\\s+")), QString::SkipEmptyParts);
                    if (Q_LIKELY(!wordParts.isEmpty())) {
                        QString partString;
                        for (const QString &part : wordParts) {
                            if (partString.size() < 100) {
                                partString.append(part);
                                partString.append(QLatin1String(" "));
                            } else {
                                parts << partString.trimmed();
                                partString.clear();
                            }
                        }
                        if (!partString.trimmed().isEmpty()) {
                            parts << partString.trimmed();
                        }
                    }
                    parts << QString();
                }
                parts.removeLast();
            }
        } else {
            parts << c;
        }
    }

    return parts;
}
