#include "apimanager.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QTextStream>
#include <QUrlQuery>

APIManager::APIManager(QObject *parent) : QObject(parent), uSingleton<APIManager>(*this)
{
    manager = new QNetworkAccessManager(this);
    _baseUrl = "http://api.skid.kz";

    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(replyFinished(QNetworkReply *)));
}

void APIManager::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << reply->error() << reply->errorString();
        emit replyError(reply, reply->error(), reply->errorString());
    }
}

void APIManager::replyError(QNetworkReply::NetworkError error)
{
    qDebug() << "Error" << error;
}

void APIManager::slotSslErrors(QList<QSslError> errors)
{
    qDebug() << errors;
}

void APIManager::setRawHeaders(QNetworkRequest *request)
{
    request->setRawHeader("Accept", "application/json");
}

void APIManager::connectReplyToErrors(QNetworkReply *reply)
{
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(replyError(QNetworkReply::NetworkError)));

    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(slotSslErrors(QList<QSslError>)));
}

bool APIManager::checkReplyIsError(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << reply->rawHeaderList();
        qDebug() << reply->bytesAvailable() << reply->errorString();
        return true;
    } else {
        return false;
    }
}

QJsonDocument APIManager::getJSONDocument(QByteArray bytes)
{
    QString str = QString::fromUtf8(bytes.data(), bytes.size());

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << parseError.errorString();
    }

    return document;
}

QNetworkReply *APIManager::get(QUrl url)
{
    QNetworkRequest request(url);
    setRawHeaders(&request);

    QNetworkReply *reply = manager->get(request);
    connectReplyToErrors(reply);
    return reply;
}

QNetworkReply *APIManager::getCoupons(QStringList sort, int perPage, int page, QVariantMap filters, QStringList fields)
{
    //URL and GET parameters
    QUrl url = QUrl(_baseUrl+"/v1/coupon");
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

    connect(reply, SIGNAL(finished()), this, SLOT(slotGetCouponsFinished()));

    return reply;
}

QNetworkReply *APIManager::getCouponDetail(QString id)
{
    if (id.isEmpty()) {
        qDebug() << "ID is empty!";
        return 0;
    }

    QUrl url = QUrl(_baseUrl+"/v1/coupon"+id);

    QNetworkReply *reply = get(url);

    connect(reply, SIGNAL(finished()), this, SLOT(slotGetCouponsFinished()));

    return reply;
}

void APIManager::slotGetCouponsFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!checkReplyIsError(reply) && reply->isFinished()) {
        emit getCouponsFinished(getJSONDocument(reply->readAll()), reply);
    }
}

void APIManager::slotGetCouponDetailFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!checkReplyIsError(reply) && reply->isFinished()) {
        emit getCouponDetailFinished(getJSONDocument(reply->readAll()), reply);
    }
}

