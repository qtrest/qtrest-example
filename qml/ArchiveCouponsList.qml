import QtQuick 2.0
import ru.forsk.coupons 1.0

CouponsList {
    anchors.fill: parent

    couponsModel: CouponModel {
        id: coupons;
        filters: {'isArchive': '1'}
        sort: "-id"
        perPage: 20
        Component.onCompleted: reload()
    }
}
