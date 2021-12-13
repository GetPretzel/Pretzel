import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.UiComponents 1.0


ItemDelegate {
    id: root
    width: parent.width
    checkable: true

    property var model: ListView.view.model

    onClicked: ListView.view.currentIndex = index

    contentItem = ColumnLayout {
        anchors.fill: parent
    }
}

