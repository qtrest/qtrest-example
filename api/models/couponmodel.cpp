#include "couponmodel.h"

CouponModel::CouponModel(QObject *parent) : JsonRestListModel(parent)
{

}

QNetworkReply *CouponModel::fetchMoreImpl(const QModelIndex &parent)
{
    return api.getCoupons(sort(), perPage(), currentPage(), filters(), fields());
}

QNetworkReply *CouponModel::fetchDetailImpl(QString id)
{
    return api.getCouponDetail(id);
}

QVariantMap CouponModel::preProcessItem(QVariantMap item)
{
    QDate date = QDateTime::fromString(item.value("createTimestamp").toString(), "yyyy-MM-dd hh:mm:ss").date();
    item.insert("createDate", date.toString("dd.MM.yyyy"));

    return item;
}
