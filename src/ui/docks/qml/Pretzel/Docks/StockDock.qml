import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Pretzel.UiComponents 1.0
import com.kdab.dockwidgets 1.0 as KDDW

KDDW.DockWidget {
    id: root

    uniqueName: "stockDock"
    title: qsTr("Stock")

    Item {
        ColumnLayout {
            anchors.fill: parent

            PListView {
                id: stockListView
                
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        PButton {
            id: addStockButton

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            width: 30
            text: qsTr("+")
        }
    }

}
