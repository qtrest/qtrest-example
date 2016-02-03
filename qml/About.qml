import QtQuick 2.6

Rectangle {
    anchors.fill: parent

    property string titleText: qsTr("About")

    Text {
        id: about
        text: "About page"
        anchors.centerIn: parent
    }
}
