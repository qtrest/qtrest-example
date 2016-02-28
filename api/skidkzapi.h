#ifndef SKIDKZAPI_H
#define SKIDKZAPI_H

#include "apibase.h"
#include "usingleton.h"
#include <QtQml>

class SkidKZApi : public APIBase, public uSingleton<SkidKZApi>
{
    Q_OBJECT
public:
    SkidKZApi();

    //get list of objects
    QNetworkReply *getCoupons(QStringList sort, Pagination *pagination, QVariantMap filters = QVariantMap(), QStringList fields = QStringList());
    //get full data for specified item
    QNetworkReply *getCouponDetail(QString id);
};

#endif // SKIDKZAPI_H
