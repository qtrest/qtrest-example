#include "skidkzapi.h"
#include <QFile>
#include <QTextStream>
#include <QUrlQuery>

SkidKZApi::SkidKZApi() : APIBase(0), uSingleton<SkidKZApi>(*this)
{
    setBaseUrl("http://api.skid.kz");
    setAuthToken("Bearer 8aef452ee3b32466209535b96d456b06");
}

QNetworkReply *SkidKZApi::getCoupons(QStringList sort, Pagination *pagination, QVariantMap filters, QStringList fields)
{
    //URL and GET parameters
    QUrl url = QUrl(baseUrl()+"/v1/coupon");
    QUrlQuery query;

    if (!sort.isEmpty()) {
        query.addQueryItem("sort", sort.join(","));
    }

    switch(pagination->policy()) {
    case Pagination::PageNumber:
        query.addQueryItem("per-page", QString::number(pagination->perPage()));
        query.addQueryItem("page", QString::number(pagination->currentPage()));
        break;
    case Pagination::None:
    case Pagination::LimitOffset:
    case Pagination::Cursor:
    default:
        break;
    }

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

QNetworkReply *SkidKZApi::getCouponDetail(QString id)
{
    if (id.isEmpty()) {
        qDebug() << "ID is empty!";
        return 0;
    }

    QUrl url = QUrl(baseUrl()+"/v1/coupon/"+id);

    QNetworkReply *reply = get(url);

    return reply;
}
