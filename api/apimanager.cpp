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
    //int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &parseError);
    qDebug() << document.isArray();

//    QFile file("json.txt");
//    file.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream out(&file);
//    out << str;

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << parseError.errorString();
    }

    return document;

    //qDebug() << statusCode;
    //qDebug() << str.length();
}

QNetworkReply *APIManager::getCoupon(QString sort)
{
    //URL and GET parameters
    QUrl url = QUrl(_baseUrl+"/v1/coupon");
    QUrlQuery query;

    if (!sort.isEmpty()) {
        query.addQueryItem("sort", sort);
    }

    url.setQuery(query.query());

    QNetworkRequest request(url);
    setRawHeaders(&request);

    QNetworkReply *reply = manager->get(request);
    connectReplyToErrors(reply);

    connect(reply, SIGNAL(finished()), this, SLOT(slotGetCouponFinished()));

    return reply;
}

void APIManager::slotGetCouponFinished()
{

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!checkReplyIsError(reply) && reply->isFinished()) {
        qDebug() << "finished";
        emit getCouponFinished(getJSONDocument(reply->readAll()));
    }
    reply->deleteLater();
}

