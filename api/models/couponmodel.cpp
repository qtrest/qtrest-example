#include "couponmodel.h"

CouponModel::CouponModel(QObject *parent) : RESTListModel(parent)
{

}

void CouponModel::fetchMoreHelper(const QModelIndex &parent)
{
    currentReply = couponapi.getCoupon(sort(), perPage(), currentPage(), filters());
}

QVariantMap CouponModel::processItem(QVariantMap item)
{
    QDate date = QDateTime::fromString(item.value("createTimestamp").toString(), "yyyy-MM-dd hh:mm:ss").date();
    item.insert("createDate", date.toString("dd.MM.yyyy"));

    return item;
}
