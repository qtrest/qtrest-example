import QtQuick 2.6

Item {
    anchors.fill: parent

    property string titleText: qsTr("Statistics")
    property string type: "statistics"

    Text {
        id: statistics
        text: "Statistics page"
        anchors.centerIn: parent
    }
}
