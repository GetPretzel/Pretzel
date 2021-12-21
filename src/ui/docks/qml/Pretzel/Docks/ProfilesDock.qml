import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.Delegates 1.0
import Pretzel.Framework 1.0
import Pretzel.UiComponents 1.0
import com.kdab.dockwidgets 1.0 as KDDW

import SortFilterProxyModel 0.2


KDDW.DockWidget {
    id: root
    uniqueName: "profilesDock"
    title: qsTr("Profiles")

    Item {
        ColumnLayout {
            anchors.fill: parent

            /*PLineEdit {
                id: filterProfilesLineEdit
                Layout.fillWidth: true
                placeholderText: qsTr("Search for a profile...")
            }*/

            PListView {
                id: profilesListView
                Layout.fillWidth: true
                Layout.fillHeight: true
                delegate: ProfilesDelegate {
                    model: profilesModel
                    // WARNING: This code may cause some trouble down the track
                    propertiesModel: profilesModel.getEditable(index, 1)
                }
                // TODO: Does the proxy model edit the items in profiles model?
                // model: profilesProxyModel
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

        SortFilterProxyModel {
            id: profilesProxyModel
            sourceModel: profilesModel
            filters: RegExpFilter {
                roleName: "name"
                pattern: filterProfilesLineEdit.text
                caseSensitivity: Qt.CaseInsensitive
            }
            sorters: StringSorter {
                roleName: "name"
            }
        }
    }
}
