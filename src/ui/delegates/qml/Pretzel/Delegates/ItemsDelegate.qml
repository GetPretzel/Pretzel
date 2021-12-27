import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.Framework 1.0
import Pretzel.UiComponents 1.0

ItemDelegate {
    id: root

    property var model: ListView.view.model
    
    width: ListView.view.width
    checkable: true
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
                placeholderText: qsTr("The name of this item")
                onTextEdited: root.model.set(index, nameEdit.text, 0)
            }
        }
    }
}
