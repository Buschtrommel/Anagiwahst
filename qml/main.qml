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

    function setTitle(prj) {
        if (prj) {
            anagiwahst.title = "Anagiwahst - " + prj
        } else {
            anagiwahst.title = "Anagiwahst"
        }
    }

    Component.onDestruction: {
        config.windowWidth = anagiwahst.width
        config.windowHeight = anagiwahst.height
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")

            MenuItem {
                text: qsTr("Exit")
                shortcut: StandardKey.Quit
                iconName: "application-exit"
                onTriggered: Qt.quit()
            }
        }

        Menu {
            title: qsTr("&Project")

            MenuItem {
                text: qsTr("New project")
                shortcut: qsTr("Ctrl+Shift+N")
                enabled: stack.currentItem.objectName === "welcomeView"
                iconName: "project-development-new-template"
                onTriggered: stack.push({item: Qt.resolvedUrl("ProjectEdit.qml"), replace: false})
            }

            MenuItem {
                text: qsTr("Edit project")
                enabled: stack.currentItem.objectName === "projectView"
                iconName: "configure_project"
                onTriggered: stack.push({item: Qt.resolvedUrl("ProjectEdit.qml"), replace: false, properties: {project: stack.currentItem.project}})
            }

            MenuItem {
                text: qsTr("Delete project")
                enabled: stack.currentItem.objectName === "projectView"
                iconName: "delete"
                onTriggered: {
                    delPrjDialog.name = stack.currentItem.project.name
                    delPrjDialog.projectId = stack.currentItem.project.id
                    delPrjDialog.open()
                }
            }

            MenuItem {
                text: qsTr("Close project")
                enabled: stack.currentItem.objectName === "projectView"
                iconName: "project-development-close"
                shortcut: StandardKey.Close
                onTriggered: stack.pop()
            }
        }

        Menu {
            title: qsTr("&Class")
            visible: stack.currentItem.objectName === "projectView"

            MenuItem {
                text: qsTr("Add new class")
                shortcut: qsTr("Ctrl+Shift+N")
                iconName: "list-add"
                enabled: stack.currentItem.objectName === "projectView"
                onTriggered: stack.push({item: Qt.resolvedUrl("UnitEdit.qml"), replace: false, properties: {project: stack.currentItem.project, unitModel: stack.currentItem.unitModel}})
            }

            MenuItem {
                text: qsTr("Edit class")
                iconName: "configure"
                enabled: stack.currentItem.objectName === "projectView" && stack.currentItem.currentUnit
                onTriggered: stack.push({item: Qt.resolvedUrl("UnitEdit.qml"), replace: false, properties: {project: stack.currentItem.project, unitModel: stack.currentItem.unitModel, unit: stack.currentItem.currentUnit}})
            }

            MenuItem {
                text: qsTr("Delete class")
                iconName: "delete"
                enabled: stack.currentItem.objectName === "projectView" && stack.currentItem.currentUnit
                shortcut: qsTr("Shift+Del")
                onTriggered: {
                    delUnitDialog.name = stack.currentItem.currentUnit.name
                    delUnitDialog.unitId = stack.currentItem.currentUnit.id
                    delUnitDialog.open()
                }
            }

            MenuItem {
                text: qsTr("Build class")
                iconName: "run-build-file"
                shortcut: qsTr("Ctrl+R")
                enabled: stack.currentItem.objectName === "projectView" && stack.currentItem.currentUnit
            }
        }
    }

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: ScrollView {
            id: welcomeScroll
            objectName: "welcomeView"
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
                onClicked: {
                    anagiwahst.title = model.item.name
                    stack.push({item: Qt.resolvedUrl("ProjectView.qml"), replace: false, properties: {project: model.item}})
                }
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
            anagiwahst.title = ""
            stack.pop()
        }
    }

    MessageDialog {
        id: delUnitDialog
        property string name
        property string unitId
        title: qsTr("Delete class %1").arg(name)
        text: qsTr("Do you really want delete this class? This will also delete all properties.")
        icon: StandardIcon.Warning
        standardButtons: StandardButton.No | StandardButton.Yes
        onYes: {
            stack.currentItem.currentUnit = null
            stack.currentItem.unitModel.deleteUnit(unitId)
        }
    }
}

