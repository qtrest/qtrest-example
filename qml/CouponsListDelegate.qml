import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    height: column.height

    Rectangle {
        id: rectangle1
        anchors.fill: parent
        color: "black"
        opacity: 0.5

        border.color: "black"
        border.width: 1
    }

    Column {
        id: column
        spacing: utils.mm(0);
        width: parent.width - utils.mm(4)
        anchors.horizontalCenter: parent.horizontalCenter

//        Item {
//            width: parent.width - utils.mm(2)
//            height: utils.mm(2)
//        }

        Item {
            id: imageContainer
            width: parent.width
            height: image1.height > 0 ? image1.height : 300

            anchors {
                horizontalCenter: parent.horizontalCenter
            }

            Image {
                id: image1
                y: 10
                width: parent.width
                //height: parent.height
                source: mainImageLink
                fillMode: Image.PreserveAspectCrop
            }
            BusyIndicator {
                running: image1.status === Image.Loading
                visible: image1.status != Image.Ready
                anchors.centerIn: parent
            }
        }

        Item {
            width: parent.width - utils.mm(2)
            height: utils.mm(2)
        }

        Text {
            id: titleText
            text: title
            anchors.horizontalCenter: parent.horizontalCenter
            font.bold: true
            font.pointSize: 12
            color: "white"
            wrapMode: Text.WordWrap
            width: parent.width
            //height:
        }

        Item {
            width: parent.width - utils.mm(2)
            height: utils.mm(2)
        }
    }
}
