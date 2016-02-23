import QtQuick 2.6
import Qt.labs.controls 1.0
import ru.forsk.coupons 1.0

Item {
    id: details
    anchors.fill: parent

    property string titleText: qsTr("Detail")

    property var detailsModel
    property var couponsModel

    Loader {
        id: pageLoader
    }

    MouseArea {
        anchors.fill: parent
        onClicked: pageLoader.sourceComponent = detailComponent
    }

    BusyIndicator {
        id: loadingIndicator
        width: settings.busyIndicatorSize*1.5
        height: settings.busyIndicatorSize*1.5

        running: couponsModel.loadingStatus == CouponModel.LoadDetailsProcessing
        visible: opacity > 0
        opacity: couponsModel.loadingStatus == CouponModel.LoadDetailsProcessing ? 1 : 0
        anchors.centerIn: parent
        Behavior on opacity {
            NumberAnimation { duration: 400; }
        }
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
