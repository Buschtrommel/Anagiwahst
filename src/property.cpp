#include "property_p.h"
#include <QRegularExpression>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

/*!
 * \brief Constructs a new Property object.
 */
Property::Property(QObject *parent) :
    QObject(parent), d_ptr(new PropertyPrivate)
{
}


/*!
 * \overload
 */
Property::Property(int id, const QString &name, const QString &type, const QString &read, const QString &write, const QString &member, const QString &reset, const QString &notify, const QString &defaultValue, bool argsByRef, bool pointer, bool docMethods, QObject *parent) :
    QObject(parent), d_ptr(new PropertyPrivate)
{
    Q_D(Property);
    d->id = id;
    d->name = name;
    d->type = type;
    d->read = read;
    d->write = write;
    d->member = member;
    d->reset = reset;
    d->notify = notify;
    d->defaultValue = defaultValue;
    d->argsByRef = argsByRef;
    d->pointer = pointer;
    d->documentMethods = docMethods;
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
int Property::id() const { Q_D(const Property); return d->id; }

/*!
 * \brief Part of the \link Property::id id \endlink property.
 */
void Property::setId(int nId)
{
    Q_D(Property); 
    if (nId != d->id) {
        d->id = nId;
#ifdef QT_DEBUG
        qDebug() << "Changed id to" << d->id;
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
QString Property::name() const { Q_D(const Property); return d->name; }

/*!
 * \brief Part of the \link Property::name name \endlink property.
 */
void Property::setName(const QString &nName)
{
    Q_D(Property); 
    if (nName != d->name) {
        d->name = nName;
#ifdef QT_DEBUG
        qDebug() << "Changed name to" << d->name;
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
QString Property::type() const { Q_D(const Property); return d->type; }

/*!
 * \brief Part of the \link Property::type type \endlink property.
 */
void Property::setType(const QString &nType)
{
    Q_D(Property); 
    if (nType != d->type) {
        d->type = nType;
#ifdef QT_DEBUG
        qDebug() << "Changed type to" << d->type;
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
QString Property::read() const { Q_D(const Property); return d->read; }

/*!
 * \brief Part of the \link Property::read read \endlink property.
 */
void Property::setRead(const QString &nRead)
{
    Q_D(Property); 
    if (nRead != d->read) {
        d->read = nRead;
#ifdef QT_DEBUG
        qDebug() << "Changed read to" << d->read;
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
QString Property::write() const { Q_D(const Property); return d->write; }

/*!
 * \brief Part of the \link Property::write write \endlink property.
 */
void Property::setWrite(const QString &nWrite)
{
    Q_D(Property); 
    if (nWrite != d->write) {
        d->write = nWrite;
#ifdef QT_DEBUG
        qDebug() << "Changed write to" << d->write;
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
QString Property::member() const { Q_D(const Property); return d->member; }

/*!
 * \brief Part of the \link Property::member member \endlink property.
 */
void Property::setMember(const QString &nMember)
{
    Q_D(Property); 
    if (nMember != d->member) {
        d->member = nMember;
#ifdef QT_DEBUG
        qDebug() << "Changed member to" << d->member;
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
QString Property::reset() const { Q_D(const Property); return d->reset; }

/*!
 * \brief Part of the \link Property::reset reset \endlink property.
 */
void Property::setReset(const QString &nReset)
{
    Q_D(Property); 
    if (nReset != d->reset) {
        d->reset = nReset;
#ifdef QT_DEBUG
        qDebug() << "Changed reset to" << d->reset;
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
QString Property::notify() const { Q_D(const Property); return d->notify; }

/*!
 * \brief Part of the \link Property::notify notify \endlink property.
 */
void Property::setNotify(const QString &nNotify)
{
    Q_D(Property); 
    if (nNotify != d->notify) {
        d->notify = nNotify;
#ifdef QT_DEBUG
        qDebug() << "Changed notify to" << d->notify;
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
quint8 Property::revision() const { Q_D(const Property); return d->revision; }

/*!
 * \brief Part of the \link Property::revision revision \endlink property.
 */
void Property::setRevision(quint8 nRevision)
{
    Q_D(Property); 
    if (nRevision != d->revision) {
        d->revision = nRevision;
#ifdef QT_DEBUG
        qDebug() << "Changed revision to" << d->revision;
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
QString Property::designable() const { Q_D(const Property); return d->designable; }

/*!
 * \brief Part of the \link Property::designable designable \endlink property.
 */
void Property::setDesignable(const QString &nDesignable)
{
    Q_D(Property); 
    if (nDesignable != d->designable) {
        d->designable = nDesignable;
#ifdef QT_DEBUG
        qDebug() << "Changed designable to" << d->designable;
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
QString Property::scriptable() const { Q_D(const Property); return d->scriptable; }

/*!
 * \brief Part of the \link Property::scriptable scriptable \endlink property.
 */
void Property::setScriptable(const QString &nScriptable)
{
    Q_D(Property); 
    if (nScriptable != d->scriptable) {
        d->scriptable = nScriptable;
#ifdef QT_DEBUG
        qDebug() << "Changed scriptable to" << d->scriptable;
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
bool Property::stored() const { Q_D(const Property); return d->stored; }

/*!
 * \brief Part of the \link Property::stored stored \endlink property.
 */
void Property::setStored(bool nStored)
{
    Q_D(Property); 
    if (nStored != d->stored) {
        d->stored = nStored;
#ifdef QT_DEBUG
        qDebug() << "Changed stored to" << d->stored;
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
bool Property::user() const { Q_D(const Property); return d->user; }

/*!
 * \brief Part of the \link Property::user user \endlink property.
 */
void Property::setUser(bool nUser)
{
    Q_D(Property); 
    if (nUser != d->user) {
        d->user = nUser;
#ifdef QT_DEBUG
        qDebug() << "Changed user to" << d->user;
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
bool Property::constant() const { Q_D(const Property); return d->constant; }

/*!
 * \brief Part of the \link Property::constant constant \endlink property.
 */
void Property::setConstant(bool nConstant)
{
    Q_D(Property); 
    if (nConstant != d->constant) {
        d->constant = nConstant;
#ifdef QT_DEBUG
        qDebug() << "Changed constant to" << d->constant;
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
bool Property::final() const { Q_D(const Property); return d->final; }

/*!
 * \brief Part of the \link Property::final final \endlink property.
 */
void Property::setFinal(const bool &nFinal)
{
    Q_D(Property); 
    if (nFinal != d->final) {
        d->final = nFinal;
#ifdef QT_DEBUG
        qDebug() << "Changed final to" << d->final;
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
QString Property::brief() const { Q_D(const Property); return d->brief; }

/*!
 * \brief Part of the \link Property::brief brief \endlink property.
 */
void Property::setBrief(const QString &nBrief)
{
    Q_D(Property); 
    if (nBrief != d->brief) {
        d->brief = nBrief;
#ifdef QT_DEBUG
        qDebug() << "Changed brief to" << d->brief;
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
QString Property::comment() const { Q_D(const Property); return d->comment; }

/*!
 * \brief Part of the \link Property::comment comment \endlink property.
 */
void Property::setComment(const QString &nComment)
{
    Q_D(Property); 
    if (nComment != d->comment) {
        d->comment = nComment;
#ifdef QT_DEBUG
        qDebug() << "Changed comment to" << d->comment;
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
QString Property::defaultValue() const { Q_D(const Property); return d->defaultValue; }

/*!
 * \brief Part of the \link Property::defaultValue defaultValue \endlink property.
 */
void Property::setDefaultValue(const QString &nDefaultValue)
{
    Q_D(Property); 
    if (nDefaultValue != d->defaultValue) {
        d->defaultValue = nDefaultValue;
#ifdef QT_DEBUG
        qDebug() << "Changed defaultValue to" << d->defaultValue;
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
bool Property::pointer() const { Q_D(const Property); return d->pointer; }

/*!
 * \brief Part of the \link Property::pointer pointer \endlink property.
 */
void Property::setPointer(bool nPointer)
{
    Q_D(Property); 
    if (nPointer != d->pointer) {
        d->pointer = nPointer;
#ifdef QT_DEBUG
        qDebug() << "Changed pointer to" << d->pointer;
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
bool Property::argsByRef() const { Q_D(const Property); return d->argsByRef; }

/*!
 * \brief Part of the \link Property::argsByRef argsByRef \endlink property.
 */
void Property::setArgsByRef(bool nArgsByRef)
{
    Q_D(Property); 
    if (nArgsByRef != d->argsByRef) {
        d->argsByRef = nArgsByRef;
#ifdef QT_DEBUG
        qDebug() << "Changed argsByRef to" << d->argsByRef;
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
bool Property::documentMethods() const { Q_D(const Property); return d->documentMethods; }

/*!
 * \brief Part of the \link Property::documentMethods documentMethods \endlink property.
 */
void Property::setDocumentMethods(bool nDocumentMethods)
{
    Q_D(Property);
    if (nDocumentMethods != d->documentMethods) {
        d->documentMethods = nDocumentMethods;
#ifdef QT_DEBUG
        qDebug() << "Changed documentMethods to" << d->documentMethods;
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
