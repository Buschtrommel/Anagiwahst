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
    property alias propertyModel: pm
    readonly property int childMargins: 5

    Item {
        id: leftCol
        Layout.minimumWidth: 250
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

            Button {
                iconName: "list-add"
                text: qsTr("Add property")
                Layout.leftMargin: projectView.childMargins
                Layout.rightMargin: projectView.childMargins
                Layout.fillWidth: true
                enabled: projectView.currentUnit !== null
                onClicked: anagiwahst.createProperty()
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
            visible: projectView.currentUnit !== null

            RowLayout {
                Layout.leftMargin: projectView.childMargins
                Layout.rightMargin: projectView.childMargins

                Header {
                    text: currentUnit ? currentUnit.displayName : ""
                }
            }

            ScrollView {
                Layout.fillHeight: true
                Layout.fillWidth: true


                ListView {
                    model: PropertyModel { id: pm; unitId: currentUnit ? currentUnit.id : -1 }

                    delegate: Item {
                        id: propListItem
                        anchors { left: parent.left; right: parent.right; leftMargin: projectView.childMargins; rightMargin: projectView.childMargins }
                        property bool expanded: false
                        height: model.item.expanded ? propGrid.height : propOverview.height

                        Rectangle {
                            id: propOverview
                            visible: !model.item.expanded
                            width: parent.width
                            height: 30
                            color: propItemMousa.containsMouse ? "white" : "transparent"

                            MouseArea {
                                id: propItemMousa
                                hoverEnabled: true
                                anchors.fill: parent
                                onClicked: pm.expandProperty(model.item)
                            }

                            RowLayout {
                                id: propOverviewRow
                                anchors { left: parent.left; right: parent.right; verticalCenter: parent.verticalCenter; leftMargin: 5; rightMargin: 5 }

                                Label {
                                    text: model.item.type
                                    Layout.minimumWidth: propListItem.width * 0.1
                                }

                                Label {
                                    text: (model.item.pointer ? "*" : "") + model.item.name
                                    Layout.minimumWidth: propListItem.width * 0.1
                                }

                                Label {
                                    text: model.item.defaultValue
                                    elide: Text.ElideRight
                                    Layout.minimumWidth: propListItem.width * 0.1
                                    Layout.preferredWidth: propListItem.width * 0.1
                                    Layout.maximumWidth: propListItem.width * 0.2
                                }

                                CheckBox {
                                    checked: model.item.read
                                    text: "R"
                                    enabled: false
                                }

                                CheckBox {
                                    checked: model.item.write
                                    text: "W"
                                    enabled: false
                                }

                                CheckBox {
                                    checked: model.item.notify
                                    text: "N"
                                    enabled: false
                                }

                                CheckBox {
                                    checked: model.item.member
                                    text: "M"
                                    enabled: false
                                }

                                CheckBox {
                                    checked: model.item.reset
                                    text: "U"
                                    enabled: false
                                }


                                CheckBox {
                                    checked: model.item.argsByRef
                                    text: "A"
                                    enabled: false
                                }

                                CheckBox {
                                    checked: model.item.stored
                                    text: "S"
                                    enabled: false
                                }

                                CheckBox {
                                    checked: model.item.constant
                                    text: "C"
                                    enabled: false
                                }

                                CheckBox {
                                    checked: model.item.final
                                    text: "F"
                                    enabled: false
                                }
                            }
                        }

                        GridLayout {
                            id: propGrid
                            width: parent.width
                            columns: 10
                            visible: model.item.expanded

                            LabeledTextField {
                                id: nameField
                                label: qsTr("Name")
                                text: model.item.name
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "name"; value: nameField.text }

                            LabeledTextField {
                                id: typeField
                                label: qsTr("Type")
                                text: model.item.type
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "type"; value: typeField.text }

                            LabeledTextField {
                                id: readField
                                label: qsTr("Read")
                                text: model.item.read
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "read"; value: readField.text }

                            LabeledTextField {
                                id: writeField
                                label: qsTr("Write")
                                text: model.item.write
                                Layout.columnSpan: 2
                                Binding { target: model.item; property: "write"; value: writeField.text }
                            }

                            LabeledTextField {
                                id: notifyField
                                label: qsTr("Notify")
                                text: model.item.notify
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "notify"; value: notifyField.text }

                            LabeledTextField {
                                id: memberField
                                label: qsTr("Member")
                                text: model.item.member
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "member"; value: memberField.text }

                            LabeledTextField {
                                id: resetField
                                label: qsTr("Reset")
                                text: model.item.reset
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "reset"; value: resetField.text }

                            LabeledTextField {
                                id: revisionField
                                label: qsTr("Revision")
                                text: model.item.revision
                                Layout.columnSpan: 2
                                validator: IntValidator { bottom: 0 }
                                inputMethodHints: Qt.ImhDigitsOnly
                            }
                            Binding { target: model.item; property: "revision"; value: parseInt(revisionField.text) }

                            LabeledTextField {
                                id: designableField
                                label: qsTr("Desginable")
                                text: model.item.designable
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "designable"; value: designableField.text }

                            LabeledTextField {
                                id: scriptableField
                                label: qsTr("Scriptable")
                                text: model.item.scriptable
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "scriptable"; value: scriptableField.text }

                            CheckBox {
                                id: storedCheck
                                text: qsTr("Stored")
                                checked: model.item.stored
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "stored"; value: storedCheck.checked }

                            CheckBox {
                                id: userCheck
                                text: qsTr("User")
                                checked: model.item.user
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "user"; value: userCheck.checked }

                            CheckBox {
                                id: constantCheck
                                text: qsTr("Constant")
                                checked: model.item.constant
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "constant"; value: constantCheck.checked }

                            CheckBox {
                                id: finalCheck
                                text: qsTr("Final")
                                checked: model.item.final
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "final"; value: finalCheck.checked }

                            CheckBox {
                                id: pointerCheck
                                text: qsTr("Pointer")
                                checked: model.item.pointer
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "pointer"; value: pointerCheck.checked }

                            CheckBox {
                                id: argsbyrefCheck
                                text: qsTr("Args by Ref")
                                checked: model.item.final
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "argsByRef"; value: argsbyrefCheck.checked }

                            CheckBox {
                                id: docmethodsCheck
                                text: qsTr("Document methods")
                                checked: model.item.documentMethods
                                Layout.columnSpan: 2
                            }
                            Binding { target: model.item; property: "documentMethods"; value: docmethodsCheck.checked }

                            LabeledTextField {
                                id: defValueField
                                label: qsTr("Default value")
                                text: model.item.defaultValue
                                Layout.columnSpan: 6
                            }
                            Binding { target: model.item; property: "defaultValue"; value: defValueField.text }

                            LabeledTextField {
                                id: briefField
                                label: qsTr("Brief description")
                                text: model.item.brief
                                Layout.columnSpan: 10
                            }
                            Binding { target: model.item; property: "brief"; value: briefField.text }

                            Label {
                                text: qsTr("Detailed description")
                                Layout.fillWidth: true
                                Layout.columnSpan: 10
                            }

                            TextArea {
                                id: commentField
                                Layout.columnSpan: 10
                                Layout.fillWidth: true
                                text: model.item.comment
                            }
                            Binding { target: model.item; property: "comment"; value: commentField.text }

                            RowLayout {
                                Layout.columnSpan: propGrid.columns
                                Button {
                                    iconName: "dialog-cancel"
                                    text: qsTr("Close")
                                    onClicked: model.item.expanded = false
                                }

                                Item {
                                    Layout.fillWidth: true
                                }

                                Button {
                                    iconName: "delete"
                                    text: qsTr("Delete")
                                    onClicked: pm.deleteProperty(model.item)
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
