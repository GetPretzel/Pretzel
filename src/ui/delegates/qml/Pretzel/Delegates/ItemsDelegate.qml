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

    // TODO: Think of a better name for this function
    function resetCurrentIndexProfilesDropDown() {
        root.updateProfilesDropDown()
        profileDropDown.currentIndex = root.model.get(index, 0) - 1
    }

    function updateProfilesDropDown() {
        var profileDropDownIndex = profileDropDown.currentIndex;

        var newModel = [];
        for (var i = 0; i < model.profilesModel.count; i++) {
            newModel.push({"text": model.profilesModel.get(i, 0), "value": model.profilesModel.get(i, 2)});
        }
        profileDropDown.model = newModel;
    }

    function updateItemProfileId() {
        root.model.set(index, profileDropDown.currentValue, 0)
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
        var propertiesModel = root.model.profilesModel.getProfileFromId(profileId)[1]

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
                        Layout.fillWidth: true
                        onTextEdited: layoutRoot.itemPropertyChanged(${i} + 1, lineEdit.text)
                    }
                }
            `

            var integerLayout = `
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

                    PSpinBox {
                        id: spinBox
                        Layout.fillWidth: true
                        onValueModified: layoutRoot.itemPropertyChanged(${i} + 1, spinBox.value)
                    }
                }
            `

            if (propertiesModel.get(i, 1) === "String") {
                root.model.get(index, 1).append([propertiesModel.get(i, 3), ""])
                var newObject = Qt.createQmlObject(stringLayout, contentLayout, "StringLayout.qml")
                newObject.itemPropertyChanged.connect(root.updateItemProperty)
            } else if (propertiesModel.get(i, 1) === "Integer") {
                root.model.get(index, 1).append([propertiesModel.get(i, 3), 0])
                var newObject = Qt.createQmlObject(integerLayout, contentLayout, "IntegerLayout.qml")
                newObject.itemPropertyChanged.connect(root.updateItemProperty)
            } else {
                console.log("[WARNING] Type '" + propertiesModel.get(i, 1) + "' is not supported (ItemsDelegate.qml)");
            }

            root.properties.push(newObject)
        }
    }


    function loadItemProperties() {
        var profileId = root.model.get(index, 0)
        var propertiesModel = root.model.profilesModel.getProfileFromId(profileId)[1]

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
                        Layout.fillWidth: true
                        text: "${root.model.get(index, 1).get(i, 1)}"
                        onTextEdited: layoutRoot.itemPropertyChanged(${i} + 1, lineEdit.text)
                    }
                }
            `

            var integerLayout = `
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

                    PSpinBox {
                        id: spinBox
                        Layout.fillWidth: true
                        value: ${root.model.get(index, 1).get(i, 1)}
                        onValueModified: layoutRoot.itemPropertyChanged(${i} + 1, spinBox.value)
                    }
                }
            `

            if (propertiesModel.get(i, 1) === "String") {
                // root.model.get(index, 1).append([propertiesModel.get(i, 3), ""])
                var newObject = Qt.createQmlObject(stringLayout, contentLayout, "StringLayout.qml")
                newObject.itemPropertyChanged.connect(root.updateItemProperty)
            } else if (propertiesModel.get(i, 1) === "Integer") {
                // root.model.get(index, 1).append([propertiesModel.get(i, 3), 0])
                var newObject = Qt.createQmlObject(integerLayout, contentLayout, "IntegerLayout.qml")
                newObject.itemPropertyChanged.connect(root.updateItemProperty)
            } else {
                console.log("[WARNING] Type '" + propertiesModel.get(i, 1) + "' is not supported (ItemsDelegate.qml)");
            }

            root.properties.push(newObject)
        }
    }

    function updateItemProperty(itemPropertyId, value) {
        root.model.get(index, 1).set(itemPropertyId, value)
    }

    function deleteItem() {
        root.model.remove(index)
    }

    contentItem: ColumnLayout {
        id: contentLayout
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            
            // TODO: Display the value of the first property

            Item {
                Layout.fillWidth: true
            }

            PButton {
                id: removeItemButton
                implicitWidth: height
                text: qsTr("-")
                onClicked: root.deleteItem()
            }
        }

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
                    root.updateItemProfileId()
                    root.updateItemProperties()
                }

                Component.onCompleted: root.resetCurrentIndexProfilesDropDown()
            }
        }
    }

    Component.onCompleted: root.loadItemProperties()
}
