import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.UiComponents 1.0


Item {
    id: root

    signal clicked

    property bool hovered: false
    property bool toggled: false

    height: 32

    property alias radius: backgroundRect.radius
    property alias text: label.text

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        color: "#313844"
        border.color: {
            if (hovered) {
                return "#535F74"
            } else {
                return "#0D0F12"
            }
        }
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
        hoverEnabled: true
        onClicked: {
            root.toggled = !root.toggled
            root.clicked()
        }

        onHoveredChanged: {
            root.hovered = !root.hovered
            root.hoveredChanged()
        }
    }
}
