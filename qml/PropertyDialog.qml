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
import QtQuick.Dialogs 1.2
import Buschtrommel.Anagiwahst 1.0

Dialog {
    id: propDialog
    title: qsTr("Create new property")

    property PropertyModel propsModel
    property Unit unit

    standardButtons: StandardButton.Ok | StandardButton.Cancel

    ColumnLayout {
        width: parent.width
        RowLayout {
            LabeledTextField {
                id: name
                label: qsTr("Name")
                Layout.fillWidth: true
            }

            LabeledTextField {
                id: type
                label: qsTr("Type")
                Layout.fillHeight: true
            }
        }

        RowLayout {
            CheckBox {
                id: read
                text: qsTr("Read")
                checked: unit.read
            }

            CheckBox {
                id: write
                text: qsTr("Write")
                checked: unit.write
            }

            CheckBox {
                id: notify
                text: qsTr("Notify")
                checked: unit.notify
            }

            CheckBox {
                id: member
                text: qsTr("Member")
                checked: unit.member
            }

            CheckBox {
                id: reset
                text: qsTr("Reset")
                checked: unit.reset
            }
        }

        RowLayout {
            CheckBox {
                id: propread
                text: qsTr("Use property name for Read")
                checked: unit.propread
            }
        }
    }

    onAccepted: {
        propsModel.createProperty(name.text, type.text, read.checked, write.checked, member.checked, reset.checked, notify.checked, unit.docmethod, propread.checked)
    }
}
