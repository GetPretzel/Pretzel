import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Pretzel.Framework 1.0
import Pretzel.Delegates 1.0
import Pretzel.UiComponents 1.0
import com.kdab.dockwidgets 1.0 as KDDW

KDDW.DockWidget {
    id: root

    property var itemsModel
    property var stockModel

    uniqueName: "itemsDock"
    title: qsTr("Items")

    signal profilesModelDataChanged
    signal propertiesModelDataChanged(int profileId)

    Item {
        ColumnLayout {
            anchors.fill: parent

            PListView {
                id: itemsListView

                Layout.fillWidth: true
                Layout.fillHeight: true
                model: itemsModel

                delegate: ItemsDelegate {
                    id: itemsDelegate
                    Component.onCompleted: {
                        root.profilesModelDataChanged.connect(itemsDelegate.updateProfilesDropDown)
                        root.propertiesModelDataChanged.connect(itemsDelegate.updateItemProperties)
                    }
                }

                PLabel {
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: itemsModel.count < 1
                    text: qsTr("Click the '+' button to add a new item")
                }
            }

        }

        PButton {
            id: addItemsButton

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            width: 30
            text: qsTr("+")
            onClicked: {
                itemsModel.append([])
                stockModel.append([itemsModel.count - 1, 0, "", 0])
            }
        }

    }

}
