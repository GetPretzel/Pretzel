import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Pretzel.UiComponents 1.0

ItemDelegate {
    id: root

    property var model: ListView.view.model

    width: ListView.view.width
    checkable: true
    onClicked: ListView.view.currentIndex = index
    // WARNING: This doesn't seem to work. Which means there is a bug
    hoverEnabled: true
    onHoveredChanged: ListView.currentIndex = index

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
                onActivated: root.model.set(root.ListView.view.currentIndex, typeDropDown.currentText, 1)
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
                onActivated: root.model.set(root.ListView.view.currentIndex, displayItemDropDown.currentText, 2)
                Component.onCompleted: displayItemDropDown.currentIndex = 1
            }

        }

    }

}
