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

SplitView {
    id: projectView
    objectName: "projectView"

    width: parent.width
    height: parent.height

    property Project project: null

    Item {
        id: leftCol
        Layout.minimumWidth: 200
        Layout.preferredWidth: anagiwahst.width * 0.2
        Layout.fillWidth: false
        readonly property int childMargins: 5

        ColumnLayout {
            width: parent.width
            height: parent.height

            Label {
                text: project ? project.name : ""
                font.pointSize: 16
                Layout.leftMargin: leftCol.childMargins
                Layout.rightMargin: leftCol.childMargins
            }

            Button {
                iconName: "configure_project"
                text: qsTr("Configure project")
                Layout.leftMargin: leftCol.childMargins
                Layout.rightMargin: leftCol.childMargins
                Layout.fillWidth: true
                onClicked: stack.push({item: Qt.resolvedUrl("ProjectEdit.qml"), replace: false, properties: {project: projectView.project}})
            }

            Button {
                iconName: "delete"
                text: qsTr("Delete project")
                Layout.leftMargin: leftCol.childMargins
                Layout.rightMargin: leftCol.childMargins
                Layout.fillWidth: true
                onClicked: {
                    delPrjDialog.name = projectView.project.name
                    delPrjDialog.projectId = projectView.project.id
                    delPrjDialog.open()
                }
            }

            Button {
                iconName: "project-development-close"
                text: qsTr("Close project")
                Layout.leftMargin: leftCol.childMargins
                Layout.rightMargin: leftCol.childMargins
                Layout.fillWidth: true
                onClicked: stack.pop()
            }

            Button {
                iconName: "list-add"
                text: qsTr("Add class")
                Layout.leftMargin: leftCol.childMargins
                Layout.rightMargin: leftCol.childMargins
                Layout.fillWidth: true
            }

            TableView {
                Layout.fillWidth: true
                Layout.fillHeight: true

                TableViewColumn {
                    role: "item"
                    title: qsTr("Classes")
                    delegate: TableText {
                        text: styleData.value ? styleData.value.name : ""
                    }
                }
            }
        }
    }

    ScrollView {
        Layout.fillWidth: true
    }

    ScrollView {
        Layout.minimumWidth: 200
        Layout.preferredWidth: anagiwahst.width * 0.2
        Layout.fillWidth: false
    }
}
