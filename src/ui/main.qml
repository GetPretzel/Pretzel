import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import Pretzel.Docks 1.0
import Pretzel.Framework 1.0
import Pretzel.UiComponents 1.0
import com.kdab.dockwidgets 1.0 as KDDW

Window {
    id: root

    title: qsTr("Pretzel")
    width: 640
    height: 480
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint
    color: "transparent"

    function focusWindow() {
        root.show()
        root.raise()
        root.requestActivate()
    }

    // TODO: Make window resizable
    Item {
        anchors.fill: parent
        Rectangle {
            id: windowBackground
            anchors.fill: parent
            color: "#313844"
            radius: root.visibility === Window.Maximized ? 0 : 4
        }

        Item {
            id: titleBar
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            height: 40

            Rectangle {
                anchors.fill: parent
                color: "#F2F2F2"
                radius: windowBackground.radius

                // Make the bottom of the title bar look like a straight line
                Rectangle {
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    color: parent.color
                    width: parent.radius
                    height: parent.radius
                }

                Rectangle {
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    color: parent.color
                    width: parent.radius
                    height: parent.radius
                }
            }

            TapHandler {
                onTapped: {
                    if (tapCount === 2) {
                        if (root.visibility === Window.Windowed) {
                            root.showMaximized()
                        } else if (root.visibility === Window.Maximized) {
                            root.showNormal()
                        }
                    }
                }

                gesturePolicy: TapHandler.DragThreshold
            }

            DragHandler {
                grabPermissions: TapHandler.CanTakeOverFromAnything
                onActiveChanged: {
                    if (active) {
                        root.startSystemMove();
                    }
                }
            }

            PLabel {
                anchors.centerIn: parent
                text: qsTr("Pretzel")
            }

            RowLayout {
                anchors.right: parent.right
                anchors.rightMargin: 24
                height: parent.height
                spacing: 8

                PButton {
                    id: toggleMaximizedButton
                    implicitWidth: 18
                    implicitHeight: 18
                    text: {
                        // NOTE: Once icons are used, will only need one icon here
                        if (root.visibility === Window.Windowed) {
                            return qsTr("[]")
                        } else if (root.visibility === Window.Maximized) {
                            return qsTr("_")
                        }
                    }
                    onClicked: {
                        if (root.visibility === Window.Windowed) {
                            root.showMaximized()
                        } else if (root.visibility === Window.Maximized) {
                            root.showNormal()
                        }
                    }
                }

                PButton {
                    id: quitButton
                    implicitWidth: 18
                    implicitHeight: 18
                    text: qsTr("X")
                    onClicked: {
                        DatabaseHost.quit()
                        Qt.quit()
                    }
                }
            }

        }

        KDDW.MainWindowLayout {
            anchors.fill: parent
            anchors.topMargin: titleBar.height
            uniqueName: "pretzelWindowLayout"
            Component.onCompleted: {
                // TODO: Add these dock widgets on top of each other
                addDockWidget(stockDock, KDDW.KDDockWidgets.Location_OnLeft)
                addDockWidget(itemsDock, KDDW.KDDockWidgets.Location_OnLeft);
                addDockWidget(profilesDock, KDDW.KDDockWidgets.Location_OnLeft);
                // addDockWidget(homeDock, KDDW.KDDockWidgets.Location_OnLeft)
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

                Component.onCompleted: {
                    profilesDock.propertiesModelDataChanged.connect(itemsDock.propertiesModelDataChanged)
                }
            }

            ItemsDock {
                id: itemsDock
                itemsModel: itemsModel
                stockModel: stockModel
            }

            StockDock {
                id: stockDock
                stockModel: stockModel
            }
        }
    }

    ProfilesModel {
        id: profilesModel
    }

    ItemsModel {
        id: itemsModel

        profilesModel: profilesModel
        stockModel: stockModel
    }

    StockModel {
        id: stockModel
        itemsModel: itemsModel
    }
}
