import QtQuick 2.6

Item {
    anchors.fill: parent

    property string titleText: qsTr("Detail")
    property string type: "couponDetail"

    property var detailsModel

    ListView {
        id: couponsList
        anchors.fill: parent
        spacing: settings.spacing
        model: detailsModel
        maximumFlickVelocity: 5000
        interactive: false

        header: Item {
            id: listHeader
            width: parent.width
            height: settings.spacing
        }

        delegate: CouponsListDelegate {
            id: delegate
            width: couponsList.width - settings.spacing;
            anchors.horizontalCenter: parent.horizontalCenter

            //Component.onCompleted: { console.log(imagesLinks) }
        }
        //Component.onCompleted: { console.log("details count", detailsModel.rowCount()) }
    }
}
