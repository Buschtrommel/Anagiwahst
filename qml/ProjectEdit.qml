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
    id: prjEdit
    property Project project: null

    objectName: "projectEdit"

    width: parent.width
    height: parent.height

    ColumnLayout {
        id: prjCol
        anchors.fill: parent

        Label {
            text: project ? qsTr("Edit project") : qsTr("Create a new project")
        }

        GroupBox {
            Layout.fillWidth: true

            GridLayout {
                columns: prjEdit.width > 450 ? 2 : 1
                width: parent.width

                LabeledTextField {
                    id: name
                    label: qsTr("Project name")
                    text: project ? project.name : ""
                }

                LabeledTextField {
                    id: namespaces
                    label: qsTr("Default namespaces")
                    text: project ? project.namespaces : ""
                }
            }
        }

        GroupBox {
            title: qsTr("Default settings")
            Layout.fillWidth: true

            GridLayout {
                width: parent.width
                columns: prjEdit.width > 450 ? 3 : 1

                ColumnLayout {
                    CheckBox {
                        id: read
                        text: qsTr("Read")
                        checked: project ? project.read : true
                    }

                    CheckBox {
                        id: write
                        text: qsTr("Write")
                        checked: project ? project.write: true
                    }

                    CheckBox {
                        id: notify
                        text: qsTr("Notify")
                        checked: project ? project.notify : true
                    }
                }

                ColumnLayout {
                    Layout.alignment: Qt.AlignTop

                    CheckBox {
                        id: member
                        text: qsTr("Member")
                        checked: project ? project.member: false
                    }

                    CheckBox {
                        id: reset
                        text: qsTr("Reset")
                        checked: project ? project.reset: false
                    }
                }

                ColumnLayout {
                    Layout.alignment: Qt.AlignTop

                    CheckBox {
                        id: propread
                        text: qsTr("Use property name for Read")
                        Layout.columnSpan: 3
                        checked: project ? project.propread : false
                    }

                    CheckBox {
                        id: docmethod
                        text: qsTr("Document methods")
                        Layout.columnSpan: 3
                        checked: project ? project.docmethod : true
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
                text: project ? project.license : ""
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignBottom

            Button {
                iconName: project ? "arrow-left" : "dialog-cancel"
                text: project ? qsTr("Back") : qsTr("Cancel")
                onClicked: stack.pop()
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                iconName: "dialog-ok-apply"
                text: project ? qsTr("Update") : qsTr("Create")
                onClicked: {
                    if (prjEdit.project) {
                        projects.updateProject(project.id, name.text, license.text, namespaces.text, read.checked, write.checked, member.checked, reset.checked, notify.checked, propread.checked, docmethod.checked, "default_qobject")
                        stack.pop()
                    } else {
                        var prj = projects.createProject(name.text, license.text, namespaces.text, read.checked, write.checked, member.checked, reset.checked, notify.checked, propread.checked, docmethod.checked, "default_qobject")
                        stack.push({item: Qt.resolvedUrl("ProjectView.qml"), replace: true, properties: {project: prj}})
                    }
                }
            }
        }
    }
}
