import QtQuick 2.6

Rectangle {
    anchors.fill: parent

    property string titleText: qsTr("About")

    Image {
        id: background
        source: "qrc:/images/bgvar1.png"
        fillMode: Image.Tile
        anchors.fill: parent
    }

    Text {
        id: about
        text: "About page"
        anchors.centerIn: parent
    }
}
