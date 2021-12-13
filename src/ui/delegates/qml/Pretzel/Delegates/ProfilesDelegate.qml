import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Pretzel.UiComponents 1.0


Component {
    id: root
    Item {
        width: ListView.view.width
        height: 40

        ColumnLayout {
            anchors.fill: parent
            PLabel {
                Layout.alignment: Qt.AlignHCenter
                text: index
            }
        }
    }
}
