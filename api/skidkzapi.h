#ifndef SKIDKZAPI_H
#define SKIDKZAPI_H

#include "apibase.h"
#include <QtQml>

class SkidKZApi : public APIBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SkidKZApi();

    static void declareQML() {
        qmlRegisterType<SkidKZApi>("com.github.qtrestexample.skidkzapi", 1, 0, "SkidKZApi");
    }

    //requests
    QNetworkReply *handleRequest(QString path, QStringList sort, Pagination *pagination,
                           QVariantMap filters = QVariantMap(), QStringList fields = QStringList(), QString id = 0);

    //get list of objects
    QNetworkReply *getCoupons(QStringList sort, Pagination *pagination,
                              QVariantMap filters = QVariantMap(), QStringList fields = QStringList());
    //get full data for specified item
    QNetworkReply *getCouponDetail(QString id);
};

#endif // SKIDKZAPI_H
