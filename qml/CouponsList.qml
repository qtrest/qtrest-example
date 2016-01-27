import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    ListView {
        id: couponsList
        anchors.fill: parent
        spacing: utils.mm(2)
        model: coupons
        visible: coupons.count > 0
        maximumFlickVelocity: 5000

        Component.onCompleted: console.log('velocity', maximumFlickVelocity);

        header: Item {
            width: parent.width
            height: utils.mm(2)
        }

        footer: Item {
            width: parent.width
            height: utils.mm(10)
        }

        delegate: CouponsListDelegate {
            width: couponsList.width - utils.mm(3);
            anchors.horizontalCenter: parent.horizontalCenter

            Component.onCompleted: showAnim.start();
            transform: Scale { id: rt; origin.x: width/2; origin.y: height/2; xScale: 0.5; yScale: 0.5 }
            SequentialAnimation {
                id: showAnim
                running: false
                NumberAnimation { target: rt; to: 1; duration: 500; properties: "xScale,yScale" }
            }
        }
    }

    BusyIndicator {
        running: coupons.count == 0
        visible: coupons.count == 0
        anchors.centerIn: parent
    }
}

