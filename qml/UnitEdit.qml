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

Item {
    id: unitEdit
    property Project project: null
    property Unit unit: null
    property UnitModel unitModel: null

    objectName: "unitEdit"

    width: parent.width
    height: parent.height

    ColumnLayout {
        id: prjCol
        anchors.fill: parent

        Header {
            text: unit ? qsTr("Edit class") : qsTr("Create a new class")
        }

        GroupBox {
            Layout.fillWidth: true

            GridLayout {
                columns: unitEdit.width > 450 ? 2 : 1
                width: parent.width

                LabeledTextField {
                    id: name
                    label: qsTr("Class name")
                    text: unit ? unit.name : ""
                }

                LabeledTextField {
                    id: namespaces
                    label: qsTr("Namespaces")
                    text: unit ? unit.namespaces : project.namespaces
                }
            }
        }

        GroupBox {
            title: qsTr("Default settings")
            Layout.fillWidth: true

            GridLayout {
                width: parent.width
                columns: unitEdit.width > 450 ? 3 : 1

                ColumnLayout {
                    CheckBox {
                        id: read
                        text: qsTr("Read")
                        checked: unit ? unit.read : project.read
                    }

                    CheckBox {
                        id: write
                        text: qsTr("Write")
                        checked: unit ? unit.write: project.write
                    }

                    CheckBox {
                        id: notify
                        text: qsTr("Notify")
                        checked: unit ? unit.notify : project.notify
                    }
                }

                ColumnLayout {
                    Layout.alignment: Qt.AlignTop

                    CheckBox {
                        id: member
                        text: qsTr("Member")
                        checked: unit ? unit.member: project.member
                    }

                    CheckBox {
                        id: reset
                        text: qsTr("Reset")
                        checked: unit ? unit.reset: project.member
                    }
                }

                ColumnLayout {
                    Layout.alignment: Qt.AlignTop

                    CheckBox {
                        id: propread
                        text: qsTr("Use property name for Read")
                        Layout.columnSpan: 3
                        checked: unit ? unit.propread : project.propread
                    }

                    CheckBox {
                        id: docmethod
                        text: qsTr("Document methods")
                        Layout.columnSpan: 3
                        checked: unit ? unit.docmethod : project.docmethod
                    }
                }
            }
        }

        GroupBox {
            title: qsTr("License header")
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextArea {
                id: license
                width: parent.width
                height: parent.height
                textFormat: Text.PlainText
                text: unit ? unit.license : project.license
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignBottom

            Button {
                iconName: unit ? "arrow-left" : "dialog-cancel"
                text: unit ? qsTr("Back") : qsTr("Cancel")
                onClicked: stack.pop()
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                iconName: "dialog-ok-apply"
                text: unit ? qsTr("Update") : qsTr("Create")
                onClicked: {
                    if (unitEdit.unit) {
                        unitModel.updateUnit(unit.id, name.text, license.text, namespaces.text, read.checked, write.checked, member.checked, reset.checked, notify.checked, propread.checked, docmethod.checked, "default_qobject")
                    } else {
                        unitModel.createUnit(name.text, license.text, namespaces.text, read.checked, write.checked, member.checked, reset.checked, notify.checked, propread.checked, docmethod.checked, "default_qobject");
                    }
                    stack.pop();
                }
            }
        }
    }
}
