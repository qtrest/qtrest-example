import QtQuick 2.6
import ru.forsk.coupons 1.0

CouponsList {
    anchors.fill: parent

    property string titleText: qsTr("Archive")

    couponsModel: CouponModel {
        id: coupons;
        filters: {'isArchive': '1'}
        sort: "-id"
        perPage: 20
        Component.onCompleted: reload()
    }
}