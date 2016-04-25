#ifndef COUPONMODEL_H
#define COUPONMODEL_H

#include "abstractjsonrestlistmodel.h"
#include "api/skidkzapi.h"

class CouponModel : public AbstractJsonRestListModel
{
    Q_OBJECT

public:
    explicit CouponModel(QObject *parent = 0);

    static void declareQML() {
        AbstractJsonRestListModel::declareQML();
        qmlRegisterType<CouponModel>("com.github.qtrestexample.coupons", 1, 0, "CouponModel");
    }

protected:
    QNetworkReply *fetchMoreImpl(const QModelIndex &parent);
    QNetworkReply *fetchDetailImpl(QString id);
    QVariantMap preProcessItem(QVariantMap item);
};

#endif // COUPONMODEL_H
