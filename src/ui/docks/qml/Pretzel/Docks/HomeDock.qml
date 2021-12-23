import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Pretzel.UiComponents 1.0
import com.kdab.dockwidgets 1.0 as KDDW

KDDW.DockWidget {
    id: root

    uniqueName: "homeDock"
    title: qsTr("Home")

    ColumnLayout {
        anchors.fill: parent

        PButton {
            text: qsTr("Hello")
        }

    }

}
