import QtQuick 2.6
import ru.forsk.coupons 1.0

CouponsList {
    anchors.fill: parent

    property string titleText: qsTr("Actual")
    property string type: "archive"

    couponsModel: CouponModel {
        id: coupons;
        filters: {'isArchive': '0'}
        idField: 'id'
        fields: ['id','title','sourceServiceId','imagesLinks','mainImageLink','pageLink','cityId','boughtCount','shortDescription',
            'createTimestamp', 'serviceName', 'discountType', 'originalCouponPrice', 'originalPrice', 'discountPercent', 'discountPrice']
        sort: ['-id']
        perPage: 20
        Component.onCompleted: reload()
    }
}
