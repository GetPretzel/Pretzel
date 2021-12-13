import QtQuick 2.15
import QtQuick.Controls 2.15


// NOTE: The following is temporary
// TODO: Create a custom popup following Pretzel's UI/UX style guide
Popup {
    id: root
    y: parent.height
    width: parent.width
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    // TODO: Add an option to have an arrow pointing to the parent item
}
