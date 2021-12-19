import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.UiComponents 1.0


ItemDelegate {
    id: root
    width: ListView.view.width
    checkable: true

    property var model: ListView.view.model

    onClicked: ListView.view.currentIndex = index

    contentItem: ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            PLabel {
                text: nameEdit.text
            }
        }

        RowLayout {
            Layout.fillWidth: true
            visible: root.checked

            PLabel {
                text: qsTr("Name")
            }

            PLineEdit {
                id: nameEdit
                Layout.fillWidth: true
                text: root.model.get(index, 0)
                placeholderText: qsTr("The name of this property")
                onTextEdited: root.model.set(index, nameEdit.text, 0)
            }
        }

        RowLayout {
            Layout.fillWidth: true
            visible: root.checked

            PLabel {
                text: qsTr("Type")
            }

            PDropDown {
                id: typeDropDown
                Layout.fillWidth: true
                model: ["String", "Integer", "Float"]
                // TODO: Surely "index - 1" will cause an error down the track. Also why "index" doesn't work when "displayItemDropDown" works? 
                onActivated: root.model.set(index - 1, typeDropDown.currentText, 1)
            }
        }

        RowLayout {
            Layout.fillWidth: true
            visible: root.checked

            PLabel {
                text: qsTr("Display Item")
            }

            PDropDown {
                id: displayItemDropDown
                Layout.fillWidth: true
                // TODO: Update the availbe components when the type is changed
                model: ["PDropDown", "PLineEdit", "PTextEdit"]
                onActivated: root.model.set(index, displayItemDropDown.currentText, 2)

                Component.onCompleted: displayItemDropDown.currentIndex = 1
            }
        }
    }
}

