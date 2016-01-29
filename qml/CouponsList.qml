import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import ru.forsk.coupons 1.0

Item {
    ListView {
        id: couponsList
        anchors.fill: parent
        spacing: utils.mm(2)
        model: coupons
        visible: coupons.count > 0
        maximumFlickVelocity: 5000
        property bool fullReloadFlag: false

        //Component.onCompleted: console.log('velocity', maximumFlickVelocity);

        //onVerticalVelocityChanged: console.log('velocity', verticalVelocity);

        onAtYEndChanged: {
            if ( atYEnd && coupons.count > 0 ) { coupons.more() }
        }

        header: Item {
            id: listHeader
            width: parent.width
            height: utils.mm(2)
        }

        footer: Item {
            id: listFooter
            width: parent.width
            height: utils.mm(10)
        }

        delegate: CouponsListDelegate {
            id: delegate
            opacity: 0
            width: couponsList.width - utils.mm(3);
            anchors.horizontalCenter: parent.horizontalCenter

            Component.onCompleted: showAnim.start();
            transform: [
                Scale { id: scale; origin.x: width/2; origin.y: height/2; xScale: 0.5; yScale: 0.5 },
                Rotation { id: rotation; origin.x: width/2; origin.y: height/2; axis { x: x; y: 0; z: 0 } angle: 0 }
            ]
//            SequentialAnimation {

//                PauseAnimation {
//                    duration: 50
//                }
                ParallelAnimation {
                    id: showAnim
                    running: false
                    NumberAnimation { target: scale; to: 1; duration: 300; properties: "xScale,yScale" }
                    RotationAnimation { target: rotation; from: (couponsList.verticalVelocity >= 0 ? -90 : 90); to: 0; duration: 300; property: "angle" }
                    NumberAnimation { target: delegate; to: 1; duration: 300; properties: "opacity" }
                }
//            }
        }

        onContentYChanged: {
            //console.debug(contentY)
            if (contentY < -200) {
                fullReloadFlag = true
            }
        }

        onMovementEnded: {
            if (fullReloadFlag) {
                coupons.update()
                fullReloadFlag = false
            }
        }
    }

    BusyIndicator {
        id: emptyIndicator
        running: coupons.count == 0 && coupons.loadingStatus != CouponModel.Idle
        visible: opacity > 0
        opacity: coupons.count == 0 && coupons.loadingStatus != CouponModel.Idle ? 1 : 0
        anchors.centerIn: parent
        Behavior on opacity {
            NumberAnimation { duration: 400; }
        }
    }

    Text {
        id: emptyText
        visible: opacity > 0
        opacity: coupons.count == 0 && coupons.loadingStatus == CouponModel.Idle ? 1 : 0
        anchors.centerIn: parent
        text: qsTr("List is empty")
        font.pointSize: 16
        font.bold: true
        color: "white"
        Behavior on opacity {
            NumberAnimation { duration: 400; }
        }
    }

    BusyIndicator {
        id: fullReloadIndicator

        property int loadingStatus: coupons.loadingStatus

        //onLoadingStatusChanged: console.log("onLoadingStatusChanged", loadingStatus, CouponModel.FullReloadProcessing)

        y: coupons.count > 0 && loadingStatus == CouponModel.FullReloadProcessing ? couponsList.y + height*2 : -height

        Behavior on y {
            NumberAnimation { duration: 400; easing.type: Easing.InOutBack }
        }

        anchors {
            horizontalCenter: parent.horizontalCenter
        }
    }

    BusyIndicator {
        id: loadMoreIndicator

        property int loadingStatus: coupons.loadingStatus

        //onLoadingStatusChanged: console.log("onLoadingStatusChanged", loadingStatus, CouponModel.LoadMoreProcessing)

        y: loadingStatus == CouponModel.LoadMoreProcessing ? couponsList.y + couponsList.height - utils.mm(10) - height*2 : root.height

        Behavior on y {
            NumberAnimation { duration: 400; easing.type: Easing.InOutBack }
        }

        anchors {
            horizontalCenter: parent.horizontalCenter
        }
    }
}
