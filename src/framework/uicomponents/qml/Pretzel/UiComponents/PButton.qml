import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.UiComponents 1.0


Item {
    id: root

    signal clicked

    height: 32

    property alias radius: backgroundRect.radius
    property alias text: label.text

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        color: "#39414A"
        border.color: "#00010B"
        border.width: 2
        radius: 4
    }

    PLabel {
        id: label
        anchors.centerIn: parent
        color: "#DFE3F2"
        font.pixelSize: 12
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
