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

    property PropertyModel propsModel

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
                    Component.onCompleted: text = propsModel.createOutput(PropertyModel.HeaderFile)
                    Connections {
                        target: propsModel
                        onTypeChanged: headerText.text = propsModel.createOutput(PropertyModel.HeaderFile)
                        onCommentsPositionChanged: headerText.text = propsModel.createOutput(PropertyModel.HeaderFile)
                    }
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
                    Component.onCompleted: text = propsModel.createOutput(PropertyModel.PrivateHeaderFile)
                    Connections {
                        target: propsModel
                        onTypeChanged: privateText.text = propsModel.createOutput(PropertyModel.PrivateHeaderFile)
                        onCommentsPositionChanged: privateText.text = propsModel.createOutput(PropertyModel.PrivateHeaderFile)
                    }
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
                    Component.onCompleted: text = propsModel.createOutput(PropertyModel.CodeFile)
                    Connections {
                        target: propsModel
                        onTypeChanged: codeText.text = propsModel.createOutput(PropertyModel.CodeFile)
                        onCommentsPositionChanged: codeText.text = propsModel.createOutput(PropertyModel.CodeFile)
                    }
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
                    fd.folder = Qt.resolvedUrl(config.lastSaveAllPath)
                    fd.selectFolder = false
                    fd.selectExisting = false
                    fd.title = qsTr("Save file")
                    fd.open()
                }
            }

            Button {
                text: qsTr("Save all")
                iconName: "document-save-all"
                onClicked: {
                    fd.folder = Qt.resolvedUrl(config.lastSaveSinglePath)
                    fd.selectFolder = true
                    fd.title = qsTr("Save all to folder")
                    fd.open()
                }
            }
            
            ComboBox {
                id: privTypeChooser
                currentIndex: 0
                model: ListModel {
                    id: classTypeValues
                    ListElement { value: PropertyModel.PrivateClass; text: qsTr("Private class (d_ptr)") }
                    ListElement { value: PropertyModel.SharedData; text: "QSharedPointer/Data" }
                }
                Binding { target: propsModel; property: "type"; value: classTypeValues.get(privTypeChooser.currentIndex).value }
            }
            
            ComboBox {
                id: commentsPlaceChooser
                currentIndex: 0
                model: ListModel {
                    id: commentsPlaceModel
                    ListElement { value: PropertyModel.InCode; text: qsTr("In the code") }
                    ListElement { value: PropertyModel.InHeader; text: qsTr("In the header") }
                    ListElement { value: PropertyModel.InFronOfHeader; text: qsTr("In front of header") }
                }
                Binding { target: propsModel; property: "commentsPosition"; value: commentsPlaceModel.get(commentsPlaceChooser.currentIndex).value }
            }
        }
    }

    FileDialog {
        id: fd
        selectMultiple: false
        onAccepted: {
            if (fd.selectFolder) {
                config.lastSaveAllPath = fd.folder.toString()
                if (!propsModel.saveAll(fd.fileUrl)) {
                    md.icon = StandardIcon.Warning
                    md.title = qsTr("Error")
                    md.text = qsTr("Could not save files to folder.")
                    md.visible = true
                }
            } else {
                config.lastSaveSinglePath = fd.folder.toString()
                if (!propsModel.saveToFile(resultTabs.getTab(resultTabs.currentIndex).type, fd.fileUrl)) {
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

