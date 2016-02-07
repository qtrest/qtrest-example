#ifndef COUPONMODEL_H
#define COUPONMODEL_H

#include "jsonrestlistmodel.h"

class CouponModel : public JsonRestListModel
{
    Q_OBJECT
public:
    explicit CouponModel(QObject *parent = 0);

    static void declareQML() {
        qmlRegisterType<CouponModel>("ru.forsk.coupons", 1, 0, "CouponModel");
    }
protected:
    void fetchMoreImpl(const QModelIndex &parent);
    QVariantMap preProcessItem(QVariantMap item);
};

#endif // COUPONMODEL_H
