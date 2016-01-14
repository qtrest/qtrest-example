#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkReply>
#include "usingleton.h"
#include <QJsonDocument>

class QNetworkAccessManager;
class QNetworkReply;
#define couponapi APIManager::instance()

class APIManager : public QObject, public uSingleton<APIManager>
{
    Q_OBJECT
public:
    explicit APIManager(QObject *parent = 0);
    QNetworkReply *getCoupon(QString sort);

signals:
    void getCouponFinished(QJsonDocument json);

public slots:

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
    void slotGetCouponFinished();
};

#endif // APIMANAGER_H
