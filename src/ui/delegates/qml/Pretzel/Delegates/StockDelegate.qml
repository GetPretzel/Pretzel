import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.UiComponents 1.0


ItemDelegate {
    id: root

    width: ListView.view.width
    checkable: true
    onClicked: ListView.view.currentIndex = index

    property var model: ListView.view.model

    contentItem: ColumnLayout {
        id: contentLayout
        anchors.fill: parent

        PLabel {
            // TODO: Add display text
            // text: {
            //     var itemProperties = ???
            //     model.itemsModel.get(index, 1)
            // }
        }

        RowLayout {
            id: quantityLayout
            Layout.fillWidth: true
            visible: root.checked

            PLabel {
                text: qsTr("Quantity")
            }

            PSpinBox {
                id: quantitySpinBox
                Layout.fillWidth: true
                value: 0
                onValueModified: stockModel.set(index, quantitySpinBox.value, 1)
            }
        }

        RowLayout {
            id: unitLayout
            Layout.fillWidth: true
            visible: root.checked

            PLabel {
                text: qsTr("Unit")
            }

            PLineEdit {
                id: unitLineEdit
                Layout.fillWidth: true
                placeholderText: qsTr("The measuring unit of this item (cm, mm etc.")
                onTextEdited: stockModel.set(index, unitLineEdit.text, 2)
            }
        }

        RowLayout {
            id: costLayout
            Layout.fillWidth: true
            visible: root.checked

            PLabel {
                text: qsTr("Cost")
            }

            PSpinBox {
                id: costSpinBox
                Layout.fillWidth: true
                value: 0
                onValueModified: stockModel.set(index, costSpinBox.value, 3)
            }
        }
    }
}
