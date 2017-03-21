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
    property Unit currentUnit: null
    property alias unitModel: um
    readonly property int childMargins: 5

    Item {
        id: leftCol
        Layout.minimumWidth: 200
        Layout.preferredWidth: anagiwahst.width * 0.2
        Layout.fillWidth: false

        ColumnLayout {
            width: parent.width
            height: parent.height

            Header {
                text: project ? project.name : ""
                Layout.leftMargin: projectView.childMargins
                Layout.rightMargin: projectView.childMargins
            }

            Button {
                iconName: "project-development-close"
                text: qsTr("Close project")
                Layout.leftMargin: projectView.childMargins
                Layout.rightMargin: projectView.childMargins
                Layout.fillWidth: true
                onClicked: {
                    anagiwahst.title = ""
                    stack.pop()
                }
            }

            Button {
                iconName: "list-add"
                text: qsTr("Add class")
                Layout.leftMargin: projectView.childMargins
                Layout.rightMargin: projectView.childMargins
                Layout.fillWidth: true
                onClicked: stack.push({item: Qt.resolvedUrl("UnitEdit.qml"), replace: false, properties: {project: projectView.project, unitModel: um}})
            }

            TableView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: UnitModel { id: um; projectId: project ? project.id : -1 }

                onCurrentRowChanged: {
                    projectView.currentUnit = model.get(currentRow)
                }

                TableViewColumn {
                    role: "item"
                    title: qsTr("Classes")
                    delegate: TableText {
                        text: styleData.value ? styleData.value.displayName : ""
                    }
                }
            }
        }
    }

    Item {
        Layout.fillWidth: true

        ColumnLayout {
            width: parent.width
            height: parent.height

            Header {
                text: currentUnit ? currentUnit.displayName : ""
                Layout.leftMargin: projectView.childMargins
                Layout.rightMargin: projectView.childMargins
            }

            ListView {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }

//    ScrollView {
//        Layout.minimumWidth: 200
//        Layout.preferredWidth: anagiwahst.width * 0.2
//        Layout.fillWidth: false
//    }
}
