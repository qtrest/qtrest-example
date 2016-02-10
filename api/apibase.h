#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkReply>

class QNetworkAccessManager;
class QNetworkReply;

class APIBase : public QObject
{
    Q_OBJECT
public:
    explicit APIBase(QObject *parent = 0);
    bool checkReplyIsError(QNetworkReply *reply);

    Q_PROPERTY(QByteArray accept READ accept WRITE setAccept NOTIFY acceptChanged)

    QByteArray accept() const
    {
        return m_accept;
    }

public slots:
    void setAccept(QString accept)
    {
        QByteArray newData;
        newData.append(accept);

        if (m_accept == newData)
            return;

        m_accept = newData;
        emit acceptChanged(newData);
    }

signals:
    void replyError(QNetworkReply *reply, QNetworkReply::NetworkError error, QString errorString);
    void acceptChanged(QByteArray accept);

protected:
    QNetworkReply *get(QUrl url);

    QNetworkAccessManager *manager;
    QString _baseUrl;

    void setRawHeaders(QNetworkRequest *request);
    void connectReplyToErrors(QNetworkReply *reply);

protected slots:
    void replyFinished(QNetworkReply *reply);
    void replyError(QNetworkReply::NetworkError error);
    void slotSslErrors(QList<QSslError> errors);

private:
    QByteArray m_accept;
};

#endif // APIMANAGER_H
