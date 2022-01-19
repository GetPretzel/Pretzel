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
            Layout.fillWidth: true
            visible: root.checked
        }
    }
    PLabel {
        text: index
    }
}
