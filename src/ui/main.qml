import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

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

        Button {
            anchors.centerIn: parent
            text: qsTr("Print Hello")
            onClicked: ActionController.getActionFromName("hello").trigger()
        }
    }
}