import QtQuick 2.6

Item {
    id: details
    anchors.fill: parent

    property string titleText: qsTr("Detail")
    property string type: "couponDetail"

    property var detailsModel

    Loader {
        id: pageLoader
    }

    MouseArea {
        anchors.fill: parent
        onClicked: pageLoader.sourceComponent = detailComponent
    }

    Component {
        id: detailComponent

        ListView {
            id: couponsList
            width:details.width
            height: details.height
            spacing: settings.spacing
            model: detailsModel
            maximumFlickVelocity: 5000
            interactive: false
            Component.onCompleted: console.log("loaded")

            header: Item {
                id: listHeader
                width: parent.width
                height: settings.spacing
            }

            delegate: CouponsDetailDelegate {
                id: delegate
                width: couponsList.width;
                anchors.horizontalCenter: parent.horizontalCenter

                //Component.onCompleted: { console.log(imagesLinks) }
            }
            //Component.onCompleted: { console.log("details count", detailsModel.rowCount()) }
        }
    }
}
