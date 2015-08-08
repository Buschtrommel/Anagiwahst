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

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import Buschtrommel.Anagiwahst.Models 1.0

ApplicationWindow {
    id: anagiwahst
    visible: true
    width: 640
    height: 480

    property int rowCount: -1
    property int currentRow: -1
    property bool editChanged: false

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")

            MenuItem {
                text: qsTr("New tab")
                shortcut: StandardKey.AddTab
                iconName: "tab-new"
                onTriggered: {
                    var newTab = mainContent.addTab(qsTr("New class"))
                    newTab.setSource("FileTab.qml", {file: ""})
                    mainContent.currentIndex = mainContent.count-1
                }
            }

            MenuItem {
                text: qsTr("Read from file")
                shortcut: StandardKey.Open
                iconName: "document-open"
                onTriggered: openFileDialog.open()
            }

            MenuSeparator {}

            MenuItem {
                text: anagiwahst.title !== "" ? qsTr("Close \"%1\"").arg(anagiwahst.title) : qsTr("Close")
                shortcut: StandardKey.Close
                iconName: "tab-close"
                enabled: mainContent.count > 0
                onTriggered: mainContent.removeTab(mainContent.currentIndex)
            }

            MenuItem {
                text: qsTr("Close all")
                shortcut: "Ctrl+Shift+W"
                iconName: "tab-close"
                enabled: mainContent.count > 1
                onTriggered: {
                    while(mainContent.count > 0) {
                        mainContent.removeTab(0)
                    }
                }
            }

            MenuItem {
                text: anagiwahst.title !== "" ? qsTr("Close all except \"%1\"").arg(anagiwahst.title) : qsTr("Close all except ...")
                iconName: "tab-close-other"
                enabled: mainContent.count > 1
                onTriggered: {
                    var current = mainContent.currentIndex
                    mainContent.moveTab(current, 0)
                    while(mainContent.count > 1) {
                        mainContent.removeTab(1)
                    }
                }
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Exit")
                shortcut: StandardKey.Quit
                iconName: "application-exit"
                onTriggered: Qt.quit()
            }
        }

        Menu {
            title: qsTr("&Edit")

            MenuItem {
                text: qsTr("New property")
                enabled: mainContent.count > 0
                iconName: "document-new"
                shortcut: StandardKey.New
                onTriggered: mainContent.getTab(mainContent.currentIndex).item.newProperty()
            }

            MenuItem {
                text: qsTr("Delete property")
                enabled: mainContent.count > 0 && anagiwahst.currentRow > -1
                iconName: "edit-delete"
                shortcut: StandardKey.Delete
                onTriggered: mainContent.getTab(mainContent.currentIndex).item.deleteProperty()
            }

            MenuItem {
                text: qsTr("Apply changes")
                enabled: mainContent.count > 0 && anagiwahst.editChanged
                iconName: "dialog-ok-apply"
                shortcut: StandardKey.Save
                onTriggered: mainContent.getTab(mainContent.currentIndex).item.updateProperty()
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Previous property")
                enabled: mainContent.count > 0 && anagiwahst.currentRow > 0
                iconName: "go-previous"
                shortcut: StandardKey.Back
                onTriggered: mainContent.getTab(mainContent.currentIndex).item.previousProperty(saveOnChange.checked)
            }

            MenuItem {
                text: qsTr("Next property")
                enabled: mainContent.count > 0 && anagiwahst.currentRow < anagiwahst.rowCount-1 && anagiwahst.rowCount > 0
                iconName: "go-next"
                shortcut: StandardKey.Forward
                onTriggered: mainContent.getTab(mainContent.currentIndex).item.nextProperty(saveOnChange.checked)
            }

            MenuItem {
                id: saveOnChange
                text: qsTr("Save on change")
                checkable: true
                checked: true
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Generate properties")
                enabled: mainContent.count > 0 && anagiwahst.rowCount > 0
                iconName: "run-build"
                onTriggered: {
                    var component = Qt.createComponent("ResultDialog.qml")
                    if (component.status === Component.Ready) {
                        var dialog = component.createObject(anagiwahst, {model: mainContent.getTab(mainContent.currentIndex).item.model})
                        dialog.open()
                    }
                }
            }
        }
    }

    TabView {
        id: mainContent
        anchors.fill: parent
        onCurrentIndexChanged: {
            if (currentIndex > -1) {
                anagiwahst.title = mainContent.getTab(mainContent.currentIndex).title
            }
        }

    }

    FileDialog {
        id: openFileDialog
        title: qsTr("Please choose a file")
        selectMultiple: false
        nameFilters: [qsTr("Header files (*.h *.hpp)")]
        onAccepted: {
            var fileName = openFileDialog.fileUrl.toString().split("/").pop()
            var newTab = mainContent.addTab(fileName)
            newTab.setSource("FileTab.qml", {file: openFileDialog.fileUrl})
            mainContent.currentIndex = mainContent.count-1
        }
    }
}
