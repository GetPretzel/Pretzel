import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.Framework 1.0
import Pretzel.UiComponents 1.0

import com.kdab.dockwidgets 1.0 as KDDW

ItemDelegate {
    id: root

    property var model: ListView.view.model
    
    width: ListView.view.width
    checkable: true
    onClicked: ListView.view.currentIndex = index

    function updateProfilesModel() {
        var profileDropDownIndex = profileDropDown.currentIndex;

        var newModel = [];
        for (var i = 0; i < itemsModel.profilesModel.count; i++) {
            newModel.push({"text": itemsModel.profilesModel.get(i, 0), "value": itemsModel.profilesModel.get(i, 2)});
        }
        profileDropDown.model = newModel;

        if (profileDropDownIndex < profileDropDown.model.length) {
            profileDropDown.currentIndex = profileDropDownIndex
        }
    }


    function updateProperties() {
        var profileId = profileDropDown.currentValue
        var profile = itemsModel.profilesModel.getProfileFromId(profileId)
        var profileProperties = profile[1]
        for (var i = 0; i < profileProperties.count; i++) {
            console.log(profileProperties.get(i, 0))
        }
    }


    contentItem: ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            visible: root.checked

            PLabel {
                text: qsTr("Profile")
            }

            PDropDown {
                id: profileDropDown

                Layout.fillWidth: true

                textRole: "text"
                valueRole: "value"
                model: []

                Component.onCompleted: root.updateProfilesModel()
            }
        }
    }
}
