import QtQuick 2.6
import Qt.labs.controls 1.0
import QtQuick.Layouts 1.3
import com.github.qtrestexample.coupons 1.0

Item {
    id: couponsContainer

    property var couponsModel

    ProgressBar {
        id: progressBar

        property int percent: couponsList.contentY
        property int maxPercent: -200
        property int isLoading: couponsModel.count > 0 && (couponsContainer.couponsModel.loadingStatus == CouponModel.FullReloadProcessing)

        from: 0
        value: percent
        to: maxPercent

        indeterminate: isLoading

        opacity: isLoading ? 1 : position
        visible: opacity > 0

        width: parent.width
        padding: 0
        z: 100
    }

    ListView {
        id: couponsList
        anchors.fill: parent
        spacing: settings.spacing
        model: couponsContainer.couponsModel
        visible: couponsContainer.couponsModel.count > 0
        maximumFlickVelocity: 5000
        interactive: true

        ScrollIndicator.vertical: ScrollIndicator { }

        header: Item {
            id: listHeader
            width: parent.width
            height: settings.spacing
        }

        //        footer: Item {
        //            id: listFooter
        //            width: parent.width
        //            height: utils.mm(10)
        //        }

        delegate: CouponsListDelegate {
            id: delegate
            opacity: 0
            width: couponsList.width - settings.spacing;
            anchors.horizontalCenter: parent.horizontalCenter

            Component.onCompleted: showAnim.start();
            transform: [
                Scale { id: scale; origin.x: width/2; origin.y: height/2; xScale: 0.5; yScale: 0.5 },
                Rotation { id: rotation; origin.x: width/2; origin.y: height/2; axis { x: x; y: 0; z: 0 } angle: 0 }
            ]
            ParallelAnimation {
                id: showAnim
                running: false
                NumberAnimation { target: scale; to: 1; duration: 300; properties: "xScale,yScale" }
                RotationAnimation { target: rotation; from: (couponsList.verticalVelocity >= 0 ? -90 : 90); to: 0; duration: 300; property: "angle" }
                NumberAnimation { target: delegate; to: 1; duration: 300; properties: "opacity" }
            }
        }

        onContentYChanged: {
            if (!draggingVertically) {
                return;
            }
            if (contentY < -200) {
                couponsContainer.couponsModel.requestToReload()
            } else {
                couponsContainer.couponsModel.forceIdle()
            }
        }

        onMovementEnded: {
            if (couponsContainer.couponsModel.loadingStatus == CouponModel.RequestToReload) {
                couponsContainer.couponsModel.reload()
            }
        }
    }

    MouseArea {
        id: moveToTop
        width: parent.width
        height: settings.spacing
        anchors {
            top: couponsList.top
            left: couponsList.left
        }
        onClicked: {
            //couponsList.contentY = -settings.spacing
            couponsList.positionViewAtBeginning()
            couponsModel.forceIdle()
        }
    }

    BusyIndicator {
        id: emptyIndicator
        width: settings.busyIndicatorSize*1.5
        height: settings.busyIndicatorSize*1.5

        running: couponsContainer.couponsModel.count == 0 && (couponsContainer.couponsModel.loadingStatus != CouponModel.Idle || couponsContainer.couponsModel.loadingStatus != CouponModel.Error)
        visible: opacity > 0
        opacity: couponsContainer.couponsModel.count == 0 && (couponsContainer.couponsModel.loadingStatus != CouponModel.Idle || couponsContainer.couponsModel.loadingStatus != CouponModel.Error) ? 1 : 0
        anchors.centerIn: parent
        Behavior on opacity {
            NumberAnimation { duration: 400; }
        }
    }

    Text {
        id: emptyText
        visible: opacity > 0
        opacity: couponsContainer.couponsModel.count == 0 && (couponsContainer.couponsModel.loadingStatus == CouponModel.Idle || couponsContainer.couponsModel.loadingStatus == CouponModel.Error) ? 1 : 0
        anchors.centerIn: parent
        text: couponsContainer.couponsModel.loadingStatus != CouponModel.Error ? qsTr("List is empty") : couponsContainer.couponsModel.loadingErrorString
        font.pointSize: 18
        font.bold: true
        color: "white"
        Behavior on opacity {
            NumberAnimation { duration: 400; }
        }
    }

    //    BusyIndicator {
    //        id: fullReloadIndicator
    //        width: settings.busyIndicatorSize
    //        height: settings.busyIndicatorSize
    //        //Component.onCompleted: console.log(settings.busyIndicatorSize)

    //        Behavior on y {
    //            NumberAnimation { duration: 400; easing.type: Easing.InOutBack }
    //            enabled: couponsContainer.couponsModel.count > 0 && !couponsList.draggingVertically &&
    //                     (couponsContainer.couponsModel.loadingStatus == CouponModel.RequestToReload || couponsContainer.couponsModel.loadingStatus == CouponModel.FullReloadProcessing)
    //        }

    //        y: couponsContainer.couponsModel.count > 0 && !couponsList.draggingVertically &&
    //           (couponsContainer.couponsModel.loadingStatus == CouponModel.RequestToReload || couponsContainer.couponsModel.loadingStatus == CouponModel.FullReloadProcessing)
    //           ? couponsList.y + height*0.5 : -couponsList.contentY - height*1.5

    //        anchors {
    //            horizontalCenter: parent.horizontalCenter
    //        }
    //    }

    BusyIndicator {
        id: loadMoreIndicator
        width: settings.busyIndicatorSize
        height: settings.busyIndicatorSize

        y: couponsContainer.couponsModel.loadingStatus == CouponModel.LoadMoreProcessing ? couponsList.y + couponsList.height - settings.bottomPadding - height : root.height

        Behavior on y {
            NumberAnimation { duration: 400; easing.type: Easing.InOutBack }
        }

        anchors {
            horizontalCenter: parent.horizontalCenter
        }
    }
}
