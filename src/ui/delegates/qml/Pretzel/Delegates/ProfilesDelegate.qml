import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.UiComponents 1.0


ItemDelegate {
    id: root
    width: parent.width
    checkable: true

    onClicked: ListView.view.currentIndex = index

    contentItem: ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            PLabel {
                text: name
            }
        }

        RowLayout {
            Layout.fillWidth: true
            visible: root.checked

            PLabel {
                text: qsTr("Name")
            }

            PLineEdit {
                Layout.fillWidth: true
                placeholderText: qsTr("The name of this profile")
            }
        }

        PButton {
            Layout.fillWidth: true
            visible: root.checked
            text: qsTr("Properties")
        }
    }
}
