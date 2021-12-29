import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Pretzel.Docks 1.0
import Pretzel.Framework 1.0
import Pretzel.UiComponents 1.0
import com.kdab.dockwidgets 1.0 as KDDW

ApplicationWindow {
    id: root

    title: qsTr("Pretzel")
    width: 640
    height: 480
    visible: true

    KDDW.MainWindowLayout {
        // addDockWidget(stockDock, KDDW.KDDockWidgets.Location_OnLeft)

        anchors.fill: parent
        uniqueName: "pretzelWindowLayout"
        Component.onCompleted: {
            // TODO: Add these dock widgets on top of each other
            // addDockWidget(homeDock, KDDW.KDDockWidgets.Location_OnLeft)
            addDockWidget(profilesDock, KDDW.KDDockWidgets.Location_OnLeft);
            addDockWidget(itemsDock, KDDW.KDDockWidgets.Location_OnRight);
        }

        HomeDock {
            id: homeDock
        }

        ProfilesDock {
            id: profilesDock

            profilesModel: profilesModel
            onProfilesModelDataChanged: {
                itemsDock.profilesModelDataChanged()
            }
        }

        ItemsDock {
            id: itemsDock

            itemsModel: itemsModel
        }

        StockDock {
            id: stockDock
        }

    }

    ProfilesModel {
        id: profilesModel
    }

    ItemsModel {
        id: itemsModel

        profilesModel: profilesModel
    }

}
