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

Item {
    id: resultView

    objectName: "resultView"

    width: parent.width
    height: parent.height

    property Unit unit: null
    property PropertyModel props: null

    Component.onCompleted: {
        PropertyWriter.unit = resultView.unit
        PropertyWriter.propertyModel = resultView.props
        PropertyWriter.createProperties()
    }

    ColumnLayout {
        width: parent.width
        height: parent.height

        TabView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Tab {
                title: qsTr("Header")

                TextArea {
                    id: headerText
                    anchors.fill: parent
                    readOnly: true
                    selectByKeyboard: true
                    selectByMouse: true
                    textFormat: TextEdit.PlainText
                    font.family: "mono"
                    text: PropertyWriter.headerContent
                }
            }

            Tab {
                title: qsTr("Private")

                TextArea {
                    id: privateText
                    anchors.fill: parent
                    readOnly: true
                    selectByKeyboard: true
                    selectByMouse: true
                    textFormat: TextEdit.PlainText
                    font.family: "mono"
                    text: PropertyWriter.privateContent
                }
            }

            Tab {
                title: qsTr("Code")

                TextArea {
                    id: codeText
                    anchors.fill: parent
                    readOnly: true
                    selectByKeyboard: true
                    selectByMouse: true
                    textFormat: TextEdit.PlainText
                    font.family: "mono"
                    text: PropertyWriter.codeContent
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
                    fileDialog.folder = config.lastSaveAllPath !== "" ? Qt.resolvedUrl(config.lastSaveAllPath) : fileDialog.shortcuts.documents
                    fileDialog.selectFolder = false
                    fileDialog.selectExisting = false
                    fileDialog.title = qsTr("Save file")
                    fileDialog.open()
                }
            }

            Button {
                text: qsTr("Save all")
                iconName: "document-save-all"
                onClicked: {
                    fileDialog.folder = config.lastSaveSinglePath !== "" ?  Qt.resolvedUrl(config.lastSaveSinglePath) : fileDialog.shortcuts.documents
                    fileDialog.selectFolder = true
                    fileDialog.title = qsTr("Save all to folder")
                    fileDialog.open()
                }
            }

            ComboBox {
                id: commentsPlaceChooser
                currentIndex: 0
                model: ListModel {
                    id: commentsPlaceModel
                    ListElement { value: PropertyWriter.InCode; text: qsTr("In the code") }
                    ListElement { value: PropertyWriter.InHeader; text: qsTr("In the header") }
                    ListElement { value: PropertyWriter.InFronOfHeader; text: qsTr("In front of header") }
                }
                onCurrentIndexChanged: {
                    PropertyWriter.commentsPosition = commentsPlaceModel.get(commentsPlaceChooser.currentIndex).value
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: qsTr("Back")
                iconName: "arrow-left"
                onClicked: stack.pop()
            }
        }
    }
}
