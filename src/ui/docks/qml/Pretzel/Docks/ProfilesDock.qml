import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.Delegates 1.0
import Pretzel.Framework 1.0
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
                id: profilesListView
                Layout.fillWidth: true
                Layout.fillHeight: true
                delegate: ProfilesDelegate {}
                model: ProfilesModel {
                    id: profilesModel
                }
            }
        }

        PButton {
            id: addProfilesButton
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            width: 30
            text: qsTr("+")
            onClicked: {
                profilesModel.append(["New profile", 0])
                ActionController.getActionFromName("hello").trigger([])
            }
        }
    }
}
