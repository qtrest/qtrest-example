#ifndef API_H
#define API_H

#include "apibase.h"
#include "usingleton.h"
#include <QtQml>

#define api API::instance()

class API : public APIBase, public uSingleton<API>
{
    Q_OBJECT
public:
    API();

    //api methods
    QNetworkReply *getCoupons(QStringList sort, int perPage = 20, int page = 1, QVariantMap filters = QVariantMap(), QStringList fields = QStringList());
    QNetworkReply *getCouponDetail(QString id);
};

#endif // API_H
