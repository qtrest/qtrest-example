import QtQuick 2.6

Item {
    anchors.fill: parent

    property string titleText: qsTr("Detail")

    Text {
        id: statistics
        text: "Detail page"
        anchors.centerIn: parent
    }
}
