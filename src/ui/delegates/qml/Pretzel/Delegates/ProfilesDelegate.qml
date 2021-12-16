import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.UiComponents 1.0
import Pretzel.Framework 1.0


ItemDelegate {
    id: root
    width: ListView.view.width
    checkable: true

    property var model: ListView.view.model
    property var propertiesModel
    // property alias propertiesModel: propertiesModel

    onClicked: ListView.view.currentIndex = index

    contentItem: ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            PLabel {
                // TODO: Why isn't "name" not working? Should there be another signal called ("dataChanged" or "layoutChanged")?
                text: nameEdit.text
            }
        }

        RowLayout {
            Layout.fillWidth: true
            visible: root.checked

            PLabel {
                text: qsTr("Name")
            }

            PLineEdit {
                id: nameEdit
                Layout.fillWidth: true
                text: root.model.get(root.index, 0)
                placeholderText: qsTr("The name of this profile")
                onTextEdited: root.model.set(root.index, nameEdit.text, 0)
            }
        }

        PButton {
            Layout.fillWidth: true
            visible: root.checked
            text: qsTr("Properties")
            onClicked: propertiesPopup.open()

            PPopup {
                id: propertiesPopup
                contentWidth: profilesListView.implicitWidth
                contentHeight: profilesListView.implicitHeight

                height: 200

                contentItem: Item {
                    ColumnLayout {
                        anchors.fill: parent

                        PListView {
                            id: profilesListView
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            delegate: PropertiesDelegate {}
                            model: propertiesModel
                        }
                    }

                    PButton {
                        id: addPropertyButton
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 8
                        width: 30
                        text: qsTr("+")
                        onClicked: {
                            propertiesModel.append(["New property", "String", "PLineEdit"])
                        }
                    }

                    /*PropertiesModel {
                        id: propertiesModel
                    }*/
                }
            }
        }
    }
}
