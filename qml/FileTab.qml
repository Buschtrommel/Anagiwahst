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
import Buschtrommel.Anagiwahst.Models 1.0

SplitView {
    id: tabRoot
    anchors.fill: parent
    orientation: Qt.Horizontal

    onVisibleChanged: if (visible) { anagiwahst.rowCount = propertyTable.rowCount; anagiwahst.currentRow = propertyTable.currentRow; anagiwahst.editChanged = tabRoot.editChanged; }

    property alias file: propModel.fileUrl
    property alias fileName: propModel.fileName
    property alias model: propModel
    property alias table: propertyTable
    property alias rowCount: propertyTable.rowCount
    property bool editChanged: editName.changed || editType.changed || editRead.changed || editWrite.changed || editMember.changed || editReset.changed || editNotify.changed || editRevision.changed || editDesignable.changed || editScriptable.changed || editStored.changed || editUser.changed || editConstant.changed || editFinal.changed || editPrivate.changed || editPointer.changed || editBrief.changed || editComment.changed || editDefaultValue.changed

    onEditChangedChanged: anagiwahst.editChanged = tabRoot.editChanged

    Component.onCompleted: {
        propertyTable.resizeColumnsToContents()
        if (className.text === "") {
            className.forceActiveFocus()
        }
    }

    function deleteProperty() {
        propModel.deleteProperty(propertyTable.currentRow)
    }

    function previousProperty(save) {
        if (save && tabRoot.editChanged) updateProperty()
        var targetRow = propertyTable.currentRow-1
        propertyTable.selection.clear()
        propertyTable.currentRow = targetRow
        propertyTable.selection.select(targetRow)
    }

    function nextProperty(save) {
        if (save && tabRoot.editChanged) updateProperty()
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
        if (propModel.addProperty(newPropName.text, newPropType.text, newPropRead.checked, newPropWrite.checked, newPropMember.checked, newPropReset.checked, newPropNotify.checked, newPropPrivate.checked)) {
            newPropBox.visible = false
            newPropName.text = ""
            newPropType.text = ""
            newPropRead.checked = defaultReadFunction.checked
            newPropWrite.checked = defaultWriteFunction.checked
            newPropMember.checked = defaultMemeberFunction.checked
            newPropReset.checked = defaultResetFunction.checked
            newPropNotify.checked = defaultNotifyFunction.checked
            newPropPrivate.checked = defaultPrivateClass.checked
            propertyTable.selection.clear()
            propertyTable.selection.select(propertyTable.rowCount-1)
            propertyTable.currentRow = propertyTable.rowCount-1
            propertyTable.positionViewAtRow(propertyTable.rowCount-1)
            editName.forceActiveFocus()
        }
    }

    function setEditorValues() {
        var rowIndex = propertyTable.currentRow
        editName.init(propModel.getData("name", rowIndex))
        editType.init(propModel.getData("type", rowIndex))
        editRead.init(propModel.getData("read", rowIndex))
        editWrite.init(propModel.getData("write", rowIndex))
        editMember.init(propModel.getData("member", rowIndex))
        editReset.init(propModel.getData("reset", rowIndex))
        editNotify.init(propModel.getData("notify", rowIndex))
        editRevision.init(propModel.getData("revision", rowIndex))
        editDesignable.init(propModel.getData("designable", rowIndex))
        editScriptable.init(propModel.getData("scriptable", rowIndex))
        editStored.init(propModel.getData("stored", rowIndex))
        editUser.init(propModel.getData("user", rowIndex))
        editConstant.init(propModel.getData("constant", rowIndex))
        editFinal.init(propModel.getData("final", rowIndex))
        editPrivate.init(propModel.getData("private", rowIndex))
        editPointer.init(propModel.getData("pointer", rowIndex))
        editDefaultValue.init(propModel.getData("default", rowIndex))
        editBrief.init(propModel.getData("brief", rowIndex))
        editComment.initialText = propModel.getData("comment", rowIndex)
        editComment.text = propModel.getData("comment", rowIndex)
        editName.focus = true;
        editName.forceActiveFocus()
    }

    function updateProperty() {
        var rowIndex = propertyTable.currentRow
        propModel.updateData("name", rowIndex, editName.apply())
        propModel.updateData("type", rowIndex, editType.apply())
        propModel.updateData("read", rowIndex, editRead.apply())
        propModel.updateData("write", rowIndex, editWrite.apply())
        propModel.updateData("member", rowIndex, editMember.apply())
        propModel.updateData("reset", rowIndex, editReset.apply())
        propModel.updateData("notify", rowIndex, editNotify.apply())
        propModel.updateData("revision", rowIndex, parseInt(editRevision.apply()))
        propModel.updateData("designable", rowIndex, editDesignable.apply())
        propModel.updateData("scriptable", rowIndex, editScriptable.apply())
        propModel.updateData("stored", rowIndex, editStored.apply())
        propModel.updateData("user", rowIndex, editUser.apply())
        propModel.updateData("constant", rowIndex, editConstant.apply())
        propModel.updateData("final", rowIndex, editFinal.apply())
        propModel.updateData("private", rowIndex, editPrivate.apply())
        propModel.updateData("pointer", rowIndex, editPointer.apply())
        propModel.updateData("default", rowIndex, editDefaultValue.apply())
        propModel.updateData("brief", rowIndex, editBrief.apply())
        propModel.updateData("comment", rowIndex, editComment.text)
        editComment.initialText = editComment.text
        editComment.changed = false;
    }

    function resetProperty() {
        editName.reset()
        editType.reset()
        editRead.reset()
        editWrite.reset()
        editMember.reset()
        editReset.reset()
        editNotify.reset()
        editRevision.reset()
        editDesignable.reset()
        editScriptable.reset()
        editStored.reset()
        editUser.reset()
        editConstant.reset()
        editFinal.reset()
        editPrivate.reset()
        editPointer.reset()
        editDefaultValue.reset()
        editBrief.reset()
        editComment.text = editComment.initialText
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
                setEditorValues(currentRow)
            }
        }

        TableViewColumn {
            role: "name"
            title: qsTr("Name")
        }

        TableViewColumn {
            role: "type"
            title: qsTr("Type")
        }

        TableViewColumn {
            role: "read"
            title: qsTr("Read")
        }

        TableViewColumn {
            role: "write"
            title: qsTr("Write")
        }

        TableViewColumn {
            role: "member"
            title: qsTr("Member")
        }

        TableViewColumn {
            role: "reset"
            title: qsTr("Reset")
        }

        TableViewColumn {
            role: "notify"
            title: qsTr("Notify")
        }

        TableViewColumn {
            role: "revision"
            title: qsTr("Revision")
        }

        TableViewColumn {
            role: "designable"
            title: qsTr("Designable")
        }

        TableViewColumn {
            role: "scriptable"
            title: qsTr("Scriptable")
        }

        TableViewColumn {
            role: "stored"
            title: qsTr("Stored")
            delegate: CheckBox {
                checked: styleData.value
                enabled: false
            }
        }

        TableViewColumn {
            role: "user"
            title: qsTr("User")
            delegate: CheckBox {
                checked: styleData.value
                enabled: false
            }
        }

        TableViewColumn {
            role: "constant"
            title: qsTr("Constant")
            delegate: CheckBox {
                checked: styleData.value
                enabled: false
            }
        }

        TableViewColumn {
            role: "final"
            title: qsTr("Final")
            delegate: CheckBox {
                checked: styleData.value
                enabled: false
            }
        }

        TableViewColumn {
            role: "private"
            title: qsTr("Private")
            delegate: CheckBox {
                checked: styleData.value
                enabled: false
            }
        }

        TableViewColumn {
            role: "pointer"
            title: qsTr("Pointer")
            delegate: CheckBox {
                checked: styleData.value
                enabled: false
            }
        }

        model: PropertyModel { id: propModel }
    }

    ScrollView {
        id: editorView
        Layout.minimumWidth: 310
        Layout.preferredWidth: 350



        ColumnLayout {
            id: editorMainCol
            spacing: 7
            anchors { left: parent.left; right: parent.right; leftMargin: 7; rightMargin: 7 }

            TextField {
                id: className
                placeholderText: qsTr("Class name")
                Layout.fillWidth: true
                text: propModel.className
                onTextChanged: tabRoot.parent.title = text
            }

            Binding { target: propModel; property: "className"; value: className.text }

            GroupBox {
                title: qsTr("Defaults")
                Layout.fillWidth: true

                GridLayout {
                    columns: editorView.width > 600 ? 6 : 3
                    width: parent.width

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
                        id: defaultPrivateClass
                        text: qsTr("Private class")
                        checked: propModel.privateClass
                    }

                    Binding { target: propModel; property: "privateClass"; value: defaultPrivateClass.checked }

                }
            }

            ComboBox {
                currentIndex: 0
                Layout.fillWidth: true
                model: ListModel {
                    id: classTypeValues
                    ListElement { value: PropertyModel.PrivateClass; text: "Q_DECLARE_PRIVATE" }
                    ListElement { value: PropertyModel.SharedData; text: "QSharedPointer/Data" }
                }
                onCurrentIndexChanged: propModel.type = classTypeValues.get(currentIndex).value
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

                ColumnLayout {

                    RowLayout {

                        TextField {
                            id: newPropName
                            placeholderText: qsTr("Name")
                            validator: nameTypeValidator
                            Layout.fillWidth: true
                            onAccepted: addProperty()
                        }

                        TextField {
                            id: newPropType
                            placeholderText: qsTr("Type")
                            validator: nameTypeValidator
                            Layout.fillWidth: true
                            onAccepted: addProperty()
                        }

                    }

                    GridLayout {
                        columns: editorView.width > 600 ? 6 : 3

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

                        CheckBox {
                            id: newPropPrivate
                            text: qsTr("Private class")
                            checked: defaultPrivateClass.checked
                            Layout.fillWidth: true
                        }

                    }

                    RowLayout {

                        Button {
                            iconName: "dialog-cancel"
                            text: qsTr("Cancel")
                            onClicked: {
                                newPropBox.visible = false
                                newPropName.text = ""
                                newPropType.text = ""
                                newPropRead.checked = defaultReadFunction.checked
                                newPropWrite.checked = defaultWriteFunction.checked
                                newPropMember.checked = defaultMemeberFunction.checked
                                newPropReset.checked = defaultResetFunction.checked
                                newPropNotify.checked = defaultNotifyFunction.checked
                                newPropPrivate.checked = defaultPrivateClass.checked
                            }
                        }

                        Button {
                            id: addPropertyButton
                            iconName: "list-add"
                            text: qsTr("Add")
                            onClicked: addProperty()
                        }

                    }

                }

            }


            GroupBox {
                id: editBox
                title: qsTr("Edit property")
                Layout.fillWidth: true
                visible: propertyTable.currentRow > -1

                ColumnLayout {

                    GridLayout {
                        width: editBox.width
                        columns: 2

                        LabeledTextField {
                            id: editName
                            label: qsTr("Name")
                            width: parent.width/parent.columns
                            validator: nameTypeValidator
                        }

                        LabeledTextField {
                            id: editType
                            label: qsTr("Type")
                            validator: nameTypeValidator
                        }

                        LabeledTextField {
                            id: editRead
                            label: qsTr("Read")
                        }

                        LabeledTextField {
                            id: editWrite
                            label: qsTr("Write")
                        }

                        LabeledTextField {
                            id: editNotify
                            label: qsTr("Notify")
                        }

                        LabeledTextField{
                            id: editMember
                            label: qsTr("Member")
                        }

                        LabeledTextField {
                            id: editReset
                            label: qsTr("Reset")
                        }

                        LabeledTextField {
                            id: editRevision
                            label: qsTr("Revision")
                            inputMethodHints: Qt.ImhDigitsOnly
                            validator: IntValidator { bottom: 0; top: 255 }
                        }

                        LabeledTextField {
                            id: editDesignable
                            label: qsTr("Designable")
                        }

                        LabeledTextField {
                            id: editScriptable
                            label: qsTr("Scriptable")
                        }
                    }

                    GridLayout {
                        columns: 3
                        width: parent.width

                        CheckBoxWithReset {
                            id: editStored
                            text: qsTr("Stored")
                        }

                        CheckBoxWithReset {
                            id: editUser
                            text: qsTr("User")
                        }

                        CheckBoxWithReset {
                            id: editConstant
                            text: qsTr("Constant")
                        }

                        CheckBoxWithReset {
                            id: editFinal
                            text: qsTr("Final")
                        }

                        CheckBoxWithReset {
                            id: editPrivate
                            text: qsTr("Private")
                        }

                        CheckBoxWithReset {
                            id: editPointer
                            text: qsTr("Pointer")
                        }

                    }

                    LabeledTextField {
                        id: editDefaultValue
                        label: qsTr("Default value")
                        Layout.fillWidth: true
                    }

                    LabeledTextField {
                        id: editBrief
                        label: qsTr("Brief description")
                        Layout.fillWidth: true
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
                        text: ""
                        onTextChanged: editCommentTimer.restart()

                        Timer {
                            id: editCommentTimer
                            interval: 500
                            onTriggered: {
                                editComment.changed = editComment.initialText !== editComment.text
                            }
                        }
                    }

                    RowLayout {

                        Button {
                            text: qsTr("Reset")
                            iconName: "edit-undo"
                            enabled: tabRoot.editChanged
                            onClicked: resetProperty()
                        }

                        Button {
                            text: qsTr("Cancel")
                            iconName: "dialog-cancel"
                            onClicked: {
                                propertyTable.selection.clear()
                                propertyTable.currentRow = -1
                            }
                        }

                        Button {
                            text: qsTr("Apply")
                            iconName: "dialog-ok-apply"
                            enabled: tabRoot.editChanged
                            onClicked: updateProperty()
                        }
                    }
                }
            }
        }
    }
}

