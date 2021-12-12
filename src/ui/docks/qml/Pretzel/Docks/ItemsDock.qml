import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.UiComponents 1.0
import com.kdab.dockwidgets 1.0 as KDDW


KDDW.DockWidget {
    id: root
    uniqueName: "itemsDock"
    title: qsTr("Items")
    Rectangle {
        color: "white"
    }
}
