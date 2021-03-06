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

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import Buschtrommel.Anagiwahst 1.0

ColumnLayout {
    id: labeledTextField
    property alias label: textLabel.text
    property alias text: textField.text
    property alias validator: textField.validator
    property alias inputMethodHints: textField.inputMethodHints

    function setFocus() {
        textField.forceActiveFocus()
    }

    Label {
        id: textLabel
        width: parent.width
        Layout.fillWidth: true
    }

    TextField {
        id: textField
        width: parent.width
        Layout.fillWidth: true
    }
}

