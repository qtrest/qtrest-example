import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

ListView {
    id: couponsList

    spacing: 10
    model: coupons

    delegate: CouponsListDelegate {
        width: couponsList.width - utils.mm(3);
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

