import QtQuick 2.6
import com.github.qtrest.pagination 1.0
import com.github.qtrestexample.coupons 1.0

CouponsList {
    anchors.fill: parent

    property string titleText: qsTr("Archive")

    function filter(filters)
    {
        filters.isArchive = 0;
        coupons.filters = filters;
        coupons.reload();
    }

    couponsModel: CouponModel {
        id: coupons;
        api: skidKZApi

        filters: {'isArchive': '1'}
        idField: 'id'
        fields: ['id','title','sourceServiceId','imagesLinks','mainImageLink','pageLink','cityId',
                 'boughtCount','shortDescription','createTimestamp', 'serviceName']
        sort: ['-id']

        pagination {
            policy: Pagination.PageNumber
            perPage: 20
            currentPageHeader: "X-Pagination-Current-Page"
            totalCountHeader: "X-Pagination-Total-Count"
            pageCountHeader: "X-Pagination-Page-Count"
        }

        Component.onCompleted: reload()
    }
}
