#include "api.h"
#include <QFile>
#include <QTextStream>
#include <QUrlQuery>

API::API() : APIBase(0), uSingleton<API>(*this)
{
    setBaseUrl("http://api.skid.kz");
    setAuthToken("Bearer 8aef452ee3b32466209535b96d456b06");
}

QNetworkReply *API::getCoupons(QStringList sort, int perPage, int page, QVariantMap filters, QStringList fields)
{
    //URL and GET parameters
    QUrl url = QUrl(baseUrl()+"/v1/coupon");
    QUrlQuery query;

    if (!sort.isEmpty()) {
        query.addQueryItem("sort", sort.join(","));
    }

    query.addQueryItem("per-page", QString::number(perPage));
    query.addQueryItem("page", QString::number(page));

    if (!filters.isEmpty()) {
        QMapIterator<QString, QVariant> i(filters);
        while (i.hasNext()) {
            i.next();
            query.addQueryItem(i.key(), i.value().toString());
        }
    }

    if (!fields.isEmpty()) {
        query.addQueryItem("fields", fields.join(","));
    }

    url.setQuery(query.query());

    QNetworkReply *reply = get(url);

    return reply;
}

QNetworkReply *API::getCouponDetail(QString id)
{
    if (id.isEmpty()) {
        qDebug() << "ID is empty!";
        return 0;
    }

    QUrl url = QUrl(baseUrl()+"/v1/coupon/"+id);

    QNetworkReply *reply = get(url);

    return reply;
}
