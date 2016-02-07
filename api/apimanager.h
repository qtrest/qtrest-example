#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkReply>
#include "usingleton.h"
#include <QJsonDocument>

class QNetworkAccessManager;
class QNetworkReply;
#define apimanager APIManager::instance()

class APIManager : public QObject, public uSingleton<APIManager>
{
    Q_OBJECT
public:
    explicit APIManager(QObject *parent = 0);

    //api methods
    QNetworkReply *getCoupons(QStringList sort, int perPage = 20, int page = 1, QVariantMap filters = QVariantMap(), QStringList fields = QStringList());
    QNetworkReply *getCouponDetail(QString id);

signals:
    //api results signals
    void getCouponsFinished(QJsonDocument json, QNetworkReply *reply);
    void getCouponDetailFinished(QJsonDocument json, QNetworkReply *reply);

    void replyError(QNetworkReply *reply, QNetworkReply::NetworkError error, QString errorString);

public slots:

protected:
    QNetworkReply *get(QUrl url);

private:
    QNetworkAccessManager *manager;
    QString _baseUrl;

    void setRawHeaders(QNetworkRequest *request);
    void connectReplyToErrors(QNetworkReply *reply);
    bool checkReplyIsError(QNetworkReply *reply);
    QJsonDocument getJSONDocument(QByteArray bytes);

private slots:
    void replyFinished(QNetworkReply *reply);
    void replyError(QNetworkReply::NetworkError error);
    void slotSslErrors(QList<QSslError> errors);
    void slotGetCouponsFinished();
    void slotGetCouponDetailFinished();
};

#endif // APIMANAGER_H
