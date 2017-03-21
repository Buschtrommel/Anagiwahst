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

ApplicationWindow {
    id: anagiwahst
    visible: true
    width: config.windowWidth
    height: config.windowHeight
    minimumWidth: 600
    minimumHeight: 600

    Component.onDestruction: {
        config.windowWidth = anagiwahst.width
        config.windowHeight = anagiwahst.height
    }

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: ScrollView {
            id: welcomeScroll
            width: parent ? parent.width : anagiwahst.width
            GridLayout {
                columns: 2
                width: parent.width
                ColumnLayout {
                    Layout.alignment: Qt.AlignTop
                    Layout.minimumWidth: 180
                    Layout.preferredWidth: anagiwahst.width * 0.25
                    Layout.margins: 9
                    Button {
                        text: qsTr("New project")
                        iconName: "project-development-new-template"
                        Layout.fillWidth: true
                        onClicked: stack.push({item: Qt.resolvedUrl("ProjectEdit.qml"), replace: false})
                    }
                }

                Column {
                    Layout.minimumWidth: 360
                    Layout.fillWidth: true
                    Layout.margins: 9
                    spacing: 9
                    Repeater {
                        model: filteredProjects
                        delegate: prjGridDelegate
                    }
                }
            }
        }
    }

    Component {
        id: prjGridDelegate
        Rectangle {
            width: parent ? parent.width : 0
            height: prjItemCol.height
            color: mousa.containsMouse ? "white" : "transparent"

            MouseArea {
                id: mousa
                anchors.fill: parent
                hoverEnabled: true
                onClicked: stack.push({item: Qt.resolvedUrl("ProjectView.qml"), replace: false, properties: {project: model.item}})
            }

            ColumnLayout {
                id: prjItemCol
                width: parent.width
                Label {
                    text: model.item.name
                }

                Label {
                    text: qsTr("Last change: %1").arg(model.item.updatedAt.toLocaleString(Qt.locale(), Locale.ShortFormat))
                }
            }
        }
    }

    MessageDialog {
        id: delPrjDialog
        property string name
        property int projectId
        title: qsTr("Delete project %1").arg(name)
        text: qsTr("Do you really want delete this project? This will also delete all classes and properties.")
        icon: StandardIcon.Warning
        standardButtons: StandardButton.No | StandardButton.Yes
        onYes: {
            projects.deleteProject(projectId)
            stack.pop()
        }
    }
}

