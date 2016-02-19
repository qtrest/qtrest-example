import QtQuick 2.6
import ru.forsk.coupons 1.0
import ru.forsk.pagination 1.0

CouponsList {
    anchors.fill: parent

    property string titleText: qsTr("Actual")
    property string type: "actual"

    couponsModel: CouponModel {
        id: coupons;
        filters: {'isArchive': '0'}
        idField: 'id'
        fields: ['id','title','sourceServiceId','imagesLinks','mainImageLink','pageLink','cityId','boughtCount','shortDescription',
            'createTimestamp', 'serviceName', 'discountType', 'originalCouponPrice', 'originalPrice', 'discountPercent', 'discountPrice']
        sort: ['-id']

        pagination {
            policy: Pagination.PageNumber
            perPage: 20
        }

        Component.onCompleted: { console.log(pagination.perPage); reload(); }
    }
}
