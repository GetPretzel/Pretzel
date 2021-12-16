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
                delegate: ProfilesDelegate {
                    // WARNING: This code may cause some trouble down the track 
                    propertiesModel: profilesModel.getEditable(index, 1)
                }
                model: profilesModel
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
                // WARNING: This code may cause some trouble down the track 
                var newPropertiesModel = Qt.createQmlObject("import Pretzel.Framework 1.0; PropertiesModel {}", profilesModel, "dynamicPropertiesModel.qml")
                profilesModel.append(["New profile", newPropertiesModel])
                // console.log("get(): " + profilesModel.get(profilesModel.count - 1, 2))
                // ActionController.getActionFromName("hello").trigger([])
            }
        }

        ProfilesModel {
            id: profilesModel
        }
    }
}
