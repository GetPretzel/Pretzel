import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.UiComponents 1.0
import com.kdab.dockwidgets 1.0 as KDDW


ApplicationWindow {
    id: root
    title: qsTr("Pretzel")
    width: 640
    height: 480
    visible: true

    KDDW.MainWindowLayout {
        anchors.fill: parent
        uniqueName: "pretzelWindowLayout"

        KDDW.DockWidget {
            id: homeDock
            uniqueName: "navigationToolBar"
            title: qsTr("Home")
            ColumnLayout {
                anchors.fill: parent
                PButton {
                    text: qsTr("Hello")
                }
            }
        }

        KDDW.DockWidget {
            id: profilesDock
            uniqueName: "profilesDock"
            title: qsTr("Profiles")
            Rectangle {
                color: "white"
            }
        }

        KDDW.DockWidget {
            id: itemsDock
            uniqueName: "itemsDock"
            title: qsTr("Items")
            Rectangle {
                color: "white"
            }
        }

        KDDW.DockWidget {
            id: stockDock
            uniqueName: "stockDock"
            title: qsTr("Stock")
            Rectangle {
                color: "white"
            }
        }

        Component.onCompleted: {
            // TODO: Add these dock widgets on top of each other
            addDockWidget(homeDock, KDDW.KDDockWidgets.Location_OnLeft)
            // addDockWidget(profilesDock, KDDW.KDDockWidgets.Location_OnLeft)
            // addDockWidget(itemsDock, KDDW.KDDockWidgets.Location_OnLeft)
            // addDockWidget(stockDock, KDDW.KDDockWidgets.Location_OnLeft)
        }
    }
}