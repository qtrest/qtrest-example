#ifndef COUPONMODEL_H
#define COUPONMODEL_H

#include "jsonrestlistmodel.h"
#include "api/skidkzapi.h"

class CouponModel : public JsonRestListModel
{
    Q_OBJECT
public:
    explicit CouponModel(QObject *parent = 0);

    static void declareQML() {
        JsonRestListModel::declareQML();
        qmlRegisterType<CouponModel>("com.github.qtrestexample.coupons", 1, 0, "CouponModel");
    }
protected:
    QNetworkReply *fetchMoreImpl(const QModelIndex &parent);
    QNetworkReply *fetchDetailImpl(QString id);
    QVariantMap preProcessItem(QVariantMap item);

    APIBase *apiInstance();
};

#endif // COUPONMODEL_H
