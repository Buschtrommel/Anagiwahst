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
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import Buschtrommel.Anagiwahst.Models 1.0

Dialog {
    id: dialogRoot
    title: qsTr("Result of property generation")
    standardButtons: StandardButton.Save | StandardButton.Close

    width: 640
    height: 480

    property PropertyModel model

    contentItem: ColumnLayout {
            TabView {
            id: resultTabs
            Layout.fillHeight: true
            Layout.fillWidth: true

            Tab {
                title: qsTr("Header")
                readonly property int type: PropertyModel.HeaderFile

                TextArea {
                    id: headerText
                    anchors.fill: parent
                    readOnly: true
                    selectByKeyboard: true
                    selectByMouse: true
                    textFormat: TextEdit.PlainText
                    font.family: "mono"
                    Component.onCompleted: text = model.createOutput(PropertyModel.HeaderFile)
                }
            }

            Tab {
                title: qsTr("Private")
                readonly property int type: PropertyModel.PrivateHeaderFile

                TextArea {
                    id: privateText
                    anchors.fill: parent
                    readOnly: true
                    selectByKeyboard: true
                    selectByMouse: true
                    textFormat: TextEdit.PlainText
                    font.family: "mono"
                    Component.onCompleted: text = model.createOutput(PropertyModel.PrivateHeaderFile)
                }
            }

            Tab {
                title: qsTr("Code")
                readonly property int type: PropertyModel.CodeFile

                TextArea {
                    id: codeText
                    anchors.fill: parent
                    readOnly: true
                    selectByKeyboard: true
                    selectByMouse: true
                    textFormat: TextEdit.PlainText
                    font.family: "mono"
                    Component.onCompleted: text = model.createOutput(PropertyModel.CodeFile)
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            layoutDirection: Qt.RightToLeft

            Button {
                text: qsTr("Save")
                iconName: "document-save"
                onClicked: {
                    fd.selectFolder = false
                    fd.selectExisting = false
                    fd.title = qsTr("Save file")
                    fd.visible = true
                }
            }

            Button {
                text: qsTr("Save all")
                iconName: "document-save-all"
                onClicked: {
                    fd.selectFolder = true
                    fd.title = qsTr("Save all to folder")
                    fd.visible = true
                }
            }
        }
    }

    FileDialog {
        id: fd
        selectMultiple: false
        onAccepted: {
            if (fd.selectFolder) {
                if (!model.saveAll(fd.fileUrl)) {
                    md.icon = StandardIcon.Warning
                    md.title = qsTr("Error")
                    md.text = qsTr("Could not save files to folder.")
                    md.visible = true
                }
            } else {
                if (!model.saveToFile(resultTabs.getTab(resultTabs.currentIndex).type, fd.fileUrl)) {
                    md.icon = StandardIcon.Warning
                    md.title = qsTr("Error")
                    md.text = qsTr("Could not save file.")
                    md.visible = true
                }
            }
        }
    }

    MessageDialog {
        id: md
    }
}

