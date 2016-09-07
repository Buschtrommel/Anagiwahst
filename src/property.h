#ifndef PROPERTY_H
#define PROPERTY_H

#include <QObject>

class PropertyPrivate;

/*!
 * \brief The Property class.
 */
class Property : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString read READ read WRITE setRead NOTIFY readChanged)
    Q_PROPERTY(QString write READ write WRITE setWrite NOTIFY writeChanged)
    Q_PROPERTY(QString member READ member WRITE setMember NOTIFY memberChanged)
    Q_PROPERTY(QString reset READ reset WRITE setReset NOTIFY resetChanged)
    Q_PROPERTY(QString notify READ notify WRITE setNotify NOTIFY notifyChanged)
    Q_PROPERTY(quint8 revision READ revision WRITE setRevision NOTIFY revisionChanged)
    Q_PROPERTY(QString designable READ designable WRITE setDesignable NOTIFY designableChanged)
    Q_PROPERTY(QString scriptable READ scriptable WRITE setScriptable NOTIFY scriptableChanged)
    Q_PROPERTY(bool stored READ stored WRITE setStored NOTIFY storedChanged)
    Q_PROPERTY(bool user READ user WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(bool constant READ constant WRITE setConstant NOTIFY constantChanged)
    Q_PROPERTY(bool final READ final WRITE setFinal NOTIFY finalChanged)
    Q_PROPERTY(QString brief READ brief WRITE setBrief NOTIFY briefChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)
    Q_PROPERTY(bool privateClass READ privateClass WRITE setPrivateClass NOTIFY privateClassChanged)
    Q_PROPERTY(QString defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)
    Q_PROPERTY(bool pointer READ pointer WRITE setPointer NOTIFY pointerChanged)
    Q_PROPERTY(bool argsByRef READ argsByRef WRITE setArgsByRef NOTIFY argsByRefChanged)
    Q_PROPERTY(bool documentMethods READ documentMethods WRITE setDocumentMethods NOTIFY documentMethodsChanged)
public:
    explicit Property(QObject *parent = nullptr);
    Property(int id, const QString &name, const QString &type, const QString &read, const QString &write, const QString &member, const QString &reset, const QString &notify, bool privateClass, const QString &defaultValue, bool argsByRef, bool pointer, bool docMethods, QObject *parent = nullptr);
    ~Property();

    int id() const;
    QString name() const;
    QString type() const;
    QString read() const;
    QString write() const;
    QString member() const;
    QString reset() const;
    QString notify() const;
    quint8 revision() const;
    QString designable() const;
    QString scriptable() const;
    bool stored() const;
    bool user() const;
    bool constant() const;
    bool final() const;
    QString brief() const;
    QString comment() const;
    bool privateClass() const;
    QString defaultValue() const;
    bool pointer() const;
    bool argsByRef() const;
    bool documentMethods() const;

    void setId(int nId);
    void setName(const QString &nName);
    void setType(const QString &nType);
    void setRead(const QString &nRead);
    void setWrite(const QString &nWrite);
    void setMember(const QString &nMember);
    void setReset(const QString &nReset);
    void setNotify(const QString &nNotify);
    void setRevision(quint8 nRevision);
    void setDesignable(const QString &nDesignable);
    void setScriptable(const QString &nScriptable);
    void setStored(bool nStored);
    void setUser(bool nUser);
    void setConstant(bool nConstant);
    void setFinal(const bool &nFinal);
    void setBrief(const QString &nBrief);
    void setComment(const QString &nComment);
    void setPrivateClass(bool nPrivateClass);
    void setDefaultValue(const QString &nDefaultValue);
    void setPointer(bool nPointer);
    void setArgsByRef(bool nArgsByRef);
    void setDocumentMethods(bool nDocumentMethods);

signals:
    void idChanged(int id);
    void nameChanged(const QString &name);
    void typeChanged(const QString &type);
    void readChanged(const QString &read);
    void writeChanged(const QString &write);
    void memberChanged(const QString &member);
    void resetChanged(const QString &reset);
    void notifyChanged(const QString &notify);
    void revisionChanged(quint8 revision);
    void designableChanged(const QString &designable);
    void scriptableChanged(const QString &scriptable);
    void storedChanged(bool stored);
    void userChanged(bool user);
    void constantChanged(bool constant);
    void finalChanged(const bool &final);
    void briefChanged(const QString &brief);
    void commentChanged(const QString &comment);
    void privateClassChanged(bool privateClass);
    void defaultValueChanged(const QString &defaultValue);
    void pointerChanged(bool pointer);
    void argsByRefChanged(bool argsByRef);
    void documentMethodsChanged(bool documentMethods);

protected:
    const QScopedPointer<PropertyPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Property)
    Q_DECLARE_PRIVATE(Property)

};

#endif // PROPERTY_H
