import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.UiComponents 1.0
import com.kdab.dockwidgets 1.0 as KDDW


KDDW.DockWidget {
    id: root
    uniqueName: "profilesDock"
    title: qsTr("Profiles")

    Item {
        ColumnLayout {
            anchors.fill: parent
            PListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                delegate: Item {}
            }
        }

        PButton {
            id: addProfilesButton
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            width: 30
            text: qsTr("+")
            onClicked: ActionController.getActionFromName("hello").trigger([])
        }
    }
}
