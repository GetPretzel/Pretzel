import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.Framework 1.0
import Pretzel.UiComponents 1.0

import com.kdab.dockwidgets 1.0 as KDDW

ItemDelegate {
    id: root

    property var model: ListView.view.model
    property var dynamicObjects: []
    
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
        // TODO: There is a bug involving using where profile doesn't exist (when no items exist). The following does not fix the bug
        /*if (root.parent === "undefined") {
            console.log("No parent")
        }*/

        // TODO: Is there a way to fix the visual glitch of replacing/updating the properties shown in the item?
        for (var i = 0; i < root.dynamicObjects.length; i++) {
            root.dynamicObjects[i].destroy()
        }
        root.dynamicObjects = []

        var profileId = profileDropDown.currentValue
        var profile = itemsModel.profilesModel.getProfileFromId(profileId)
        var profileProperties = profile[1]
        for (var i = 0; i < profileProperties.count; i++) {
            var stringLayout = `
                import QtQuick 2.15
                import QtQuick.Controls 2.15
                import QtQuick.Layouts 1.15
                import Pretzel.UiComponents 1.0

                RowLayout {
                    Layout.fillWidth: true
                    visible: root.checked

                    PLabel {
                        text: qsTr("${profileProperties.get(i, 0)}")
                    }

                    PLineEdit {
                        Layout.fillWidth: true
                    }
                }
            `

            var integerLayout = `
                import QtQuick 2.15
                import QtQuick.Controls 2.15
                import QtQuick.Layouts 1.15
                import Pretzel.UiComponents 1.0

                RowLayout {
                    Layout.fillWidth: true
                    visible: root.checked

                    PLabel {
                        text: qsTr("${profileProperties.get(i, 0)}")
                    }

                    PSpinBox {
                        Layout.fillWidth: true
                        value: 0
                    }
                }
            `

            // TODO: Add properties where needed to the layout code for modifying data in the database
            if (profileProperties.get(i, 1) == "String") {
                var newObject = Qt.createQmlObject(stringLayout, contentLayout, "StringLayout.qml")
            } else if (profileProperties.get(i, 1) == "Integer" || profileProperties.get(i, 1) == "Float") {
                var newObject = Qt.createQmlObject(integerLayout, contentLayout, "IntegerLayout.qml")
            } else {
                return
            }

            root.dynamicObjects.push(newObject)
        }
    }


    contentItem: ColumnLayout {
        id: contentLayout
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

                onActivated: {
                    // Go through all items which use the old profile id and clear all data in the database
                    /*for (var i = 0; i < root.model.count; i++) {
                        if (root.model.get(i, 0) == currentValue) {
                            ActionController.getActionFromName("clear-item-properties").trigger([root.model.get(i, 1)])
                        }
                    }*/

                    // Reset the item properties
                    // WARNING: "root.ListView.view.currentIndex" will cause problems when implementing filtering and searching
                    ActionController.getActionFromName("reset-item-properties").trigger([root.model.get(root.ListView.view.currentIndex, 1), root.model.profilesModel.getProfileFromId(root.model.get(root.ListView.view.currentIndex, 0))])

                    // Update the profile id
                    root.model.set(root.ListView.view.currentIndex, profileDropDown.currentValue, 0)
                    // Add the new data
                    root.updateProperties()
                }

                Component.onCompleted: root.updateProfilesModel()
            }
        }
    }
}
