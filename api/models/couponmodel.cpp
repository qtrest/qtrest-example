#include "couponmodel.h"

CouponModel::CouponModel(QObject *parent) : AbstractJsonRestListModel(parent)
{

}

QNetworkReply *CouponModel::fetchMoreImpl(const QModelIndex &parent)
{
    Q_UNUSED(parent)

    return static_cast<SkidKZApi *>(apiInstance())->getCoupons(sort(), pagination(), filters(), fields());
}

QNetworkReply *CouponModel::fetchDetailImpl(QString id)
{
    return static_cast<SkidKZApi *>(apiInstance())->getCouponDetail(id);
}

QVariantMap CouponModel::preProcessItem(QVariantMap item)
{
    QDate date = QDateTime::fromString(item.value("createTimestamp").toString(), "yyyy-MM-dd hh:mm:ss").date();
    item.insert("createDate", date.toString("dd.MM.yyyy"));

    QString originalCouponPrice = item.value("originalCouponPrice").toString().trimmed();
    if (originalCouponPrice.isEmpty()) { originalCouponPrice = "?"; }
    QString discountPercent = item.value("discountPercent").toString().trimmed().remove("—").remove("-").remove("%");
    if (discountPercent.isEmpty()) { discountPercent = "?"; }
    QString originalPrice = item.value("originalPrice").toString().trimmed();
    if (originalPrice.isEmpty()) { originalPrice = "?"; }
    QString discountPrice = item.value("discountPrice").toString().remove("тг.").trimmed();
    if (discountPrice.isEmpty()) { discountPrice = "?"; }

    QString discountType = item.value("discountType").toString();
    QString discountString = tr("Undefined Type");
    if (discountType == "freeCoupon" || discountType == "coupon") {
        discountString = tr("Coupon: %1. Discount: %2%").arg(originalCouponPrice).arg(discountPercent);
    } else if (discountType == "full") {
        discountString = tr("Cost: %1. Certificate: %2. Discount: %3%").arg(originalPrice).arg(discountPrice).arg(discountPercent);
    }

    item.insert("discountString", discountString);

    return item;
}

