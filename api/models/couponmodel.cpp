#include "couponmodel.h"

CouponModel::CouponModel(QObject *parent) : JsonRestListModel(parent)
{
    connect(&apimanager,SIGNAL(getCouponsFinished(QJsonDocument, QNetworkReply *)), this, SLOT(fetchMoreFinished(QJsonDocument, QNetworkReply *)));
}

void CouponModel::fetchMoreImpl(const QModelIndex &parent)
{
    currentReply = apimanager.getCoupons(sort(), perPage(), currentPage(), filters(), fields());
}

QVariantMap CouponModel::preProcessItem(QVariantMap item)
{
    QDate date = QDateTime::fromString(item.value("createTimestamp").toString(), "yyyy-MM-dd hh:mm:ss").date();
    item.insert("createDate", date.toString("dd.MM.yyyy"));

    return item;
}
