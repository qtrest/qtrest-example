#ifndef API_H
#define API_H

#include "apibase.h"
#include "usingleton.h"
#include <QtQml>

class SkidKZApi : public APIBase, public uSingleton<SkidKZApi>
{
    Q_OBJECT
public:
    SkidKZApi();

    //api methods
    //get list of objects
    QNetworkReply *getCoupons(QStringList sort, Pagination *pagination, QVariantMap filters = QVariantMap(), QStringList fields = QStringList());
    //get full data for specified item
    QNetworkReply *getCouponDetail(QString id);
};

#endif // API_H
