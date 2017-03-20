/* Anagiwahst - A Qt Property Editor/Creator
 *
 * Copyright (c) 2015-2017 Buschtrommel/Matthias Fehring <kontakt@buschmann23.de>
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

#ifndef PROPERTY_H
#define PROPERTY_H

#include <QObject>

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
    Q_PROPERTY(QString defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)
    Q_PROPERTY(bool pointer READ pointer WRITE setPointer NOTIFY pointerChanged)
    Q_PROPERTY(bool argsByRef READ argsByRef WRITE setArgsByRef NOTIFY argsByRefChanged)
    Q_PROPERTY(bool documentMethods READ documentMethods WRITE setDocumentMethods NOTIFY documentMethodsChanged)
    Q_PROPERTY(QStringList commentParts READ commentParts)
public:
    explicit Property(QObject *parent = nullptr);
    Property(int id, const QString &name, const QString &type, const QString &read, const QString &write, const QString &member, const QString &reset, const QString &notify, const QString &defaultValue, bool argsByRef, bool pointer, bool docMethods, QObject *parent = nullptr);
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
    QString defaultValue() const;
    bool pointer() const;
    bool argsByRef() const;
    bool documentMethods() const;
    QStringList commentParts() const;

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
    void defaultValueChanged(const QString &defaultValue);
    void pointerChanged(bool pointer);
    void argsByRefChanged(bool argsByRef);
    void documentMethodsChanged(bool documentMethods);

private:
    int m_id = 0;
    QString m_name;
    QString m_type;
    QString m_read;
    QString m_write;
    QString m_member;
    QString m_reset;
    QString m_notify;
    quint8 m_revision = 0;
    QString m_designable;
    QString m_scriptable;
    bool m_stored = true;
    bool m_user = false;
    bool m_constant = false;
    bool m_final = false;
    QString m_brief;
    QString m_comment;
    QString m_defaultValue;
    bool m_argsByRef = false;
    bool m_pointer = false;
    bool m_documentMethods = true;

    Q_DISABLE_COPY(Property)
};

#endif // PROPERTY_H
