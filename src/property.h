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

#ifndef PROPERTY
#define PROPERTY

#include <QString>
#include <QtGlobal>
#include "propertymodel.h"

/*!
 * \brief The Property struct
 */
struct Property {
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
};

Q_DECLARE_TYPEINFO(Property, Q_PRIMITIVE_TYPE);

#endif // PROPERTY

