#ifndef COUPONMODEL_H
#define COUPONMODEL_H

#include "restlistmodel.h"

class CouponModel : public RESTListModel
{
    Q_OBJECT
public:
    explicit CouponModel(QObject *parent = 0);

    static void declareQML() {
        qmlRegisterType<CouponModel>("ru.forsk.coupons", 1, 0, "CouponModel");
    }
protected:
    void fetchMoreHelper(const QModelIndex &parent);
    QVariantMap processItem(QVariantMap item);
};

#endif // COUPONMODEL_H
