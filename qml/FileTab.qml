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
import Buschtrommel.Anagiwahst 1.0
import Buschtrommel.Anagiwahst.Models 1.0

SplitView {
    id: tabRoot
    anchors.fill: parent
    orientation: Qt.Horizontal

    onVisibleChanged: if (visible) { anagiwahst.rowCount = propertyTable.rowCount; anagiwahst.currentRow = propertyTable.currentRow }

    property alias file: propModel.fileUrl
    property alias fileName: propModel.fileName
    property alias model: propModel
    property alias table: propertyTable
    property alias rowCount: propertyTable.rowCount

    Component.onCompleted: {
        propertyTable.resizeColumnsToContents()
        if (className.text === "") {
            className.forceActiveFocus()
        }
    }

    function deleteProperty() {
        editBox.prop = null
        propModel.deleteProperty(propertyTable.currentRow)
        propertyTable.selection.clear()
    }

    function previousProperty() {
        var targetRow = propertyTable.currentRow-1
        propertyTable.selection.clear()
        propertyTable.currentRow = targetRow
        propertyTable.selection.select(targetRow)
    }

    function nextProperty() {
        var targetRow = propertyTable.currentRow+1
        propertyTable.selection.clear()
        propertyTable.currentRow = targetRow
        propertyTable.selection.select(targetRow)
    }

    function newProperty() {
        propertyTable.selection.clear()
        propertyTable.currentRow = -1
        newPropBox.visible = true
    }

    function addProperty() {
        editBox.prop = propModel.addProperty(newPropName.text, newPropType.text, newPropRead.checked, newPropWrite.checked, newPropMember.checked, newPropReset.checked, newPropNotify.checked, defaultDocMethods.checked)

        if (editBox.prop) {
            newPropBox.visible = false
            newPropName.text = ""
            newPropType.text = ""
            newPropRead.checked = defaultReadFunction.checked
            newPropWrite.checked = defaultWriteFunction.checked
            newPropMember.checked = defaultMemeberFunction.checked
            newPropReset.checked = defaultResetFunction.checked
            newPropNotify.checked = defaultNotifyFunction.checked
            editBrief.setFocus()
            addedPropertyTimer.start()
        }
    }

    Timer {
        id: addedPropertyTimer
        interval: 200
        onTriggered: {
            propertyTable.selection.clear()
            propertyTable.selection.select(propertyTable.rowCount-1)
            propertyTable.currentRow = propertyTable.rowCount-1
            propertyTable.positionViewAtRow(propertyTable.rowCount-1)
        }
    }

    RegExpValidator {
        id: nameTypeValidator
        regExp: /\S+/
    }


    TableView {
        id: propertyTable

        Layout.fillWidth: true

        onRowCountChanged: {
            anagiwahst.rowCount = propertyTable.rowCount
            resizeColumnsToContents()
        }

        onCurrentRowChanged: {
            anagiwahst.currentRow = propertyTable.currentRow
            if (currentRow > -1) {
                editBox.prop = propModel.getItemByIndex(currentRow)
            } else {
                editBox.prop = null
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Name")
            delegate: TableText {
                text: styleData.value ? styleData.value.name : ""
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Type")
            delegate: TableText {
                text: styleData.value ? styleData.value.type : ""
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Read")
            delegate: TableText {
                text: styleData.value ? styleData.value.read : ""
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Write")
            delegate: TableText {
                text: styleData.value ? styleData.value.write : ""
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Member")
            delegate: TableText {
                text: styleData.value ? styleData.value.member : ""
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Reset")
            delegate: TableText {
                text: styleData.value ? styleData.value.reset : ""
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Notify")
            delegate: TableText {
                text: styleData.value ? styleData.value.notify : ""
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Revision")
            delegate: TableText {
                text: styleData.value ? styleData.value.revision : ""
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Designable")
            delegate: TableText {
                text: styleData.value ? styleData.value.designable : ""
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Scriptable")
            delegate: TableText {
                text: styleData.value ? styleData.value.scriptable : ""
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Stored")
            delegate: CheckBox {
                checked: styleData.value ? styleData.value.stored : false
                enabled: false
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("User")
            delegate: CheckBox {
                checked: styleData.value ? styleData.value.user : false
                enabled: false
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Constant")
            delegate: CheckBox {
                checked: styleData.value ? styleData.value.constant : false
                enabled: false
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Final")
            delegate: CheckBox {
                checked: styleData.value ? styleData.value.final : false
                enabled: false
            }
        }

        TableViewColumn {
            role: "item"
            title: qsTr("Pointer")
            delegate: CheckBox {
                checked: styleData.value ? styleData.value.pointer : false
                enabled: false
            }
        }
        
        TableViewColumn {
            role: "item"
            title: qsTr("Args by Ref")
            delegate: CheckBox {
                checked: styleData.value ? styleData.value.argsByRef : false
                enabled: false
            }
        }

        model: PropertyModel { id: propModel }
    }

    ScrollView {
        id: editorView
        Layout.minimumWidth: 310
        Layout.preferredWidth: 350


        contentItem: Flickable {
            id: editorFlick
            contentHeight: editorMainCol.height

            GridLayout {
                id: editorMainCol
                columnSpacing: 7
                rowSpacing: 7
                columns: 1
                anchors { left: parent.left; right: parent.right }

                GroupBox {
                    title: qsTr("Class")
                    Layout.fillWidth: true

                    ColumnLayout {
                        anchors { left: parent.left; right: parent.right }

                        LabeledTextField {
                            id: className
                            label: qsTr("Name")
                            text: propModel.className
                            onTextChanged: { tabRoot.parent.title = text; anagiwahst.title = text }
                        }

                        Binding { target: propModel; property: "className"; value: className.text }

                        LabeledTextField {
                            id: namespaceList
                            label: qsTr("Comma separated namespace list")
                            text: propModel.namespaces
                        }

                        Binding { target: propModel; property: "namespaces"; value: namespaceList.text }

                    }

                }

                GroupBox {
                    title: qsTr("Defaults")
                    Layout.fillWidth: true

                    GridLayout {
                        id: defaultsGrid
                        anchors { left: parent.left; right: parent.right }
                        columns: width > 500 ? 6 : 3

                        CheckBox {
                            id: defaultReadFunction
                            text:qsTr("Read")
                            checked: true
                        }

                        CheckBox {
                            id: defaultWriteFunction
                            text: qsTr("Write")
                            checked: true
                        }

                        CheckBox {
                            id: defaultMemeberFunction
                            text: qsTr("Member")
                            checked: false
                        }

                        CheckBox {
                            id: defaultResetFunction
                            text: qsTr("Reset")
                            checked: false
                        }

                        CheckBox {
                            id: defaultNotifyFunction
                            text: qsTr("Notify")
                            checked: true
                        }

                        CheckBox {
                            id: defaultReadFuncName
                            text: qsTr("Use property name for Read")
                            checked: propModel.usePropertyName
                            Layout.columnSpan: 3
                        }
                        
                        Binding { target: propModel; property: "usePropertyName"; value: defaultReadFuncName.checked }

                        CheckBox {
                            id: defaultDocMethods
                            text: qsTr("Document methods")
                            checked: true
                            Layout.columnSpan: 3
                        }

                    }
                    
                    
                }


                GroupBox {
                    id: newPropBox
                    title: qsTr("Add property")
                    visible: false
                    Layout.fillWidth: true
                    onVisibleChanged: {
                        if (visible) {
                            newPropName.forceActiveFocus()

                        } else {
                            newPropName.focus = false
                        }
                    }

                    GridLayout {
                        anchors { left: parent.left; right: parent.right }
                        columns: newPropBox.width > 500 ? 6 : 3


                        TextField {
                            id: newPropName
                            placeholderText: qsTr("Name")
                            validator: nameTypeValidator
                            Layout.columnSpan: 3
                            Layout.fillWidth: true
                            onAccepted: addProperty()
                        }

                        TextField {
                            id: newPropType
                            placeholderText: qsTr("Type")
                            validator: nameTypeValidator
                            Layout.columnSpan: 3
                            Layout.fillWidth: true
                            onAccepted: addProperty()
                        }

                        CheckBox {
                            id: newPropRead
                            text: qsTr("Read")
                            checked: defaultReadFunction.checked
                        }

                        CheckBox {
                            id: newPropWrite
                            text: qsTr("Write")
                            checked: defaultWriteFunction.checked
                        }

                        CheckBox {
                            id: newPropMember
                            text: qsTr("Member")
                            checked: defaultMemeberFunction.checked
                        }


                        CheckBox {
                            id: newPropReset
                            text: qsTr("Reset")
                            checked: defaultResetFunction.checked
                        }

                        CheckBox {
                            id: newPropNotify
                            text: qsTr("Notify")
                            checked: defaultNotifyFunction.checked
                        }

                        RowLayout {
                            Layout.columnSpan: parent.columns

                            Button {
                                iconName: "dialog-cancel"
                                text: qsTr("Cancel")
                                Layout.fillWidth: true
                                onClicked: {
                                    newPropBox.visible = false
                                    newPropName.text = ""
                                    newPropType.text = ""
                                    newPropRead.checked = defaultReadFunction.checked
                                    newPropWrite.checked = defaultWriteFunction.checked
                                    newPropMember.checked = defaultMemeberFunction.checked
                                    newPropReset.checked = defaultResetFunction.checked
                                    newPropNotify.checked = defaultNotifyFunction.checked
                                }
                            }

                            Button {
                                id: addPropertyButton
                                iconName: "list-add"
                                text: qsTr("Add")
                                Layout.fillWidth: true
                                onClicked: addProperty()
                            }
                        }

                    }

                }


                GroupBox {
                    id: editBox
                    property Property prop: null
                    title: qsTr("Edit property")
                    Layout.fillWidth: true
                    visible: prop



                    ColumnLayout {
                        width: parent.width

                        GridLayout {
                            columns: 2

                            LabeledTextField {
                                id: editName
                                label: qsTr("Name")
                                validator: nameTypeValidator
                                text: editBox.prop ? editBox.prop.name : ""
                                onTextChanged: if (editBox.prop) { editBox.prop.name = text }
                            }

                            LabeledTextField {
                                id: editType
                                label: qsTr("Type")
                                validator: nameTypeValidator
                                text: editBox.prop ? editBox.prop.type : ""
                                onTextChanged: if (editBox.prop) { editBox.prop.type = text }
                            }

                            LabeledTextField {
                                id: editRead
                                label: qsTr("Read")
                                validator: nameTypeValidator
                                text: editBox.prop ? editBox.prop.read : ""
                                onTextChanged: if (editBox.prop) { editBox.prop.read = text }
                            }

                            LabeledTextField {
                                id: editWrite
                                label: qsTr("Write")
                                validator: nameTypeValidator
                                text: editBox.prop ? editBox.prop.write : ""
                                onTextChanged: if (editBox.prop) { editBox.prop.write = text }
                            }

                            LabeledTextField {
                                id: editNotify
                                label: qsTr("Notify")
                                validator: nameTypeValidator
                                text: editBox.prop ? editBox.prop.notify : ""
                                onTextChanged: if (editBox.prop) { editBox.prop.notify = text }
                            }

                            LabeledTextField{
                                id: editMember
                                label: qsTr("Member")
                                validator: nameTypeValidator
                                text: editBox.prop ? editBox.prop.member : ""
                                onTextChanged: if (editBox.prop) { editBox.prop.member = text }
                            }

                            LabeledTextField {
                                id: editReset
                                label: qsTr("Reset")
                                validator: nameTypeValidator
                                text: editBox.prop ? editBox.prop.reset : ""
                                onTextChanged: if (editBox.prop) { editBox.prop.reset = text }
                            }

                            LabeledTextField {
                                id: editRevision
                                label: qsTr("Revision")
                                inputMethodHints: Qt.ImhDigitsOnly
                                validator: IntValidator { bottom: 0; top: 255 }
                                onTextChanged: if (editBox.prop) { editBox.prop.revision = parseInt(text) }
                            }

                            LabeledTextField {
                                id: editDesignable
                                label: qsTr("Designable")
                                text: editBox.prop ? editBox.prop.designable : ""
                                onTextChanged: if (editBox.prop) { editBox.prop.designable = text }
                            }

                            LabeledTextField {
                                id: editScriptable
                                label: qsTr("Scriptable")
                                text: editBox.prop ? editBox.prop.scriptable : ""
                                onTextChanged: if (editBox.prop) { editBox.prop.scriptable = text }
                            }
                        }

                        GridLayout {
                            columns: parent.width > 500 ? 6 : 3

                            CheckBox {
                                id: editStored
                                text: qsTr("Stored")
                                checked: editBox.prop ? editBox.prop.stored : true
                                onCheckedChanged: if (editBox.prop) { editBox.prop.stored = checked }
                            }

                            CheckBox {
                                id: editUser
                                text: qsTr("User")
                                checked: editBox.prop ? editBox.prop.user : true
                                onCheckedChanged: if (editBox.prop) { editBox.prop.user = checked }
                            }


                            CheckBox {
                                id: editConstant
                                text: qsTr("Constant")
                                checked: editBox.prop ? editBox.prop.constant : true
                                onCheckedChanged: if (editBox.prop) { editBox.prop.constant = checked }
                            }

                            CheckBox {
                                id: editFinal
                                text: qsTr("Final")
                                checked: editBox.prop ? editBox.prop.final : true
                                onCheckedChanged: if (editBox.prop) { editBox.prop.final = checked }
                            }

                            CheckBox {
                                id: editPointer
                                text: qsTr("Pointer")
                                checked: editBox.prop ? editBox.prop.pointer : true
                                onCheckedChanged: if (editBox.prop) { editBox.prop.pointer = checked }
                            }
                            
                            CheckBox {
                                id: editArgsByRef
                                text: qsTr("Args by Ref")
                                Layout.columnSpan: 2
                                checked: editBox.prop ? editBox.prop.argsByRef : true
                                onCheckedChanged: if (editBox.prop) { editBox.prop.argsByRef = checked }
                            }

                            CheckBox {
                                id: editDocMethods
                                text: qsTr("Document methods")
                                Layout.columnSpan: 2
                                checked: editBox.prop ? editBox.prop.documentMethods : defaultDocMethods.checked
                                onCheckedChanged: if (editBox.prop) { editBox.prop.documentMethods = checked }
                            }

                        }

                        LabeledTextField {
                            id: editDefaultValue
                            label: qsTr("Default value")
                            Layout.fillWidth: true
                            text: editBox.prop ? editBox.prop.defaultValue : ""
                            onTextChanged: if (editBox.prop) { editBox.prop.defaultValue = text }
                        }

                        LabeledTextField {
                            id: editBrief
                            label: qsTr("Brief description")
                            Layout.fillWidth: true
                            text: editBox.prop ? editBox.prop.brief : ""
                            onTextChanged: if (editBox.prop) { editBox.prop.brief = text }
                        }

                        Label {
                            text: qsTr("Detailed description")
                            Layout.fillWidth: true
                        }

                        TextArea {
                            id: editComment
                            property string initialText: ""
                            property bool changed: false
                            Layout.fillWidth: true
                            Layout.preferredHeight: 300
                            selectByMouse: true
                            text: editBox.prop ? editBox.prop.comment : ""
                            onTextChanged: editCommentTimer.restart()

                            Timer {
                                id: editCommentTimer
                                interval: 500
                                onTriggered: {
                                    if (editBox.prop) { editBox.prop.comment = editComment.text }
                                }
                            }
                        }

                        Button {
                            text: qsTr("Cancel")
                            iconName: "dialog-cancel"
                            onClicked: {
                                propertyTable.selection.clear()
                                propertyTable.currentRow = -1
                            }
                            Layout.fillWidth: true
                        }
                    }
                }
            }        
        }        
    }
}

