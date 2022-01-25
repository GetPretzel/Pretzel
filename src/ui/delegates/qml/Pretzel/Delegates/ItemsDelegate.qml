import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.Framework 1.0
import Pretzel.UiComponents 1.0

import com.kdab.dockwidgets 1.0 as KDDW

ItemDelegate {
    id: root

    // TODO: Use "model" or "itemsModel"?
    property var model: ListView.view.model
    property var dynamicObjects: []
    property var properties: []
    
    width: ListView.view.width
    checkable: true
    onClicked: ListView.view.currentIndex = index

    function updateProfilesModel() {
        var profileDropDownIndex = profileDropDown.currentIndex;

        var newModel = [];
        for (var i = 0; i < model.profilesModel.count; i++) {
            newModel.push({"text": model.profilesModel.get(i, 0), "value": model.profilesModel.get(i, 2)});
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
        var profile = model.profilesModel.getProfileFromId(profileId)
        var profileProperties = profile[1]
        for (var i = 0; i < profileProperties.count; i++) {
            var stringLayout = `
                import QtQuick 2.15
                import QtQuick.Controls 2.15
                import QtQuick.Layouts 1.15
                import Pretzel.UiComponents 1.0

                RowLayout {
                    id: contentLayout
                    Layout.fillWidth: true
                    visible: root.checked

                    signal propertyChanged(string propVal, int index)

                    PLabel {
                        text: qsTr("${profileProperties.get(i, 0)}")
                    }

                    PLineEdit {
                        id: lineEdit
                        Layout.fillWidth: true
                        onTextEdited: contentLayout.propertyChanged(lineEdit.text, ${i})
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

            if (profileProperties.get(i, 1) == "String") {
                var newObject = Qt.createQmlObject(stringLayout, contentLayout, "StringLayout.qml")
                ActionController.getActionFromName("add-item-property").trigger([root.model.get(root.ListView.view.currentIndex, 2), profileProperties.get(i, 3), text])
                newObject.propertyChanged.connect(root.updateItemProperty)//function(propVal, i=i) {updateItemProperty(propVal, i)})
            } else if (profileProperties.get(i, 1) == "Integer" || profileProperties.get(i, 1) == "Float") {
                var newObject = Qt.createQmlObject(integerLayout, contentLayout, "IntegerLayout.qml")
            } else {
                return
            }

            root.dynamicObjects.push(newObject)
        }
    }


    // function updateItemProperty(value, index) {
    //     var profileId = profileDropDown.currentValue
    //     var profile = model.profilesModel.getProfileFromId(profileId)
    //     var profileProperties = profile[1]
    //     ActionController.getActionFromName("update-item-property").trigger([root.model.get(root.ListView.view.currentIndex, 2), profileProperties.get(index, 3), value])
    // }


    function updateProfilesDropDown() {
        var profileDropDownIndex = profileDropDown.currentIndex;

        var newModel = [];
        for (var i = 0; i < model.profilesModel.count; i++) {
            newModel.push({"text": model.profilesModel.get(i, 0), "value": model.profilesModel.get(i, 2)});
        }
        profileDropDown.model = newModel;
    }


    function updateItemProperties() {
        root.clearItemProperties()
        root.addItemProperties()
    }


    function clearItemProperties() {
        root.model.get(index, 1).clear()

        for (var i = 0; i < root.properties.length; i++) {
            root.properties[i].destroy()
        }

        root.properties = []
    }


    function addItemProperties() {
        var profileId = profileDropDown.currentValue
        var propertiesModel = root.model.profilesModel.get(index, 1)
        for (var i = 0; i < propertiesModel.count; i++) {
            var stringLayout = `
                import QtQuick 2.15
                import QtQuick.Layouts 1.15

                import Pretzel.UiComponents 1.0

                RowLayout {
                    id: layoutRoot
                    Layout.fillWidth: true
                    visible: root.checked

                    signal itemPropertyChanged(int itemPropertyId, var value)

                    PLabel {
                        text: qsTr("${propertiesModel.get(i, 0)}")
                    }

                    PLineEdit {
                        id: lineEdit
                        onTextEdited: layoutRoot.itemPropertyChanged(${i} + 1, lineEdit.text)
                    }
                }
            `

            if (propertiesModel.get(i, 1) === "String") {
                root.model.get(index, 1).append([propertiesModel.get(i, 3), ""])
                var newObject = Qt.createQmlObject(stringLayout, contentLayout, "StringLayout.qml")
                newObject.itemPropertyChanged.connect(root.updateItemProperty)
            }

            root.properties.push(newObject)
        }
    }


    function updateItemProperty(itemPropertyId, value) {
        root.model.get(index, 1).set(itemPropertyId, value)
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

                onActivated: root.updateItemProperties()

                Component.onCompleted: {
                    root.updateProfilesDropDown()
                    // root.updateProfilesModel()
                    // currentIndex = root.model.get(index, 0) - 1
                }
            }
        }
    }
}
