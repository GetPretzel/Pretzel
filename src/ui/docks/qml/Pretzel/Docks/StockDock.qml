import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.kdab.dockwidgets 1.0 as KDDW

import Pretzel.Delegates 1.0
import Pretzel.UiComponents 1.0

KDDW.DockWidget {
    id: root

    uniqueName: "stockDock"
    title: qsTr("Stock")

    property var stockModel

    Item {
        ColumnLayout {
            anchors.fill: parent

            PListView {
                id: stockListView
                
                Layout.fillWidth: true
                Layout.fillHeight: true

                delegate: StockDelegate {}
                model: stockModel
            }
        }
    }

}
