import QtQuick 2.15
import QtQuick.Controls 2.15


Item {
    id: root
    property alias text: action.text
    property alias shortcut: action.shortcut

    function trigger() {
        action.trigger()
    }

    Action {
        id: action
    }
}
